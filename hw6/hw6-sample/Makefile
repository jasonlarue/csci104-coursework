search: search.cpp WebPage.cpp
	g++ -g -Wall -std=c++11 WebPage.cpp search.cpp -o search

WebPage: WebPage.cpp
	g++ -g -Wall -std=c++11 WebPage.cpp -c

crawler: crawler.cpp
	g++ -g -Wall -std=c++11 crawler.cpp -o crawler

clean:
	rm -rf search WebPage.o
