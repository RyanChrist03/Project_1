#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fonction.h"

void SaveIn_File(CREDENTIAL* User_Credentials)
{
	FILE* file_in = fopen("DataBase.dat", "wb");

	if (file_in == NULL)
	{
		fprintf(stderr, "Echec de l'overtur du fichier..\n");
		exit(-1);
	}
	fwrite(User_Credentials, sizeof(CREDENTIAL), 1, file_in);

	fclose(file_in);
}

void Read_File()
{
	CREDENTIAL* User_Credential = malloc(sizeof(CREDENTIAL));
	if (User_Credential == NULL)
	{
		fprintf(stderr, "Echec de l'allocation de la memoire..\n");
		exit(-1);
	}
	FILE* file_out = fopen("DataBase.dat", "rb");
	if (file_out == NULL)
	{
		fprintf(stderr, "ERROR: openning  of the is failed..\n");
		exit(EXIT_FAILURE);
	}
}
