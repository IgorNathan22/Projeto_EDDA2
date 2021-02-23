#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{
	int crm;
	char nome[42+1];
	char status[2];
	char dt_admicao[10+1];
	char dt_final[10+1];
	char cidade[37+1];
	char estado[2+1];
	char especializacao[200+1];
}MEDICO;

FILE *arqDat;
MEDICO medico;

int main(){
	setlocale (LC_ALL, "");
	char usuario[42+1];
	int crmlogin;
	printf("-----------LOGIN DO MÉDICO---------\n\n");
	printf("USUÁRIO: \t");
	scanf("%[^\n]", &usuario);
	fflush(stdin);
	printf("\nCRM:     \t");
	scanf("%i", &crmlogin);
	fflush(stdin);
	printf("\nTeste \nNOME: \t [%s] \tCRM: [%i]", usuario, crmlogin);
	return(0);
};
