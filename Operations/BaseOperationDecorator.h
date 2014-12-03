#ifndef BASEOPERATIONDECORATOR_H
#define BASEOPERATIONDECORATOR_H 

// #include <boost/shared_ptr.hpp>
#include "AbstractOperation.h"
#include <json/json.h>
using namespace Operations;

class BaseOperationDecorator : public AbstractOperation {
public:
	virtual AbstractOperation* getDecoratedOperation();
	virtual AbstractOperation* setDecoratedOperation(AbstractOperation* operation);
	virtual Json::Value execute() {
		Json::Value value;
		return value;
	};

protected:
	AbstractOperation* decorated_operation;
private:
	
};

#endif /* BASEOPERATIONDECORATOR_H */