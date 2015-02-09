ResultadoGrafo algoritmoBrelaz(Grafo * graph){
	
	clock_t t_ini, t_fin;
	double secs;
	t_ini = clock();
	std::vector<Nodo::Nodo *> nodos_solucion((graph->_nodos).size());
	n = (graph->_nodos).size();
	
	ResultadoGrafo resultado = algoritmoDsatur(graph);
	q = 0;

	graph->_nodos = resultado.nodos;

	w = numCliqueGrafo(graph);
	
//Aqui coloco los label para el clique inicial
	for(int i = 0;i<w;i++){
		(graph->_nodos[i])->SetLabel(true);
	}
	
	// Este for es para dar la primera solucion parcial
	for (int i=0; i < (graph->_nodos).size(); i++) {
			nodos_solucion[i] = (new Nodo((graph->_nodos)[i]->GetId()));
			int pos_color = ((resultado.nodos)[i])->GetColor() ;
			(nodos_solucion[i])->SetColor(pos_color);
				if(pos_color > q){
					q = pos_color;
				}
	}

	back = false;
	k = w ;

	
	while(true){
		

	
		if(back == false){
			
	  	(graph->_nodos)[k]->SetColoresPosibles(	calcularConjunto_UK(k,(graph->_nodos)));


		}else{
			
			int c = (graph->_nodos)[k]->GetColor();
			(graph->_nodos)[k]->SetLabel(false);
			(graph->_nodos)[k]->quitarColorPosible(c);	

			
		}
		
		std::vector<int> conjuntok = (graph->_nodos)[k]->GetColoresPosibles();
						
		if(	conjuntok.empty() == false){

			
			(graph->_nodos)[k]->SetColor(conjuntok[0]);

			k = k+1;

			if(k>=n){
				
				int	s = 0;
				int pos_color = 0;
				for (int i=0; i < (graph->_nodos).size(); i++) {
				
					pos_color = (graph->_nodos)[i]->GetColor() ;
					(nodos_solucion[i])->SetColor(pos_color);
					
					if (pos_color > s) {
						s = pos_color ;
					}
				}
				q = s;
				if(q==w){
					t_fin = clock();
					secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
					ResultadoGrafo resultado = {secs*1000.0,nodos_solucion,graph->GetNombre(),graph->GetNombreSolucion()} ;
				  return resultado;
				}
				for(int j = 0 ; j < n ; j++ ){	
					if((graph->_nodos)[j]->GetColor() == q){
						k = j;
						break;
					}
				}
				for(int j = n-1 ; j >= k ; j-- ){
					(graph->_nodos)[j]->SetLabel(false);
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
				
			for(int p = k-1; p >= 0;p--){
							
					if((graph->_nodos)[p]->GetLabel() == true){
						k = p;
						break;
					}
			}

			if(k<w){
			
				t_fin = clock();
				secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
				ResultadoGrafo resultado = {secs*1000.0,nodos_solucion,graph->GetNombre(),graph->GetNombreSolucion()} ;
			  	return resultado;
			}
				
		}
	
	}	
}
