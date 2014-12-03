#ifndef TcpClientConnection_H
#define TcpClientConnection_H
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string.h>
#include "OSGBufferReadable.h"

using boost::asio::ip::tcp;

class TcpClientConnection : public boost::enable_shared_from_this<TcpClientConnection> {
public:

	typedef boost::shared_ptr<TcpClientConnection> pointer;

    static pointer create(boost::asio::io_service& io_service);
    void sendMessage(std::string message_in);
    std::string readMessage();
    tcp::socket& socket();  	


private:
  TcpClientConnection(boost::asio::io_service& io_service): socket_(io_service)
  	{
  	}

  void handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/);
  std::string handle_read(const boost::system::error_code, size_t);

  

  tcp::socket socket_;
  std::string message_;
  char buffer[1024];
};


#endif /* TcpClientConnection_H */