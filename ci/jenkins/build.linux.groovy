#!groovy
{ ->
	return lokiNode("loki-controller") {
		lokiBuild('linux') {
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

			withEnv(["IREPO_CACHE_DIR=$HOME/.irepo"]) {
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
ls -la
"""
			}

			def image = docker.image("${env.DOCKER_REGISTRY}/loki-ubuntu18:1")
			def workDir = sh script: "(cd .. && pwd)", returnStdout: true
			def buildId = "${env.BUILD_NUMBER}"
			if(params.containsKey("COMMON_BUILD_ID")) {
				buildId = "${COMMON_BUILD_ID}"
			}
			image.pull()
			image.inside("-v /ccache:/ccache -e CCACHE_DIR=/ccache -e CCACHE_TEMPDIR=/tmp/ccache -e CCACHE_BASEDIR=${workDir}") {
				sh """\
mkdir ubuntu18
cd ubuntu18
cmake -GNinja .. -DCMAKE_BUILD_TYPE=Release -DLOKI_VERSION_BUILD=${buildId}
cmake --build . --config Release --clean-first --target package
"""
			}
			image.inside() {
				sh """\
cd scripts
python3 run.py --html
cd ../latex
make
"""
			}
			archiveArtifacts "ubuntu18/*.deb"
			dir('latex') {
				archiveArtifacts "*.pdf"
			}
		}()
	}
}
