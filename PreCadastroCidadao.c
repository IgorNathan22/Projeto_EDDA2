#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct{
	char nome[50+1];
//	int dia, mes, ano;
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

FILE *arqCsv;
FILE *arqDat;
Cidadao cid;

int i;
int qntlinhas;

#define ANO_ATUAL 2021

char data_aux[4+1];

//atoi()

void converter(void){
	arqCsv = fopen("MUNICIPES.CSV","r");
	if(arqCsv == NULL){
		printf("Erro ao abrir o arquivo MUNICIPES.CSV!\n");
		getch();
		exit(0);
	}
	
	arqDat = fopen("MUNICIPES.DAT","w");
	if(arqDat == NULL){
		printf("Erro ao abrir o arquivo MUNICIPES.DAT!\n");
		getch();
		exit(0);
	}
	while(!feof(arqCsv)){
		
		for(i = 0; i < 51; i++){
			cid.nome[i] = fgetc(arqCsv);
			if(cid.nome[i] == ';'){
				cid.nome[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 11; i++){
			cid.nasc[i] = fgetc(arqCsv);
			if(cid.nasc[i] == ';'){
				cid.nasc[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 5; i++) {
			data_aux[i] = cid.nasc[i+6];
		}
		
		cid.idade = ANO_ATUAL - atoi(data_aux);
		
		for(i = 0; i < 12; i++){
			cid.cpf[i] = fgetc(arqCsv);
			if(cid.cpf[i] == ';'){
				cid.cpf[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 21; i++){
			cid.pais[i] = fgetc(arqCsv);
			if(cid.pais[i] == ';'){
				cid.pais[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 26; i++){
			cid.estado[i] = fgetc(arqCsv);
			if(cid.estado[i] == ';'){
				cid.estado[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 51; i++){
			cid.munic[i] = fgetc(arqCsv);
			if(cid.munic[i] == ';'){
				cid.munic[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 51; i++){
			cid.lograd[i] = fgetc(arqCsv);
			if(cid.lograd[i] == ';'){
				cid.lograd[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 7; i++){
			cid.nro[i] = fgetc(arqCsv);
			if(cid.nro[i] == ';'){
				cid.nro[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 16; i++){
			cid.comp[i] = fgetc(arqCsv);
			if(cid.comp[i] == ';'){
				cid.comp[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 26; i++){
			cid.bairro[i] = fgetc(arqCsv);
			if(cid.bairro[i] == ';'){
				cid.bairro[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 11; i++){
			cid.cep[i] = fgetc(arqCsv);
			if(cid.cep[i] == ';'){
				cid.cep[i] = '\0';
				break;
			}
		}
		
		for(i = 0; i < 51; i++){
			cid.email[i] = fgetc(arqCsv);
			if(cid.email[i] == ';'){
				cid.email[i] = '\0';
				break;
			}
		}
		
	    i=0;  
	    do
	    {   
			cid.tel[i] = fgetc(arqCsv);
	        if ( ferror(arqCsv) ){
				printf("Deu RUIM"); 
				exit(0);
			} 
	        if ( cid.tel[i] == '\n' || cid.tel[i] == EOF ){
	        	break;
			} 
			i++;
	    }
	    while ( cid.tel[i] != '\n' && cid.tel[i] != EOF );
	    cid.tel[i] = '\0';
	    
		fwrite (&cid, sizeof(cid), 1, arqDat);
		if ( ferror(arqDat) ){
			printf("\nErro de leitura!\n"); 
			getch();
			exit(0);
		}
	}
	fclose(arqCsv);
	fclose(arqDat);
}

void mostraDAT (void)
{
	arqDat = fopen ("MUNICIPES.DAT", "r");
	printf("\n_________________________________________________________________________");
	printf("\n\n%-50s %-10s IDADE", "NOME", "NASCIMENTO");
	printf("\n_________________________________________________________________________");
	while ( !feof(arqDat) )
	{
		/* lê o DAT */
		fread (&cid, sizeof(cid), 1, arqDat);

		if (feof(arqDat)) break;
		/* Mostra registro lido */
	
		printf ("\n%-50s %-10s %d", cid.nome,cid.nasc,cid.idade);
		qntlinhas++;
	}
	fclose (arqDat);
	getch();
}

int main(){
	
	setlocale (LC_ALL, "");
	system("color 47"); system("mode 80,40");
	printf("\n\n\tPRÉ-CADASTRO DE CIDADÃOS");

	converter();
	mostraDAT();
	getch();
	return(0);
};
