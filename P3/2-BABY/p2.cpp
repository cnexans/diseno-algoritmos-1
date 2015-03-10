/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BABY SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/
 
 // Librerías a importar
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//  Máximo entero
#define MAXN 16
#define MAXB (1<<MAXN)

// Variables globales para el DP
unsigned char mascaraBit[MAXB];
int dp[MAXB];
int T, N;
int origen[MAXN], destino[MAXN];

// Función para calculo del mínimo
int min(int a, int b){ 
	return a < b ? a : b; 
}

int main(void){
	int i, j;

	// Creación de la Máscara de Bits
	for (i = 1; i < MAXB; i++)
		mascaraBit[i] = mascaraBit[i ^ (i&-i)] + 1;

	// Ciclo que itera por cada caso de prueba hasta que N sea igual a 0,
	// y guarda en N la cantidad de elementos de la secuencia a leer
	while (cin >> N, N){

		// Se lee los nodos X
		for (i = 0; i < N; i++){
			cin >> origen[i];
		}

		// Se lee los nodos Y
		for (i = 0; i < N; i++){
			cin >> destino[i];
		}

		// Ciclo del DP
		for (i = 1; i < (1<<N); i++){
			for (j = 0, dp[i] = (1<<30); (1<<j) <= i; j++){
				if (i & (1<<j)){
					dp[i] = min(dp[i],
					            dp[i^(1<<j)] + abs(mascaraBit[i]-j-1) + abs(origen[j]-destino[mascaraBit[i]-1]));
				}
			}
		}

		// Valor de salida del DP
		cout << dp[(1<<N) -1] << endl;
	}
	return 0;
}