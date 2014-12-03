#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE AbstractOperationTestsFixture

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../../HardwareAbstraction/AbstractController.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include "../../Operations/AbstractOperation.h"

// using namespace Operations;
using namespace HardwareAbstraction;

struct AbstractOperationTestsFixture {
	Operations::AbstractOperation* operation;
	BasicArduino* controller;
	AbstractOperationTestsFixture() {
		operation = new Operations::AbstractOperation();
		
		controller = new HardwareAbstraction::BasicArduino();
		
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	};

	~AbstractOperationTestsFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}

};



BOOST_FIXTURE_TEST_SUITE(CompositeOperations, AbstractOperationTestsFixture)


BOOST_AUTO_TEST_CASE(checkInit) {
	BOOST_CHECK(operation);
}



BOOST_AUTO_TEST_CASE(checkSetGetController) {
	operation->setController(controller);
	AbstractController* test_pointer = operation->setController(controller);

	BOOST_CHECK(controller == test_pointer);
	BOOST_CHECK(controller == operation->getController());

	operation->setController(NULL);
	BOOST_CHECK(!operation->getController());
}

BOOST_AUTO_TEST_SUITE_END()

