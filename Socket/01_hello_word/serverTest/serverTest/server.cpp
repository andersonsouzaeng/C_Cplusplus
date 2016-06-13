/*
  Name: Server.cpp
  Author: Anderson FC Souza
  Date: 06/12/2016
  Description: .CPP 
*/

#include "server.h"
#include "stdafx.h"
#include <iostream>

using namespace std;

Server::Server( char *ip, unsigned short port, int max )
{	 
	
	WSADATA tst;

	// check computer suport to version 2.0
	if (WSAStartup(MAKEWORD(2, 2), &tst))
	{
		cout << "Error: Computer does not suport Winsocks version 2.0" << endl;
		return;
	}
	else
	{
		max_conections = max;
		
		//create Address definitions
		my_address.sin_family = AF_INET;
		my_address.sin_addr.s_addr = inet_addr(ip);
		my_address.sin_port = htons(port);

		// create socket
		//my_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (my_socket == SOCKET_ERROR)
		{
			cout << "Error: socket()" << endl;
			is_socket_created = false;
			return;
		}
		else
		{
			cout << "Success: socket()" << endl;
			is_socket_created = true;
		}

		// The sockaddr_in structure specifies the address family,
		// IP address, and port for the socket that is being bound.
		if (bind(my_socket, (SOCKADDR *)& my_address, sizeof(my_address)) == SOCKET_ERROR) {
			cout << "Error: bind(): " << WSAGetLastError() << endl;
			if (closesocket(my_socket) == SOCKET_ERROR)
			{
				cout << "Error: closesocket function failed with error: " << WSAGetLastError() << endl;
				WSACleanup();
				return;
			}
			WSACleanup();
			return;
		}
		cout << "Success: bind()" << endl;
	}
}

Server::~Server()
{
	cout << "Close socket" << endl;
	closesocket(my_socket);
	WSACleanup();
}

void Server::start_server()
{
	// Listen for incoming connection requests 
	// on the created socket
	//SOMAXCONN
	if (listen(my_socket, max_conections) == SOCKET_ERROR)
	{
		cout << "Error: listen(): " << WSAGetLastError() << endl;
		if (closesocket(my_socket) == SOCKET_ERROR)
		{
			cout << "Error: closesocket function failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}
		WSACleanup();
		return;
	}
	cout << "Success: listen()" << endl;

	// Accept a client socket		
	my_socket = accept(my_socket, NULL, NULL);
	if (my_socket == INVALID_SOCKET)
	{
		cout << "Error: accept failed with error: " << WSAGetLastError() << endl;
		closesocket(my_socket);
		WSACleanup();
	}
	cout << "Success: accept()" << endl;
		
	send_data("Connected to server.", 22);	
}

int Server::check_data()
{
	int number_of_received_bytes;
	int number_of_send_bytes;

	number_of_received_bytes = receive_data();
	
	if (number_of_received_bytes > 0)
	{
		// Echo the buffer back to the sender
		number_of_send_bytes = send_data(buffer, number_of_received_bytes);
		cout << "Bytes sent: " << number_of_send_bytes << endl;
	}
	else
	{
		return -1;
	}
	return 0;
}

int Server::send_data(char * buff, int numer_of_bytes)
{
	int result;
	result = send(my_socket, buff, numer_of_bytes, 0);
	if (result == SOCKET_ERROR) {
		cout << "Error: send failed error: " << WSAGetLastError() << endl;
		closesocket(my_socket);
		WSACleanup();
		return -1;
	}
	cout << "Bytes sent: " << result << endl;

	return result;
}

int Server::receive_data()
{
	result = recv(my_socket, buffer, 500, 0);
	cout << "Bytes received: " << result << endl;
	
	if (result > 0) //receive data
	{
		return result;		
	}
	else if (result == 0) //socket closed
	{
		cout << "Connection closing..." << endl;
		closesocket(my_socket);
		WSACleanup();
		return -1;
	}
	else { //error receiving data
		cout << "recv failed: " << WSAGetLastError() << endl;
		closesocket(my_socket);
		WSACleanup();
		return -1;
	}	
}