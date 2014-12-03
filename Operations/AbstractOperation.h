#ifndef Operations_AbstractOperation_h
#define Operations_AbstractOperation_h
#include "../HardwareAbstraction/AbstractController.h"
#include <json/json.h>
#include <string>
#include <vector>
namespace Operations {
class CompositeOperation;
class OperationsManager;
} /* End of namespace Operations */
namespace Operations {


class AbstractOperation {

 public:
	
    virtual Json::Value execute() { 
        Json::Value ret;
        return ret;
    };
    virtual Json::Value getExecutionTree(){
        Json::Value ret;
        return ret;
    };

    std::string operation_string;
    HardwareAbstraction::AbstractController* controller;
   
    HardwareAbstraction::AbstractController* getController();
    HardwareAbstraction::AbstractController* setController(HardwareAbstraction::AbstractController* controller);

    CompositeOperation *parent;


protected:
	static int tab_depth;
    /**
     * @element-type AbstractController
     */
    // HardwareAbstraction::AbstractController *myAbstractController;
};

} /* End of namespace Operations */

#endif // Operations_AbstractOperation_h
