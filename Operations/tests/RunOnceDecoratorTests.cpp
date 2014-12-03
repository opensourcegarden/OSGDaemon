#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../BaseOperationDecorator.h"
#include "../RunOnceDecorator.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include "../AbstractOperation.h"
#include "../DigitalWriteOperation.h"
#include <json/json.h>
// using namespace Operations;
using namespace Operations;

struct RunOnceDecoratorTestsFixture {
	RunOnceDecorator* decorator; 
	DigitalWriteOperation* operation;
	RunOnceDecoratorTestsFixture() {
		operation = new DigitalWriteOperation();
		decorator =  new RunOnceDecorator();
		HardwareAbstraction::AbstractController* controller = new HardwareAbstraction::BasicArduino();
		decorator->setDecoratedOperation(operation);
		operation->setPin(4);
		operation->setValue(1);
		operation->setController(controller);

		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	};

	~RunOnceDecoratorTestsFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(RunOnceDecoratorTests, RunOnceDecoratorTestsFixture)

BOOST_AUTO_TEST_CASE(checkExecute) {
		
	Json::StyledWriter writer;
	Json::Value ret(Json::objectValue);
	ret = decorator->execute();
	// std::string ret_str(writer.write(ret));
	// std::cout << ret_str << std::endl;
	BOOST_CHECK(ret["runOnce"] == true);

}
BOOST_AUTO_TEST_SUITE_END()

