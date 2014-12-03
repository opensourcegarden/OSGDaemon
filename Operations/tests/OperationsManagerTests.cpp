// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE OperationsManager

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>

#include "../OperationsManager.h"
#include "../AbstractOperation.h"
#include "../CompositeOperation.h"
#include "../../HardwareAbstraction/BasicArduino.h"
#include "../DigitalReadOperation.h"
#include "../DigitalWriteOperation.h"
#include "../RunOnceDecorator.h"

#include <boost/thread.hpp>

using namespace Operations;

struct OperationsManagerTestFixture {
	OperationsManager* manager;
	// boost::thread manager_thread;

	CompositeOperation* composite;
	DigitalWriteOperation* child_operation;
	DigitalReadOperation* child_operation2;
	RunOnceDecorator* decorator;
	OperationsManagerTestFixture() {
		manager = new OperationsManager();
		// manager_thread = boost::thread(boost::bind(&Operations::OperationsManager::loop, manager));
		HardwareAbstraction::BasicArduino* controller = new HardwareAbstraction::BasicArduino();


		composite = new CompositeOperation();
		composite->setController(controller);

		child_operation = new DigitalWriteOperation();
		child_operation->setPin(4);
		child_operation->setValue(1);
		child_operation->setController(controller);

		child_operation2 = new DigitalReadOperation();
		child_operation2->setPin(4);
		child_operation2->setValue(1);
		child_operation2->setController(controller);

		decorator = new RunOnceDecorator();
		decorator->setDecoratedOperation((AbstractOperation*) composite);
		composite->addChild(child_operation);
		composite->addChild(child_operation2);
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~OperationsManagerTestFixture() {
		// manager_thread.join();
		// manager_thread.detach();
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};

BOOST_FIXTURE_TEST_SUITE(Operations, OperationsManagerTestFixture)

BOOST_AUTO_TEST_CASE(AddInitializedOperation) {
	AbstractOperation* test_pointer = manager->addInitializedOperation(composite); 
	
	//check to see if the pointer returned is equivalent to the pointer sent 
	BOOST_CHECK(test_pointer == composite);

	// //check to see if initialized (pending) operations vector size is 1
	// BOOST_CHECK(manager->getNumInitializedOperations() == 1);


}

BOOST_AUTO_TEST_CASE(isInitializedOperation) {
	
	BOOST_CHECK(!manager->isOperationInitialized(composite));

	manager->addInitializedOperation(composite);

	BOOST_CHECK(manager->isOperationInitialized(composite));

	// std::cout << "here" << std::endl;
}

BOOST_AUTO_TEST_CASE(removeFromInitializedOperations) {
	// OperationsManager* manager = new OperationsManager();

	manager->addInitializedOperation(child_operation);
	manager->addInitializedOperation(child_operation2);

	BOOST_CHECK(manager->getNumInitializedOperations() == 2);

	AbstractOperation* test_pointer = manager->removeFromInitializedOperations(child_operation);

	BOOST_CHECK(test_pointer == child_operation);

	BOOST_CHECK(manager->getNumInitializedOperations() == 1);

}

BOOST_AUTO_TEST_CASE(AddRunningOperation) {
	AbstractOperation* test_pointer(manager->addRunningOperation(child_operation));
	
	//check to see if the pointer returned is equivalent to the pointer sent 
	BOOST_CHECK(test_pointer == child_operation);

	//check to see if initialized (pending) operations vector size is 1
	BOOST_CHECK(manager->getNumRunningOperations() == 1);

}

BOOST_AUTO_TEST_CASE(isRunningOperation) {
	// OperationsManager* manager = new OperationsManager();

	// boost::shared_ptr<CompositeOperation> operation(new CompositeOperation());
	
	BOOST_CHECK(!manager->isOperationRunning(child_operation));

	manager->addRunningOperation(child_operation);

	BOOST_CHECK(manager->isOperationRunning(child_operation));
}

BOOST_AUTO_TEST_CASE(removeFromRunningOperations) {
	// OperationsManager* manager = new OperationsManager();

	manager->addRunningOperation(child_operation);
	manager->addRunningOperation(child_operation2);

	BOOST_CHECK(manager->getNumRunningOperations() == 2);

	AbstractOperation* test_pointer = manager->removeFromRunningOperations(child_operation);

	BOOST_CHECK(test_pointer == child_operation);

	BOOST_CHECK(manager->getNumRunningOperations() == 1);

}

BOOST_AUTO_TEST_CASE(executeTest) {
	manager->addRunningOperation((AbstractOperation*) decorator);
	// manager->addRunningOperation(child_operation);
	std::cout << "executeTest: "  << manager->getNumRunningOperations() << std::endl;
	BOOST_CHECK(manager->getNumRunningOperations() == 2);

	
	Json::Value ret = manager->execute();
	Json::StyledWriter writer;
	std::string ret_str = writer.write(ret);
	std::cout << ret_str;


	BOOST_CHECK(ret["operationString"] = "manager");
	BOOST_CHECK(ret["composite"] = "true");
	BOOST_CHECK(ret["operations"].size() == 2);

	BOOST_CHECK(ret["operations"][0].isObject());
	BOOST_CHECK(ret["operations"][0]["composite"]== true);

	BOOST_CHECK(ret["operations"][0]["execution_statuses"].isArray());
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][0].isObject());

	BOOST_CHECK(ret["operations"][0]["execution_statuses"][0]["operationString"].compare(std::string("digitalWrite")) == 0);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][0]["pin"] == 4);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][0]["value"] == 1);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][0]["status"] == "success");

	BOOST_CHECK(ret["operations"][0]["execution_statuses"][1]["operationString"].compare(std::string("digitalRead")) == 0);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][1]["pin"] == 4);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][1]["value"] == 1);
	BOOST_CHECK(ret["operations"][0]["execution_statuses"][1]["status"] == "success");

	BOOST_CHECK(ret["operations"][0]["runOnce"] == true);

	BOOST_CHECK(ret["operations"][1].isObject());
	BOOST_CHECK(ret["operations"][1]["operationString"].compare(std::string("digitalWrite")) == 0); 
	BOOST_CHECK(ret["operations"][1]["pin"] == 4);
	BOOST_CHECK(ret["operations"][1]["value"] == 1);
	BOOST_CHECK(ret["operations"][1]["status"] == "success");
	
	BOOST_CHECK(ret["runOnce"] == true);

	BOOST_CHECK(manager->getNumRunningOperations() == 2);

	
		
}
// BOOST_AUTO_TEST_CASE(OperationsManagerThreadTests) {
// 	// OperationsManager* op_manager = new Operations::OperationsManager();
// 	// 	boost::thread opmanager(boost::bind(&Operations::OperationsManager::loop, op_manager));
// 	// 	opmanager.join();
// }



BOOST_AUTO_TEST_SUITE_END()