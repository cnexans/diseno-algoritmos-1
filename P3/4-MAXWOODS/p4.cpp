#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int T; // Casos de prueba 
int m,n; // Columnas, Filas
char data[200][200]; // Almacenar la entrada
int dp[2][200]; // Almacenar dp
int salida;
int main(){
	cin >> T;
	while(T--){
		memset(data,0,sizeof(data));
		int mejor = 0;
		cin >> m >> n;
		for(int i =0; i < m;i++){
			dp[1][i]=0;
			dp[2][i]=0;
		}
		for (int in = 0 ; in < n; in++){
			for (int im = 0; im < m; im++){
				cin >> data[in][im];
			}
			// if (data[0][0] == '#'){
			// 	goto stop;
			// }else{
				if (in%2==0){ // DERECHA
					for(int i = 0; i < m; i++){
						if(i!=0){
							dp[2][i]=max(dp[2][i-1],dp[1][i]);
						}else{
							if (data[in][i]=='#'){
								dp[2][i]=-1;
							}else{
								dp[2][i]=dp[1][i];
								
							}
						}
						if(data[in][i]!='#'){
							if(in==0){
								if(dp[2][i-1]!=-1){
									if (data[in][i]=='T'){
										dp[2][i]=1+dp[2][i];
									}else{
										dp[2][i]=dp[2][i];
									}
								}else{
									dp[2][i]=-1;
								}
							}else{	
								if(i>0){
									if((dp[1][i]!=-1)||(dp[2][i-1]!=-1)){
										if (data[in][i]=='T'){
											dp[2][i]=1+dp[2][i];
										}else{
											dp[2][i]=dp[2][i];
										}

									}else{
										dp[2][i]=-1;
									}
								}else{
									if(dp[1][i]!=-1){
										if (data[in][i]=='T'){
											dp[2][i]=1+dp[2][i];
										}else{
											dp[2][i]=dp[2][i];
										}

									}else{
										dp[2][i]=-1;
									}
								}
							}
						}
						if(data[in][i]=='#'){
							dp[2][i]=-1;
						}	
					}
				}else{ // IZQUIERDA
					for(int i = m-1;i >= 0; i--){
						if(i!=m-1){
							dp[2][i]=max(dp[2][i+1],dp[1][i]);
						}else{
							dp[2][i]=dp[1][i];
						}
						if(data[in][i]!='#'){
							if(i!=m-1){
								if((dp[1][i]!=-1)||(dp[2][i+1]!=-1)){
									if(data[in][i]=='T'){
										dp[2][i]=1+dp[2][i];
									}else{
										dp[2][i]=dp[2][i];

									}
								}else{
									dp[2][i]=-1;
								}
							}else{
								if(dp[1][i]!=-1){
									if(data[in][i]=='T'){
										dp[2][i]=1+dp[2][i];
									}else{
										dp[2][i]=dp[2][i];
									}

								}else{
									dp[2][i]=-1;
								}
							}
						
						}
						if(data[in][i]=='#'){
							dp[2][i]=-1;
						}		
					}

				// }
			}
			//mejor = -1;
			for(int i =0; i < m;i++){
				mejor = max(mejor,dp[2][i]);
				dp[1][i]=dp[2][i];
				dp[2][i]=0;
			}
			// for(int i =0; i < m;i++){
			// 	mejor = max(mejor,dp[2][i]);
			// 	cout <<		dp[1][i] << " " ;
			// }
			// cout << endl;

		}
		// stop:
		salida = 0;
		//salida = mejor;
		for(int i =0; i< m; i++){
			salida = max(salida,dp[1][i]);
		}
		cout << max(salida,mejor) << endl;
		// cout << '0' << endl;
	}
return 0;

}
