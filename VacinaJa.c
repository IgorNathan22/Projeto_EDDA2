#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void testeArquivo();	
void cadastroMedico();
	
int main(void)
{
	cadastroMedico();
//	testeArquivo();
	return(0);
}

void testeArquivo() {
	// Teste de cria��o de arquivo
	typedef struct {
		char nome[31];
		float salario;
	} Func;
		
	FILE *s;
	Func f;

	if((s=fopen("func.dat", "wb")) == NULL) {
		printf("Arquivo n�o pode ser criado");
		exit(1);
	}
	
	printf("Digite ponto para finalizar o cadastramento: \n");
	
	while(1) {
		printf("\nNome? "); fflush(stdin); gets(f.nome);
		
		if( !strcmp(f.nome, ".")) break;
		
		printf("\nSalario? "); fflush(stdin); scanf("%f", &f.salario);
		
		fwrite(&f, sizeof(Func),1,s);
	}
	
	fclose(s);
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
	
	FILE *s2;
	Medico m;

	if((s2=fopen("MEDICOSCREMESP.csv", "r")) == NULL) {
		printf("Arquivo n�o pode ser criado");
		exit(1);
	}
	
	
	
}
