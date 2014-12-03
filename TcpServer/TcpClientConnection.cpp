#include "TcpClientConnection.h"


TcpClientConnection::pointer TcpClientConnection::create(boost::asio::io_service& io_service)
  	{
    	return pointer(new TcpClientConnection(io_service));
  	}

void TcpClientConnection::sendMessage(std::string message_in) {
	boost::asio::async_write(socket_, boost::asio::buffer(message_in),
        boost::bind(&TcpClientConnection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

std::string TcpClientConnection::readMessage() {
	boost::asio::streambuf b;

	boost::asio::streambuf::mutable_buffers_type bufs = b.prepare(1024);
	size_t n = socket_.receive(bufs);

	b.commit(n);

	std::istream is(&b);
	std::string s;
	is >> s;

	// std::cout << s << std::endl;
	return s;

}

tcp::socket& TcpClientConnection::socket() {
    return socket_;
}

void TcpClientConnection::handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/) {

}

std::string TcpClientConnection::handle_read(const boost::system::error_code, size_t) {
	boost::asio::streambuf b;

	// reserve 512 bytes in output sequence
	boost::asio::streambuf::mutable_buffers_type bufs = b.prepare(512);

	size_t n = socket_.receive(bufs);

	// // received data is "committed" from output sequence to input sequence
	b.commit(n);

	std::istream is(&b);
	std::string s;
	is >> s;
	return s;
}