#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;





int main(){
	string comentario;
	char tipo_dato;
	int cant_arcos = 0;
	int cant_nodos = 0;
	int contador_arcos = 0;
	int nodo1 = 0;
	int nodo2 = 0;
	int j = 0;
	vector <vector <int> > adyacentes;
	vector <vector <int> > colores_posibles;
	vector <int > colores;
	vector <bool > marcados;
	adyacentes.push_back(vector<int>());
	colores_posibles.push_back(vector<int>());
	
	while(true){
		cin >> tipo_dato;
		if(tipo_dato == 'c'){ 
			getline(cin,comentario);
		}else if(tipo_dato == 'p'){
			cin >> comentario >> cant_nodos >> cant_arcos;
			int i = 0;
			contador_arcos = cant_arcos;
			while(i<= cant_nodos){
				adyacentes.push_back(vector<int>());
				colores_posibles.push_back(vector<int>());
				i=i+1;
			}
		}else if(tipo_dato == 'e'){
			contador_arcos=contador_arcos-1;
			cin >> nodo1;
			cin >> nodo2;
			adyacentes[nodo1].push_back(nodo2);
			adyacentes[nodo2].push_back(nodo1);
			colores.push_back(j);
			marcados.push_back(true);
			j=j+1;
			if (contador_arcos==0){
				break;
			}

		}
	}

    vector<int> nodos_solucion(adyacentes.size());
	int n = adyacentes.size();
	int q = 5;
	int w = adyacentes.size();
	bool back = false;
	int k = w;
	
	while(true){
		if(back == false){
			int min = std::min(*max_element(colores.begin()+1,colores.end()) + 1, q - 1);
			vector <int> conjunto(min);

			//obtengo todos los colores de 1 hasta el min(uk+1,q-1)
			for (unsigned int i=1; i<=min; i++)
		    conjunto[i-1] = i;
			
			//Para cada elemento de la solucion parcial
			for(int j = 0;j < k; j++){
				//Si el elemento es vecino del nodo k
				if(find(adyacentes[k].begin(), adyacentes[k].end(), j) != adyacentes[k].end()){
					if((conjunto.empty())==false){
							    vector<int>::iterator elemento = find(conjunto.begin()+1,conjunto.end(),colores[j]);
								if(elemento != conjunto.end()){
									conjunto.erase(elemento);
								}
					}else{
						
						break;
					}
				}
			}
			break;

		}else{
			int c = colores[k];
			marcados[k]=false;
			if(colores_posibles[k].empty() == false){
					std::vector<int>::iterator elemento =	find(colores_posibles[k].begin()+1,colores_posibles[k].end(),c) ;
				if(elemento != colores_posibles[k].end()){
						colores_posibles[k].erase(elemento);
				}
			}
		vector<int> conjuntok = colores_posibles[k];
						
		if(conjuntok.empty() == false){
			colores[k]=conjuntok[0];
			k = k+1;
			if(k>=n){
				int	s = 0;
				int pos_color = 0;
				for (int i=1; i < adyacentes.size(); i++) {
					pos_color = colores[i];
					(nodos_solucion[i])=pos_color;
					if (pos_color > s) {
						s = pos_color ;
					}
				}
				q = s;
				if(q==w){
				   break;
				}
				for(int j = 0 ; j < n ; j++ ){	
					if(colores[j] == q){
						k = j;
						break;
					}
				}
				for(int j = n-1 ; j >= k ; j-- ){
					marcados[j] = false;
				}
				back = true;
			}else{
				back = false;		
			}	
		}else{
			back = true;		
		}
		if(back == true){

			for(int i =0; i < k; i++){
				vector<int> coloresEnUso;
				if(find(adyacentes[k].begin(), adyacentes[k].end(), i) != adyacentes[k].end()){
							if(binary_search(coloresEnUso.begin(),coloresEnUso.end(),colores[i]) == false){
								marcados[i]=true;								
								coloresEnUso.push_back(colores[i]);
								sort(coloresEnUso.begin(),coloresEnUso.end());
							}
				}
			}
			for(int p = k-1; p >= 0;p--){	
					if(marcados[p] == true){
						k = p;
						break;
					}
			}
			if(k<w){
			  break;
			}	
		}
	
	}	
}
for(int i; i < adyacentes.size(); i++){
	cout << colores[i] << " ";
}

}
