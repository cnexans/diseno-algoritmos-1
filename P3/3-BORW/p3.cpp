/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BORW SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/

// Librerías a importar
#include <stdio.h>
#include <iostream>
#include <limits>
using namespace std;

//  Máximo entero
#define MAXN 204

// Variables globales para el DP
int dp[MAXN][MAXN][MAXN]; 
	// Matriz de 3 dimensiones donde guardamos los datos del DP 
bool dp_bool[MAXN][MAXN][MAXN]; 
	// Matriz de 3 dimensiones que indica si ya hemos calculado una solución
int secuencia[MAXN]; 
	// Vector donde se guarda la secuencia de números a calcular el mejor DP
int N; // Entero donde se guarda la cantidad de elementos 

// Funcion del Dp
int dp_fun(int i, int j, int k){
	/* Cuando i < N+2, calculo el Dp, y en caso contraro se retorna  0, 
	/	ya que se enuentra en la última casilla
	*/
	if(i < N+2){
		/* Si, el elemento a considerar es mayor que el último elemento
		/ agregado en la lista de los crecientes, lo considero
		*/
		if(secuencia[j]>secuencia[i]){
			/* Si, el elemento a considerar es mayor que el último elemento 
			 / agregado en la lista de los decrecientes lo considero
			 */
			if(secuencia[k]<secuencia[i]){
				/* Si no he calculado dicho dp, lo calculo, si no, lo tomo del 
				/ arreglo, para cada caso de las opciones ha considerar
				*/
				if(!(dp_bool[i+1][i][k])){
					dp[i+1][i][k] = dp_fun(i+1,i,k);
				}
				if(!(dp_bool[i+1][j][i])){
					dp[i+1][j][i] = dp_fun(i+1,j,i);
				}
				if(!(dp_bool[i+1][j][k])){
					dp[i+1][j][k] = 1+dp_fun(i+1,j,k);
				}
				/* Entonces, el dp[i][j][k] será el mínimo entre tomarlo en 
				/ lista de crecientes, tomarlo en la lista de decrecientes, 
				/ o no tomarlo.
				*/
				dp[i][j][k] = min(dp[i+1][i][k],
											min(dp[i+1][j][i],dp[i+1][j][k]));
				dp_bool[i][j][k] = true;
				return dp[i][j][k];
			}else{
				/* En este caso no debo considerar la opción de tomar el 
				/ elemento k no es menor que elemento i, no lo considero 
				/ en la lista de los decrecientes
				*/
				if(!(dp_bool[i+1][i][k])){
					dp[i+1][i][k] = dp_fun(i+1,i,k);
				}
				if(!(dp_bool[i+1][j][k])){
					dp[i+1][j][k] = 1 + dp_fun(i+1,j,k);
				}
				dp[i][j][k] = min(dp[i+1][i][k],dp[i+1][j][k]);
				dp_bool[i][j][k] = true;
				return dp[i][j][k];
			}
		}else if(secuencia[k]<secuencia[i]){
			/* En este caso no debo considerar la opción de tomar el elemento 
			/ j no es mayor que elemento i, no lo considero en la lista de los 
			/ crecientes
			*/
			if(!(dp_bool[i+1][j][i])){
				dp[i+1][j][i] = dp_fun(i+1,j,i);
			}
			if(!(dp_bool[i+1][j][k])){
				dp[i+1][j][k] = 1+dp_fun(i+1,j,k);
			}
			dp[i][j][k] = min(dp[i+1][j][i],dp[i+1][j][k]);
			dp_bool[i][j][k] = true;
			return dp[i][j][k];
		}
		/* Si el elemento no puede ser agregado a ninguna de las dos listas, 
		/	no puedo tomarlo
		*/
		if(!(dp_bool[i+1][j][k])){
			dp[i+1][j][k] = 1+dp_fun(i+1,j,k);
		}
		dp[i][j][k]=dp[i+1][j][k];
		dp_bool[i][j][k] = true;
		return dp[i][j][k];
	}else{
		dp[i][j][k] = 0;
		dp_bool[i][j][k] = true;
		return dp[i][j][k];
	}
}

int main(void){
	int i, arriba, abajo;
	/* Ciclo que itera por cada caso de prueba hasta que N sea igual a -1,
	/  y guarda en N la cantidad de elementos de la secuencia a leer
	*/
	while (cin >> N, N != -1){

		// Se lee la secuencia de números del caso de prueba
		for (i = 0; i < N; i++){
			cin >> secuencia[i+2];
		}

		/* 
		/  Se inicializan todas las casillas de la matriz booleana del Dp en
		/    False indinando que no se ha calculado ninguno
		*/
		for(int i=0;i<=N+3;i++){
			for(int j=0;j<=N+3;j++){
				for(int k=0;k<=N+3;k++){
		 			dp_bool[i][j][k] = false;
		 		}
			}
		}

		/* Se ininizaliza el "primer" elemento de los crecientes en secuencia[0] 
		/	como -1
		*/
		secuencia[0]=-1;

		/* Se ininizaliza el "primer" elemento de los decrecientes en 
		/	secuencia[1] como el máximo de los enteros
		*/
		secuencia[1]=numeric_limits<int>::max();

		// Se imprime el caso de prueba y se ejecuta el dp
		cout << dp_fun(2,1,0) << endl;
	}
	return 0;
}