#include <stdio.h>
#include <stdlib.h>
#include <fstream>      // std::ifstream
#include <iostream>     // std::cout

#include "TestGetMethod.h"

using namespace std;

// Using ADALINE_Network Class
int main(int argc, char* argv[])
{
	rest::TestGetMethod get_method;
	get_method.send();
	std::cout << "Content" << get_method.getContent() << ", Title" << get_method.getTitle() << std::endl;


	return 0;
}