#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

#include "rating/rating.h"

#define recv_len 69420
#define sent_len 420

#define server_path "./mai-server"

int run_server();
void read_mai_rating();

int main() {
	return run_server();	
}

int run_server() {
	struct sockaddr_un server = { AF_UNIX, server_path };
	int server_sock;
	bool running = true;

	server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
	unlink(server.sun_path);
	if (server_sock == -1) {
		fprintf(stderr, "socket() error\n");
		return 1;
	}
	if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) != 0) {
		fprintf(stderr, "bind() error\n");
		return 1;
	}
	if (listen(server_sock, 10) != 0) {
		fprintf(stderr, "listen() error\n");
	}

	while (running) {
		int client_sock;
		struct sockaddr_un client;
		socklen_t sock_len = 0;
		printf("waiting for connection...\n");

		client_sock = accept(server_sock, (struct sockaddr *)&client, &sock_len);
		if (client_sock == -1) {
			fprintf(stderr, "accept() error\n");
			return 1;
		}

		printf("connected to client\n");

		ssize_t recv_size;
		char recv_msg[recv_len];
		char send_msg[sent_len];

		do {
			memset(recv_msg, 0, sizeof(recv_msg));
			memset(send_msg, 0, sizeof(send_msg));
			recv_size = recv(client_sock, recv_msg, recv_len, 0);

			if (recv_size < 0) {
				fprintf(stderr, "what the fuck?\n");
				return 1;
			}
			printf("received: %s\n", recv_msg);

			if (strstr(recv_msg, "quit") != 0) {
				printf("quitting...\n");
				running = false;
				recv_size = 0;
			} else if (strstr(recv_msg, "ratings") != 0) {
				read_mai_rating(send_msg);
			} else {
				strcpy(send_msg, "commands\nratings: prints chalk's rating history\nquit: quits. :)");
			}

			if (send(client_sock, send_msg, sizeof(send_msg), 0) == -1) {
				fprintf(stderr, "send() error\n");
			}
			memset(recv_msg, 0, sizeof(recv_msg));
			memset(send_msg, 0, sizeof(send_msg));
			
		} while(recv_size > 0);

		close(client_sock);
	}
	
	return 0;
}

void read_mai_rating(char *send_msg) {
	Rating* ratings = NULL;
	size_t size = read_rating_from_file("./ratings", &ratings);
	int prev_rating = ratings[0].rating;
	strcat(send_msg, "\nchalk's rating history:\n");
	for (size_t i=0; i<size; i++) {
		char buffer[69];
		sprintf(buffer, "%d/%d/%d : %d (+%d)\n",
			ratings[i].date.year,
			ratings[i].date.month,
			ratings[i].date.day,
			ratings[i].rating,
			ratings[i].rating-prev_rating
		);
		prev_rating = ratings[i].rating;
		strcat(send_msg, buffer);
	}
	free(ratings);
}
