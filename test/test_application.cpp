#include <stdio.h>
#include <stdlib.h>
#include <fstream>      // std::ifstream
#include <iostream>     // std::cout

#include "TestGetMethod.h"
#include "log_utils.h"

using namespace std;

// Using ADALINE_Network Class
int main(int argc, char* argv[])
{
	log_setLevel(LOG_LEVEL_DEBUG);

	rest::TestGetMethod get_method;
	get_method.send();
	//std::cout << "Content: " << std::string(get_method.getContent()) << ", Title: " << std::string(get_method.getTitle()) << std::endl;
	log_info("%s", get_method.getContent());
	log_info("%s", get_method.getTitle());


	return 0;
}