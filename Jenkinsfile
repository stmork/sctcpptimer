pipeline {
	agent any
	options {
		skipStagesAfterUnstable()
	}
	stages {
		stage ('Build') {
			steps {
				sh """
				cd SctCppTimer
				qmake -r
				make -j
				"""
			}
		}
		stage ('Test') {
			steps {
				sh """
				cd SctCppTimer
				make cppcheck
				./SctCppTimer
				"""
			}
		}
	}
}
