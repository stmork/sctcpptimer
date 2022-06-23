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
				./SctCppTimer
				"""
			}
		}
	}

	post {
		chuckNorris()
	}
}
