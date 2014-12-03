#include "OperationsManager.h"
#include <iostream>
namespace Operations {
	void OperationsManager::loop()
	{
		for(;;) {
			this->execute();
			if (state == STATE_MANAGER_SHUTDOWN) {
				break;
			} else if (state == STATE_MANAGER_RUNNING) {
				this->execute();
			}
			// std::cout << "here" << std::endl;
		}
		
		
		// std::cout << "here" << std::endl;
 		// return object;
	}

	void OperationsManager::shutdown() {
		this->state = STATE_MANAGER_SHUTDOWN;
	}

	void OperationsManager::setState(int state) {
		this->state = state;
	}

	Json::Value OperationsManager::execute() {
		boost::unique_lock<boost::shared_mutex> lock(running_operations_lock);
		std::vector<AbstractOperation* >::iterator it;
		std::vector<AbstractOperation* > pending_removal;

		Json::Value execute_root(Json::objectValue);
		Json::Value operations(Json::arrayValue);
		execute_root["operationString"] = "manager";
		std::cout << "Operations: " << RunningOperations.size() << std::endl;
		if (RunningOperations.size() > 0) 
		{
			for(it = RunningOperations.begin(); it != RunningOperations.end(); ++it) {
				Json::Value execution((**it).execute());
				
				// Json::StyledWriter writer;
				// std::string exe_string(writer.write(execution));
				// std::cout << exe_string;

				operations.append(execution);

				if(execution.isMember("runOnce")) {
					execute_root["runOnce"] = true;
					pending_removal.push_back(*it);
					
				}
			}
		}

		execute_root["operations"] = operations;

		if(pending_removal.size() > 0) {
			std::vector<AbstractOperation*>::iterator rem_it;
			for(rem_it = pending_removal.begin(); rem_it != pending_removal.end(); ++rem_it) {
				this->removeFromRunningOperations(*it);
			}
			std::cout << "pending removed" << std::endl;
			execute_root["pending_cleared"] = true;
		}
		



		// boost::unique_lock<boost::shared_mutex> unlock(running_operations_lock);
		return execute_root;
	}

	AbstractOperation* OperationsManager::addInitializedOperation(AbstractOperation* operation)
	{
		InitializedOperations.push_back(operation);
		return operation;
		// std::cout << operation << std::endl;
	}

	AbstractOperation* OperationsManager::addRunningOperation(AbstractOperation* operation)
	{
		// std::cout << "Operation address: " << operation << std::endl;
		if (operation != NULL) {
			RunningOperations.push_back(operation);	
		}
		

		return operation;
	}

	AbstractOperation* OperationsManager::removeFromRunningOperations(AbstractOperation* operation)
	{
		std::vector<AbstractOperation* >::iterator it;
		// std::cout << "Running Operations Size: " << RunningOperations.size() << std::endl;
		if (RunningOperations.size() > 0) {
			for(it = RunningOperations.begin(); it != RunningOperations.end(); ++it) {
					std::cout << "Removing Operation iterator address " << *it << std::endl;
					std::cout << "Removing Operation op address" << operation << std::endl;	
				if(operation == *it) {
					AbstractOperation* op = *it;
					
// 					it = std::remove(RunningOperations.begin(), RunningOperations.end(), operation);
					std::remove(RunningOperations.begin(), RunningOperations.end(), operation);
					// std::cout << "Erased Correctly!" << std::endl;
					// std::cout << "Running Operations Size: " << RunningOperations.size() << std::endl;
					// RunningOperations.erase(std::remove(RunningOperations.begin(), RunningOperations.end(), operation), RunningOperations.end());
					// it = RunningOperations.erase(it);
					return op;
				}
				std::cout << "passed if" << std::endl;
			}
		}
		std::cout << "Returning operation" << std::endl;
		return operation;
	}

	AbstractOperation* OperationsManager::removeFromInitializedOperations(AbstractOperation* operation)
	{
		std::vector<AbstractOperation* >::iterator it;

		for(it = InitializedOperations.begin(); it != InitializedOperations.end(); ++it) {
			if(operation == *it) {
				AbstractOperation* op = *it;
				InitializedOperations.erase(std::remove(InitializedOperations.begin(), InitializedOperations.end(), operation), InitializedOperations.end());
				return op;
			}
		}
	}

	bool OperationsManager::isOperationRunning(AbstractOperation* operation)
	{
		std::vector<AbstractOperation* >::iterator it;

		for(it = RunningOperations.begin(); it != RunningOperations.end(); ++it) {
			if(operation == *it) {
				return true;
			}
		}

		return false;
	}

	bool OperationsManager::isOperationInitialized(AbstractOperation* operation)
	{
		std::vector<AbstractOperation* >::iterator it;

		for(it = InitializedOperations.begin(); it != InitializedOperations.end(); ++it) {
			if(operation == *it) {
				return true;
			}
		}

		return false;
	}

	int OperationsManager::getNumInitializedOperations() {
		return InitializedOperations.size();
	}

	int OperationsManager::getNumRunningOperations() {
		return RunningOperations.size();
	}
} /* End of namespace Operations */
