pipeline
{
	agent any
	options
	{
		skipStagesAfterUnstable()
	}
	stages
	{
		stage ('Build')
		{
			steps
			{
				cd SctCppTimer
				sh 'qmake -r'
				sh 'make -j'
			}
		}
		stage ('Test')
		{
			steps
			{
				cd SctCppTimer
				sh 'make cppcheck'
				sh ./SctCppTimer
			}
		}
	}
}
