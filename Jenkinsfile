pipeline {
	agent any

	stages {
		stage('Build')
		{
			steps
			{
				sh """
				cd SctCppTimer
				qmake -r
				make -j
				"""
			}
		}

		stage('CppCheck)
		{
			steps
			{
				sh """
				cd SctCppTimer
				make cppcheck
				publishCppcheck pattern: 'cppcheck.xml'
				"""
			}
		}
		
		stage('Test')
		{
			steps
			{
				sh """
				cd SctCppTimer
				./SctCppTimer
				"""
			}
		}
	}

	post
	{
		always
		{
			chuckNorris()
		}
	}
}
