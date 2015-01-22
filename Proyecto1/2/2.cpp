#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;


vector<pair<int,int> > arcos;
vector<pair<char,int> > querys;
vector<int> salida;
vector<int> elementos;
vector<int> eliminados;
vector<int> padre;
vector<int> cant;

int find(int nodo){
	if(padre[nodo]== nodo){
		return nodo;
	}else{
		return find(padre[nodo]);
	}
}

int unir(int nodo_e, int nodo_s){
	int representante_nodo_e = find(nodo_e);
	int representante_nodo_s = find(nodo_s);
	int cant_nodos_conectados = cant[representante_nodo_e]*cant[representante_nodo_s];
	padre[representante_nodo_s] = representante_nodo_e;
	if(representante_nodo_s!=representante_nodo_e){
		cant[representante_nodo_s] = cant[representante_nodo_s] + cant[representante_nodo_e];
	}
	return cant_nodos_conectados;
}

int main(){
	int cant_casos;
	int cant_oficinas;
	int cant_querys;
	int arco_eliminar;
	int v, w, i;
	int oficinas_conectadas = 0;
	char tipo_query;


	// Lectura de cantidad de casos 
	cin >> cant_casos;
	while(cant_casos > 0){
		arcos.clear();
		querys.clear();
		cant_casos-=1;
		cin >> cant_oficinas;
		i=0;
		oficinas_conectadas = (cant_oficinas*(cant_oficinas-1))/2;

		while(i < cant_oficinas){
			elementos.push_back(i+1);
			padre.push_back(i+1);
			cant.push_back(1);
			eliminados.push_back(0);
			i+=1;
		}
		while(cant_oficinas > 1){
			cant_oficinas-=1;
			cin >> v >> w;
			arcos.push_back(make_pair(v,w));
		}
		cin >> cant_querys;
		while(cant_querys > 0){
			cant_querys-=1;
			cin >> tipo_query;
			if(tipo_query == 'Q'){
				querys.push_back(make_pair(tipo_query,-1));
			}else{
				cin >> arco_eliminar;
				eliminados[i-1]=1;
				querys.push_back(make_pair(tipo_query,arco_eliminar));
			}
		}
		for(int i = 0; i < arcos.size(); i++){
			if(eliminados[i]==0){
				unir(arcos[i].first,arcos[i].second);
			}
		}
		for(){}

		for(){}
			
	}
}
