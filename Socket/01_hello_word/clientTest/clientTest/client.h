/* Name: client.h 
   Author: Anderson FC Souza
   Date: 06/12/2016
   Description: 
   
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

//using namespace std;

class Client
{    
private:
	int bytes_received, result;
	char buffer[500];
	SOCKET my_socket;	
	sockaddr_in server_address;

	bool is_socket_created;
	
public:
       
    Client();
    ~Client();        
	int connect_server(char* ip = "127.0.0.1", unsigned short port = 5005);
	void Client::send_data(char * msg);
};

#endif
