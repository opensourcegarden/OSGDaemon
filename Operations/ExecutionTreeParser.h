#ifndef EXECUTIONTREEPARSER_H
#define EXECUTIONTREEPARSER_H
#include "AbstractOperation.h"
#include "CompositeOperation.h"
#include "DigitalWriteOperation.h"
#include "DigitalReadOperation.h"
#include <json/json.h>
#include <typeinfo>

class ExecutionTreeParser {
public:
	static Operations::AbstractOperation* parseJson(Json::Value root) {
		
		
		if(!root["composite"].isNull()) {
			Operations::CompositeOperation* ret_operation = buildComposite(root);
			return ret_operation;
		}

		if (root["operationString"].isString()) {
			std::string operationString = root["operationString"].asString();
			
			if (operationString.compare("digitalWrite") == 0) {
				Operations::DigitalWriteOperation* ret_operation = buildDigitalWrite(root);	
				return ret_operation;
			}
			
			if (operationString.compare("digitalRead") == 0) {
				Operations::DigitalReadOperation* ret_operation = buildDigitalRead(root);	
				return ret_operation;
			}
			

			
		}
		return NULL;
	}

private:
	static Operations::DigitalWriteOperation* buildDigitalWrite(Json::Value object) {
		Operations::DigitalWriteOperation* ret_operation = new Operations::DigitalWriteOperation();
		int pin, value;

		if (object["pin"].isInt()) {
			pin = object["pin"].asInt();
		}
		if (object["value"].isInt()) {
			value = object["value"].asInt();
		}
		ret_operation->setPin(pin);
		ret_operation->setValue(value);
		return ret_operation;
		// if() {

		// }
	}

	static Operations::DigitalReadOperation* buildDigitalRead(Json::Value object) {
		Operations::DigitalReadOperation* ret_operation = new Operations::DigitalReadOperation();
		int pin, value;

		if (object["pin"].isInt()) {
			pin = object["pin"].asInt();
		}
		if (object["value"].isInt()) {
			value = object["value"].asInt();
		}

		ret_operation->setPin(pin);
		ret_operation->setValue(value);
		return ret_operation;
		// if() {

		// }
	}	

	static Operations::CompositeOperation* buildComposite(Json::Value object) {
		return NULL;
	}
};

#endif /* EXECUTIONTREEPARSER_H */