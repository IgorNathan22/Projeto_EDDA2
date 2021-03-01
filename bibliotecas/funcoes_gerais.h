#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define true 0
#define false -1

FILE      *DAT;
int       i, cont=0;

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
