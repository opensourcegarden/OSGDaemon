#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
// #include "../Operations/OperationsManager.cpp"
#include "../CompositeOperation.h"
#include "../DigitalWriteOperation.h"
#include "../DigitalReadOperation.h"
using namespace Operations;
// class CompositeOperation;
struct OperationsManagerFixture {
	CompositeOperation* parent;
	DigitalWriteOperation* child_operation;
	DigitalReadOperation* child_operation2;
	OperationsManagerFixture() {
		parent = new CompositeOperation();
		child_operation = new DigitalWriteOperation();
		child_operation2 = new DigitalReadOperation();
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	}

	~OperationsManagerFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");
	}
};



BOOST_FIXTURE_TEST_SUITE(CompositeOperations, OperationsManagerFixture)


BOOST_AUTO_TEST_CASE(addChildrenToComposite) {
	BOOST_CHECK(parent);

	parent->addChild(child_operation);

	BOOST_CHECK(parent->getNumChildren() == 1);
	// std::cout << "here" << std::endl;
}


BOOST_AUTO_TEST_CASE(removeChildFromComposite) {
	// boost::shared_ptr<CompositeOperation> operation(new CompositeOperation());
	// boost::shared_ptr<AbstractOperation> child_operation(new DigitalWriteOperation());
	// boost::shared_ptr<AbstractOperation> child_operation2(new DigitalReadOperation());

	parent->addChild(child_operation);
	parent->addChild(child_operation2);

	BOOST_CHECK(parent->getNumChildren() == 2);

	parent->removeChild(child_operation);

	BOOST_CHECK(parent->getNumChildren() == 1);	
}

BOOST_AUTO_TEST_CASE(getExecutionString) {
	child_operation->setPin(4);
	child_operation->setValue(1);

	parent->addChild(child_operation);

	// std::vector<std::string> ret = operation->execute();
	// std::vector<std::string>::iterator it;
	// it = ret.begin();
	Json::FastWriter writer;	

	Json::Value return_json = parent->getExecutionTree();
	std::string r_json = writer.write(return_json);
	// std::cout << r_json << std::endl;

	Json::Value object;
	Json::Value operations(Json::arrayValue);
	Json::Value operation1(Json::objectValue);
	
	operation1["operationString"] = "digitalWrite";
	operation1["pin"] = 4;
	operation1["value"] = 1;

	operations.append(operation1);
	object["composite"] = true;
	object["operations"] = operations;
	


	std::string test_json = writer.write(object);
	// std::cout << test_json << std::endl;
	BOOST_CHECK(test_json.compare(r_json) == 0);
}

BOOST_AUTO_TEST_SUITE_END()