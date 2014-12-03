#include "OSGConnection.h"

void OSGConnection::loop() {
	while(true) {
		switch(current_state) {
			case NEW_CONNECTION_STATE: 
			{
				connection->sendMessage("OSG/1.0:SYN\n");
				current_state = RECEIVE_ACK_STATE;
			}
			break;


			case RECEIVE_ACK_STATE:
			{
				std::string ack = connection->readMessage();

				if(ack.compare("OSG/1.0:ACK") == 0) {

					connection->sendMessage("OSG/1.0:COMMAND\n");
					current_state = RECEIVE_COMMAND_STATE;
				} else {
					//TODO: Disconnect.
				}
			}
			break;

			case RECEIVE_COMMAND_STATE:
			{
				std::string command = connection->readMessage();
				// std::cout << command << std::endl;
				
				std::string expression = "(OSG)/(1\\.0):([a-zA-Z]+)*";
				std::string expression2 = "(OSG)/(1\\.0):([a-zA-Z_]+):([a-zA-Z_]+)";
				std::string expression3 = "(OSG)/(1\\.0):([a-zA-Z_]+):([a-zA-Z_]+):(.*)";

				boost::regex rex;
				rex = expression;

				boost::regex rex2(expression2);
				boost::regex rex3(expression3);

				boost::smatch base_matches;


				// std::cout << "True?: " << std::regex_match(test, base_match, e) << std::endl;
				
				
				
				if (boost::regex_match(command, base_matches, rex) )
				{
					if (base_matches.size() != 4) {
						connection->sendMessage("OSG/1.0:UNKNOWN_ERROR\n");
						break;
					}
					// std::cout << "Size: " << base_matches.size() << std::endl;
	
					if (std::string("SENDCOMMAND").compare(base_matches[3]) == 0) {
						// std::cout << "Here" << std::endl;
						// std::cout << base_matches[5] << std::endl;
						connection->sendMessage("OSG/1.0:COMMAND:IDLE\n");

						
					} 
					// std::cout << base_matches[4] << std::endl;
				} else if (boost::regex_match(command, base_matches, rex2)) {
					// std::cout << "Size: " << base_matches.size() << std::endl;
					// std::cout << base_matches[3] << std::endl;
					// std::cout << base_matches[4] << std::endl;
					// std::cout << base_matches[5] << std::endl;

					if (std::string("SENDCOMMAND").compare(base_matches[3])==0) {
						if (std::string("ACCEPT_JSON").compare(base_matches[4])==0) {
							connection->sendMessage("OSG/1.0:ERROR:ACCEPT_JSON:NO_JSON\n");
						}
					}

				} else if (boost::regex_match(command, base_matches, rex3)) {
					
					if (std::string("SENDCOMMAND").compare(base_matches[3]) == 0) {
						if (std::string("ACCEPT_JSON").compare(base_matches[4])==0 && base_matches[5].length() != 0) {
								connection->sendMessage("OSG/1.0:JSON_RECEIVED:" + base_matches[5] + "\n");
								Json::Value accept_json;
								Json::Reader reader;
								bool parseSuccessful = reader.parse(base_matches[5], accept_json);
								if (parseSuccessful) {
									connection->sendMessage("OSG/1.0:JSON_PARSED:" + base_matches[5] + "\n");
								}	
						}
					}
				}
				
				
			}
			break;
			// case RECEIVE_COMMAND_STATE:
			// 	// std::string command = connection->readMessage();

			// break;

		}
	}
}
