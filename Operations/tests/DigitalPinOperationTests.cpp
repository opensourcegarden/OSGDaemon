// #define BOOST_TEST_MODULE DigitalWriteOperationTests

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../DigitalPinOperation.h"
#include <vector>
#include <string>
#include <iostream>
using namespace Operations;
using namespace HardwareAbstraction;
// class DigitalPinOperation;
// class CompositeOperation;
struct DigitalPinOperationFixture {
	DigitalPinOperation* operation;
	int pin_num;
	int value;

	DigitalPinOperationFixture() {
		operation = new DigitalPinOperation();
		pin_num=9;
		value=1;

		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~DigitalPinOperationFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};

BOOST_FIXTURE_TEST_SUITE(DigitalPinOperationTests, DigitalPinOperationFixture)

BOOST_AUTO_TEST_CASE(checkConstruct) {
	BOOST_CHECK(operation);
}

BOOST_AUTO_TEST_CASE(checkSetGetPin) {
	BOOST_CHECK(operation->setPin(pin_num) == pin_num);
	BOOST_CHECK(operation->getPin() == pin_num);
}

BOOST_AUTO_TEST_CASE(checkSetGetValue) {
	BOOST_CHECK(operation->setValue(value) == value);
	BOOST_CHECK(operation->getValue() == value);
} 

BOOST_AUTO_TEST_SUITE_END()

