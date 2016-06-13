/* Name: server.h 
   Author: Anderson FC Souza
   Date: 06/12/2016
   Description: 
   
   
   
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

class Server
{    
private:
	int max_conections, bytes_received, result;
	SOCKET my_socket;
	char buffer[500];
	sockaddr_in my_address;
	bool is_socket_created;
	
	int send_data(char * buff, int numer_of_bytes);
	int receive_data();
public:
       
    Server(char* ip = "127.0.0.1", unsigned short port = 55555, int max_connections = 1);
    ~Server();        
	void start_server();
	int check_data();

};

#endif
