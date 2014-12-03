#ifndef HardwareAbstraction_BasicArduino_h
#define HardwareAbstraction_BasicArduino_h

#include "AbstractController.h"

namespace HardwareAbstraction {

class BasicArduino : public AbstractController {

 public:
 	BasicArduino() {
 		controller_id = 1;
 	}

     int digitalRead(int pin);

     int digitalWrite(int pin, int value);

     int analogRead(int pin);

     int analogWrite(int pin, int value);
};

} /* End of namespace HardwareAbstraction */

#endif // HardwareAbstraction_BasicArduino_h
