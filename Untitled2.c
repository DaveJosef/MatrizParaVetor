#include<stdio.h>

void preencherVet (int *matrix, int a, int l) {
	int n,o;
	int c = 0;
	for (n = 0; n < a; n++) {
		for (o = 0; o < l; o++) {
			matrix[n * l + o] = c;
			c++;
		}
	}
}

void zerarVet (int *matrix, int a, int l) {
	int n,o;
	for (n = 0; n < a; n++) {
		for (o = 0; o < l; o++) {
			matrix[n * l + o] = 0;
		}
	}
}

void imprimirVet(int *matrix, int a, int l) {
	int n,o;
	for (n = 0; n < a; n++) {
		for (o = 0; o < l; o++) {
			printf(" %d", matrix[n * l + o]);
		}
		printf("\n");
	}
}

void produto_Matriz(int *vet_1, int *vet_2, int a1, int l1, int a2, int l2, int *matrixProd) {
	zerarVet(matrixProd, a1, l2);
	int n,o,p;
	for (n = 0; n < a1; n++) {
		for (o = 0; o < l2; o ++) {
			for (p = 0; p < l1; p++) {
				matrixProd[n * l2 + o] += vet_1[n * l1 + p] * vet_2[p * l2 + o];
			}
		}
	}
}

void transposta_da_soma_Matriz(int *vet_1, int *vet_2, int a, int l, int *matrixResult) {
	int n,o;
	int matrixSoma[l * a];
	preencherVet(matrixResult, l, a);
	for (n = 0; n < a; n++) {
		for (o = 0; o < l; o++) {
			matrixSoma[n * l + o] = vet_1[n * l + o] + vet_2[n * l + o];
		}
	}
	transporVet(matrixSoma, a, l, matrixResult);
}

int identidade_Matriz(int *vet_1, int a) {
	int n,o;
	for (n = 0; n < a; n++) {
		for (o = 0; o < a; o++) {
			if (n == o) {
				if (vet_1[n * a + o] != 1) {
					return 0;
				}
			} else {
				if (vet_1[n * a + o] != 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int inversa_Matriz(int *vet_1, int *vet_2, int n) {
	int matrixProd[n * n];
	produto_Matriz(vet_1, vet_2, n, n, n, n, matrixProd);
	return identidade_Matriz(matrixProd, n);
}

void transporVet(int *matrix, int a, int l, int *matrixTrans) {
	int n,o;
	for (n = 0; n < a; n++) {
		for (o = 0; o < l; o++) {
			matrixTrans[trocarInd(n, a, l, o)] = matrix[n * l + o];
		}
	}
}

int trocarInd(int i, int altura, int largura, int j) {
	return j * altura + i;
}

void preencherVetId(int *matrixA, int a) {
	int n,o;
	for (n = 0; n < a; n++) {
		for (o = 0; o < a; o++) {
			matrixA[n * a + o] = n == o;
		}
	}
}

void testeIniciar(int *matrixA, int *matrixB, int *matrixC, int *matrixD, int *matrixTrans, int a, int l) {
	preencherVet(matrixA, a, l);
	preencherVet(matrixB, a, l);
	preencherVet(matrixC, a, l);
	preencherVet(matrixD, a, a);
	preencherVet(matrixTrans, l, a);
	printf("\nIniciando valores...");
	printf("\nMatrix A\n");
	imprimirVet(matrixA, a, l);
	
	printf("\nMatrix B\n");
	imprimirVet(matrixB, a, l);
	
	printf("\nMatrix C\n");
	imprimirVet(matrixC, a, l);
	
	printf("\nMatrix D\n");
	imprimirVet(matrixD, a, a);
	
	printf("\nMatrix Trans\n");
	imprimirVet(matrixTrans, l, a);
	
	printf("\n");
}

void testeTranspor(int *vet_1, int a, int l, int *matrixTrans) {
	transporVet(vet_1, a, l, matrixTrans);
	printf("\nTranspondo matrizes...");
	printf("\nMatrix Origin\n");
	imprimirVet(vet_1, a, l);
	
	printf("\nMatrix Trans\n");
	imprimirVet(matrixTrans, l, a);
	
	printf("\n");
}

void testeMulti(int *vet_1, int *vet_2, int a1, int l1, int a2, int l2, int *result) {
	preencherVet(vet_1, a1, l1);
	preencherVet(vet_2, a2, l2);
	preencherVet(result, a1, l2);
	printf("\nMultiplicando matrizes...");
	produto_Matriz(vet_1, vet_2, a1, l1, a2, l2, result);
	printf("\nMatrix A\n");
	imprimirVet(vet_1, a1, l1);
	
	printf("\nMatrix B\n");
	imprimirVet(vet_2, a2, l2);
	
	printf("\nMatrix AxB\n");
	imprimirVet(result, a1, l2);
	
}

void testeSomaTrans(int *matrixA, int *matrixB, int a, int l, int *matrixC) {
	preencherVet(matrixA, a, l);
	preencherVet(matrixB, a, l);
	preencherVet(matrixC, a, l);
	printf("\nTranspondo a soma...");
	transposta_da_soma_Matriz(matrixA, matrixB, a, l, matrixC);
	printf("\nMatrix A\n");
	imprimirVet(matrixA, a, l);
	
	printf("\nMatrix B\n");
	imprimirVet(matrixB, a, l);
	
	printf("\nMatrix A+B transposta\n");
	imprimirVet(matrixC, l, a);
	
}

void testeIdentidade(int *matrixA, int a) {
	preencherVetId(matrixA, a);
	//preencherVet(matrixA, a, a);
	printf("\nProcessando se matriz é identidade...");
	printf("\nMatrix Amostra\n");
	imprimirVet(matrixA, a, a);
	
	if (identidade_Matriz(matrixA, a)) {
		printf("\nA matriz informada é sim identidade\n");
	} else {
		printf("\nA matriz informada não é identidade\n");
	}
}

void testeInversa(int *matrixA, int *matrixB, int n) {
	//preencherVetId(matrixA, n);
	//preencherVetId(matrixB, n);
	preencherVet(matrixA, n, n);
	preencherVet(matrixB, n, n);
	printf("\nProcessando se é inversa...");
	printf("\nMatrix A\n");
	imprimirVet(matrixA, n, n);
	
	printf("\nMatrix B\n");
	imprimirVet(matrixB, n, n);
	
	if (inversa_Matriz(matrixA, matrixB, n)) {
		printf("\nA matriz B é sim inversa de A\n");
	} else {
		printf("\nA matriz B informada não é inversa de A\n");
	}
}

int main () {
	system("cls");
	system("title Vetores");
	system("color 2b");
	
	printf("\n");
	putchar('\n');
	
	int l = 2;
	int a = 4;
	int matrixA[l * a];
	int matrixB[2 * 4];
	int matrixC[l * a];
	int matrixD[a * a];
	int matrixTrans[l * a];
	
	testeIniciar(matrixA, matrixB, matrixC, matrixD, matrixTrans, a, l);
	
	testeTranspor(matrixA, a, l, matrixTrans);
	
	testeMulti(matrixA, matrixB, a, l, 2, 4, matrixD);
	
	testeSomaTrans(matrixA, matrixB, a, l, matrixC);
	
	testeIdentidade(matrixD, a);
	
	testeInversa(matrixD, matrixD, a);
	
	printf("\n");
	putchar('\n');
	
	system("PAUSE");
	return(0);
}
