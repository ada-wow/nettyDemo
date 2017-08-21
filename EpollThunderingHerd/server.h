/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   server.h
 * Author: ada
 *
 * Created on August 20, 2017, 10:12 AM
 */

#ifndef SERVER_H
#define SERVER_H

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


class Server
{
public:
    Server(int p,int worknum):port(p),worknum(worknum){
        numOpenFds = 1024;
    };
    ~Server(){};
    void run();
private:
    struct sockaddr_in sin;    
    int port;
    
    int epfd;
    int numOpenFds;
    
    int eventCnt;
    struct epoll_event evlist;
    
    std::string pidname;
    int worknum;
    
    int do_listen();
    void do_accept(int fd);
};

#endif /* SERVER_H */

