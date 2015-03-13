#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

string palabras_excluir[100];
string frase_revisar[150];

int main(){
	string line;
	istringstream linestream(line); // #include <sstream>
	string word;
	int cant;
	int i;
	int j;
	while(cin >> cant, cant=!0){
		i = 0;
		while(i < cant){
			cin >> palabras_excluir[i];
			i=i+1;
		}
		bool ultimo = false;
		while(!(ultimo)){
			while (std::getline(cin, line)){
				istringstream linestream(line);
				string word;
				j = 0;
				while (linestream >> word){
					frase_revisar[j] = word;
					if(frase_revisar[j] == "CASE"){
						cout << ultimo;
							ultimo = true;
							cout << ultimo;
							break;
					}
					// cout << frase_revisar[j];
					j = j + 1;
				}
				if(ultimo) break;
			}	
			if(ultimo) break;
			
		}

	}
	return 0;
}



