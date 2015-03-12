#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
string t = "Banana nana nana nana";
string s = "nana";
string::size_type i = t.find(s);
if (i != string::npos)
   t.erase(i, s.length());

cout << endl << t;
return 0;

}
