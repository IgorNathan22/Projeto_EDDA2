#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct{
	char crm[6+1];
	char nome[42+1];
	char status[2];
	char dt_admicao[10+1];
	char dt_final[10+1];
	char cidade[37+1];
	char estado[2+1];
	char especializacao[80+1];
}MEDICO;

FILE *arqCsv;
FILE *arqDat;
MEDICO medico;
int i;
int j;
int count = 0;

void converter(void){
	char especialaux[80+1];
		arqCsv = fopen("MEDICOSCREMESP.CSV","r");
	if(arqCsv == NULL){
		printf("Erro ao abrir o arquivo MEDICOSCREMESP.CSV!\n");
		getch();
		exit(0);
	}
	
	arqDat = fopen("MEDICOS.DAT","w");
	if(arqDat == NULL){
		printf("Erro ao abrir o arquivo MEDICOS.DAT!\n");
		getch();
		exit(0);
	}
	while(!feof(arqCsv)){
		
		//printf("Convertendo o CRM\n");
		for(i = 0; i < 7; i++){
			medico.crm[i] = fgetc(arqCsv);
			if(medico.crm[i] == ';'){
				medico.crm[i] = '\0';
			}
		}
		//printf("\nConvertendo o nome\n");
		for(i = 0; i < 43; i++){
			medico.nome[i] = fgetc(arqCsv);
			if(medico.nome[i] == ';'){
				medico.nome[i] = '\0';
			}
		}
		//printf("\nConvertendo o status\n");
		for(i = 0; i < 2; i++){
			medico.status[i] = fgetc(arqCsv);
			if(medico.status[i] == ';'){
				medico.status[i] = '\0';
			}
		}
		//printf("\nConvertendo a dt_admição\n");
		for(i = 0; i < 11; i++){
			medico.dt_admicao[i] = fgetc(arqCsv);
			if(medico.dt_admicao[i] == ';'){
				medico.dt_admicao[i] = '\0';
			}
		}
		//printf("\nConvertendo a dt_final\n");
		for(i = 0; i < 11; i++){
			medico.dt_final[i] = fgetc(arqCsv);
			if(medico.dt_final[i] == ';'){
				medico.dt_final[i] = '\0';
			}
		}
		//printf("\nConvertendo a cidade\n");
		for(i = 0; i < 38; i++){
			medico.cidade[i] = fgetc(arqCsv);
			if(medico.cidade[i] == ';'){
				medico.cidade[i] = '\0';
			}
		}
		//printf("\nConvertendo o estado\n");
		for(i = 0; i < 3; i++){
			medico.estado[i] = fgetc(arqCsv);
			if(medico.estado[i] == ';'){
				medico.estado[i] = '\0';
			}
		}
		
		//printf("\nConvertendo a especialização\n");
		
		for (i=0; i<81; i++){
			especialaux[i] = '\0';
		}
		  // trata o custoaux
		  // "limpa" o custoaux preenchendo-o com '\0' NULL TERMINATOR
	    i=0;  
	    
	    do
	    {   
			medico.especializacao[i] = fgetc(arqCsv);
	        if ( ferror(arqCsv) ){
				printf("Deu RUIM"); 
				exit(0);
			} 
	        //printf ("Teste");
	        if ( medico.especializacao[i] == '\n' || medico.especializacao[i] == EOF ){
	        	break;
			} 
			i++;
	    }
	    while ( medico.especializacao[i] != '\n' && medico.especializacao[i] != EOF );
	    medico.especializacao[i] = '\0';
		/*
		//printf ("\nTeste2\n");
		count = 0;
		//printf("\n %i i || %i count", i, count);
		if(i != -1){
			while (count != i){
				medico.especializacao[count] = especialaux[count];
				count++;
			}
		}
		//printf("\n %i i || %i count", i, count);
		
	    //printf("\nConverção especial concluida\n");
	    */
		fwrite (&medico, sizeof(medico), 1, arqDat);
		if ( ferror(arqDat) ){
			printf("\nErro de leitura!\n"); 
			getch();
			exit(0);
		}
		//printf("\nEscrita da linha concluida\n");

	}
	//printf("\nTESTETESTETESTE\n");
	fclose(arqCsv);
	fclose(arqDat);
}

void mostraDAT (void)
{
	arqDat = fopen ("MEDICOS.DAT", "r");
	if (arqDat==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO PRODUTOS.DAT  ");
		getch();
		exit(0);
	}
	
	printf ("\n----- CONTEÚDO DE MEDICOS.DAT ------");
	//printf ("\nCOD    NOME DO PRODUTO     CUSTO (R$)");
	//printf ("\n-------------------------------------");
	while ( !feof(arqDat) )
	{
		/* lê o DAT */
		fread (&medico, sizeof(medico), 1, arqDat);
		if ( ferror(arqDat) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO PRODUTOS.DAT  ");
			getch();
			exit(0);
		}
		if (feof(arqDat)) break;
		/* Mostra registro lido */
		printf ("\n[%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s]", medico.crm, medico.nome, medico.status,  medico.dt_admicao, medico.dt_final, medico.cidade, medico.estado, medico.especializacao);
	}
	fclose (arqDat);
	getch();
}

int main(){

	setlocale (LC_ALL, "");
	converter();
	mostraDAT();
	printf("\nOperação concluida!\n");
	getch();
	return(0);
};
