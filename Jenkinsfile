pipeline
{
	agent any

	stages
	{
		stage('Build')
		{
			steps
			{
				sh """
				qmake -r
				make -j
				"""
			}
		}

		stage('CppCheck')
		{
			steps
			{
				sh 'make cppcheck'
				publishCppcheck pattern: 'cppcheck.xml'
			}
		}

		stage('Test')
		{
			steps
			{
				sh """
				cd SctCppTimer
				./SctCppTimer
				./SctCppUnit --gtest_output="xml:gtest-results.xml"
				"""
				xunit([GoogleTest(pattern: '*/gtest-results.xml', stopProcessingIfError: true)])
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
