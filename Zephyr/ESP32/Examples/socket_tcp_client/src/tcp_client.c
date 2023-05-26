// Client side C/C++ program to demonstrate Socket
// programming

#include "tcp_client.h"
/* LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL); */

static ssize_t sendall(int sock, const void *buf, size_t len)
{
	while (len) {
		ssize_t out_len = send(sock, buf, len, 0);

		if (out_len < 0) {
			return out_len;
		}
		buf = (const char *)buf + out_len;
		len -= out_len;
	}

	return 0;
}
 
int tcp_client_start(void)
{
  LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL);
  /* LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL); */
  LOG_INF("tcp_client function start");

  int ret;
  int sock = 0, valread, client_fd;
  struct sockaddr_in serv_addr;
  char* hello = "Hello from esp32 client";
	char buf[RECV_BUF_SIZE];
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    LOG_ERR("Socket creation error");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(CONFIG_PORT_SERVER);
  LOG_INF("sin_port config");

  // Convert IPv4 and IPv6 addresses from text to binary
  // form
  if (inet_pton(AF_INET, CONFIG_IP_SERVER, &serv_addr.sin_addr)
      <= 0) {
    LOG_ERR("Invalid address/ Address not supported");
    return -1;
  }

  if ((client_fd
        = connect(sock, (struct sockaddr*)&serv_addr,
          sizeof(serv_addr)))
      < 0) {
    LOG_ERR("Connection Failed %d", client_fd);
    return -1;
  }
  else
  {
    LOG_INF("Connection OK %d", client_fd);
  }

  sendall(sock, hello, strlen(hello));
  LOG_INF("Hello message sent");

  /* valread = recv(sock, buf, sizeof(buf), MSG_DONTWAIT); */
  /* LOG_INF("%s\n", buffer); */

  /* do { */
  /*   valread = recv(sock, buf, sizeof(buf), MSG_DONTWAIT); */

		/* /1* No data or error. *1/ */
		/* if (valread == 0) { */
			/* ret = -EIO; */
			/* continue; */
		/* } else if (valread < 0) { */
			/* if (errno == EAGAIN || errno == EWOULDBLOCK) { */
				/* ret = 0; */
			/* } else { */
				/* ret = -errno; */
			/* } */
			/* continue; */
		/* } */

	/* } while (valread > 0); */


  // closing the connected socket
  close(client_fd);
  return 0;
}
