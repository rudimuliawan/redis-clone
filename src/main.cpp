//
// Created by rudi on 09/03/23.
//

#include <iostream>
#include <server.h>

int main()
{
    Server server{9000};
    server.runForever();
}