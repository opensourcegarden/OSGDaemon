#ifndef Operations_DigititalWriteOperation_h
#define Operations_DigititalWriteOperation_h

#include "DigitalPinOperation.h"
#include <vector>
#include <string>
#include <json/json.h>

namespace Operations {

class DigitalWriteOperation : public DigitalPinOperation {

public:
    virtual Json::Value execute();
    virtual Json::Value getExecutionTree();
private:
};

} /* End of namespace Operations */

#endif // Operations_DigititalWriteOperation_h
