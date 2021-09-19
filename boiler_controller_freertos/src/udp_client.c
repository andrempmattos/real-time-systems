/**
 * \brief UDP client implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup upd_client
 * \{
 */

#include <FreeRTOS.h>
#include <semphr.h>

#include "../inc/udp_client.h"

SemaphoreHandle_t xSocketMutex;

int local_socket;
struct sockaddr_in server_socket;

void udp_init(char *address, int port) {

    /* Create socket mutex */
    xSocketMutex = xSemaphoreCreateMutex();

    /* Set local socket */
    local_socket = set_local_socket();

    /* Set server socket */
    server_socket = set_server_socket(address, port);
}

int set_local_socket(void) {

    int socket_target = 0;

    //xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    /* Socket used for communication */
    socket_target = socket(PF_INET, SOCK_DGRAM, 0);

    /* Check if socket creation was successful */
    if(socket_target < 0) {
        perror("socket");
    }

    //xSemaphoreGive(xSocketMutex);
    return socket_target;
}

struct sockaddr_in set_server_socket(char *address, int port) {
    
    struct hostent *server_address;   /* Target server address in hostent format */
    struct in_addr server_ip;         /* Target server address in ip numeric format */
    struct sockaddr_in socket;        /* Server socket */

    //xSemaphoreTake(xSocketMutex, portMAX_DELAY);
    
    if (inet_aton(address, &server_ip)) {
        server_address = gethostbyaddr((char *)&server_ip, sizeof(server_ip), AF_INET);
    }
    else {
        server_address = gethostbyname(address);
    }

    if (server_address == NULL) {
        printf("Socket connection failed due to invalid network address!\n");
        //xSemaphoreGive(xSocketMutex);
    }
    else {
        memset((char *) &socket, 0, sizeof(socket));
        memcpy(&socket.sin_addr, server_address->h_addr_list[0], sizeof(socket.sin_addr));
        socket.sin_family = AF_INET;
        socket.sin_port = htons(port);

        //xSemaphoreGive(xSocketMutex);
        return socket;
    }
}

int send_message(char *buffer) {

    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    /* Send message to the server */
    if (sendto(local_socket, buffer, strlen(buffer)+1, 0, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0 ) { 
        //perror("sendto");

        /* Try to solve the problem by resetting socket */
        close(local_socket);
        local_socket = set_local_socket();
        
        xSemaphoreGive(xSocketMutex);
        return -1;
    }
    else {
        xSemaphoreGive(xSocketMutex);
        return 0;
    }
}

int receive_message(char *buffer) {
  
    int received_bytes;

    xSemaphoreTake(xSocketMutex, portMAX_DELAY);

    /* Espera pela msg de resposta do servidor */
    received_bytes = recvfrom(local_socket, buffer, MAX_BUFFER_SIZE, 0, NULL, 0);
    if (received_bytes <= 0) {
        //perror("recvfrom");

        /* Try to solve the problem by resetting socket */
        close(local_socket);
        local_socket = set_local_socket();
        
        xSemaphoreGive(xSocketMutex);
        return -1;
    }
    else {
        xSemaphoreGive(xSocketMutex);
        return received_bytes;
    }
}


/** \} End of upd_client group */