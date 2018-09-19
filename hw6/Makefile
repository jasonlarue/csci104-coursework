search: search.cpp WebPage.cpp
	g++ -g -Wall -std=c++11 WebPage.cpp search.cpp -o search

limitErrors: search.cpp WebPage.cpp
	g++ -g -Wall -std=c++11 -fmax-errors=5 WebPage.cpp search.cpp -o search

WebPage: WebPage.cpp
	g++ -g -Wall -std=c++11 WebPage.cpp -c

crawler: crawler.cpp WebPage.cpp
	g++ -g -Wall -std=c++11 WebPage.cpp crawler.cpp -o crawler

clean:
	