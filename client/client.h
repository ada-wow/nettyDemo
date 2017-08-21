/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   client.h
 * Author: ada
 *
 * Created on August 20, 2017, 1:35 PM
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <sstream>


class Client
{
public:
    Client(int p):port(p){};
    ~Client(){};
    void run();
private:
    struct sockaddr_in sin;    
    int port;
    
    std::string pidname;
    
    int prepare();
};

#endif /* CLIENT_H */

