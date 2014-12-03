#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <json/json.h>

#include "../TcpServer.h"

using boost::asio::ip::tcp;


TcpServer* server;
void serverThread() {
	boost::asio::io_service my_service;
	server = new TcpServer(my_service);
	my_service.run();
}

boost::thread tcp_server_worker(serverThread);

boost::asio::io_service io_service_client;
tcp::resolver resolver(io_service_client);
tcp::resolver::query ask_server("localhost", "8102");
tcp::resolver::iterator endpoint_iterator = resolver.resolve(ask_server);
tcp::resolver::iterator end;
tcp::socket client_socket(io_service_client);
boost::system::error_code error = boost::asio::error::host_not_found;

struct TcpServerTestsFixture {
	std::string test_json;
	TcpServerTestsFixture() {
		Json::FastWriter writer;
		Json::Value sample_json;
		sample_json["operationString"] = "digitalWrite";
		sample_json["pin"] ="3";
		sample_json["value"] = "1";
		test_json = writer.write(sample_json);
		boost::algorithm::trim(test_json);
		// std::cout << test_json << std::endl;
	  

	while (error && endpoint_iterator != end)
	{
		
	  	client_socket.close();
	  	client_socket.connect(*endpoint_iterator++, error);
	 	// std::cout << error << std::endl;
	}

		// my_resolver = tcp::resolver(my_service);
		// server = new TcpServer(my_service);
		BOOST_TEST_MESSAGE("Set Up Operations Manager");
	};

	~TcpServerTestsFixture() {
		BOOST_TEST_MESSAGE("Tear Down Operations Manager");

		
	}

	std::string readMessage() {
		std::string data;
		boost::system::error_code error;
		boost::asio::streambuf in_stream;
		boost::asio::streambuf::mutable_buffers_type bufs = in_stream.prepare(512);
		size_t num_read = client_socket.receive(bufs);
		in_stream.commit(num_read);
		std::istream is(&in_stream);
		std::string s;
		is >> s;
		return s;
	}

	void sendMessage(std::string message) {
		boost::system::error_code error;
		boost::asio::streambuf out_stream;
		std::ostream os(&out_stream);

		os << message;
		size_t stream_size = client_socket.send(out_stream.data());
		out_stream.consume(stream_size);
	}
};



BOOST_FIXTURE_TEST_SUITE(TcpServerTests, TcpServerTestsFixture)


BOOST_AUTO_TEST_CASE(checkStart) {

	//server sends a syn first
	BOOST_CHECK(readMessage().compare("OSG/1.0:SYN") == 0);
	// std::cout << "test 90 " << std::endl;
	//send an ack
	sendMessage(std::string("OSG/1.0:ACK\n"));

	//receive a command
	BOOST_CHECK(readMessage().compare("OSG/1.0:COMMAND") == 0);
	
	

}

BOOST_AUTO_TEST_CASE(checkCommand) {

	//server is now waiting for a command
	//an empty command says the client is waiting for a command
	sendMessage(std::string("OSG/1.0:SENDCOMMAND"));

	// std::string ret(readMessage());
	// std::cout << ret << std::endl;

	BOOST_CHECK(readMessage().compare("OSG/1.0:COMMAND:IDLE") == 0);
	//lets do ACCEPT_JSON
	sendMessage(std::string("OSG/1.0:SENDCOMMAND:ACCEPT_JSON\n"));
	
	BOOST_CHECK(readMessage().compare("OSG/1.0:ERROR:ACCEPT_JSON:NO_JSON") == 0);
	
	sendMessage(std::string("OSG/1.0:SENDCOMMAND:ACCEPT_JSON:" + test_json));
	//there is no JSON attached so return an error message
	
	BOOST_CHECK(readMessage().compare("OSG/1.0:JSON_RECEIVED:" + test_json) == 0);
	BOOST_CHECK(readMessage().compare("OSG/1.0:JSON_PARSED:" + test_json) == 0);
}
BOOST_AUTO_TEST_SUITE_END()

