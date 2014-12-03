#include "RunOnceDecorator.h"

Json::Value RunOnceDecorator::execute() {
	Json::Value root(Json::objectValue);

	// if(&decorated_operation) {
	// 	std::cout << "Decorated Object Found" << std::endl;
	// } else {
	// 	std::cout << "Decorated Object Not Found" << std::endl;
	// }
	root = decorated_operation->execute();
	root["runOnce"] = true;
	// Json::StyledWriter writer;
	// std::string root_str(writer.write(root));
	// std::cout << "Root: " << std::endl << root_str << std::endl;
	return root;
}
