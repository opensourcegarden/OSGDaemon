#ifndef RUNONCEDECORATOR
#define RUNONCEDECORATOR value
#include <json/json.h>

#include "BaseOperationDecorator.h"

using namespace Operations;

class RunOnceDecorator : public BaseOperationDecorator {
public:
	virtual Json::Value execute();
private:
};


#endif /*RUNONCEDECORATOR*/