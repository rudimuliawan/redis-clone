//
// Created by rudi on 08/03/23.
//

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#include <server.h>
#include <request.h>
#include <utils.h>

// Public methods.
Server::Server(
    const int port
) : port_{port}
{
}

Server::~Server() = default;

void Server::initListeningSocket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        Util::die_error("socket()");
    }

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port_);
    addr.sin_addr.s_addr = ntohl(0);
    int rv = bind(fd_, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) {
        Util::die_error("bind()");
    }

    rv = listen(fd_, SOMAXCONN);
    if (rv) {
        Util::die_error("listen()");
    }
}

[[noreturn]] void Server::runForever() {
    initListeningSocket();

    while (true) {
        struct sockaddr_in clientAddr{};
        socklen_t sockLen{sizeof(clientAddr)};
        int connFd = accept(fd_, (struct sockaddr *)&clientAddr, &sockLen);
        if (connFd < 0) {
            continue; // Error
        }

        while (true) {
            Request request{};
            int32_t err = request.handle(connFd);
            if (err) {
                break;
            }
        }

        close(connFd);
    }
}