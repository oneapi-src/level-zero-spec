#!groovy
{ ->
  def cmakeFlags = []

  if(env.JOB_BASE_NAME == "ocl-loki-verification") {
  } else if(env.JOB_BASE_NAME == "ocl-loki-publish") {
    cmakeFlags << "-Dlevel_zero_BUILD_TESTS=FALSE"
  }

	return lokiNode('loki-windows') {
		lokiBuild('windows-64') {
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

			echo "irepo cache dir = ${BASE}\\.irepo"
			withEnv(["IREPO_CACHE_DIR=${BASE}\\.irepo"]) {
				bat """\
call c:\\irepo\\irepo select third_party\\windows_embargo.yml

call c:\\irepo\\irepo ignore-folder extended
call c:\\irepo\\irepo ignore-folder scripts
call c:\\irepo\\irepo ignore-folder .git
call c:\\irepo\\irepo ignore-folder ci
call c:\\irepo\\irepo ignore-folder icd_loader
call c:\\irepo\\irepo ignore-folder tests
call c:\\irepo\\irepo ignore-folder images
call c:\\irepo\\irepo ignore-folder core
call c:\\irepo\\irepo ignore-folder samples
call c:\\irepo\\irepo ignore-folder cmake

call c:\\irepo\\irepo sync --clean --delete-unknown-content
"""
			}
			def buildId = "${env.BUILD_NUMBER}"
			if(params.containsKey("COMMON_BUILD_ID")) {
				buildId = "${COMMON_BUILD_ID}"
			}
			bat """
md build
cd build
cmake -G "Visual Studio 15 2017 Win64" .. -DCMAKE_BUILD_TYPE=Release -DLOKI_VERSION_BUILD=${buildId} -DLOKI_CPACK_GENERATOR="ZIP" ${cmakeFlags.join(' ')}
cmake --build . --config Release --clean-first --target ALL_BUILD
"""
			// archiveArtifacts "build/*.zip"
		}()
	}
}
