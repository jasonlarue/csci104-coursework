#include "functor.h"
#include <iostream>

using namespace std;

int main(){
	string s2 = "ABCD";
	string s1 = "1234";

	NumStrComp test;

	cout << test(s1, s2) << endl;
}
