#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

FILE      *DAT;
int       i, cont=0;

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

typedef struct{
	char nome[50+1];
	char nasc[10+1];
	int idade;
	char cpf[11+1];
	char pais[20+1];
	char estado[25+1];
	char munic[50+1];
	char lograd[50+1];
	char nro[6+1];
	char comp[15+1];
	char bairro[25+1];
	char cep[10+1];
	char email[50+1];
	char tel[15+1];
}Cidadao;

int menuprincipal (int controle) {
	printf("\n\t\t\tADM VACINA");
	printf("\n\n ---------------------------------------------------------------------");
	printf("\n\t\t1. Pré-cadastro de cidadãos");
	printf("\n\t\t2. Cadastro de vacinas");
	printf("\n\t\t3. Atendimento");
	printf("\n\t\t0. ENCERRAR");
	printf("\n\n\t\t Opção desejada: ");
	scanf("%i", &controle);
	switch(controle)
	{
		case 1 :
			system("PreCadastroCidadao.exe");
			return controle = 1;
		break;
		
		case 2 :
			system("CadastroVacinaLote.exe");
			return controle = 2;
		break;
			
		case 3 :
			printf("\n\tEM CONSTRUÇÃO\n");
			system("");
			getch();
			return controle = 3;
		break;
		
		case 0 : 
			return controle = 0;
		default :
			printf("\nValor inválido\n");
			getch();
	}
}

long int findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r");   
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
    fseek(fp, 0L, SEEK_END); 
    // calculating the size of the file 
    long int res = ftell(fp); 
    // closing the file 
    fclose(fp); 
    return res; 
}

