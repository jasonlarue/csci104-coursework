#include "LengthMismatch.h"
#include <iostream>


using namespace std;


int test_function(int x, int y){
	if (x != y) {
		throw LengthMismatch(x,y);
	}
	return 0;
}

int main(){
	int x;
	int y;
	cout << "Enter an int: "; 
	cin >> x;
	cout << "Enter an int: "; 
	cin >> y;
	
	try {
		test_function(x,y);
	}
	catch (LengthMismatch& error) {
		cout << error.what() << endl;
	}

}