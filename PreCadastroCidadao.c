#include "bibliotecas\\funcoes_gerais.h"
#define ANO_ATUAL 2021

FILE *arqCsv;
FILE *arqDat;
Cidadao cid;
int i;
int qntlinhas;

//atoi()

void cadastrodefault(void){
	char data_aux[4+1];
	arqCsv = fopen("MUNICIPES.CSV","rb");
	if(arqCsv == NULL){
		printf("Erro ao abrir o arquivo MUNICIPES.CSV!\n");
		getch();
		exit(0);
	}
	
	arqDat = fopen("MUNICIPES.DAT","wb");
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
				printf("\nErro de leitrura!\n"); 
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
	printf("\nCadastro default concluído!\n");
	getch();
	fclose(arqCsv);
	fclose(arqDat);
}

void cadastrarcidadao(void){
	system("cls");
	arqDat = fopen("MUNICIPES.dat", "ab");
	if(arqDat == NULL){
		printf("\nErro na abertura do arquivo!\n");
		getch();
		exit(0);
	}
	printf("\n---------Cadastro do munícipe--------\n\n");
	
	printf("Nome completo	: ");
	fflush(stdin);
	gets(cid.nome);
	printf("\n----------------------\n");
	
	printf("\nData de nascimento: ");
	fflush(stdin);
	gets(cid.nasc);
	printf("\n----------------------\n");
	
	printf("\nIdade			: ");
	fflush(stdin);
	scanf("%i", &cid.idade);
	printf("\n----------------------\n");
	
	printf("\nCPF			: ");
	fflush(stdin);
	gets(cid.cpf);
	printf("\n----------------------\n");
	
	printf("\nPaís			: ");
	fflush(stdin);
	gets(cid.pais);
	printf("\n----------------------\n");
	
	printf("\nEstado		: ");
	fflush(stdin);
	gets(cid.estado);
	printf("\n----------------------\n");
	
	printf("\nMunícipio		: ");
	fflush(stdin);
	gets(cid.munic);
	printf("\n----------------------\n");
	
	printf("\nLogradouro	: ");
	fflush(stdin);
	gets(cid.lograd);
	printf("\n----------------------\n");
	
	printf("\nNúmero		: ");
	fflush(stdin);
	gets(cid.nro);
	printf("\n----------------------\n");
	
	printf("\nComplemento	: ");
	fflush(stdin);
	gets(cid.comp);
	printf("\n----------------------\n");
	
	printf("\nBairro		: ");
	fflush(stdin);
	gets(cid.bairro);
	printf("\n----------------------\n");
	
	printf("\nCEP			: ");
	fflush(stdin);
	gets(cid.cep);
	printf("\n----------------------\n");
	
	printf("\nEmail			: ");
	fflush(stdin);
	gets(cid.email);
	printf("\n----------------------\n");
	
	printf("\nTelefone		: ");
	fflush(stdin);
	gets(cid.tel);
	printf("\n----------------------\n");
	
	fwrite (&cid, sizeof(cid), 1, arqDat);
	if ( ferror(arqDat) ){
		printf("\nErro de leitura!\n"); 
		getch();
		exit(0);
	}
	printf("\nCadastro do %s concluído com sucesso!\n", cid.nome);
	getch();
	fclose(arqDat);
}

void consulta_dat_em_relatorio(void)
{
	FILE 				*Relat;
	int 				qtd_registros;
	int tamanhovetor;
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("MUNICIPES.DAT");
	qtd_registros = tamanhovetor/sizeof(Cidadao);
    
	arqDat = fopen ("MUNICIPES.DAT", "rb+");
	if ( arqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo MUNICIPES.DAT");
		getch();
		exit(0);
	}
	
	Relat = fopen ("MUNICIPES.TXT", "wt");
	if ( arqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo MUNICIPES.TXT");
		getch();
		exit(0);
	}
	
	printf ("\nGerando relatório: MUNICIPES.TXT...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "NOME COMPLETO                                        DATA NASCIMENTO         CPF    PAÍS      ESTADO             MUNICÍPIO                      LOGRADOURO                  NÚMERO COMPLEMENTO          BAIRRO        CEP           E-MAIL                                           CELULAR\n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(arqDat) )
	{
		fread (&cid, sizeof(cid), 1, arqDat);
				
		if ( !feof(arqDat) )
			fprintf (Relat,"\n[%-53s]\t[%-10s]\t[%3i]\t[%-11s]\t[%-10s]\t[%-20s]\t[%-30s]\t[%-30s]\t[%-14s]\t[%-14s]\t[%-20s]\t[%-8s]\t[%-50s]\t[%-10s]\n", 
			cid.nome, cid.nasc, cid.idade, cid.cpf, cid.pais, cid.estado, cid.munic, cid.lograd, cid.nro, cid.comp, cid.bairro, cid.cep, cid.email, cid.tel);
		if (feof(arqDat)) break; 		
	}
    fclose(arqDat);
    fclose(Relat);
    system ("notepad MUNICIPES.TXT");
}

int menu (int controle) {
	printf("\n\t\t\tPRÉ-CADASTRO CIDADÃO");
	printf("\n\n ---------------------------------------------------------------------");
	printf("\n\t\t1. Pré-cadastro de cidadãos default");
	printf("\n\t\t2. Cadastro de cidadão");
	printf("\n\t\t3. Consulta cidadões");
	printf("\n\t\t0. ENCERRAR");
	printf("\n\n\t\t Opção desejada: ");
	scanf("%i", &controle);
	switch(controle)
	{
		case 1 :
			cadastrodefault();
			return controle = 1;
		break;
		
		case 2 :
			cadastrarcidadao();
			return controle = 2;
		break;
			
		case 3 :
			consulta_dat_em_relatorio();
			return controle = 3;
		break;
		
		case 0 : 
			return controle = 0;
		default :
			printf("\nValor inválido\n");
			getch();
	}
}

int main(){
	
	setlocale (LC_ALL, "");
	int controle;
	controle = -1;
	while(controle != 0){
		system("cls"); system("color 90"); system("mode 80,20");
		controle = menu(controle);
	}
	return(0);
};
