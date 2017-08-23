/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


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

#include "client.h"

int Client::prepare() {
    const char* ip = "192.168.31.209";
    
    sin.sin_family = AF_INET;
    //sin.sin_addr.s_addr = 0;
    inet_pton(AF_INET,ip,&sin.sin_addr);
    sin.sin_port = htons(port);

    int listener = socket(AF_INET, SOCK_STREAM, 0);

    int option = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &option, sizeof (option)) < 0) {
        perror("set reuse addr");
        return -1;
    }
    if (connect(listener, (struct sockaddr*) &sin, sizeof (sin)) == -1) {
        perror("connect() error");
    }
    return listener;
}

void Client::run() {
    char message[30];
    int str_len;
    memset(&sin, 0, sizeof (sin));

    int socket = prepare();

    str_len = read(socket, message, sizeof (message) - 1);
    message[str_len] = '\0';
    if (str_len == -1) {
        perror("read() error");
    }
    printf("str_len:%d\n",str_len);
    printf("Message from server : %s \n", message);
    close(socket);
}