#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

// Declaracion de variables globales
vector<pair<int,int> > arcos;
vector<pair<char,int> > querys;
vector<int> salida;
vector<int> elementos;
vector<int> eliminados;
vector<int> padre;
vector<int> cant;

// Procedimiento Find, emulando conjuntos disjuntos
int find(int nodo){
	if(padre[nodo-1] == nodo){
		return nodo;
	}else{
		return find(padre[nodo-1]);
	}
}

// Procedimiento Unir, emulando conjuntos disjuntos
int unir(int nodo_e, int nodo_s){
	int representante_nodo_e = find(nodo_e);
	int representante_nodo_s = find(nodo_s);
	int cant_nodos_conectados = cant[representante_nodo_e-1]*cant[representante_nodo_s-1];
	padre[representante_nodo_s-1] = representante_nodo_e;
	if(representante_nodo_s!=representante_nodo_e){
		cant[representante_nodo_e-1] += cant[representante_nodo_s-1];
	}
	return cant_nodos_conectados;
}

int main(){
	// Declaro las variables
	int cant_casos;
	int cant_oficinas;
	int cant_querys;
	int arco_eliminar;
	int v, w, i;
	int oficinas_conectadas = 0;
	char tipo_query;


	// Lectura de cantidad de casos de prueba
	cin >> cant_casos;

	// Realizo cada caso de prueba
	while(cant_casos > 0){

		// Limpio todas las listas usadas en cada caso de prueba
		arcos.clear();
		querys.clear();
		salida.clear();
		elementos.clear();
		eliminados.clear();
		padre.clear();
		cant.clear();
		cant_casos-=1;
		i = 0;
		
		// Leo la cantidad de oficinas que tendré 
		cin >> cant_oficinas;

		// Calculo la cantidad total de oficinas conectadas al principio
		oficinas_conectadas = (cant_oficinas*(cant_oficinas-1))/2;

		// Lleno las listas con los datos necesarios
		while(i < cant_oficinas){
			elementos.push_back(i+1);
			padre.push_back(i+1);
			cant.push_back(1);
			eliminados.push_back(0);
			i+=1;
		}

		// Leo de la entrada, y creo los arcos
		while(cant_oficinas > 1){
			cant_oficinas-=1;
			cin >> v >> w;
			arcos.push_back(make_pair(v,w));
		}

		// Leo la cantidad de Querys a realizar
		cin >> cant_querys;

		// Creo una lista con los Querys a realizar, y marco los arcos elimnados
		while(cant_querys > 0){
			cant_querys-=1;
			cin >> tipo_query;
			if(tipo_query == 'Q'){
				querys.push_back(make_pair(tipo_query,-1));
			}else{
				cin >> arco_eliminar;
				eliminados[arco_eliminar-1]=1;
				querys.push_back(make_pair(tipo_query,arco_eliminar));
			}
		}

		// Agrego los arcos no eliminados
		for(int i = 0; i < arcos.size(); i++){
			if(eliminados[i]==0){
				unir(arcos[i].first,arcos[i].second);
			}
		}

		// Realizo los Querys en orden inverso y creo los arcos cuando se 'eliminan' para saber cuantas conexiones pierdo al desconectar dicho arco.
		for(int i = querys.size(); i > 0; i--){
			if(querys[i-1].first == 'Q'){
				salida.push_back(oficinas_conectadas);
			}else{
				oficinas_conectadas-=unir(arcos[querys[i-1].second-1].first, arcos[querys[i-1].second-1].second);
			}
		}

		// Imprimo los Querys, pero recorro la lista en orden inverso
		for(int i = salida.size(); i > 0; i--){
			cout << salida[i-1] << endl;
		}
		cout << endl;
			
	}
}