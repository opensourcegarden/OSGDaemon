// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE OperationsManager

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <json/json.h>
#include "../ExecutionTreeParser.h"
#include "../OperationsManager.h"
#include "../AbstractOperation.h"
#include "../CompositeOperation.h"
// #include "Operations/DigitalWriteOperation.h"
#include "../DigitalWriteOperation.h"
struct ExecutionTreeParserFixture {
	int pin, value;

	Json::Value digitalWriteJson;
	Json::Value digitalReadJson;

	ExecutionTreeParserFixture() {
		pin = 4;
		value = 1;

		digitalWriteJson["operationString"] = "digitalWrite";
		digitalWriteJson["pin"] = 4;
		digitalWriteJson["value"] = 1;

		digitalReadJson["operationString"] = "digitalRead";
		digitalReadJson["pin"] = 4;

		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~ExecutionTreeParserFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};

BOOST_FIXTURE_TEST_SUITE(ExecutionTreeParserTests, ExecutionTreeParserFixture)

BOOST_AUTO_TEST_CASE(digitalWriteParse) {

	Json::FastWriter writer;	
	std::string test_string = writer.write(digitalWriteJson);
	// std::cout << test_string << std::endl;

	Operations::AbstractOperation* concrete_operation = ExecutionTreeParser::parseJson(digitalWriteJson);
	Json::Value return_json = concrete_operation->getExecutionTree();

	std::string return_string = writer.write(return_json);
	// std::cout << return_string << std::endl;

	BOOST_CHECK(test_string.compare(return_string) == 0);
}

BOOST_AUTO_TEST_CASE(digitalReadParse) {
	

	Json::FastWriter writer;	
	std::string test_string = writer.write(digitalReadJson);
	// std::cout << test_string << std::endl;

	Operations::AbstractOperation* concrete_operation = ExecutionTreeParser::parseJson(digitalReadJson);
	Json::Value return_json = concrete_operation->getExecutionTree();

	std::string return_string = writer.write(return_json);
	// std::cout << return_string << std::endl;
	// BOOST_CHECK(test_string.compare(return_string) == 0);
}

BOOST_AUTO_TEST_CASE(compositeOperationParse) {
	Json::Value root(Json::objectValue);
	root["composite"] = true;

	Json::Value operations(Json::arrayValue);

	operations.append(digitalReadJson);
	operations.append(digitalWriteJson);

	root["operations"] = operations;

	Json::StyledWriter writer;	
	// std::string test_string = writer.write(root);
	// std::cout << test_string << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()