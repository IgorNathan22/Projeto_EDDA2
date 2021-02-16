#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "quicksort.h"

//void testeArquivo();	
void cadastroMedico();
#define MAX 5	

int main(void)
{
//	int *tamanho_vetor = 6;
//	float notas[6] = {8.0, 3.5, 7.2, 30.0, 15.5, 22.2}; 
//	float * ptr_quick = notas;
//	
//	quick_sort(ptr_quick, 0, MAX - 1);
//	mostra_notas(ptr_quick, MAX);
	
//	cadastroMedico();
	testeArquivo();
	return(0);
}

void testeArquivo() {
	int c;
	FILE *file;
	file = fopen("MEDICOSCREMESP.csv", "r");
	if (file) {
	  while ((c = getc(file)) != EOF) putchar(c);
  	fclose(file);
	}	
}

void cadastroMedico() {
	// Prot�tipo do cadastro de m�dicos
	typedef struct {
		char crm[6];
		char nome[42];
		char atividade[1];
		char ano_inicial[10];
		//	char ano_final[10];  n�o sei se � necess�rio, j� que a "atividade" indica que ele j� parou
		char cidade[37]; 
		char uf[2];
		// Adicionar a especialidade?
	} Medico;
	
	FILE *s;
	Medico m;

	if((s=fopen("MEDICOSCREMESP.csv", "r")) == NULL) {
		printf("Arquivo n�o pode ser lido");
		exit(1);
	}
	
}
