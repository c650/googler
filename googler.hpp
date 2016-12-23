#include <iostream>
#include <fstream>
#include <string>

#include<curl/curl.h>

#include "./json.hpp"

size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string& stream);

void get_json_from_web(const std::string& url , nlohmann::json& json_obj) {

	CURL *curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, url.data());

		std::string response;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

		CURLcode res = curl_easy_perform(curl);
		if (res == CURLE_OK) {
			json_obj = nlohmann::json::parse(response);
		}
		curl_easy_cleanup(curl);
	}
}

size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string& stream) {
	size_t realsize = size * nmemb;
	std::string temp(static_cast<const char*>(ptr), realsize);
	stream.append(temp);
	return realsize;
}

void get_json_from_file(const std::string& file, nlohmann::json& json_obj) {
	std::fstream fs(file, std::fstream::in);
	fs >> json_obj;
}
