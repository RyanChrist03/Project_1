#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client_inter.h"

#define LISTENING_PORT 4304
#define BUFFER_SIZE 1024
#define Ip_HOST "127.0.0.1"
int main(void)
{
#ifdef _WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		fprintf(stderr, "[Client]: Echec d'initialisation de WinSock!..\n ");
		exit(-1);
	}
#endif
	int Client_Socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ClientSocket_Address;
	ClientSocket_Address.sin_port   = LISTENING_PORT;
	ClientSocket_Address.sin_family = AF_INET ;
	int Inet_Return = inet_pton(AF_INET, Ip_HOST, &ClientSocket_Address.sin_addr);

	if (Inet_Return == -1)
	{
		fprintf(stderr, "[Client]: Address client Invalid..\n");
		exit(-1);
	}
	int ClientSocketAddress_length = sizeof(ClientSocket_Address);

	int Connection_Status = connect(Client_Socket, (struct sockaddr*)&ClientSocket_Address, (socklen_t)ClientSocketAddress_length);

	if (Connection_Status == -1)
	{
		fprintf(stderr, "[Client]: Echec de la connection au serveur..\n");
		exit(-1);
	}
	const char Message[] = "Bonjour Serveur, je suis le Client\n";

	int Sent_Return = send(Client_Socket, Message, strlen(Message), 0);

	if (Sent_Return == -1)
	{
		fprintf(stderr, "Echec de l'envoie du message au serveur...\n");
		exit(-1);
	}

	char Buffer[BUFFER_SIZE] = { 0 };

	int Recv_Return = recv(Client_Socket, Buffer, BUFFER_SIZE, 0);

	if (Recv_Return == -1)
	{
		fprintf(stderr, "Echec de la reception du message du Serveur..\n");
		exit(-1);
	}
	printf("(Serveur): %s\n", Buffer);

#ifdef _WIN32
	closesocket(Client_Socket);
	WSACleanup();
#endif
}