#ifndef TCPSERVER_H
#define TCPSERVER_H value

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
// #include <boost/mutex.hpp>
#include <iostream>
#include "TcpClientConnection.h"
#include "OSGConnection.h"
#include "../Operations/OperationsManager.h"
class TcpServer  {
public:
	TcpServer(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 8102))
	{
		op_manager = new Operations::OperationsManager();
		// opmanager = boost::thread(boost::bind(&Operations::OperationsManager::loop, op_manager));
		// opmanager.join();
		// boost::thread t(boost::bind(&OSGConnection::loop,connection_handler));
	    try {
		    start_accept();
	    } catch(...) {
	     	std::cout << "Unknown Exception" << std::endl;
	    }
  	}

private:
	tcp::acceptor acceptor_;
  	TcpClientConnection::pointer new_connection;
  	Operations::OperationsManager* op_manager;
  	boost::thread opmanager;
  	boost::mutex manager_lock;

	void start_accept();
	void handle_accept(TcpClientConnection::pointer new_connection,
      const boost::system::error_code& error);
};

#endif /* TCPSERVER_H */
