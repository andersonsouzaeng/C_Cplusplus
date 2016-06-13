/*
  Name: client.cpp
  Author: Anderson FC Souza
  Date: 06/12/2016
  Description: .CPP 
*/

#include "client.h"
#include "stdafx.h"
#include <iostream>

using namespace std;

Client::Client()
{

	WSADATA tst;

	// check computer suport to version 2.0
	if (WSAStartup(MAKEWORD(2, 2), &tst))
	{
		cout << "# Error: Computer does not suport Winsocks version 2.0" << endl;
		return;
	}
	else
	{
		
		// create socket
		//my_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (my_socket == SOCKET_ERROR)
		{
			cout << "# Error: socket()" << endl;
			is_socket_created = false;
			return;
		}
		else
		{
			cout << "# Success: socket()" << endl;
			is_socket_created = true;
		}
	}
}

Client::~Client()
{
	cout << "# Close socket" << endl;
	closesocket(my_socket);
	WSACleanup();
}


int Client::connect_server(char *ip, unsigned short port)
{
	//create Address definitions
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ip);
	server_address.sin_port = htons(port);

	cout << "# Conect (" << ip << ", " << port << ")" << endl;
	if (connect(my_socket,
		reinterpret_cast <SOCKADDR *> (&server_address),
		sizeof(server_address))
		== SOCKET_ERROR) {
		cout << "# Error: conect(): " << WSAGetLastError() << endl;
		if (closesocket(my_socket) == SOCKET_ERROR)
		{
			cout << "# Error: closesocket function failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}
		WSACleanup();
		return -1;
	}
	cout << "# Success: conect()" << endl;

	//Waiting for a success message
	result = 0;
	while (result == -1)
	{
		result = recv(my_socket, buffer, 500, 0);
		cout << "# Result: " << result << endl;
		if (result != -1)
		{
			buffer[result + 1] = '\0';			
			cout << "# Read: " << buffer << endl;			
		}
	}
		
	return 0;
}

void Client::send_data(char * msg)
{
	cout << "send message (" << strlen(msg) << "): " << msg << endl;
	send(my_socket, msg, (int)strlen(msg)+1, 0);
}

