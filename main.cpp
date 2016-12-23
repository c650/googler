#include <iostream>
#include <fstream>
#include <string>

#include<curl/curl.h>

#include "./json.hpp"
#include "./googler.hpp"

#define GOOGLE_CONFIG_PATH "./google_search_api_info.json"
/*
	Formats num_res_to_show results into

	title
		snippet
		link
*/
void do_google_search(const std::string& formatted_query, const size_t& num_res_to_show, std::vector<std::string>& res_vec);

int main(void) {

	std::vector<std::string> res_vec;
	do_google_search("test", 3 , res_vec);

	for (auto& result : res_vec)
		std::cout << result << "\n\n";

}

void do_google_search(const std::string& formatted_query, const size_t& num_res_to_show, std::vector<std::string>& res_vec) {

	// requires a JSON file with google API stuff

	nlohmann::json google_api_info;
	get_json_from_file( GOOGLE_CONFIG_PATH , google_api_info);

	nlohmann::json search_result;
	get_json_from_web(google_api_info["address"].get<std::string>()
						+ "key=" + google_api_info["key"].get<std::string>()
						+ "&cx=" + google_api_info["cx"].get<std::string>()
						+ "&q=" + formatted_query, search_result);

	size_t count = search_result["items"].size() > 3 ? 3 : search_result["items"].size();
	for (auto& item : search_result["items"]) {

		res_vec.push_back( item["title"].get<std::string>() + "\n\t" + item["snippet"].get<std::string>() + "\n\t" + item["link"].get<std::string>() );

		if (!(count--))
			break;
	}

}
