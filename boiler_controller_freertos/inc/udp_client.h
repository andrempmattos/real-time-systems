/**
 * \brief UDP client definitions.
 * 
 * \date 2021/08/09
 * 
 * \defgroup upd_client UDP_client
 * \ingroup src
 * \{
 */

#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE		100

#define SERVER_ADDRESS		"localhost"
#define SERVER_PORT			8000

/**
 * \brief UPD client initialization.
 *
 * \param[in] *address is a string to the server address.
 * 
 * \param[in] port is the interface to be used for communication.
 */
void udp_init(char *address, int port);

/**
 * \brief Set local socket.
 * 
 * \return Local socket id or error code.
 */
int set_local_socket(void);

/**
 * \brief Set server socket.
 *
 * \param[in] *address is a string to the server address.
 * 
 * \param[in] port is the interface to be used for communication.
 * 
 * \return Server socket struct or error code.
 */
struct sockaddr_in set_server_socket(char *address, int port);

/**
 * \brief Send message using configured socket.
 *
 * \param[in] *buffer is a string of the message to be sent.
 * 
 * \return Error code.
 */
int send_message(char *buffer);

/**
 * \brief Receive message using configured socket.
 *
 * \param[out] *buffer is a string of the received message.
 * 
 * \return Error code.
 */
int receive_message(char *buffer);

#endif /* UDP_CLIENT_H_ */

/** \} End of upd_client group */