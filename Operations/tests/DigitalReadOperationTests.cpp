// #define BOOST_TEST_MODULE DigitalWriteOperationTests

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../DigitalReadOperation.h"
#include "../../HardwareAbstraction/AbstractController.h"
#include "../DigitalPinOperation.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include <vector>
#include <string>
#include <iostream>
using namespace Operations;
using namespace HardwareAbstraction;
// class DigitalPinOperation;
// class CompositeOperation;
struct DigitalReadOperationFixture {
	AbstractController* controller;
	DigitalPinOperation* operation;
	int pin_num;
	int value;

	DigitalReadOperationFixture() {
		operation = new DigitalReadOperation();
		controller = new BasicArduino();
		operation->setController(controller);
		pin_num=9;
		value=1;

		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~DigitalReadOperationFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(DigitalReadOperationTests, DigitalReadOperationFixture)

BOOST_AUTO_TEST_CASE(checkNoExecute) {
	Json::Value ret = operation->execute();
	Json::FastWriter writer;
	// std::string r_json = writer.write(ret);
	// std::cout << r_json << std::endl;

	BOOST_CHECK(ret["operationString"].compare( "digitalRead") == 0);
	BOOST_CHECK(ret["pin"] == -1);
	BOOST_CHECK(ret["value"] == -1);
	BOOST_CHECK(ret["status"].compare( "failed") == 0);
	
}

BOOST_AUTO_TEST_CASE(checkConstruct) {
	BOOST_CHECK(operation);
	BOOST_CHECK(controller);
}

BOOST_AUTO_TEST_CASE(checkExecute) {
	operation->setPin(pin_num);
	operation->setValue(value);

	Json::Value ret = operation->execute();
	
	// std::cout << r_json << std::endl;
	// BOOST_CHECK((std::string (*it).compare(std::to_string(pin_num)));
}

BOOST_AUTO_TEST_CASE(checkGetExecutionTree) {
	operation->setPin(pin_num);
	operation->setValue(value);

	//Make a new writer object to parse the json tree from the object
	Json::FastWriter writer;	

	//test the execution tree (jsoncpp library)
	Json::Value return_json = operation->getExecutionTree();
	std::string r_json = writer.write(return_json);
	// std::cout << r_json << std::endl;

	Json::Value object;
	object["operationString"] = "digitalRead";
	object["pin"] = pin_num;
	// object["value"] = value;

	std::string test_json = writer.write(object);
	// std::cout << test_json << std::endl;
	// std::cout << r_json << std::endl;
	
	BOOST_CHECK(test_json.compare(r_json) == 0);

} 

BOOST_AUTO_TEST_SUITE_END()

