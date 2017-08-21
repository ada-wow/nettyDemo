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

#include "server.h"

int Server::do_listen() {
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    int listener = socket(AF_INET, SOCK_STREAM, 0);

    int option = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, &option, sizeof (option)) < 0) {
        perror("set reuse port");
        return -1;
    }

    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &option, sizeof (option)) < 0) {
        perror("set reuse addr");
        return -1;
    }

    if (bind(listener, (struct sockaddr*) &sin, sizeof (sin)) < 0) {
        perror("bind ");
        return -1;
    }

    if (listen(listener, 16) < 0) {
        perror("listen");
        return -1;
    }

    return listener;
}

void Server::do_accept(int listener) {
    struct sockaddr_storage ss;
    socklen_t slen = sizeof (ss);
    int fd = accept(listener, (struct sockaddr*) &ss, &slen);
    if (fd < 0) perror("accept");
    else {
        std::cout << std::endl;
        std::cout << pidname << "";
        printf(" yeah , accepted \n");
    }
    char *message = "child:";
    strcat(message,pidname.c_str());
    write(fd, message, strlen(message));
    close(fd);
}

void Server::run() {
    pidname = "father";
    for (int i = 0; i < worknum; i++) {
        if (fork() == 0) {
            std::ostringstream oss;
            oss << i;
            pidname = oss.str();
            break;
        }
    }
    int listener = do_listen();
    if (listener < 0) return;
    epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll");
        return;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listener;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &ev) == -1) {
        perror("epoll_ctl add listener");
        return;
    }

    while (true) {
        int ready = epoll_wait(epfd, &evlist, numOpenFds, -2);

        std::cout << pidname << " ";
        printf("epoll wait return\n");

        if (evlist.events & EPOLLIN) {
            printf("%d begin to accept", atoi(pidname.c_str()));
            if (evlist.data.fd == listener) {
                do_accept(listener);
                continue;
            }
        }
    }
}