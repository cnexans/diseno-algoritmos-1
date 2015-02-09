#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
using namespace std;

vector <pair<int,vector <int> > >adyacentes;
vector <pair<int,vector <int> > >adyacentes2;
vector <vector <int> >colores_posibles;
vector <int > colores;
vector <bool > marcados;
vector <pair<int, int> > grado;

bool compInt(int i,int j) { 
	return (i<j); 
}

bool compGradoAdyNodo (pair<int,vector<int > > i, pair<int,vector<int > > j){
	return ((i.second.size()) > (j.second.size())); 
}

bool OrdenGrado(pair<int,int> i,pair<int,int> j) { 
	return (i.second>j.second); 
}

int obtenerColorMinimo(){
	int colorPosible = 1;
	vector <int> cuenta_colores;
		for (int i=0; i <  adyacentes2[0].second.size(); i++){
			cuenta_colores.push_back(colores[adyacentes2[0].second[i]]);
		    sort(cuenta_colores.begin(),cuenta_colores.end(),compInt);
		}
		for(int i =0;i<cuenta_colores.size();i++){
		//	cout << " " << cuenta_colores[i];
		}
		for (int i=0; i < cuenta_colores.size(); i++){
			if(colorPosible == cuenta_colores[i] ){
				colorPosible++;
			} else if(colorPosible < cuenta_colores[i]){
				return colorPosible;
			}
	   }
		return colorPosible;	
}

bool verticesSinColor(){
	for (int i=0; i <  colores.size(); i++){
			if(colores[i] == 0) return true;
	}
	return false;
}

void CalcularGradoColor(int j){
	vector <int> cuenta_colores;
	for(int i =0;i<adyacentes2[grado[j].first].second.size();i++){
		int color_ady = colores[adyacentes2[j].second[i]];
		bool estaColor = false;
		for(int j = 0; j < cuenta_colores.size(); j++){
			if (cuenta_colores[j] == color_ady){  
				estaColor = true;
				break;
			}
		}	
	   if( !estaColor && color_ady > 0){
			cuenta_colores.push_back(color_ady);
	   }
	}
	grado[j].second = cuenta_colores.size();
}


