//
//
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

/* #include <arpa/inet.h> */
/* #include <stdio.h> */
/* #include <string.h> */
/* #include <sys/socket.h> */
/* #include <unistd.h> */

#ifndef __ZEPHYR__

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#else

#include <zephyr/net/socket.h>
#include <zephyr/kernel.h>

#endif

#include <errno.h>
#include <zephyr/logging/log.h>
/* LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_REGISTER(tcp_client, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_REGISTER(tcp_client); */

/* #define PORT_SERVER 3000 */

#ifndef CONFIG_IP_SERVER
#error "Se require configurar el CONFIG_IP_SERVER en prj.conf"
#endif

#ifndef CONFIG_PORT_SERVER
#error "Se require configurar el CONFIG_PORT_SERVER en prj.conf"
#endif

#define RECV_BUF_SIZE 1024 

int tcp_client_start(void);

#endif
