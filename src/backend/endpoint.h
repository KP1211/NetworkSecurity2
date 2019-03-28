#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <string>
#include "socket.h"
#include "shinyarmor_hdr.h"
#include "constant.h"


/* Notes on Endpoint
 * 
 * This class is the level that we will be implemeenting our protocol. 
 * PURPOSE: Input of this class: if it's a to-send-message. Will break one message down into more than one packets if needed, append header to each packet, and send it off.
 *          Input of this class: if it's a received-message. Will collect one packet or multiple packets. Build the message, and return it by reference.
 * 
 * Current max buffer length for each transaction(listen or send) is 100 as defined by BUFF_MAX_LEN
 * Current packets being sended from Endpoint to client and vice versa is *assumes to be null terminated c-string*!!!
 */
class Endpoint {            // BIND THIS TO A PORT NUMBER AND LISTEN WILL GUARANTEE ONE MESSAGE FROM NEXT MSG WITH SPECIFIED PROT NUM
    private:
        Socket                  endpoint;
        size_t                  max_buffer_len;
        size_t                  max_msg_len;
        unsigned char           *buf_to_send;
        struct sockaddr         incom_src_addr;
        int                     incom_src_addr_len;
        
        /* Feature fcts */
        bool build_packet(unsigned char*, unsigned int);
        unsigned int get_packet_port_num(unsigned char*);
        bool is_eof(unsigned char*);

    public:
        /* Core fcts */
        Endpoint();
        Endpoint(const char *);
        ~Endpoint();
        bool bootup();
        bool listen(unsigned char *, ssize_t &, unsigned int);    // fct returns after one transmission in the correct port number sepcified in the header, it will be wrped in a while loop and return message of that psecific port
        bool send(unsigned char *, const size_t, unsigned int);           // fct returns after one transmission, TODO will need to specify where to send to
        bool shutdown();
        
        
        /* Interactions fcts that will implement our own protocol */
        // fcts goes here

        void run_protocol_rcv(Endpoint &dummyRcv,unsigned char *incom_buf, ssize_t &bytes, unsigned int port_number);

        void run_protocol_send(Endpoint &dummyRcv, unsigned char *buff, const size_t buf_size, ssize_t &bytes, unsigned int port_number); 


};
               


#endif
