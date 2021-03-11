#include "bibliotecas\\funcoes_gerais.h"
#include "bibliotecas\\mensagens.h"
	
int main(void)
{
	setlocale (LC_ALL, "");
	int controle;
	controle = -1;
	while(controle != 0){
		system("cls"); system ("color B0"); system ("mode 70,15");
		controle = menu(controle);
	}
	return(0);
}	
