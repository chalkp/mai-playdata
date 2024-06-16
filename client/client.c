#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

#define recv_len 69420
#define sent_len 420

#define server_path "./mai-server"

int main() {
	struct sockaddr_un server = { AF_UNIX, server_path };
	int sock;

  sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == -1) {
		fprintf(stderr, "client: socket() failed\n");
		return 1;
	}
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
		fprintf(stderr, "client: connect() failed\n");
		return 1;
	}

	printf("client: server connected\n");
	char send_msg[sent_len];
	char recv_msg[recv_len];
	memset(send_msg, 0, sizeof(sent_len));

	while (printf("> "), fgets(send_msg, sent_len, stdin), !feof(stdin)) {
		memset(recv_msg, 0, sizeof(recv_len));

		ssize_t recv_size;
    if (send(sock, send_msg, sizeof(send_msg), 0) == -1 ) {
			printf("client: send() failed\n");
		}

    recv_size = recv(sock, recv_msg, recv_len, 0);

		if (recv_size > 0) {
			printf("server:%s\n", recv_msg);
      continue;
		}
    if (recv_size < 0) {
      fprintf(stderr, "what the fuck?\n");
    } else {
      fprintf(stderr, "server closed\n");
      close(sock);
      break;
    }
    memset(send_msg, 0, sizeof(sent_len));
		
	}

	printf("client: exiting...\n");

	return 0;
}