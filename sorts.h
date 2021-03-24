#ifndef SORTS_H_INCLUDED
#define SORTS_H_INCLUDED

#include <stdlib.h>

void troca(int *a, int *b) {
	int x = *a;
	*a = *b;
	*b = x;
}

unsigned int insertion(int *numeros, int tamanho) {
	unsigned int total = 0;
	int *pJ, *pK, *pKA, *pI = numeros, *pF = numeros + tamanho - 1;
	for (pJ = numeros + 1; pJ <= pF; ++pJ) {
		for (pK = pJ, pKA = pJ - 1; pK > pI && * pK < *pKA; --pK, --pKA) {
			troca(pK, pKA);
			++total;
		}
		++total;
	}
	return total;
}

unsigned int selection(int *numeros, int tamanho) {
	unsigned int total = 0;
	int *pJ, *pK, *pM, *pI = numeros, *pF = numeros + tamanho - 1;
	for (pJ = pM = pI; pJ < pF; ++pJ, pM = pJ) {
		for (pK = pJ + 1; pK <= pF; ++pK) {
			if (*pK < *pM)
				pM = pK;
			++total;
		}
		if (pJ != pM)
			troca(pJ, pM);
		++total;
	}
	return total;
}

unsigned int bubble(int *numeros, int tamanho) {
	unsigned int total = 0;
	char trocado;
	int *pJ, *pK, *pKA, *pF = numeros + tamanho - 1;
	for (pJ = numeros; pJ < pF; ++pJ) {
		trocado = 0;
		for (pK = pF, pKA = pF - 1; pK > pJ; --pK, --pKA) {
			if (*pK < *pKA) {
				troca(pK, pKA);
				trocado = 1;
			}
			++total;
		}
		++total;
		if (!trocado)
			return total;
	}
	return total;
}

unsigned int merge(int *numeros, int tamanho) {
	unsigned int total = 0;
	if (tamanho > 1) {
		int meio = tamanho / 2;
		int *pM = numeros + meio, *pI = numeros, *pJ = pM, *pF = numeros + tamanho - 1;
		int *temp = (int*) malloc(tamanho * sizeof(int)), *pT = temp;
		if (!temp)
			exit(-1);
		total += merge(numeros, meio);
		total += merge(numeros + meio, tamanho - meio);
		while (pI < pM && pJ <= pF) {
			if (*pI < *pJ)
				*pT++ = *pI++;
			else
				*pT++ = *pJ++;
			++total;
		}
		while (pI < pM) {
			*pT++ = *pI++;
			++total;
		}
		while (pJ <= pF) {
			*pT++ = *pJ++;
			++total;
		}
		for (pT = temp, pI = numeros; pI <= pF; ++pT, ++pI) {
			*pI = *pT;
			++total;
		}
		free(temp);
	}
	return total;
}

unsigned int quick(int *numeros, int tamanho) {
	unsigned int total = 0;
	if (tamanho > 0) {
		int pivo, *pI = numeros, *pJ, *pE = pI, *pD = numeros + tamanho - 1;
		for (pJ = pE + 1; pJ <= pD; ++pJ) {
			if (*pJ < *pE)
				troca(++pI, pJ);
			++total;
		}
		troca(pE, pI);
		pivo = (int) (pI - numeros);
		total += quick(numeros, pivo);
		total += quick(numeros + pivo + 1, tamanho - pivo - 1);
	}
	return total;
}

unsigned int heap(int *numeros, int tamanho) {
	unsigned int total = 0;
	if (tamanho > 1) {
		int i, j;
		for (i = 2; i <= tamanho; ++i) {
			for (j = i; j > 1 && numeros[j - 1] > numeros[(j >> 1) - 1]; j >>= 1) {
				troca(&numeros[j - 1], &numeros[(j >> 1) - 1]);
				++total;
			}
			++total;
		}
		troca(&numeros[0], &numeros[tamanho - 1]);
		total += heap(numeros, tamanho - 1);
	}
	return total;
}

#endif
