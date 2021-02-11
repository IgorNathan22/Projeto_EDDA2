#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "quicksort.h"


//void testeArquivo();	
void cadastroMedico();
	
int main(void)
{
	float notas[6] = {8.0, 3.5, 7.2, 30.0, 15.5, 22.2}; 
	float * ptr_quick = notas;
	
	quick_sort(ptr_quick, 0, 4);
	mostra_notas(ptr_quick, 6);
	
	cadastroMedico();
//	testeArquivo();
	return(0);
}

//void testeArquivo() {
//	// Teste de criação de arquivo
//	typedef struct {
//		char nome[31];
//		float salario;
//	} Func;
//		
//	FILE *s;
//	Func f;
//
//	if((s=fopen("func.dat", "wb")) == NULL) {
//		printf("Arquivo não pode ser criado");
//		exit(1);
//	}
//	
//	printf("Digite ponto para finalizar o cadastramento: \n");
//	
//	while(1) {
//		printf("\nNome? "); fflush(stdin); gets(f.nome);
//		
//		if( !strcmp(f.nome, ".")) break;
//		
//		printf("\nSalario? "); fflush(stdin); scanf("%f", &f.salario);
//		
//		fwrite(&f, sizeof(Func),1,s);
//	}
//	
//	fclose(s);
//}

void cadastroMedico() {
	// Protótipo do cadastro de médicos
	typedef struct {
		char crm[6];
		char nome[42];
		char atividade[1];
		char ano_inicial[10];
		//	char ano_final[10];  não sei se é necessário, já que a "atividade" indica que ele já parou
		char cidade[37]; 
		char uf[2];
		// Adicionar a especialidade?
	} Medico;
	
	FILE *s2;
	Medico m;

	if((s2=fopen("MEDICOSCREMESP.csv", "r")) == NULL) {
		printf("Arquivo não pode ser criado");
		exit(1);
	}
	
}
