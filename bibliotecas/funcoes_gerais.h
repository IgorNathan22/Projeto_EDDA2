#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>


#define true 0
#define false -1

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

int lerQtdRegistros(char file_name[]) {

	DAT = fopen (file_name, "r");
	if (DAT == NULL) {
		return 0;
	}
	fseek(DAT, 0L, SEEK_END);
	long int res = ftell(DAT);
	fclose(DAT);
	return res;
}

void  errolerCSV (void)
{
	system ("cls");
	printf ("\n  ERRO AO LER ARQUIVO PRODUTOS.CSV  ");
	getch();
	exit(0);
}

void errogravarDAT (void)
{
	system ("cls");
	printf ("\n  ERRO AO GRAVAR NO ARQUIVO PRODUTOS.DAT  ");
	getch();
	exit(0);
}
