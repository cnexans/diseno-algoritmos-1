#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	// Decalaracion de Variables
	int cant_empleados = 0;
	int cant_actividades = 0;
	int desde = 0;
	int hasta = 0;
	int ultimo;
	int total = 0;
	vector<pair<int,int> > actividades;

	// Leo la cantidad de Empleados
	cin >> cant_empleados;
	
	// Hago el procedimiento por cada empleado de DACE
	while(cant_empleados > 0){
		total=0;
		cin >> cant_actividades;
		actividades.clear();
		// Leo las actividades de dicho empleado de DACE

		while(cant_actividades > 0){
			cin >> desde >> hasta;
			actividades.push_back(make_pair(desde,hasta));
			cant_actividades-=1;
		}

		ultimo = -1;
		// Ordeno el Vector
		sort(actividades.begin(), actividades.end());

		for (int i=1; i < actividades.size(); i++){
			if(ultimo > actividades[i].first){
				total+=1;
			}
			ultimo = actividades[i].second; 
		}

		// Imprimo la cantidad por cada empleado
		cout << total << endl;
		cant_empleados-=1;
	}
	return 0;
}