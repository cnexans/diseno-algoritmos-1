/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema MAXWOODS SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/

/* Se realiza una ejecución del DP bottom-up, usando un vector de memorización 
/  2*n, donde n es el ancho de la matriz.
*/

// Librerias a usar
#include <iostream>
#include <cstring>
using namespace std;

// Declaración de variables globales
int cant; // Casos de prueba 
int m,n; // Columnas, Filas
char data[200][200]; // Almacenar la entrada
int dp[2][200]; // Vector de soluciones parciales del dp
int mejor; //Variable donde se va guardando de manera temporal la mejor solucion
const int infi_neg = -100000;

int main(){

	//Se lee la cantidad de casos de prueba
	cin >> cant;

	// Se itera una vez por cada caso de prueba
	while(cant--){

		// Se inicializan las variables a usar
		memset(data,0,sizeof(data));
		mejor = 0;
		int salida = 0;

		// Se lee la cantidad de filas y de columnas del caso de prueba
		cin >> n >> m;

		// Se lee la matriz a recorreer
        for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++){
            	cin >> data[i][j];
        	}
        }

        // Se inicializa las variables del Dp en 0
        for(int j=0;j<m;j++){
            dp[1][j]=0;   
            dp[0][j]=0;            
        }

        /*  Si la primera casilla tiene arbol, le marco 1 en dicha posicion
        /   del dp
        */
        if(data[0][0]=='T'){
        	mejor = dp[1][0] = 1;  
        }

        /*  Si la primera casilla esta bloqueada, le colo infinito en dicha
        /   posicion del dp
        */
        if(data[0][0]=='#'){
        	mejor = 0;
        	dp[1][0] = infi_neg;
        }
     
     	// Ejecuto el dp para la primera fila de la matriz
        for(int i=1;i<m;i++){
            if(data[0][i]=='#'){
                for(int j=i;j<m;j++){
                    dp[1][j]=infi_neg;             
                }
                break;
            }
            dp[1][i]=dp[1][i-1]+(data[0][i]=='T');
            mejor = max(mejor,dp[1][i]);
		}

		// Selecciono el mejor de dicha ejecucion
		for(int k =0; k< m; k++){
			mejor = max(mejor,dp[1][k]);	
			dp[0][k] = dp[1][k];
		}

		// Ejecuto el dp para el resto de la matriz
		for(int i=1;i<n;i++){
			/* Selecciono como vector de soluciones al vector de
			/  soluciones parciales anterior, y reinicializo 
			/  el nuevo vector de soluciones parciales 
			*/
			for(int k =0; k< m; k++){
				mejor = max(mejor,dp[1][k]);
				dp[0][k] = dp[1][k];
			}

			// Si estoy en una fila par
			if(i%2==0){
				/* Si esta bloqueado, el minimo para llegar a dicha casilla
				/  es infinito, en caso contrario le coloco la maxima cantida
				/  de arboles cortado para llegar a dicha posicion.
				/  El caso borde en que se esta en la primera casilla de la 
				/  izquierda se toma en cuenta.
				*/
		    	if(data[i][0]=='#'){
			        dp[1][0]=infi_neg;
		        }
		        else{
		        	if(data[i][0]=='T'){
		            	dp[1][0]=dp[0][0]+1;
		        	}else{
		        		dp[1][0]=dp[0][0];
		        	}
		        }
		        mejor = max(mejor,dp[1][0]);
		        for(int j=1;j<=m-1;j+=1){
		        	/*	Se selecciona la maxima cantidad de arboles cortados
		        	/ de haber venido de arriba o a la izquierda, y en el caso 
		        	/ borde solo se toma en cuenta el de arriba. En caso de
		        	/ camino bloqueado, es infito.
		        	*/
		        	if(data[i][j]=='T'){
		            	dp[1][j] = max(dp[0][j],dp[1][j-1])+1;
		        	}else{
		        		dp[1][j] = max(dp[0][j],dp[1][j-1]);
		        	}
		            if(data[i][j]=='#'){
		                dp[1][j]=infi_neg;
		            }
		        }
		    }else{
		    	/* Si esta bloqueado, el minimo para llegar a dicha casilla
				/  es infinito, en caso contrario le coloco la maxima cantida
				/  de arboles cortado para llegar a dicha posicion.
				/  El caso borde en que se esta en la primera casilla de la 
				/  derecha se toma en cuenta.
				*/
		    	if(data[i][m-1]=='#'){
			        dp[1][m-1]=infi_neg;
		        }
		        else{
		        	if(data[i][m-1]=='T'){
		            	dp[1][m-1]=dp[0][m-1]+1;
		        	}else{
		        		dp[1][m-1]=dp[0][m-1];
		        	}
		        }
		        mejor = max(mejor,dp[1][m-1]);
		        for(int j=m-2;j>=0;j-=1){
		        	/*	Se selecciona la maxima cantidad de arboles cortados
		        	/ de haber venido de arriba o a la izquierda, y en el caso 
		        	/ borde solo se toma en cuenta el de arriba. En caso de
		        	/ camino bloqueado, es infito.
		        	*/
		        	if(data[i][j]=='T'){
		            	dp[1][j] = max(dp[0][j],dp[1][j+1])+1;
		        	}else{
		        		dp[1][j] = max(dp[0][j],dp[1][j+1]);
		        	}
		            if(data[i][j]=='#'){
		                dp[1][j]=infi_neg;
		            }
		        }
		    }
		}

		// Selecciono al mejor de la solucion
		for(int i =0; i< m; i++){
			mejor = max(mejor,dp[1][i]);
		}

		// Imprimo la solucion
		cout << mejor << endl;
	}

	return 0;
}