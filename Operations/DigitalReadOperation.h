#ifndef Operations_DigitalReadOperation_h
#define Operations_DigitalReadOperation_h

#include "DigitalPinOperation.h"
#include <json/json.h>
#include <string>
namespace Operations {

class DigitalReadOperation : public DigitalPinOperation {

 public:

    virtual Json::Value execute();
    virtual Json::Value getExecutionTree();

 private:
 	int pin;
 	int value;
};

} /* End of namespace Operations */

#endif // Operations_DigitalReadOperation_h
