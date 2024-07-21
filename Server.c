#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client_inter.h"
#define LISTENING_PORT 4304
#define PENDING_QUEU_MAXLength 1
#define BUFFER_SIZE 1024
int main(void)
{
#ifdef _WIN32
	WSADATA wsa;
	WORD wVersionRequested;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsa);
	if (err != 0)
	{
		fprintf(stderr, "(serveur): Echec d'initialisation de WinSock! \n");
		exit(1);
	}
#endif // _WIN32
	int Server_Socket = socket(AF_INET, SOCK_STREAM, 0); // creation du Socket
	if (Server_Socket == -1)
	{
		fprintf(stderr, "(serveur): Echec de la creation du socket..\n");
		exit(1);
	}
	struct sockaddr_in socket_Address;
	socket_Address.sin_family = AF_INET;
	socket_Address.sin_port = LISTENING_PORT;
	socket_Address.sin_addr.s_addr = INADDR_ANY;

	int SocketAddress_Length = sizeof(socket_Address);

	int Bind_Return = bind(Server_Socket, (struct sockaddr*)&socket_Address, SocketAddress_Length);
	if (Bind_Return == -1)
	{
		fprintf(stderr, "(serveur): Echer de liaison du socket...\n");
		exit(1);
	}

	if (listen(Server_Socket, PENDING_QUEU_MAXLength) == -1)
	{
		fprintf(stderr, "(server): Echec de demarage..\n");
		exit(-1);
	}
	puts("En attente de nouvelles connections..\n");
	int Connected_Socket = accept(Server_Socket, (struct sockaddr*)&socket_Address, (socklen_t*)&SocketAddress_Length);

	if (Connected_Socket == -1)
	{
		fprintf(stderr, "Echec de l'etablissement de la connection..\n");
		exit(-1);
	}

	char Buffer[BUFFER_SIZE] = {0};
	int Recived_Bytes = recv(Connected_Socket, Buffer, BUFFER_SIZE, 0);

	if (Recived_Bytes == -1)
	{
		fprintf(stderr, "Echec de la reception du message du Client..\n");
		exit(-1);
	}
	printf("[Client]: %s\n", Buffer);

	const char Message[] = "je suis le message du serveur\n";
	int Send_Bytes = send(Connected_Socket, Message, strlen(Message), 0);

	if (Send_Bytes == -1)
	{
		fprintf(stderr, "Echec de l'envoi du message au Client..\n");
		exit(-1);
	}
#ifdef _WIN32
	closesocket(Connected_Socket);
	closesocket(Server_Socket);
	WSACleanup();
#endif
	return 0;
}
