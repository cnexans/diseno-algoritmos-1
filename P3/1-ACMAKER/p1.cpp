/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BORW SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/

/*
/    Se utiliza una matriz de memorización de n*n*2, donde n es el tamaño de
/    la pabara, haciendo uso de una estrategia top-down.
*/

// Librerias  ausar
#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

// Constantes
#define inf 100000000
#define MAXN 101

// Variables globales
int dp_sol[MAXN][MAXN][2]; // Matriz de memorizacion del Dp
int tam_abre; // Tamaño de la abreviacion
int tam_palabra; // Tamaño de la palabra de entrada
string abre, abreviacion; /* String que tienen guardada la abreviacion en
 minúscula y mayúscula */
string palabra; // String que guarda la palabra

// Procedimiento recursivo para el calculo del dp
int dp(int pal_pos, int abre_pos, bool agarrado) {

    /* Si el tamaño de la palabra es igual
    / a la posicion de la palabra en la que te encuentras
    / retorno 1 si me encuentro en la ultima posicion de la abreviacion
    / y he agarrado uno antes
    */
    if (pal_pos == tam_palabra){
    	return abre_pos == tam_abre && agarrado;
    }

    // Si la solucion al dp ha sido calculado antes, retorno su valor
    if (dp_sol[pal_pos][abre_pos][agarrado] != -1){
    	return dp_sol[pal_pos][abre_pos][agarrado];
    }

    /* Si hay un espacio en blanco y no he agarrado nada retorno 0
    / en caso de contrario retorno la solucion de la siguiente posicion del 
    / vector
    */
    if (palabra[pal_pos] == ' ') {
        if (!agarrado){
        	return 0;
        }else{
        	return dp_sol[pal_pos][abre_pos][agarrado] = 
                                            dp(pal_pos+1, abre_pos, false);
    	}
    }

    /* Si estoy en la ultima casilla de la abreviacion, retorno 
    /  paso a la siguiente letra y no agarro ninguna letra, ya que no puedo.
    */
    if (abre_pos == tam_abre){
    	return dp_sol[pal_pos][abre_pos][agarrado] = 
                                            dp(pal_pos+1, abre_pos, agarrado);
    }

    // Igualo a la solucion el no haber agarrado dicha palabra
    dp_sol[pal_pos][abre_pos][agarrado] = dp(pal_pos+1, abre_pos, agarrado);
    
    /* Si puedo agarra dicha letra, suma la cantidad de formas que genera 
    /   agarrar dicha palabra
    */
    if (palabra[pal_pos] == abre[abre_pos]) {
        dp_sol[pal_pos][abre_pos][agarrado] +=
                                             dp(pal_pos+1, abre_pos+1, true);
    }

    // Retorno la solucion de haber agarrado y no agrrado la letra
    return dp_sol[pal_pos][abre_pos][agarrado];
}

int main() {

    while (true) {
        int cant;
        //Leo la cantiadad de palabra a omitir
        cin >> cant;
        // Si es 0, salgo del programa
        if (!cant) return 0;

        // Cojunto de frases a omitir
        set<string> frases_insignificantes;
        
        // Leo y agrego las frases insignificantes
        string palabras_insignificantes;
        for (int i = 0; i < cant; i++) {
            cin >> palabras_insignificantes;
            frases_insignificantes.insert(palabras_insignificantes);
        }
        
        string line;
        getline(cin, line); 

        while (true) {
            getline(cin, line);

            istringstream temp(line);

            // Separo la linea por espacios en blanco
            getline(temp, abreviacion, ' ');
            abre = abreviacion;
            for(int i = 0; i<abreviacion.size();i++){
                // Coloco en minúscula la abreviacion
            	abre[i] = tolower(abreviacion[i]);
            }

            tam_abre = abre.size();

            vector<string> palabras;
            string palabra_temp;
            getline(temp, palabra_temp, ' ');
            
            // Cuando leo CASE, y nuestra anterior lectura fue LAST
            if (abreviacion == "LAST" && palabra_temp == "CASE") {
            	break;
            }

            // Procedimiento para eliminar palabras insignificantes
            do {
                if (!palabra_temp.empty() &&
                     frases_insignificantes.find(palabra_temp) == 
                                              frases_insignificantes.end()) {
                    palabras.push_back(palabra_temp);
                }
            } while (getline(temp, palabra_temp, ' '));

            // Rearmo la frase con las palabras significantes
            palabra = "";
            for (vector<string>::iterator it = palabras.begin();
                                     it != palabras.end(); ++it) {
                palabra += ' ' + *it;
            }
            tam_palabra = palabra.size();

            /* Inicializo en vector de soluciones parciales
            /   i ejecuto el dep, desde la posicion 1 de la palabra, 
            /   y la 0 de la abreviacion
            */
            memset(dp_sol, -1, sizeof dp_sol);
            int sol = dp(1,0,false);
            
            // Imprimo la solucion según el caso
            if (sol) cout << abreviacion << " can be formed in "
                                                 << sol << " ways" << endl;
            else cout << abreviacion << 
                                    " is not a valid abbreviation" << endl;
        }
    }

    return 0;
}