/**
 * \brief UDP client implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup upd_client
 * \{
 */

#include "udp_client.h"

int local_socket;
struct sockaddr_in server_socket;

void udp_init(char *address, int port) {

    /* Set local socket */
    local_socket = set_local_socket();

    /* Set read socket timeout */
    struct timeval read_timeout;
    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = READ_TIMEOUT_US;
    setsockopt(local_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);

    /* Set server socket */
    server_socket = set_server_socket(address, port);
}

int set_local_socket(void) {

    /* Socket used for communication */
    local_socket = socket(PF_INET, SOCK_DGRAM, 0);

    /* Check if socket creation was successful */
    if(local_socket < 0) {
        perror("socket");
        return -1;
    }

    return local_socket;
}

struct sockaddr_in set_server_socket(char *address, int port) {
  
    struct hostent *server_address;   /* Target server address in hostent format */
    struct in_addr server_ip;         /* Target server address in ip numeric format */

    if (inet_aton(address, &server_ip)) {
        server_address = gethostbyaddr((char *)&server_ip, sizeof(server_ip), AF_INET);
    }
    else {
        server_address = gethostbyname(address);
    }

    if (server_address == NULL) {
        printf("Socket connection failed due to invalid network address!\n");
    }
    else {
        memset((char *) &server_socket, 0, sizeof(server_socket));
        memcpy(&server_socket.sin_addr, server_address->h_addr_list[0], sizeof(server_socket.sin_addr));
        server_socket.sin_family = AF_INET;
        server_socket.sin_port = htons(port);

        return server_socket;
    }
}

int send_message(char *buffer) {

    /* Send message to the server */
    if (sendto(local_socket, buffer, strlen(buffer)+1, 0, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0 ) { 
        perror("sendto");
        return -1;
    }
    else {
        return 0;
    }
}

int receive_message(char *buffer) {
  
    int received_bytes;

    /* Espera pela msg de resposta do servidor */
    received_bytes = recvfrom(local_socket, buffer, MAX_BUFFER_SIZE, 0, NULL, 0);
    if (received_bytes <= 0) {
        perror("recvfrom");
        return -1;
    }
    else {
        return received_bytes;
    }
}


/** \} End of upd_client group */