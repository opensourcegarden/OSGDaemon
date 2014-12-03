#ifndef Operations_DigitalPinOperation_h
#define Operations_DigitalPinOperation_h

#include "AbstractOperation.h"
#include <string>
#include <vector>
#include <iostream>
#include <json/json.h>


namespace Operations {

class DigitalPinOperation : public AbstractOperation {

 public:
 	DigitalPinOperation() {
 		pin = -1;
 		value = -1;
 	}
    virtual Json::Value execute();
    virtual Json::Value getExecutionTree();
    virtual int getPin();
    virtual int setPin(int pin);
    virtual int getValue();
    virtual int setValue(int value);


private:
	int pin;
	int value;
};

} /* End of namespace Operations */

#endif // Operations_DigitalPinOperation_h
