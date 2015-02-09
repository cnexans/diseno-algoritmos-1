int obtenerColorMinimo(){
	int colorPosible = 1;
	std::vector <int> cuenta_colores;
		for (int i=0; i <  adyacentes[0].second.size(); i++){
			cuenta_colores.push_back(colores[adyacentes[0].second]);
		    sort(cuenta_colores.begin(),cuenta_colores.end(),compInt);
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
	for (int i=0; i <  (this->_nodos).size(); i++){
			if((colores[i] == 0) return true;
	}
	return false;
}

bool compGradoAdyNodo (vector i, vector j){
	return ((i.size()) > (j.size())); 
}

void CalcularGradoColor(int j){
	vector <int> cuenta_colores;
	for(int i =0;i<adyacente[grado[j].first].second.size();i++){
		int color_ady = colores[adyacente[j].second[i]];
		bool estaColor = false;
		for(int j = 0; j < cuenta_colores.size(); j++){
			if (cuenta_colores[j] == color_ady){  
				estaColor = true;
				break;
			}
		}	
	   if( !estaColor && color_ady > 0){
			colores.push_back(color_ady);
	   }
	}
	grado[j].second = cuenta_colores.size();
}

ResultadoGrafo algoritmoDsatur(){

  	//Vector de nodos que se irá llenando con los nodos a los que ya se le haya asignado 
  	//un color
	vector <int > nodos_aux;
	//Ordenar el conjunto de nodos tomando en cuenta sus grados de adyacencia
	sort (adyacentes.begin(), adyacentes.end(), compGradoAdyNodo);
	colores[0]=1;	
	int i =0;
	nodos_aux.push_back(i);
	adyacentes.erase(adyacentes.begin());
	
	if(verticesSinColor()){
		do{
			//Ordenar el conjunto de nodos tomando en cuenta el grado de color del nodo
		    sort (grado.begin(), grado.end(), compGradoColorNodo);	
		    CalcularGradoColor(0)
			int grado_max = grado[0].second;
			int numNodGrado = 1;
			for( int i = 0;i <  adyacentes.size(); i++){
				if(adyacentes.second.size() == grado_max ) 
					numNodGrado++;
			}
			sort (adyacentes.begin(), adyacentes.begin() + numNodGrado - 1, compGradoAdyNodo);		
			//Luego de ordenar los nodos, se colorean en ese orden con el mínimo color posible
			int min_color = obtenerColorMinimo();
			colores[adyacentes[0].first]=min_color;
			nodos_aux.push_back(adyacentes[0].first);
			
			(graph->_nodos).erase((graph->_nodos).begin());
		} while(verticesSinColor());
	}
	   return resultado;
}