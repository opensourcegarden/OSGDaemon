#include "AbstractOperation.h"

namespace Operations {




// section 127-0-1-1-7cb871eb:1499b9437b8:-8000:0000000000000A6F end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element
HardwareAbstraction::AbstractController* AbstractOperation::setController(HardwareAbstraction::AbstractController* controller) {
	this->controller = controller;
	return this->controller;
}

HardwareAbstraction::AbstractController* AbstractOperation::getController() {
	return this->controller;
}

} /* End of namespace Operations */
