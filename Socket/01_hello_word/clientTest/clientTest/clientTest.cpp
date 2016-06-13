// clientTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include "client.h"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Client client;

	client.connect_server("127.0.0.1", 5005);

	cout << "Sending data ... " << endl;
	client.send_data("teste");


	return 0;
}



