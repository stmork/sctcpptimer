pipeline {
	agent any

	stages {
		stage('Build') {
			steps {
				sh """
				cd SctCppTimer
				qmake -r
				make -j
				"""
			}
		}
		stage('Test') {
			steps {
				sh """
				cd SctCppTimer
				make cppcheck
				./SctCppUnit --gtest_output="xml:gtest-results.xml"
				./SctCppTimer
				"""
			}
		}
		stage('Reports')
		{
			steps
			{
				publishCppcheck pattern: 'cppcheck.xml'
				xunit([GoogleTest(excludesPattern: '', pattern: 'test-results.xml', stopProcessingIfError: true)])
			}
		}
	}

	post {
		always {
			chuckNorris()
		}
	}
}
