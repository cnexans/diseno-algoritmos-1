/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BORW SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/

// Librerías a importar
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

//  Máximo entero
#define MAXN 201

// Variables globales para el DP
int dp[MAXN][MAXN][MAXN]; // Matriz de 3 dimensiones usada para calcular el DP
int secuencia_num[MAXN]; // Vector donde se guarda la secuencia de números a calcular el mejor DP
int N; // Entero donde se guarda la cantidad de elementos 

int main(void){
	int i, arriba, abajo;
	// Ciclo que itera por cada caso de prueba hasta que N sea igual a -1,
	// y guarda en N la cantidad de elementos de la secuencia a leer
	while (cin >> N, N != -1){

		// Se lee la secuencia de números del caso de prueba
		for (i = 1; i <= N; i++){
			cin >> secuencia_num[i];
		}

		// For donde se realiza el DP, tomando en cuenta las subsecuencias anteriores
		for (i = 1; i <= N; i++){
			for (arriba = i+1; arriba <= N+1; arriba++){
				for (abajo = i+1; abajo <= N+1; abajo++){
					dp[i][arriba][abajo] = dp[i-1][arriba][abajo] + 1;
					if (abajo > N || secuencia_num[i] < secuencia_num[abajo]){
						dp[i][arriba][abajo] = min(dp[i][arriba][abajo], dp[i-1][arriba][i]);
					}
					if (arriba > N || secuencia_num[i] > secuencia_num[arriba]){
						dp[i][arriba][abajo] = min(dp[i][arriba][abajo], dp[i-1][i][abajo]);
					}
				}
			}
		}
		// Se imprime el caso de prueba actual
		cout << dp[N][N+1][N+1] << endl;
	}
	return 0;
}