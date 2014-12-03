#ifndef OSGPROTOCOLPARSER_H
#define	OSGPROTOCOLPARSER_H

#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <string>
#include "TcpClientConnection.h"

class OSGProtocolParser {
public:
	OSGProtocolParser() {
		// this->c_in = c_in;
	}

	void loop();
private:
	// TcpClientConnection::pointer c_in;
};

#endif /* OSGPROTOCOLPARSER_H */