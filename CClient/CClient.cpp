// CClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "json/json.h"
#include "HTTPClient.h"


#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl;  }

std::string readFile(std::string fileName) {
	std::ifstream t(fileName);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	return str;
}

std::string JsonToString(Json::Value obj) {
	Json::StreamWriterBuilder wbuilder;
	wbuilder["indentation"] = "\t";
	return Json::writeString(wbuilder, obj); 
}

void PostData() {
	std::unique_ptr<CHTTPClient> m_pHTTPClient;
	m_pHTTPClient.reset(new CHTTPClient(PRINT_LOG));
	m_pHTTPClient->SetHTTPS(true);

	CHTTPClient::HeadersMap requestHeaders;
	CHTTPClient::HttpResponse response;

	requestHeaders.emplace("Content-Type", "application/json");
	std::string strPostData = readFile("Activate.json");


	auto init = m_pHTTPClient->InitSession();
	auto post = m_pHTTPClient->Post("https://localhost:44382/Activate", requestHeaders, strPostData, response);
	std::cout << post << std::endl;
	std::cout << response.strBody << std::endl;

	m_pHTTPClient->CleanupSession();
}

void PostActivate() {
	std::unique_ptr<CHTTPClient> m_pHTTPClient;
	m_pHTTPClient.reset(new CHTTPClient(PRINT_LOG));
	m_pHTTPClient->SetHTTPS(true);

	CHTTPClient::HeadersMap requestHeaders;
	CHTTPClient::HttpResponse response;

	requestHeaders.emplace("Content-Type", "application/json");
	Json::Value jsonData;
	jsonData["LicenseKey"] = "demo";
	jsonData["SystemName"] = "portal";
	
	jsonData["Hosts"][0] = "quyoo.jan.io";
	jsonData["Hosts"][1] = "quyoo.jansoft.vn";
	 
	std::string data = JsonToString(jsonData);

	std::cout << data << std::endl;

	auto init = m_pHTTPClient->InitSession();
	auto post = m_pHTTPClient->Post("https://localhost:44382/Activate", requestHeaders, data, response);
	std::cout << post << std::endl;
	std::cout << response.strBody << std::endl;

	m_pHTTPClient->CleanupSession();
}


int main()
{
	std::cout << "Hello World!\n";
	PostActivate();


	//std::string strWebPage;
	//long lWebPageCode = 0;

	//std::unique_ptr<CHTTPClient> m_pHTTPClient(nullptr);
	////m_pHTTPClient.reset(new CHTTPClient(PRINT_LOG));

	///* to enable HTTPS, use the proper scheme in the URI
	// * or use SetHTTPS(true) */
	//m_pHTTPClient->InitSession();

	//m_pHTTPClient->SetHTTPS(true);
	//// get
	//// auto get = m_pHTTPClient->GetText("www.google.com", strWebPage, lWebPageCode);

	// post




	/*	std::unique_ptr<CHTTPClient> m_pRESTClient;
	m_pRESTClient.reset(new CHTTPClient(PRINT_LOG));
	m_pRESTClient->SetHTTPS(true);
	auto init = m_pRESTClient->InitSession();*/
	//CHTTPClient::HeadersMap RequestHeaders;
	//CHTTPClient::HttpResponse ServerResponse;
	//// GET request
	//m_pRESTClient->Get("http://jansoft.vn", RequestHeaders, ServerResponse);

	//// POST request
	//std::string strPostData = "data";
	//RequestHeaders.emplace("Content-Type", "text/text");
	//pRESTClient->Post("http://httpbin.org/post", RequestHeaders, strPostData, ServerResponse);

	//// PUT request
	//std::string strPutData = "data";
	//RequestHeaders.emplace("Content-Type", "text/text");

	//// 1. with a string
	//pRESTClient->Put("http://httpbin.org/put", RequestHeaders, strPutData, ServerResponse);

	//// 2. with a vector of char
	//CHTTPClient::ByteBuffer Buffer; // or std::vector<char>
	//Buffer.push_back('d');
	//Buffer.push_back('a');
	//Buffer.push_back('t');
	//Buffer.push_back('a');
	//pRESTClient->Put("http://httpbin.org/put", RequestHeaders, Buffer, ServerResponse);

	//// DELETE request
	//pRESTClient->Del("http://httpbin.org/delete", RequestHeaders, ServerResponse);

	// Server's response
	//ServerResponse.iCode; // response's code
	//ServerResponse.mapHeaders; // response's headers
	//ServerResponse.strBody; // response's body


}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
