#include "rotateBST.h"
#include "splayTree.h"
#include "cacheLRU.h"
#include <string>

using namespace std;

int main() {
	SplayTree<int, string> s;
		pair<int, string> item1(1, "one");
			//pair<int, string> item4(4, "four");
	pair<int, string> item5(5, "five");
	pair<int, string> item3(3, "three");
	pair<int, string> item7(7, "seven");
	pair<int, string> item4(4, "four");
	pair<int, string> item6(6, "six");
	pair<int, string> item9(9, "nine");
	pair<int, string> item10(10, "ten");
	pair<int, string> item2(2, "two");
	pair<int, string> item8(8, "eight");
	pair<int, string> item13(13, "thirteen");
	pair<int, string> item11(11, "eleven");
	pair<int, string> item12(12, "twelve");
	pair<int, string> item15(15, "fifteen");
	pair<int, string> item14(14, "fourteen");
	pair<int, string> item16(16, "sixteen");
	pair<int, string> item17(17, "seventeen");

		//3 5 8 4 2 1 7 9 10 6
	s.insert(item3);
	s.insert(item5);
	s.insert(item8);
	s.insert(item4);
	s.insert(item2);
	s.insert(item1);
	s.insert(item7);
	s.insert(item9);
	s.insert(item10);
	s.insert(item6);
	s.print();
	s.remove(2);
	s.print();
	s.clear();


	// testing on empty tree
	if(s.findMin() == s.end()) {
		cout << "min is null" << endl;
	}
	if(s.findMax() == s.end()) {
		cout << "max is null" << endl;
	}
	s.deleteMaxLeaf();
	s.deleteMinLeaf();
	if(s.find(6) == s.end()) {
		cout << "null" << endl;
	}
	s.remove(56);

	// testing on tree with one node
	s.insert(item5);
	s.print();
	s.insert(item5);
	cout << s.findMin()->first << endl;
	cout << s.findMax()->first << endl;
	s.print();
	s.remove(5);
	cout << "1" << endl;
	s.print();
	cout << "2" << endl;

	s.insert(item7);
	s.print();
	s.deleteMaxLeaf();
	s.print();

	s.insert(item8);
	s.print();
	s.deleteMinLeaf();
	s.print();

	// testing on tree with two nodes
	s.insert(item9);
	s.insert(item3);
	s.print();
	cout << "it3: " << endl;
	cout << s.find(3)->first << endl;
	s.printRoot();
	s.print();
	cout << "it9: " << endl;
	cout << s.find(9)->first << endl;
	s.printRoot();
	s.print();
	s.deleteMaxLeaf();
	s.print();
	s.printRoot();
	s.deleteMaxLeaf();
	s.print();
	s.printRoot();

	// im bored
	s.insert(item10);
	s.print();
	s.printRoot();
	s.insert(item3);
		s.print();
	s.printRoot();
	s.insert(item2);
		s.print();
	s.printRoot();
	s.insert(item15);
		s.print();
	s.printRoot();
	s.insert(item12);
		s.print();
	s.printRoot();
	s.insert(item11);
		s.print();
	s.printRoot();
	s.insert(item14);
		s.print();
	s.printRoot();
	s.insert(item13);
		s.print();
	s.printRoot();
	s.insert(item16);
		s.print();
	s.printRoot();
	s.insert(item17);

	s.print();
	s.printRoot();
	s.deleteMinLeaf();
	s.print();
	s.printRoot();
	s.deleteMaxLeaf();
	s.print();
	s.printRoot();
	s.deleteMaxLeaf();
	s.print();
	s.printRoot();

	s.insert(item15);
		s.print();
	s.printRoot();
	s.find(1);
			s.print();
	s.printRoot();

	s.find(17);
	s.print();
	s.printRoot();

		s.findMin();
	s.print();
	s.printRoot();

		s.findMax();
	s.print();
	s.printRoot();

	s.find(12);
		s.print();
	s.printRoot();

	s.remove(12);
			s.print();
	s.printRoot();

	s.deleteMinLeaf();
			s.print();
	s.printRoot();

		s.deleteMaxLeaf();
			s.print();
	s.printRoot();

			s.deleteMaxLeaf();
			s.print();
	s.printRoot();

				s.remove(3);
			s.print();
	s.printRoot();

			s.remove(100);
			s.print();
	s.printRoot();





	s.print();
	s.remove(4);
	s.print();
	s.insert(item5);
	s.print();
	s.insert(item11);
	s.print();
	s.insert(item15);
	s.print();
	cout << (s.findMin())->first << endl;
	s.print();
	cout << (s.findMax())->first << endl;
	s.print();
	s.find(4);
	s.print();
	s.remove(5);
	s.print();
	s.remove(11);
	s.print();
	s.deleteMinLeaf();
	s.print();
	s.insert(item12);
	s.insert(item14);
	s.insert(item17);
	s.insert(item3);
	s.insert(item2);
	s.print();
	s.findMax();
	s.print();
	s.findMin();
	s.print();
	s.find(4);
	s.print();
	s.deleteMaxLeaf();
	s.print();

	s.clear();
	s.print();

	s.deleteMaxLeaf();
	s.print();


	// cacheLRU<int, string> c(5);
	// c.put(item5);
	// c.print();
	// try {
	// 	c.get(4);
	// } catch(logic_error& e) {
	// 	cout << e.what() << endl;
	// }
	// c.put(item6);
	// c.put(item3);
	// c.put(item11);
	// c.put(item12);
	// c.print();
	// try {
	// 	cout << c.get(3).first << endl;
	// } catch(logic_error& e) {
	// 	cout << e.what() << endl;
	// }
	// c.print();
	// c.put(item7);
	// c.print();
	// try {
	// 	cout << c.get(80).first << endl;
	// } catch(logic_error& e) {
	// 	cout << e.what() << endl;
	// }

	return 0;
}
