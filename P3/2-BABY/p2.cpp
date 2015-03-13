/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BABY SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/
 
/*  Se utilizó una estartegia top-down usando memorizacion en un
/ vector de bits. Donde, se se hace uso de una máscara de bits, 
/ que indica que posiciones se han usado o no en dicho momentos.
/ 1 indica que si ha sido usado, y 0 que no. Se realiza una comparacion
/ de bits, si el or lógico resulta 0 entonces esta vacia la posición
/ si resulta 1, esta ocupada.
*/

// Librerías a importar
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

// Constantes
#define max_num 16
#define max_bits (1<<max_num) 

// Variables Globales para el dp
int n;
int y_pos[max_num];
int x_pos[max_num];
int dp_sol[max_bits];

// Función recursiva para el Dp
int dp(int mascara, int pos){

    // Si la posicion que estoy revisando es la ultima, retorno 0
    if(pos == n){
        return 0;
    } 

    /*  Si he calculado el dp de dicha instancia, la retorno,  
    /  en caso contraro la calculo diciendo el mínimo de mover la reina 
    /  a una posicion correcta
    */
    if(dp_sol[mascara]!=-1){
        return dp_sol[mascara];
    }else{
        int ans=10000000;
        for(int i=0; i<n; i++)
            if(!(mascara & (1<<i)))
                ans=min(ans,abs(i-pos)+ 
                        abs(y_pos[pos]-x_pos[i])+
                            dp(mascara | (1<<i), pos+1));
        return dp_sol[mascara]=ans;
    }
}

int main(){

    // Se realiza la lectura de cada caso, hasta que se lea un 0
    while(cin >> n, n !=0){

        // Se inicializa el vector  de soluciones de bits
        memset(dp_sol,-1,sizeof (int)*(1<<n));

        // Se leen las posiciones X de las reinas
        for(int i=0; i<n; i++){
            cin >> x_pos[i];
        }

        // Se leen las posiciones Y de las reinas
        for(int i=0; i<n; i++){
            cin >> y_pos[i];
        }

        // Se ejecuta el dep y se imprime el resultado
        cout << dp(0,0) << endl; 
    }
    return 0;
}