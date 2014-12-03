#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../BaseOperationDecorator.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include "../AbstractOperation.h"
#include "../DigitalWriteOperation.h"
// using namespace Operations;
using namespace Operations;

struct BaseOperationDecoratorTests {
	BaseOperationDecorator* decorator; 
	DigitalWriteOperation* operation;
	BaseOperationDecoratorTests() {
		operation = new DigitalWriteOperation();
		decorator = new BaseOperationDecorator();
		HardwareAbstraction::AbstractController* controller = new HardwareAbstraction::BasicArduino();
		operation->setController(controller);
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	};

	~BaseOperationDecoratorTests() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(BasicOperationDecoratorTests, BaseOperationDecoratorTests)

BOOST_AUTO_TEST_CASE(checkGetAndSetDecoratedOperation) {
	BOOST_CHECK(!decorator->getDecoratedOperation());
	BOOST_CHECK(decorator->setDecoratedOperation(operation));
	BOOST_CHECK(decorator->getDecoratedOperation());
	// boost::shared_ptr<DigitalWriteOperation> operation2 = (boost::shared_ptr<DigitalWriteOperation>) decorator->getDecoratedOperation();
	// BOOST_CHECK(*operation2 == *operation);
	// BOOST_CHECK(decorator->getDecoratedOperation() == (boost::shared_ptr<AbstractOperation>) operation);
}

BOOST_AUTO_TEST_SUITE_END()

