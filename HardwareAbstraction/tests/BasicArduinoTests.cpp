// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE BasicArduinoTestsFixture


#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../BasicArduino.h"

// class BasicArduino;
struct BasicArduinoTestsFixture {
	HardwareAbstraction::BasicArduino* controller;

	BasicArduinoTestsFixture() {
		controller = new HardwareAbstraction::BasicArduino();
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	};

	~BasicArduinoTestsFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(CompositeOperations, BasicArduinoTestsFixture)

BOOST_AUTO_TEST_CASE(checkCompositeOperationCompile) {
	BOOST_CHECK(controller);
}

BOOST_AUTO_TEST_CASE(addChildrenToCompositeOperation) {
	BOOST_CHECK(controller);
}

BOOST_AUTO_TEST_SUITE_END()

