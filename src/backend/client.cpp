#include <string>
#include "client.h"

/* Default constructor
 */
Client::Client() : buffer_len(BUFF_MAX_LEN), incom_src_addr(), incom_src_addr_len(sizeof(incom_src_addr)) {
     memset(&incom_src_addr,0,sizeof(incom_src_addr));
}

/*  Changes the default interface name that is used to bind the underlying socket
 */
Client::Client(const char *interface) : endpoint(interface), buffer_len(BUFF_MAX_LEN), incom_src_addr(), incom_src_addr_len(sizeof(incom_src_addr)) {
    memset(&incom_src_addr,0,sizeof(incom_src_addr));
}

/* Ensure Client is closed.
 */
Client::~Client() {
    memset(&incom_src_addr,0,sizeof(incom_src_addr));
    this->shutdown();
}

/* Opens, and bind the socket endpoint
 */
bool Client::bootup() {
    return ( endpoint.openSocket() && endpoint.bindSocket() );
}

/* Listens for ONE incoming transmission. bytes is how much bytes was receieved.
 */
bool Client::listen(unsigned char *buff, ssize_t &bytes) {
    return endpoint.recvMsg(buff, this->buffer_len, bytes, this->incom_src_addr, this->incom_src_addr_len);
}

/* Sends ONE outgoing transmission.
 * TODO: need to specify where to send to
 */
bool Client::send(const unsigned char *buffer) {
    return endpoint.sendMsg(buffer, this->buffer_len, 0);
}


/* Closes the socket, no more listening or sending...
 */
bool Client::shutdown() {
    return endpoint.closeSocket();
}

/* 
 * For the purpose of returning something of sockaddr that operator<< can process for std::cout
 * In this case, we return a string of formated text
 *  */
std::string Client::get_string_src_addr() {
    std::string format_output;
    format_output = "Feature Coming Soon!";                 /* TODO */
    return format_output;
}

/* 
 * Returns the length of sockaddr len of the incoming packet
 *  */
int Client::get_src_addr_len() {
    return this->incom_src_addr_len;
}

// Add fcts here to 