

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include<iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <curl.h>

using namespace std;

//size_t write_data(char* ptr, size_t size, size_t nmemb, FILE* data)
//{
//	return fwrite(ptr, size, nmemb, data);
//}

class HyperandEmail
{
private:
	string text;
	set <string> hyperlinks;
	set <string> email;

public:
	HyperandEmail(ifstream& f);
	void extract_hyperlinks();
	void extract_email();
	void CheckHyper();
	void printEmail();
};

HyperandEmail::HyperandEmail(ifstream& f) : hyperlinks{}, email {}
{
	text = string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

void HyperandEmail::extract_hyperlinks()
{
	regex hl_regex("((http:\/\/)?([\da-z-\.]+)[.]([a-z\.]{2,6})[./]([a-z0-9_\/\.-]*)*\/?)", std::regex_constants::icase);
	hyperlinks = set <string> (std::sregex_token_iterator(text.begin(), text.end(), hl_regex, 0),
		sregex_token_iterator{});
}

void HyperandEmail:: extract_email()
{
	regex h2_regex("([A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,64})", std::regex_constants::icase);


	email=set <string> (std::sregex_token_iterator(text.begin(), text.end(), h2_regex, 0),
		sregex_token_iterator{});	
}

void HyperandEmail::CheckHyper()
{
	CURL* curl;
	
	CURLcode res;
	curl = curl_easy_init();
	for (auto str :hyperlinks )
		if (curl) 
		{

			curl_easy_setopt(curl, CURLOPT_URL, str.c_str());
			curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

			/*curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEHEADER, header_file);*/

			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				cout << str << "\t" << "Error #" << res << " " << curl_easy_strerror(res) << '\n';
			else cout << str << "\t" << "GOODLINKS" << '\n';
		}
	curl_easy_cleanup(curl);
}

void HyperandEmail::printEmail()
{
	for (auto str : email)
		cout << str << '\n';
}

void result(HyperandEmail& ohh)
{
	cout << "URL"<<'\n';
	for (int i = 0; i < 30; ++i)
		cout << '_' ;
	cout << '\n';
	ohh.extract_hyperlinks();
	ohh.CheckHyper();
	cout << '\n';
	cout << "EMAILS"<<'\n';
	for (int i = 0; i < 30; ++i)
		cout << '_';
	cout << '\n';
	ohh.extract_email();
	ohh.printEmail();


}
	


int main()
{


	
	ifstream f("write.txt");
	HyperandEmail ohh(f);
	result(ohh);
	f.close();
  return 0;
}


