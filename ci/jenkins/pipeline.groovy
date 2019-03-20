#!groovy
import groovy.json.JsonOutput

{ ->

gerritLocalBranch="change"
def buildData = [:]
def currentStage = null

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

def lokiBuild = { name, body ->
	if(!buildData[currentStage].containsKey('builds')) {
		buildData[currentStage]['builds'] = [:]
	}
	if(isUnix()) {
		sh "ccache -z"
	}
	buildData[currentStage]['builds'][name] = [:]
	buildData[currentStage]['builds'][name]['start'] = System.currentTimeMillis()
	body()
	if (!(buildData[currentStage]['builds'][name].containsKey('node')) && (env.NODE_NAME)) {
		buildData[currentStage]['builds'][name]['node'] = env.NODE_NAME
	}
	buildData[currentStage]['builds'][name]['end'] = System.currentTimeMillis()


	if(isUnix()) {
		def tmp = sh script: "ccache -s | grep 'hit rate' | cut -d ' ' -f 4-", returnStdout: true
		buildData[currentStage]['builds'][name]['ccache'] = tmp.trim()
	}
}

node("loki-controller") {
	try {
		lokiStage("checkout") {
			checkout changelog: false, poll: false,
				scm: [$class: 'GitSCM',
					branches: [[name: "${gerritLocalBranch}"]],
					doGenerateSubmoduleConfigurations: false,
					extensions: [
						[$class: 'CleanCheckout'],
						// [$class: 'RelativeTargetDirectory', relativeTargetDir: 'loki'],
						[$class: 'CloneOption', noTags: true, reference: '', shallow: false, honorRefspec: true],
						[$class: 'PruneStaleBranch']],
					submoduleCfg: [],
					userRemoteConfigs: [[
						credentialsId: '0f565f2a-f10f-421d-ac50-3b169adf5f06',
						url: "${GERRIT_SCHEME}://${GERRIT_HOST}:${GERRIT_PORT}/${GERRIT_PROJECT}",
						refspec: "+${GERRIT_REFSPEC}:${gerritLocalBranch}"
					]]]
		}
		lokiStage("sync manifest") {
			sh """\
~/irepo/irepo select -d . third_party/linux_embargo.yml
~/irepo/irepo ignore-folder extended
~/irepo/irepo ignore-folder scripts
~/irepo/irepo ignore-folder .git
~/irepo/irepo ignore-folder ci
~/irepo/irepo ignore-folder icd_loader
~/irepo/irepo ignore-folder tests
~/irepo/irepo ignore-folder images
~/irepo/irepo ignore-folder core
~/irepo/irepo ignore-folder samples

~/irepo/irepo sync --clean --delete-unknown-content
"""
		}

		lokiStage('build') {
			lokiBuild('linux') {
				def image = docker.image("${env.DOCKER_REGISTRY}/neo-build-gcc5:9")
				def workDir = sh script: "(cd .. && pwd)", returnStdout: true
				image.inside("-v /ccache:/ccache -e CCACHE_DIR=/ccache -e CCACHE_TEMPDIR=/tmp/ccache -e CCACHE_BASEDIR=${workDir}") {
					sh """\
mkdir build
cd build
cmake -GNinja .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --clean-first --target package
"""
				}
			}
		}

		lokiStage('publish') {
			archiveArtifacts "build/*.deb"
		}
	} finally {
		dir("tmp") {
			writeFile file: 'build_data.json', text: JsonOutput.prettyPrint(JsonOutput.toJson(buildData))
			archiveArtifacts "build_data.json"
			deleteDir()
		}
	}
}

}
