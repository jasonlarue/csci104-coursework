#!/bin/bash

cd team3128_wiki
rm -rf searchengine_test/output.txt

# test search engine's ability to use config.txt if no file is provided
cp searchengine_test/config.txt .
valgrind --tool=memcheck --leak-check=yes ../../search
rm -rf config.txt

if diff -s searchengine_test/output.check searchengine_test/output.txt ; then
	echo "Passed flashback test!"
	exit 0
else
	echo "Failed flashback test!"
	exit 1
fi
