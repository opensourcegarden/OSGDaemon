#ifndef OSGCONNECTION_H
#define OSGCONNECTION_H value

#include "TcpClientConnection.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include <json/json.h>

#define NEW_CONNECTION_STATE 0
#define RECEIVE_ACK_STATE 1
#define RECEIVE_COMMAND_STATE 2

#include "OSGBufferReadable.h"
#include "../Operations/OperationsManager.h"
#include "../Operations/AbstractOperation.h"
#include "../Operations/ExecutionTreeParser.h"

class OSGConnection : public OSGBufferReadable {
public:
	OSGConnection(TcpClientConnection::pointer c_in, Operations::OperationsManager* operations_manager){
		this->connection = c_in;
		this->operations_manager = operations_manager;
	}

	void loop();


private:
	TcpClientConnection::pointer connection;
	Operations::OperationsManager* operations_manager;
	int current_state;
};
#endif