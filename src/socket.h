#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <string.h>

class Socket {
    private:
        int fd;
        sockaddr_ll myaddr;
        int error_code;

    public:
        Socket();
        ~Socket();

        bool isValid() const;

        bool openSocket();
        bool getMsg(void *buf, size_t len, int flags);
        bool bindSocket(unsigned short sll_protocol_in, int sll_ifindex_in);    /* Work on hold, need to test if raw port can already receive data. */
        bool unlinkSocket();        /* Need work */
        bool closeSocket();









        std::string getErrorStr();

        /* ~For testing purposes~ */    //
        int getFd() {           //
            return this->fd;            //
        }                               //
        int getErrorCode() {    //
            return this->error_code;    //
        }                               //
        /* ~End of testing purposes~ */ //
};

#endif