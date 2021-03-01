#include "VacinaJa.h"

FILE *arqCsv;
FILE *arqDat;
MEDICO medico;
int i;
int contTeste;
int qntlinhas;

void converter(void){
	char aux[6+1];
	contTeste = 0;
	arqCsv = fopen("MEDICOSCREMESP.CSV","r");
	if(arqCsv == NULL){
		printf("Erro ao abrir o arquivo MEDICOSCREMESP.CSV!\n");
		getch();
		exit(0);
	}
	
	arqDat = fopen("MEDICOSCREMESP.DAT","w");
	if(arqDat == NULL){
		printf("Erro ao abrir o arquivo MEDICOSCREMESP.DAT!\n");
		getch();
		exit(0);
	}
	while(!feof(arqCsv)){
		
		//printf("Convertendo o CRM\n");
		
		for(i = 0; i < 7;i++){
			aux[i] = '\0';
		}
		
		for(i = 0; i < 7; i++){
			aux[i] = fgetc(arqCsv);
			if(aux[i] == ';'){
				aux[i] = '\0';
			}
		}
		aux[--i] ='\0';
		medico.crm = atoi(aux);
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
	    
		fwrite (&medico, sizeof(medico), 1, arqDat);
		if ( ferror(arqDat) ){
			printf("\nErro de leitura!\n"); 
			getch();
			exit(0);
		}
		qntlinhas++;
	}
	fclose(arqCsv);
	fclose(arqDat);
}

void ordenarMedicos(void){
	int *vetorcrm;
	vetorcrm = (int *) malloc(qntlinhas * sizeof(int));
	arqDat = fopen("MEDICOSCREMESP.DAT", "r+");
	if (arqDat == NULL){
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO MEDICOSCREMESP.DAT  ");
		getch();
		exit(0);
	}
	i = 0;
	while( !feof(arqDat)){
		fread(&medico, sizeof(medico), 1, arqDat);
		if ( ferror(arqDat) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO MEDICOSCREMESP.DAT  ");
			getch();
			exit(0);
		}
		if (feof(arqDat))
		{
			break;
		} 
		vetorcrm[i] = medico.crm;
		printf("Nome [%s] [%6.i] indice = %i\n", medico.nome,vetorcrm[i], i );
		i++;
	}
	for( i = 0; i > qntlinhas; i++){
		printf("[%6.i]\n", vetorcrm[i]);
	}
}

void mostraDAT (void)
{
	arqDat = fopen ("MEDICOSCREMESP.DAT", "r");
	if (arqDat==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO MEDICOSCREMESP.DAT  ");
		getch();
		exit(0);
	}
	
	printf ("\n----- CONTEÚDO DE MEDICOSCREMESP.DAT ------");
	while ( !feof(arqDat) )
	{
		fread (&medico, sizeof(medico), 1, arqDat);
		if ( ferror(arqDat) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO MEDICOSCREMESP.DAT  ");
			getch();
			exit(0);
		}
		if (feof(arqDat))
		{
			break;
		} 
		printf ("\n[%6.i] [%s] [%s] [%s] [%s] [%s] [%s] [%s]", medico.crm, medico.nome, medico.status,  medico.dt_admicao, medico.dt_final, medico.cidade, medico.estado, medico.especializacao);
		
	}
	fclose (arqDat);
}

int main(){
	setlocale (LC_ALL, "");
	system ("mode 170,50");
	converter();
	mostraDAT();
	//ordenarMedicos();
	printf("\nOperação concluida! \nLinhas convertidas: %i\n", qntlinhas);
	printf("\nContTeste = %i", contTeste);
	getch();
	return(0);
};
