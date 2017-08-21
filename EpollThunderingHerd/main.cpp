/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ada
 *
 * Created on August 20, 2017, 10:09 AM
 */

#include <cstdlib>

#include "server.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    Server server(3331,4);
    server.run();
    return 0;
}

