#include "DigitalPinOperation.h"

namespace Operations {




Json::Value DigitalPinOperation::execute()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 127-0-1-1--1fc1d787:149a46700ab:-8000:0000000000000ABE begin
{
}
// section 127-0-1-1--1fc1d787:149a46700ab:-8000:0000000000000ABE end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Json::Value DigitalPinOperation::getExecutionTree() {

}

int DigitalPinOperation::setPin(int pin) {
	this->pin = pin;
	return this->pin;
}

int DigitalPinOperation::getPin() {
	return pin;
}

int DigitalPinOperation::setValue(int value) {
	this->value = value;
	return this->value;
}

int DigitalPinOperation::getValue() {
	return this->value;
}
} /* End of namespace Operations */