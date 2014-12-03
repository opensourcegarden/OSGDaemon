// #define BOOST_TEST_MODULE DigitalWriteOperationTests

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include "../DigitalWriteOperation.h"
#include "../../HardwareAbstraction/AbstractController.h"
#include "../DigitalPinOperation.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace Operations;
using namespace HardwareAbstraction;
// class DigitalPinOperation;
// class CompositeOperation;
struct DigitalWriteOperationFixture {
	AbstractController* controller;
	DigitalPinOperation* operation;
	int pin_num;
	int value;

	DigitalWriteOperationFixture() {
		operation = new DigitalWriteOperation();
		controller = new BasicArduino();
		operation->setController(controller);
		pin_num=9;
		value=1;

		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~DigitalWriteOperationFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(DigitalWriteOperationTests, DigitalWriteOperationFixture)

BOOST_AUTO_TEST_CASE(checkNoExecute) {
	// std::vector<std::string> ret = operation->execute();

	// std::vector<std::string>::iterator it;
	// it=ret.begin();

	// BOOST_CHECK(ret.size());
	// BOOST_CHECK((*it) == "digitalWrite");
	// BOOST_CHECK((*++it) == "-1");
	// BOOST_CHECK((*++it) == "-1");
	// BOOST_CHECK((*++it) == "failed");
}

BOOST_AUTO_TEST_CASE(checkConstruct) {
	BOOST_CHECK(operation);
	BOOST_CHECK(controller);
}

BOOST_AUTO_TEST_CASE(checkExecute) {
	operation->setPin(pin_num);
	operation->setValue(value);

	
	Json::Value ret = operation->execute();
	BOOST_CHECK(ret["operationString"].compare( "digitalWrite") == 0);
	BOOST_CHECK(ret["pin"] == pin_num);
	BOOST_CHECK(ret["value"] == value);
	BOOST_CHECK(ret["status"].compare( "success") == 0);
	// std::vector<std::string> ret = operation->execute();
	// std::vector<std::string>::iterator it;
	// // it = ret.begin();

	// // BOOST_CHECK(ret.size());
	// // BOOST_CHECK((*it) == "digitalWrite");
	// // BOOST_CHECK((*++it) == std::to_string(pin_num));
	// // BOOST_CHECK((*++it) == std::to_string(value));
	// // BOOST_CHECK((*++it) == "success");

	// BOOST_CHECK((std::string (*it).compare(std::to_string(pin_num)));
} 

BOOST_AUTO_TEST_CASE(checkGetExecutionTree) {
	operation->setPin(pin_num);
	operation->setValue(value);

	// std::vector<std::string> ret = operation->execute();
	// std::vector<std::string>::iterator it;
	// it = ret.begin();
	Json::FastWriter writer;	

	Json::Value return_json = operation->getExecutionTree();
	std::string r_json = writer.write(return_json);
	// std::cout << r_json << std::endl;

	Json::Value object;
	object["operationString"] = "digitalWrite";
	object["pin"] = pin_num;
	object["value"] = value;
	std::string test_json = writer.write(object);
	// std::cout << test_json << std::endl;
	
	BOOST_CHECK(test_json.compare(r_json) == 0);

		
	// BOOST_CHECK(ret.size());
	// BOOST_CHECK((*it) == "digitalWrite");
	// BOOST_CHECK((*++it) == std::to_string(pin_num));
	// BOOST_CHECK((*++it) == std::to_string(value));
	// BOOST_CHECK((*++it) == "success");

	// BOOST_CHECK((std::string (*it).compare(std::to_string(pin_num)));
}


BOOST_AUTO_TEST_SUITE_END()