int main(int argc, char* argv[]){
	string comentario;
	char tipo_dato;
	int cant_arcos = 0;
	int cant_nodos = 0;
	int contador_arcos = 0;
	int nodo1 = 0;
	int nodo2 = 0;
	int j = 0;

	std::ifstream archivo(argv[1],std::ifstream::in);
	char linea[128];
	char * tokanizer;
	char * lado2;
	long contador = 0L;

	if(archivo.fail()){
		printf("Error al abrir el archivo \n");
		exit(1);
	} else {
		while(!archivo.eof()) {
		  	archivo.getline(linea, sizeof(linea));
			tokanizer = strtok (linea," ");
			if(tokanizer != NULL){
				if(*tokanizer == 'p'){
					tokanizer = strtok (NULL, " ");
					tokanizer = strtok (NULL, " ");
					cant_nodos=atoi(tokanizer);
					tokanizer = strtok (NULL, " ");
					cant_arcos=atoi(tokanizer);
					int i =0;
					while(i< int(*tokanizer)){
			            adyacentes.push_back(make_pair(i,vector<int>()));
			            adyacentes2.push_back(make_pair(i,vector<int>()));
						colores_posibles.push_back(vector<int>());
						grado.push_back(make_pair(i,-1));
						colores.push_back(0);
						marcados.push_back(false);
						i=i+1;
							contador_arcos=cant_arcos;
					}

				} else if(*tokanizer == 'e'){
						contador_arcos=contador_arcos-1;
						tokanizer = strtok (NULL, " ");
						nodo1=atoi(tokanizer);
						tokanizer = strtok (NULL, " ");
						nodo2=atoi(tokanizer);
						adyacentes[nodo1-1].second.push_back(nodo2-1);
						adyacentes[nodo2-1].second.push_back(nodo1-1);
						adyacentes2[nodo1-1].second.push_back(nodo2-1);
						adyacentes2[nodo2-1].second.push_back(nodo1-1);
						j=j+1;
						if (contador_arcos==0){
							break;
						}
					}
				}   
		}
		archivo.close();
	}
	vector <int > nodos_aux;
	sort (adyacentes2.begin(), adyacentes2.end(), compGradoAdyNodo);
	colores[adyacentes2[0].first]=1;	
	grado.erase(grado.begin()+adyacentes2[0].first-1);
	nodos_aux.push_back(adyacentes2[0].first);
	adyacentes2.erase(adyacentes2.begin());

	if(verticesSinColor()){
		do{
			int grado_max = 0;
		    sort (grado.begin(), grado.end(), OrdenGrado);	
			for(int i =0;i<adyacentes2.size();i++){
				if(grado[0].first ==adyacentes2[i].first){
					grado_max = adyacentes2[i].second.size();
					break;
				}

			}
			
			int numNodGrado = 1;
			for( int i = 0;i <  adyacentes2.size(); i++){
				if(adyacentes2[i].second.size() == grado_max ) 
					numNodGrado++;
			}
			sort (adyacentes2.begin(), adyacentes2.begin() + numNodGrado - 1, compGradoAdyNodo);		
			int min_color = obtenerColorMinimo();
			colores[adyacentes2[0].first]=min_color;
			nodos_aux.push_back(adyacentes2[0].first);
			adyacentes2.erase(adyacentes2.begin());
			grado.erase(grado.begin());
		} while(verticesSinColor());
		
	}
    vector<int> nodos_solucion(adyacentes.size());
	int n = adyacentes.size();
	int q = 0;
	bool back = false;
	int w=0;

		int color_max = 0;
		for( int i = 0;i < colores.size(); i++){
			color_max++;
			if(color_max !=	colores[i]){
				color_max--;
				break;
			}
		}
		w = color_max;

	for (int i=0; i < colores.size(); i++) {
			int pos_color = colores[i] ;
				if(pos_color > q){
					q = pos_color;
				}
	}

	cout << q;

	
	for(int i = 0;i<w;i++){
		marcados[i]=true;
	}
	

	back = false;
	int k = w ;
	while(true){
		if(back == false){

			int min = std::min(*max_element(colores.begin(),colores.end()), q - 1);
			vector <int> conjunto(min);https://www.google.co.ve/
			for (unsigned int i=1; i<=min; i++)
		    conjunto[i-1] = i;
			for(int j = 0;j < k; j++){
				if(find(adyacentes[k].second.begin(), adyacentes[k].second.end(), j) != adyacentes[k].second.end()){
					if((conjunto.empty())==false){
							    vector<int>::iterator elemento = find(conjunto.begin()+1,conjunto.end(),colores[j]);
								if(elemento != conjunto.end()){
									conjunto.erase(elemento);
								}
					}else{
						
						j=k;
					}
				}
			}
			colores_posibles[k]=conjunto;

		}else{
			
			int c = colores[k];
			marcados[k]=false;
			if(colores_posibles[k].empty() == false){
					std::vector<int>::iterator elemento =	find(colores_posibles[k].begin(),colores_posibles[k].end(),c) ;
						if(elemento != colores_posibles[k].end()){
						colores_posibles[k].erase(elemento);
				}
			}
		}				
		if(colores_posibles[k].empty() == false){
			colores[k]=colores_posibles[k][0];
			k = k+1;
			if(k>=n){
				int	s = 0;
				int pos_color = 0;
				for (int i=1; i < adyacentes.size(); i++) {
					pos_color = colores[i];
					nodos_solucion[i]=pos_color;
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
				if(find(adyacentes[k].second.begin(), adyacentes[k].second.end(), i) != adyacentes[k].second.end()){
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

	int salida = 0;
	for(int i = 0; i< colores.size(); i ++){
	   salida=max(colores[i],salida);
	}
	cout << " " << salida << endl;
}
