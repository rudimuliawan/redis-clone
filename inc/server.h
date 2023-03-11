//
// Created by rudi on 08/03/23.
//

#ifndef REDIS_CLONE_SERVER_H
#define REDIS_CLONE_SERVER_H

class Server {
public:
    /*! \brief Construct a TCP server.
      *
      * \note This construction doesn't initiate connection.
      *
      * \param port listening port of the server
     */
    Server(
        const int port
    );

    /*! \brief Destructor
     */
    ~Server();

    /*! \brief Main loop that waiting for request
     */
    [[noreturn]] void runForever();

private:
    int fd_{};
    int port_{};

    void initListeningSocket();
};

#endif //REDIS_CLONE_SERVER_H
