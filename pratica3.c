// Aluno: Joao Pedro Thim Tarossi
// Lista de exercicios 3 - EDII

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 30228
//30228
#define MAX2 1000000

typedef struct
{
	int id;
	char estado[3];
	char municipio[20];
	char rede[10];
	float mediaCieNat;
	float mediaCieHum;
	float mediaLin;
	float mediaMat;
	float mediaRed;
} Escolas;
Escolas escolas[MAX];

clock_t inicio, fim;
unsigned long int tempo;

FILE *DadosEnem;
FILE *Indices;

int cont = 0;
char *token, *content[MAX], line[200];
int vetorInd[MAX2], cont2=0, max = MAX2;
char aux[10];

void InsertionSort(Escolas escolas[], int n){
	int menor, i, j;
	Escolas aux;
	for(i=0; i<n-1; i++){
		menor = i;
		for(j=i+1; j<n; j++){
			if(escolas[j].id<escolas[menor].id){
				menor = j;
			}
		}
		if(i != menor){
			aux = escolas[i];
			escolas[i] = escolas[menor];
			escolas[menor] = aux;
		}
	}
}

void BuscaBinaria(Escolas escolas[], int chave){
	int dir = MAX-1, esq = 0, encontrado = 0, meio;
	while(esq<=dir && encontrado==0){
		meio = (esq+dir)/2;
		if(escolas[meio].id==chave){
			encontrado = 1;
		}else if(chave<escolas[meio].id){
			dir = meio-1; 
		}else{
			esq = meio+1;
		}
	}
	/*
		printf("\n\nID: %i", escolas[meio].id);
		printf("\nEstado: %s", escolas[meio].estado);
		printf("\nMunicipio: %s", escolas[meio].municipio);
		printf("\nRede: %s", escolas[meio].rede);
		printf("\nMedia Ciencias Naturais: %.7f", escolas[meio].mediaCieNat);
		printf("\nMedia Ciencias Humanas: %.7f", escolas[meio].mediaCieHum);
		printf("\nMedia Linguagem: %.7f", escolas[meio].mediaLin);
		printf("\nMedia Matematica: %.7f", escolas[meio].mediaMat);
		printf("\nMedia Redacao: %.7f", escolas[meio].mediaRed);
	*/
}

void BuscaSequencial(Escolas escolas[], int chave){
	int i = 0;
	while(chave != escolas[i].id && i<MAX){
		i++;
	}
	/*
		printf("\n\nID: %i", escolas[i].id);
		printf("\nEstado: %s", escolas[i].estado);
		printf("\nMunicipio: %s", escolas[i].municipio);
		printf("\nRede: %s", escolas[i].rede);
		printf("\nMedia Ciencias Naturais: %.7f", escolas[i].mediaCieNat);
		printf("\nMedia Ciencias Humanas: %.7f", escolas[i].mediaCieHum);
		printf("\nMedia Linguagem: %.7f", escolas[i].mediaLin);
		printf("\nMedia Matematica: %.7f", escolas[i].mediaMat);
		printf("\nMedia Redacao: %.7f", escolas[i].mediaRed);
	*/
}

int main()
{
	DadosEnem = fopen("DadosEnem.txt", "r");
	Indices = fopen("indices.txt", "r");

	if (DadosEnem == NULL || Indices == NULL)
	{
		printf("\n Houve um erro ao abrir o arquivo.");
	}
	else
	{
		// ATRIBUINDO VALORES DO ARQUIVO
		
		inicio = clock();
		while (!feof(Indices) && cont2 < MAX2)
		{
			fgets(aux, sizeof aux, Indices);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			vetorInd[cont2] = atoi(aux);
			cont2++;
		}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo de Cadastro Indice: %lu milissegundos\n",tempo);
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
		while (!feof(DadosEnem))
		{
			while (fgets(line, sizeof line, DadosEnem) != NULL && cont<MAX)
			{
				content[cont] = strdup(line);
				token = strtok(content[cont], ";");
				
					escolas[cont].id = atoi(token);

					token = strtok(NULL, ";");
					strcpy(escolas[cont].estado, token);

					token = strtok(NULL, ";");
					strcpy(escolas[cont].municipio, token);				

					token = strtok(NULL, ";");
					strcpy(escolas[cont].rede, token);

					token = strtok(NULL, ";");
					escolas[cont].mediaCieNat = atof(token);

					token = strtok(NULL, ";");
					escolas[cont].mediaCieHum = atof(token);

					token = strtok(NULL, ";");
					escolas[cont].mediaLin = atof(token);

					token = strtok(NULL, ";");
					escolas[cont].mediaMat = atof(token);

					token = strtok(NULL, ";");
					escolas[cont].mediaRed = atof(token);

					cont++;
			}
		}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo de Cadastro Escolas: %lu milissegundos\n",tempo);
		printf("-----------------------------------------------------------------------");
	
		int n = MAX;
		int chave;
		int i;
		inicio = clock();
			InsertionSort(escolas, n);
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo InsertionSort: %lu milissegundos\n",tempo);
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<100;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 100 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<100;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 100 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<500;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 500 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<500;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 500 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<1000;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 1000 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<1000;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 1000 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<5000;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 5000 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<5000;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 5000 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<10000;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 10000 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<10000;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 10000 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<50000;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 50000 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<50000;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 50000 buscas: %lu milissegundos\n",tempo);
		
		printf("-----------------------------------------------------------------------");
		
		inicio = clock();
			for(i=0;i<1000000;i++){
				chave = vetorInd[i];
				BuscaBinaria(escolas, chave);
			}
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaBinaria para 1000000 buscas: %lu milissegundos",tempo);
		
		
		inicio = clock();
		for(i=0;i<1000000;i++){
				chave = vetorInd[i];
				BuscaSequencial(escolas, chave);
			}	
		fim = clock();
		tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
		printf("\nTempo BuscaSequencial para 1000000 buscas: %lu milissegundos\n",tempo);
	}
	
	// FECHANDO OS ARQUIVOS
	fclose(DadosEnem);
	fclose(Indices);
}
