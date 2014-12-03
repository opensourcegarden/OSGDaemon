#include "TcpServer.h"

void TcpServer::start_accept() {
	new_connection = TcpClientConnection::create(acceptor_.get_io_service());
	// std::cout << "Hello World" << std::endl;	
	acceptor_.async_accept(new_connection->socket(),
        boost::bind(&TcpServer::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
    
}	

void TcpServer::handle_accept(TcpClientConnection::pointer new_connection,
      const boost::system::error_code& error)
	  {
	  	// std::cout << "TcpServer::handle_accept" << std::endl;
	    try {
	    	
	      	if (!error)
	      	{	
	             // ArduinoConnector* connector = new ArduinoConnector(new_connection);
	            OSGConnection* connection_handler = new OSGConnection(new_connection, op_manager); 		
	      		boost::thread t(boost::bind(&OSGConnection::loop,connection_handler));
	      		t.join();
	      	}
	      	start_accept();
	      	
	    } catch (const std::exception& e) {
	        std::cout << "hwstr" << e.what() << std::endl;
	    }
	 }
