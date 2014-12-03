#include "BaseOperationDecorator.h"

AbstractOperation* BaseOperationDecorator::getDecoratedOperation() {
	return this->decorated_operation;
}


AbstractOperation* BaseOperationDecorator::setDecoratedOperation(AbstractOperation* operation) {
	this->decorated_operation = operation;
	return this->decorated_operation;
}