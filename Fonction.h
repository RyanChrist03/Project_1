#ifndef FONCTION_H
#define FONCTION_H

#define String_len 256

typedef struct Info_Person
{
	char FIRST_NAME[String_len];
	char LAST_NAME[String_len];
}USER;

// define the user credential maybe must change the name of my struct maybe....

typedef struct USER_Credential
{
	USER User_Name;
	char PASSWORD[String_len];
	char CELLULAR[String_len];
	char POSTA_ELLETRONICA[String_len];

}CREDENTIAL;


// prototypes definition

USER* Create_User(USER* user);
CREDENTIAL Create_UserCredential();
bool Cellular_Verification(CREDENTIAL* user_credential);
bool Password_verification(CREDENTIAL* user_credential);
bool Credentials_Verification(CREDENTIAL* user_credential, char* s1, char* s2);
char* strtolower(char* src);

void Connection_Session(CREDENTIAL* user_credential);
#endif