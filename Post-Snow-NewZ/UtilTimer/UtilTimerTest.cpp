//
//  UtilTimerTest.cpp

//----------------------------------------
//	include
//----------------------------------------
#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/Util/Timer.h>
#include <Poco/Util/TimerTask.h>
#include <Poco/Util/TimerTaskAdapter.h>
#include <Poco/Event.h>
#include <Poco/Timestamp.h>
#include <Poco/Format.h>

#include <string>
#include <iostream>

//----------------------------------------
//	MyTimerTask
//----------------------------------------
class MyTimerTask
{
public:
	MyTimerTask()
	{
	}
	void onTimer2(Poco::Util::TimerTask& task)
	{
		std::cout<<"MyTimerTask::onTimer() called\n";
	}
};

//----------------------------------------
//	TestSchedule
//----------------------------------------
void TestSchedule(Poco::Util::Timer& timer)
{
	MyTimerTask task;
	Poco::Util::TimerTask::Ptr pTask = new Poco::Util::TimerTaskAdapter<MyTimerTask>(task, &MyTimerTask::onTimer2);
	timer.schedule(pTask, 1000, 3000);
}

//----------------------------------------
//	main
//----------------------------------------
int main(int /*argc*/, char** /*argv*/)
{

	Poco::Util::Timer timer;

	TestSchedule(timer);
	Poco::Thread::sleep(100000000);
	return 0;
}
