// Librerías a importar
#include <stdio.h>
#include <iostream>
#include <limits>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


int main(void){
	cout << "200" << endl;
	for(int i=0;i<200;i++)
		cout << rand()%10 << " ";
	cout << endl << "-1" << endl;
}