#ifndef Operations_OperationsManager_h
#define Operations_OperationsManager_h

#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <boost/shared_ptr.hpp>
#include "AbstractOperation.h"
#include <json/json.h>
#include <boost/thread.hpp>


namespace Operations {
#define STATE_MANAGER_START 0
#define STATE_MANAGER_SHUTDOWN 1
#define STATE_MANAGER_IDLE 2
#define STATE_MANAGER_RUNNING 3

class OperationsManager {

 public:

    OperationsManager() {
        state = STATE_MANAGER_START;
    }
    virtual void loop();
    virtual void shutdown();
    virtual void setState(int state);
    virtual Json::Value execute();
    virtual AbstractOperation* addInitializedOperation(AbstractOperation* operation);
    virtual AbstractOperation* addRunningOperation(AbstractOperation* operation);
    virtual AbstractOperation* removeFromRunningOperations(AbstractOperation* operation);
    virtual AbstractOperation* removeFromInitializedOperations(AbstractOperation* operation);
    virtual bool isOperationRunning(AbstractOperation* operation);
    virtual bool isOperationInitialized(AbstractOperation* operation);
    virtual int getNumInitializedOperations();
    virtual int getNumRunningOperations();

 public:
    int state;
    boost::shared_mutex running_operations_lock;
    boost::shared_mutex initialized_operations_lock;
    std::vector<AbstractOperation* > RunningOperations;
    std::vector<AbstractOperation* > InitializedOperations;
};

} /* End of namespace Operations */

#endif // Operations_OperationsManager_h
