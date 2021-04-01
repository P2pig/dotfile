#include "./include/curl/curl.h"
#include <string.h>
#include <stdio.h>

void get_SimpleVisit() {
	//simple visist url and print out
	curl_global_init(CURL_GLOBAL_DEFAULT);  // same as "CURL_GLOBAL_ALL" 
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://petstore.swagger.io/v2/pet/123");
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

void get_toFile() {
	//simple visist url and print out
	curl_global_init(CURL_GLOBAL_DEFAULT);  // same as "CURL_GLOBAL_ALL" 
	CURL *curl = curl_easy_init();

	FILE *fd = fopen("data", "a+");
	curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, fd);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

size_t writeCallback(void *buffer, size_t size, size_t nmemb, void *userp)
{
	char tmp[2048] = {'\0'};
	strncpy(tmp, buffer, 2048);
	printf("%s \n", tmp);

	return 0;
}

void get_callback() {
	//simple visist url and print out
	curl_global_init(CURL_GLOBAL_DEFAULT);  // same as "CURL_GLOBAL_ALL" 
	CURL *curl = curl_easy_init();

	FILE *fd = fopen("data", "a+");
	curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

// ---------------------------------------------------------------------------
size_t read_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
	return 0;
}

void post_SimpleVisit() {
	curl_global_init(CURL_GLOBAL_DEFAULT);  // same as "CURL_GLOBAL_ALL" 
	CURL *curl = curl_easy_init();

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Host: petstore.swagger.io");
	headers = curl_slist_append(headers, "accept: application/jason");
	headers = curl_slist_append(headers, "Content-Type: application/jason");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_URL, "https://petstore.swagger.io/v2/pet");

	char *postthis = "{  \"id\": 123,  \"category\": {    \"id\": 0,    \"name\": \"string\"  },  \"name\": \"haha1233\",  \"photoUrls\": [    \"string\"  ],  \"tags\": [    {      \"id\": 0,      \"name\": \"string\"    }  ],  \"status\": \"available\"}";

	curl_easy_setopt(curl, CURLOPT_READDATA, postthis);

	CURLcode res = curl_easy_perform(curl);

	char errbuf[CURL_ERROR_SIZE];

	curl_easy_cleanup(curl);
}

void post_writefile() {
	curl_global_init(CURL_GLOBAL_DEFAULT);  // same as "CURL_GLOBAL_ALL" 
	CURL *curl = curl_easy_init();

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Host: petstore.swagger.io");
	headers = curl_slist_append(headers, "accept: application/jason");
	headers = curl_slist_append(headers, "Content-Type: application/jason");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_URL, "https://petstore.swagger.io/v2/pet");

	FILE *json = fopen("./d.jason", "r+");

	curl_easy_setopt(curl, CURLOPT_READDATA, json);

	CURLcode res = curl_easy_perform(curl);

	char errbuf[CURL_ERROR_SIZE];

	curl_easy_cleanup(curl);
}

int main() {

	post_SimpleVisit();

	return 0;
}
