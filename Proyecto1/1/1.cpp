#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

int pruebas;
// Variables del problema
int N , R , M , U , V ; 
double costo_regular = 0.0 , costo_especial = 0.0;
// Listas donde guardaremos los datos
vector < pair < int , int > > lista_nodos;
vector < pair < pair < int, int >, pair < int, int > > > grafo;
vector < pair < double , pair < pair < int, int > , pair < int, int > > > > lista_arcos;


double calcular_distancia(pair < int , int > punto1, pair < int, int > punto2){
	// Sacamos la distancia entre dos puntos cualquieras
	return sqrt( pow ( punto2.first - punto1.first, 2.0 ) + \
		pow( punto2.second - punto1.second, 2.0 ) );
}

double calcular_costo(pair <int, int> punto1, pair <int, int> punto2){
	// Funcion auxiliar para calcular los costos dados dos puntos
	int distancia = calcular_distancia(punto1,punto2);

	if ( distancia > R )
	{
		return distancia*V;
	}
	else
	{
		return distancia*U;
	}
}

void lanzar_cable( pair < int, int > punto1 , pair < int, int > punto2 ){
	// Funcion que crea los arcos de nuestro grafo reducido

	int distancia = calcular_distancia( punto1,punto2 );
	grafo.push_back( make_pair( punto1,punto2 ) );
	
	if (distancia > R)
	{
		costo_especial += distancia*V;
	}
	else
	{
		costo_regular +=  distancia*U;
	}

}

void calcular_posibles_arcos( vector < pair < int , int > > lista_nodos ){
	// Con esta funcion, se crean todos los posibles arcos que pueda tener el grafo

	lista_arcos.clear();
	for (int i = 0; i < lista_nodos.size(); ++i)
	{
		pair < int, int > punto1 = lista_nodos[i];

		for (int j = i + 1; j < lista_nodos.size(); ++j)
		{
			pair < int, int > punto2 = lista_nodos[j];
			lista_arcos.push_back(make_pair(calcular_costo(punto1,punto2),make_pair(punto1,punto2)));
		}
	}
}

bool buscar_nodos_en_grafo(pair < int, int > punto){
	// Buscamos la existencia delpunto en nuestro grafo reducido
	for (int i = 0; i < grafo.size(); ++i)
	{
		/* code */
		if (grafo[i].first == punto ){
			return true;
		}
		if (grafo[i].second == punto){
			return true;
		}

	}
	return false;
}

void imprimir_lista_arcos(){
	// Funcion axuiliar que sirve para debug
	for (int i = 0; i < lista_arcos.size(); ++i)
		{
		   cout << lista_arcos[i].first << " - " \
		   		<< lista_arcos[i].second.first.first << "," \
		   		<< lista_arcos[i].second.first.second << " / " \
		   		<< lista_arcos[i].second.second.first << "," \
		   		<< lista_arcos[i].second.second.second << endl;
		}
}

int main(){
	// Coordenadas
	int x , y;

	cin >> pruebas;

	for (int prueba = 0; prueba < pruebas; ++prueba)
	{
		
		// Inicializacion de las variables
		grafo.clear();
		lista_nodos.clear();
    	costo_regular = 0.0 , costo_especial = 0.0;
		
		cin >> N >> R >> M >> U >> V ;
		for (int i = 0; i < N; ++i)
		{
			
			// Lectura de pares
			cin >> x >> y;
			
			// Guardamos las variables en una lista de pares
			lista_nodos.push_back(make_pair(x,y));

		}

		// Con lo datos,creamos un arbol.
		calcular_posibles_arcos(lista_nodos);

		// Ordenamos por costo para hacer el Kruskall
		sort(lista_arcos.begin(), lista_arcos.end());
		
		// Cantidad max de compomentes conexas
		int componentes_conexas = N - M;

		for (int arco = 0; arco < lista_arcos.size() && componentes_conexas ; ++arco)
		{
			// Se guardan los puntos para un uso mas sencillo 
			pair <int, int> punto1 = lista_arcos[arco].second.first;
			pair <int, int> punto2 = lista_arcos[arco].second.second;
			
			if (arco == 0)
			{
				lanzar_cable(punto1 , punto2);
				componentes_conexas--;
			}else
			{
				if (buscar_nodos_en_grafo(punto1))
				{
					if (buscar_nodos_en_grafo(punto2))
					{
					}else
					{
						lanzar_cable(punto1 , punto2);
						componentes_conexas--;
					}
				}else
				{
					if (buscar_nodos_en_grafo(punto2))
					{

						if (buscar_nodos_en_grafo(punto1))
						{
						}else
						{
							lanzar_cable(punto1,punto2);
							componentes_conexas--;
						}
					}
				}
			}
		}
		// imprimir_lista_arcos();		
		printf("Caso #%d: %.3lf %.3lf\n",prueba+1,costo_regular,costo_especial);
		// cout << endl;
	}
}