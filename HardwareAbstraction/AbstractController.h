#ifndef HardwareAbstraction_AbstractController_h
#define HardwareAbstraction_AbstractController_h

namespace Operations {
class AbstractOperation;
} /* End of namespace Operations */

namespace HardwareAbstraction {

class AbstractController {

 public:

    virtual int digitalRead(int pin) {
    	return 0;
    } ;

    virtual int digitalWrite(int pin, int value) {
    	return 0;
    };

    virtual int analogRead(int pin) {
    	return 0;
    };

    virtual int analogWrite(int pin, int value) {
    	return 0;
    };

 public:
    int controller_id;

 public:

    /**
     * @element-type AbstractOperation
     */
    // Operations::AbstractOperation *myAbstractOperation;
};

} /* End of namespace HardwareAbstraction */

#endif // HardwareAbstraction_AbstractController_h
