//
// Created by rudi on 11/03/23.
//
#include <cassert>
#include <iostream>

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <request.h>

Request::Request() {};
Request::~Request() = default;

int32_t Request::readFull(int fd, char *buffer, size_t n) {
    while (n > 0) {
        ssize_t bytesRead = read(fd, buffer, n);
        if (bytesRead <= 0) {
            return -1;
        }

        assert((size_t)bytesRead <= n);
        n -= (size_t)bytesRead;
        buffer += bytesRead;
    }

    return 0;
}

int32_t Request::writeAll(int fd, char *buffer, size_t n) {
    while (n > 0) {
        ssize_t bytesWritten = write(fd, buffer, n);
        if (bytesWritten <= 0) {
            return -1;
        }

        assert((size_t)bytesWritten <= n);
        n -= (size_t)bytesWritten;
        buffer += bytesWritten;
    }

    return 0;
}

int32_t Request::handle(int fd) {
    char rBuffer[4 + kMaxMsg + 1];
    errno = 0;
    int32_t err = Request::readFull(fd, rBuffer, 4);
    if (err) {
        if (errno == 0) {
            std::cout << "EOF\n";
        }
        else {
            std::cout << "readFull() error" << err;
        }

        return err;
    }

    uint32_t length = 0;
    memcpy(&length, rBuffer, 4);
    if (length > kMaxMsg) {
        std::cout << "Too long!\n" ;
        return -1;
    }

    // Request body
    err = Request::readFull(fd, &rBuffer[4], length);
    if (err) {
        std::cout << "readFull() error\n";
        return err;
    }

    rBuffer[4+length] = '\0';
    std::cout << "Client says : " << &rBuffer[4] << std::endl;

    // Reply to client
    const char reply[] = "world";
    char wBuff[4 + sizeof(reply)];
    length = (uint32_t) strlen(reply);

    memcpy(wBuff, &length, 4);
    memcpy(&wBuff[4], reply, length);
    return Request::writeAll(fd, wBuff, 4 + length);
}