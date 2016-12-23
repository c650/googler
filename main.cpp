#include <iostream>
#include <fstream>
#include <string>

#include<curl/curl.h>

#include "./json.hpp"
#include "./googler.hpp"

int main(void) {

	std::vector<std::string> res_vec;
	Googler::do_google_search("test", 3 , res_vec);

	for (auto& result : res_vec)
		std::cout << result << "\n\n";

}
