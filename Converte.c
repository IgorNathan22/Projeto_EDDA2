#include "bibliotecas\\funcoes_gerais.h"

FILE *arqCsv;
FILE *arqDat;
MEDICO medico;
int i;
int tamanhovetor;
int qntregistros;
void envia_vet_ordenado_dat(MEDICO * vetormedico);

void troca (MEDICO *A, MEDICO *B) 
{
  MEDICO aux = *A; 
  *A = *B; 
  *B = aux;
}

int particiona (MEDICO * vetor, int ini, int pivo) 
{    
    int   i;
    int   p_maior = ini; /* a posição do maior é a do início do vetor */    
    
    for ( i=ini; i<pivo; i++ ) /* percorre o vetor da posição ini até a do pivô */
    {        
       if ( vetor[i].crm < vetor[pivo].crm ) /*se o elemento da posição atual for menor que o pivô...*/
       {            
            troca(  &vetor[i], &vetor[p_maior]); /*...troca o atual com o maior */
            p_maior++; /* o maior avança uma posição */
       }    
   }     
   /* percorrido o vetor, o pivô troca de posição com a do maior elemento... */
   troca(  &vetor[p_maior], &vetor[pivo]); 
   return p_maior; /* ... e o maior elemento passa a ser o novo pivô */ 
}

void quick_sort	(MEDICO * vetor, int ini, int fim) 
{    
   int pivo;
   if ( ini<fim ) /* Caso base */ 
   {        
        pivo = particiona ( vetor, ini, fim ); /* Particiona o vetor*/ 
        quick_sort( vetor, ini,    pivo-1 );    /* Ordena do início do vetor até antes do pivô */
        quick_sort( vetor, pivo+1, fim);      /* Ordena desde após o pivô até o fim do vetor */
   } 
}

void converter(void){
	char aux[6+1];
	//char ch;
	arqCsv = fopen("MEDICOSCREMESP.CSV","r");
	if(arqCsv == NULL){
		printf("Erro ao abrir o arquivo MEDICOSCREMESP.CSV!\n");
		getch();
		exit(0);
	}
	
	arqDat = fopen("MEDICOSCREMESP.DAT","wb");
	if(arqDat == NULL){
		printf("Erro ao abrir o arquivo MEDICOSCREMESP.DAT!\n");
		getch();
		exit(0);
	}
	while(!feof(arqCsv)){
		
		//printf("Convertendo o CRM\n");
		/*
		i=0;
	    do
	    {
	    	ch = fgetc(arqCsv);
	   		aux[i] = ch;
	   		i++;
	    }
	    while ( ch != ';'); 
        aux[--i] = '\0';
        medico.crm = atoi(aux);
        */
		for (i=0; i<7; i++) 
		  aux[i] = '\0';
		
        for(i= 0; i< 7; i++){
        	aux[i] = fgetc(arqCsv);
        	if(aux[i] == ';'){
        		aux[i] = '\0';
			}
		}
		aux[--i] = '\0';
        medico.crm = atoi(aux);
        //printf ("\naux = [%s] medico.crm = [%i]", aux, medico.crm); getch();
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
				printf("\nErro de leitura!"); 
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
	}
	fclose(arqCsv);
	fclose(arqDat);
}

void ordenarMedicos(void){
	MEDICO * vetormedico;
	tamanhovetor = findSize("MEDICOSCREMESP.DAT");
	qntregistros = tamanhovetor/sizeof(MEDICO);
	vetormedico = (MEDICO *) malloc (qntregistros * sizeof (MEDICO)); 
    if (vetormedico == NULL)
    {
        printf ("malloc devolveu NULL!\nNão foi possível alocar %ld bytes.", 
		(qntregistros * sizeof (MEDICO)) );
        getch();
        exit (EXIT_FAILURE);
    }
    /*
    else
    {
    	printf ("\nAlocação de memória bem-sucedida!");
    	printf ("\nmalloc alocou %ld bytes", (qntregistros * sizeof (MEDICO)) );
    	printf ("\nO arquivo MEDICOSCREMESP.DAT possui %ld bytes", tamanhovetor);
    	printf ("\nO arquivo MEDICOSCREMESP.DAT possui %ld registros", qntregistros);
    	Sleep(2000);
	}*/
	arqDat = fopen("MEDICOSCREMESP.DAT", "rb+");
	if (arqDat == NULL){
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO MEDICOSCREMESP.DAT  ");
		getch();
		exit(0);
	}
	i = 0;
	while( !feof(arqDat)){
		fread(&vetormedico[i], sizeof(vetormedico[i]), 1, arqDat);
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
		//vetormedico[i] = medico.crm;
		//printf("Nome [%s] [%6.i] indice = %i\n", medico.nome, medico.crm, i ); //DEBUG
		i++;
	}
	/*for( i = 0; i < qntlinhas; i++){
		printf("[%6.i]\n", vetorcrm[i]); DEBUG
	}*/
	quick_sort(vetormedico, 0, qntregistros-1);
	envia_vet_ordenado_dat(vetormedico);
}

void mostraDAT (void)
{
	arqDat = fopen ("MEDICOSCREMESP.DAT", "rb");
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

void envia_vet_ordenado_dat (MEDICO	* vetormedico)
{
    long int i;
	arqDat = fopen ("MEDICOSCREMESP.DAT", "wb+");
	if ( arqDat==NULL )
	{	system ("cls");
		printf ("Erro ao gerar arquivo MEDICOSCREMESP.DAT ordenado!");
		getch();
		exit(0);
	}
    for (i=0; i<qntregistros; i++)
    {
    	fwrite (&vetormedico[i], sizeof(vetormedico[i]), 1, arqDat);
    	if ( ferror(arqDat) )
   	    {  system ("cls");
		   printf ("Erro ao gravar no arquivo MEDICOSCREMESP.DAT no registro %li!", i);
		   getch();
		   exit(0);	
		}
	}
	fclose(arqDat);
	printf ("\nMEDICOSCREMESP.DAT ordenado com sucesso!");
	free(vetormedico);
	getch();
}

void consulta_dat_em_relatorio(void)
{
	FILE 				* ArqDat, *Relat;
	MEDICO				medico;
	long int 			cont=0;
	int 				qtd_registros;
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("MEDICOSCREMESP.DAT");
	qtd_registros = tamanhovetor/sizeof(MEDICO);
    qntregistros  = qtd_registros;
    
	ArqDat = fopen ("MEDICOSCREMESP.DAT", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo MEDICOSCREMESP.DAT");
		getch();
		exit(0);
	}
	
	Relat = fopen ("MEDICOSCREMESP.TXT", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo MEDICOSCREMESP.TXT");
		getch();
		exit(0);
	}
	printf ("\nGerando relatório: MEDICOSCREMESP.TXT...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         COD	         NOME                                                                                                   \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(medico.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&medico, sizeof(medico), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-100s]", 
			(int)cont, medico.crm, medico.nome);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
    system ("notepad MEDICOSCREMESP.TXT");
    getch();
}

int main(){
	setlocale (LC_ALL, "");
	system ("mode 170,50");
	converter();
	ordenarMedicos();
	//consulta_dat_em_relatorio();
	//mostraDAT();
	printf("\nOperação concluida! \nLinhas convertidas: %i\n", qntregistros);
	getch();
	return(0);
};
