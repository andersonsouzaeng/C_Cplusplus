// serverTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "server.h"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Server serv("127.0.0.1", 5005, 1);
	serv.start_server();

	cout << "Receiving data ... " << endl;
	while (serv.check_data() == 0)
	{
		cout << "Receiving data ... " << endl;
	}

	return 0;
}


