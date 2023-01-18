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
				test -f Makefile && make clean distclean
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
				./SctUnitTimer --gtest_output="xml:gtest-results.xml"
				"""
			}
		}
	}

	post
	{
		always
		{
			chuckNorris()
			step([$class: 'Mailer', recipients: 'linux-dev@morknet.de'])
		}
	}
}
