

#include <iostream>
#include <vector>
//#include "LengthMismatch.h"
#include "Thanksgiving.h"

int main(){
	std::vector<int> v1;
	std::vector<int> v2;

	while (1){
		std::cout << "Enter what you want in v1: ";
		int element;
		std::cin >> element;
		if (element == -1) {
			break;
		}
		v1.push_back(element);
	}
	for (unsigned int i=0; i<v1.size(); i++) {std::cout << v1[i] << " ";}
	std::cout << std::endl;

	while (1){
		std::cout << "Enter what you want in v2: ";
		int element;
		std::cin >> element;
		if (element == -1) {
			break;
		}
		v2.push_back(element);
	}
	for (unsigned int i=0; i<v2.size(); i++) {std::cout << v2[i] << " ";}
	std::cout << std::endl;

	std::vector<std::pair<int, int> > assignments;

	//try {
		Thanksgiving* thingy = new Thanksgiving();
		assignments = thingy -> assignPlates(v1, v2);
	/*}
	catch (LengthMismatch LM) {
		std::cout << LM.what() << std::endl;
	}*/
	std::cout << "AMOUNT OF PAIRINGS: " << assignments.size() << std::endl;
	for (unsigned int i=0; i<assignments.size(); i++){
		std::cout << assignments[i].first << " " << assignments[i].second << std::endl;
	}

}
