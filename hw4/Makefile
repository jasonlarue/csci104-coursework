search: search.cpp WebPage.cpp
	g++ -g -Wall WebPage.cpp search.cpp -o search

limitErrors: search.cpp WebPage.cpp
	g++ -g -Wall -fmax-errors=5 WebPage.cpp search.cpp -o search

WebPage: WebPage.cpp
	g++ -g -Wall WebPage.cpp -c

clean:
	rm -rf search WebPage.o
