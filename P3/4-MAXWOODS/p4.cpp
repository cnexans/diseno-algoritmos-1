#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;


int T; // Casos de prueba 
int m,n; // Columnas, Filas
char data[200][200]; // Almacenar la entrada
int dp[2][200]; // Almacenar dp
int salida;
int mejor;
const int infi_neg = -100000;
int main(){
	cin >> T;
	while(T--){
		memset(data,0,sizeof(data));
		mejor = 0;
		int salida = 0;
		cin >> n >> m;
        for(int i=0;i<n;i++){
            cin >> data[i];
        }
        for(int j=0;j<m;j++){
            dp[1][j]=0;   
            dp[0][j]=0;            
        }
        if(data[0][0]=='T'){
        	mejor = dp[1][0] = 1;  
        }
        if(data[0][0]=='#'){
        	mejor = 0;
        	dp[1][0] = infi_neg;
        }
     
        //cout << (data[0][0]=='T');
        for(int i=1;i<m;i++){
            if(data[0][i]=='#'){
                for(int j=i;j<m;j++){
                    dp[1][j]=infi_neg;             
                }
                break;
            }
            dp[1][i]=dp[1][i-1]+(data[0][i]=='T');
            mejor = max(mejor,dp[1][i]);
		}
		for(int k =0; k< m; k++){
			mejor = max(mejor,dp[1][k]);	
			// cout << dp[1][k] << " ";
			dp[0][k] = dp[1][k];
		}
		// cout << endl;
		for(int i=1;i<n;i++){
			for(int k =0; k< m; k++){
				mejor = max(mejor,dp[1][k]);
				//cout << dp[1][k] << " ";
				dp[0][k] = dp[1][k];
			}
			// cout << endl;
			if(i%2==1){
				if(data[i][m-1]=='#'){
			        dp[1][m-1]=infi_neg;
		        }
		        else{
		        	if(data[i][m-1]=='T'){
		            	dp[1][m-1]=dp[0][m-1]+1;
		        	}else{
		        		dp[1][m-1]=dp[0][m-1];
		        	}
		        }
		        mejor = max(mejor,dp[1][m-1]);
		        for(int j=m-2;j>=0;j-=1){
		        	if(data[i][j]=='T'){
		            	dp[1][j] = max(dp[0][j],dp[1][j+1])+1;
		        	}else{
		        		dp[1][j] = max(dp[0][j],dp[1][j+1]);
		        	}
		            if(data[i][j]=='#')
		                dp[1][j]=infi_neg;
		            mejor = max(mejor,dp[1][j]);
		        }
		    }else{
		    	if(data[i][0]=='#'){
			        dp[1][0]=infi_neg;
		        }
		        else{
		        	if(data[i][0]=='T'){
		            	dp[1][0]=dp[0][0]+1;
		        	}else{
		        		dp[1][0]=dp[0][0];
		        	}
		        }
		        mejor = max(mejor,dp[1][0]);
		        for(int j=1;j<=m-1;j+=1){
		        	if(data[i][j]=='T'){
		            	dp[1][j] = max(dp[0][j],dp[1][j-1])+1;
		        	}else{
		        		dp[1][j] = max(dp[0][j],dp[1][j-1]);
		        	}
		            if(data[i][j]=='#')
		                dp[1][j]=infi_neg;
		            mejor = max(mejor,dp[1][j]);
		        }
		    }
		    			for(int k =0; k< m; k++){
				// cout << dp[1][k] << " ";
			}
			 // cout << endl;

		}
		// stop:
		salida = 0;
		//salida = cu;
		for(int i =0; i< m; i++){
			salida = max(salida,dp[1][i]);
		}
		cout << max(salida,mejor) << endl;
		// cout << '0' << endl;
	}
return 0;

}