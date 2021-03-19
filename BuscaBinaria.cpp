#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};




int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	long  primeiro, meio, ultimo, tamanho, posicao;

	if (argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat", "r");
	fseek(f, 0, SEEK_END);
	tamanho = ftell(f);
	rewind(f); // fseek(f,0,SEEK_SET);
	printf("\nTamanho do Arquivo: %ld\n", tamanho);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", tamanho/ sizeof(Endereco));
	primeiro = 0;
	ultimo = (tamanho / sizeof(Endereco)) - 1;
	meio = (primeiro + ultimo) / 2;
	posicao = -1;


	while (ftell(f) != posicao) 
	{
		posicao = ftell(f);
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		fread(&e, sizeof(Endereco), 1, f);


		 if (strncmp(argv[1], e.cep, 8) < 0) {
			ultimo = meio;
			meio = (primeiro + ultimo) / 2;
		}
		else if (strncmp(argv[1], e.cep, 8) > 0) {
			primeiro = meio;
			meio = (primeiro + ultimo) / 2;
		} 
		else if (strncmp(argv[1], e.cep, 8) == 0) {
			printf("\nCEP Encontrado!!! B^) : \n\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
			break;
		}
	}
	if (posicao == ftell(f)) 
		{ 
			printf("\nO CEP provido nao foi encontrado ;---;\n");
		}

	fclose(f);
}
