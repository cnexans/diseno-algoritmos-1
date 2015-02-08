
ResultadoGrafo algoritmoBrelaz(Grafo * graph){
	std::vector<Nodo::Nodo *> nodos_solucion((graph->_nodos).size());
	n = (graph->_nodos).size();
	ResultadoGrafo resultado = algoritmoDsatur(graph);
	q = 0;
	graph->_nodos = resultado.nodos;
	w = numCliqueGrafo(graph);
	back = false;
	k = w ;

	
	while(true){
		if(back == false){
			int uk = max_element(color.begin(),color.last());
			int min = min(uk + 1, q - 1);
			vector <int> conjunto(min);

			//obtengo todos los colores de 1 hasta el min(uk+1,q-1)
			for (unsigned int i=1; i<=min; i++)
		    conjunto[i-1] = i;
			
			//Para cada elemento de la solucion parcial
			for(int j = 0;j < k; j++){
				//Si el elemento es vecino del nodo k
				if(find(adyacentes[k].begin()+1, adyacentes[k].end(), j) != v.end()){
					if((conjunto.empty())==false){
							    vector<int>::iterator elemento = find(conjunto.begin()+1,conjunto.end(),colores[j]) ;
								if(elemento != conjunto.end()){
									conjunto.erase(elemento);
								}
					}else{
						
						break;
					}
				}
			}
			return conjunto;

		}else{
			int c = colores[k];
			marcados[k]=false;
			if(colores_posibles[k].empty() == false){
					std::vector<int>::iterator elemento =	find(colores_posibles[k].begin()+1,colores_posibles[k].end(),color) ;
			if(elemento != colores_posibles.end()){
					colores_posibles.erase(elemento);
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
			label(k, graph->_nodos );

			for(int i =0; i < k; i++){
				vector<int> coloresEnUso;
				if(find(adyacentes[k].begin()+1, adyacentes[k].end(), nodo_aux2) != v.end()){
							if(binary_search(coloresEnUso.begin(),coloresEnUso.end(),nodo_aux2->GetColor()) == false){
								marcados[i]=true;								
								coloresEnUso.push_back(colores[nodo_aux2]);
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