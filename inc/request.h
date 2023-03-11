//
// Created by rudi on 11/03/23.
//

#ifndef REDISCLONE_REQUEST_H
#define REDISCLONE_REQUEST_H

#include <cstdint>

class Request {
public:
    Request();
    ~Request();

    static int32_t handle(int fd);
    static int32_t readFull(int fd, char *buffer, std::size_t n);
    static int32_t writeAll(int fd, char *buffer, std::size_t n);

private:
    static const size_t kMaxMsg{4096};
};

#endif // REDISCLONE_REQUEST_H
