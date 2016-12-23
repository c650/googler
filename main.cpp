#include <iostream>
#include <fstream>
#include <string>

#include<curl/curl.h>

#include "./json.hpp"
#include "./googler.hpp"

int main(void) {

	// requires a JSON file with google API stuff

	nlohmann::json google_api_info;
	get_json_from_file("./google_search_api_info.json", google_api_info);

	for (auto it = google_api_info.begin() ; it != google_api_info.end(); ++it)
		std::cout << it.key() << ':' << it.value() << '\n';

	nlohmann::json search_result;
	get_json_from_web(google_api_info["address"].get<std::string>()
						+ "key=" + google_api_info["key"].get<std::string>()
						+ "&cx=" + google_api_info["cx"].get<std::string>()
						+ "&q=test", search_result);

	// std::cout << std::setw(4) << search_result;

	size_t count = search_result["items"].size() > 3 ? 3 : search_result["items"].size();
	for (auto& item : search_result["items"]) {
		std::cout << item["title"] << "\n\t" << item["snippet"] << "\n\t"
					<< item["link"] << "\n\n";
		if (!(count--))
			break;
	}
}
