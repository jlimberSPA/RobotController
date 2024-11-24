#include <NewRobotControllerShared.h>
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NewRobotControllerSharedUnitTests
{
	TEST_CLASS(NewRobotControllerSharedUnitTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Logger::WriteMessage("In Test Case1");
			long opsRun = 0;
			Assert::AreEqual(MyClass::ReVal(), opsRun);
		}
	};
}