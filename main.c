#include <stdio.h>
#include <stdlib.h>

#include "sorts.h"

void copiaNumeros(int *fonte, int *destino, int tamanho) {
	int *pF = fonte, *pD = destino, *pE;
	for (pE = pF + tamanho - 1; pF <= pE; ++pF, ++pD) {
		*pD = *pF;
	}
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int i, tamanho = 0, *numerosBackup, *numeros, *pN, *pF;
	unsigned int iteracoes[6];
	char nomeSort[][10] = {"Insertion", "Selection", "Bubble", "Merge", "Quick", "Heap"};
	unsigned int (*sorts[])(int*, int) = {insertion, selection, bubble, merge, quick, heap};
	if (argc != 2) {
		printf("Uso: AutoInstrucional <arquivo.txt>\n");
		return 0;
	}
	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("Arquivo inexistente ou sem permissao de leitura.\n");
		return -1;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d", &i);
		++tamanho;
	}
	numerosBackup = (int*) malloc(tamanho * sizeof(int));
	numeros = (int*) malloc(tamanho * sizeof(int));
	if (!numerosBackup || !numeros) {
		printf("Erro de alocacao de memoria.\n");
		fclose(fp);
		return -2;
	}
	rewind(fp);
	for (pN = numerosBackup, pF = pN + tamanho - 1; pN <= pF; ++pN) {
		fscanf(fp, "%d", pN);
	}
	fclose(fp);
	for (i = 0; i < 6; ++i) {
		printf("Copiando numeros e organizando pelo %s Sort.\n", nomeSort[i]);
		copiaNumeros(numerosBackup, numeros, tamanho);
		iteracoes[i] = sorts[i](numeros, tamanho);
	}
	printf("\n+-----------------------------+\n");
	printf("|          Iteracoes          |\n");
	printf("+----------------+------------+\n");
	for (i = 0; i < 6; ++i) {
		printf("| %9s Sort | %10d |\n", nomeSort[i], iteracoes[i]);
	}
	printf("+----------------+------------+\n");
	return 0;
}
