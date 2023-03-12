//
// Created by rudi on 09/03/23.
//

#include <cstdlib>

#include <server.h>

int main(int argc, char* argv[])
{
    int port = atoi(argv[1]);

    Server server{port};
    server.runForever();
}