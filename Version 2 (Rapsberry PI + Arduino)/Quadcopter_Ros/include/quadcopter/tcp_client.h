/*
 * tcp_client.h
 *
 *  Created on: Mar 31, 2015
 *      Author: trexter
 */

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent

class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    tcp_client();
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
};



#endif /* TCP_CLIENT_H_ */
