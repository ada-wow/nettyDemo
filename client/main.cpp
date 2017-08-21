/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ada
 *
 * Created on August 20, 2017, 1:51 PM
 */

#include <cstdlib>

#include "client.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Client client(3331);
    client.run();
    return 0;
}

