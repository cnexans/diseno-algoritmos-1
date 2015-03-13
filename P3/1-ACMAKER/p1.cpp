/*
/ ci5651 (Diseño de Algoritmos I) - Proyecto 3 - Problema BORW SPOJ
/ Fabio, Castro, 10-10132
/ Leopoldo, Pimentel 06-40095
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

#define inf 100000000
#define MAXN 101

int dp_sol[MAXN][MAXN][2];
int tam_abre;
int tam_palabra;
string abre, abreviacion;
string palabra;

int dp(int pal_pos, int abre_pos, bool agarrado) {

    if (pal_pos == tam_palabra){
    	return abre_pos == tam_abre && agarrado;
    }

    if (dp_sol[pal_pos][abre_pos][agarrado] != -1){
    	return dp_sol[pal_pos][abre_pos][agarrado];
    }

    if (palabra[pal_pos] == ' ') {
        if (!agarrado){
        	return 0;
        }else{
        	return dp_sol[pal_pos][abre_pos][agarrado] = dp(pal_pos+1, abre_pos, false);
    	}
    }

    if (abre_pos == tam_abre){
    	return dp_sol[pal_pos][abre_pos][agarrado] = dp(pal_pos+1, abre_pos, agarrado);
    }

    dp_sol[pal_pos][abre_pos][agarrado] = dp(pal_pos+1, abre_pos, agarrado);
    
    if (palabra[pal_pos] == abre[abre_pos]) {
        dp_sol[pal_pos][abre_pos][agarrado] += dp(pal_pos+1, abre_pos+1, true);
    }

    return dp_sol[pal_pos][abre_pos][agarrado];
}

int main() {
    while (true) {
        int cant;
        cin >> cant;
        if (!cant) return 0;

        set<string> frases_insignificantes;
        
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

            getline(temp, abreviacion, ' ');
            abre = abreviacion;
            for(int i = 0; i<abreviacion.size();i++){
            	abre[i] = tolower(abreviacion[i]);
            }

            tam_abre = abre.size();

            vector<string> palabras;
            string palabra_temp;
            getline(temp, palabra_temp, ' ');
            
            if (abreviacion == "LAST" && palabra_temp == "CASE") {
            	break;
            }

            do {
                if (!palabra_temp.empty() && frases_insignificantes.find(palabra_temp) == frases_insignificantes.end()) {
                    palabras.push_back(palabra_temp);
                }
            } while (getline(temp, palabra_temp, ' '));

            palabra = "";
            for (vector<string>::iterator it = palabras.begin(); it != palabras.end(); ++it) {
                palabra += ' ' + *it;
            }
            tam_palabra = palabra.size();

            memset(dp_sol, -1, sizeof dp_sol);
            int sol = dp(1,0,false);
            
            if (sol) cout << abreviacion << " can be formed in " << sol << " ways" << endl;
            else cout << abreviacion << " is not a valid abbreviation" << endl;
        }
    }

    return 0;
}