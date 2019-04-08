#!groovy
import groovy.json.JsonOutput

{ ->
def gerritCreds = "0f565f2a-f10f-421d-ac50-3b169adf5f06"
def gerritGfxCreds = "696e4269-73bd-496c-8575-632dd078135c"

def skipBuild = false
def plus2Allowed = (env.JOB_BASE_NAME == "ocl-loki-verification")
def reportBuildStatus = (env.JOB_BASE_NAME == "ocl-loki-verification")

gerritLocalBranch="change"
def buildData = [:]
def currentStage = null
def buildLinux = null

def gerritPostResult = { passed ->
	if(reportBuildStatus) {
		lock('loki-gerrit') {
			node('master') {
				timeout(3) {
					def gerritOpts

					if(passed) {
						// get change data from gerrit
						def resp = httpRequest authentication: "${gerritGfxCreds}", url: "https://${GERRIT_HOST}/a/changes/${gerritReview.id}/revisions/${GERRIT_PATCHSET_REVISION}/review"
						assert resp.content.startsWith(')]}') == true

						def s = resp.content
						def tmpReview = readJSON text: s.substring(s.indexOf('\n')+1)

						def isDraft = tmpReview.revisions["${GERRIT_PATCHSET_REVISION}"].draft

						if(isDraft) {
								gerritOpts = "--label verified=+1 --publish"
						} else {
							if(plus2Allowed) {
								gerritOpts = "--code-review=+2 --label verified=+1"
							} else {
								gerritOpts = "--label verified=+1"
							}
						}
					} else {
						gerritOpts = "--label verified=-1"
					}

					withCredentials([sshUserPrivateKey(credentialsId: "${gerritCreds}", keyFileVariable: 'KEY', usernameVariable: 'K_USER')]) {
						def sshCommand = "ssh -i $KEY -l $K_USER -p ${GERRIT_PORT} ${GERRIT_HOST}"
						def gerritCommentCommand = "\"gerrit review ${GERRIT_CHANGE_NUMBER},${GERRIT_PATCHSET_NUMBER} -m '${env.BUILD_URL}' ${gerritOpts}\""
						//Add Verified and CodeRevied
						sh "${sshCommand} ${gerritCommentCommand}"
					}
				}
			}
		}
	}
}

def lokiStage = { name, body ->
  currentStage = name
	buildData[name] = [:]
	buildData[name]['start'] = System.currentTimeMillis()
	stage(name) {
		body()
	}
	buildData[name]['end'] = System.currentTimeMillis()
	if (!(buildData[name].containsKey('node')) && (env.NODE_NAME)) {
		buildData[name]['node'] = env.NODE_NAME
	}
  currentStage = null
}

lokiNode = { name, body ->
	return {
		echo "entering node ${name}"
		node(name) {
			echo "acquired node ${env.NODE_NAME}"
			body()
		}
	}
}

lokiBuild = { name, body ->
	return {
		try {
			if(!buildData[currentStage].containsKey('builds')) {
				buildData[currentStage]['builds'] = [:]
			}
			if(isUnix()) {
				sh "ccache -z"
			}
			buildData[currentStage]['builds'][name] = [:]
			buildData[currentStage]['builds'][name]['start'] = System.currentTimeMillis()
			body()
			buildData[currentStage]['builds'][name]['passed'] = true
		} finally {
			if (!(buildData[currentStage]['builds'][name].containsKey('node')) && (env.NODE_NAME)) {
				buildData[currentStage]['builds'][name]['node'] = env.NODE_NAME
			}
			buildData[currentStage]['builds'][name]['end'] = System.currentTimeMillis()


			if(isUnix()) {
				def tmp = sh script: "ccache -s | grep 'hit rate' | cut -d ' ' -f 4-", returnStdout: true
				buildData[currentStage]['builds'][name]['ccache'] = tmp.trim()
			}
		}
	}
}

try {
	timeout(time: 60, unit: 'MINUTES') {
		node("loki-common") {
			lokiStage("checkout") {
				checkout changelog: false, poll: false,
					scm: [$class: 'GitSCM',
						branches: [[name: "${GERRIT_PATCHSET_REVISION}"]],
						doGenerateSubmoduleConfigurations: false,
						extensions: [
							[$class: 'CleanCheckout'],
							// [$class: 'RelativeTargetDirectory', relativeTargetDir: 'loki'],
							[$class: 'CloneOption', noTags: true, reference: '', shallow: false, honorRefspec: true],
							[$class: 'PruneStaleBranch']],
						submoduleCfg: [],
						userRemoteConfigs: [[
							credentialsId: '0f565f2a-f10f-421d-ac50-3b169adf5f06',
							url: "${gerritUrl}",
							refspec: "+${GERRIT_REFSPEC}:${gerritLocalBranch}"
						]]]

				if(env.JOB_BASE_NAME == "ocl-loki-verification") {
					def resp = httpRequest authentication: "${gerritGfxCreds}", url: "https://${GERRIT_HOST}/a/changes/${gerritReview.id}/revisions/${GERRIT_PATCHSET_REVISION}/review"
					assert resp.content.startsWith(')]}') == true

					def s = resp.content
					def tmpReview = readJSON text: s.substring(s.indexOf('\n')+1)

					def isDraft = false
					if(tmpReview.revisions["${GERRIT_PATCHSET_REVISION}"].containsKey('draft')) {
						isDraft = tmpReview.revisions["${GERRIT_PATCHSET_REVISION}"].draft
					}
					skipBuild = !isDraft
					echo "verificaiton build.isDraft = ${isDraft}"
					echo "verificaiton build.skipBuild = ${skipBuild}"
				}
				buildLinux = load("ci/jenkins/build.linux.groovy")
				buildWindows = load("ci/jenkins/build.windows.groovy")
			}
			lokiStage("lint") {
				echo "TBD"
			}
		}

		lokiStage('build') {
			if(!skipBuild) {
				lokiBuilds = [failFast:true]
				lokiBuilds['linux'] = buildLinux()
				lokiBuilds['windows-64'] = buildWindows()

				parallel lokiBuilds
			}
		}

		lokiStage('publish') {
			gerritPostResult(true)
		}
	}
} catch(Exception e) {
	gerritPostResult(false)
	throw e
} finally {
	node("loki-common") {
		dir("tmp") {
			writeFile file: 'build_data.json', text: JsonOutput.prettyPrint(JsonOutput.toJson(buildData))
			archiveArtifacts "build_data.json"
			deleteDir()
		}
	}
}

}
