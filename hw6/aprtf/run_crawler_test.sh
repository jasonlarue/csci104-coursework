#!/bin/bash

cd team3128_wiki
rm -rf crawler_test/output.txt

valgrind --tool=memcheck --leak-check=yes ../../crawler crawler_test/config.txt

if diff -s crawler_test/output.check crawler_test/output.txt ; then
	echo "Passed crawler test!"
	exit 0
else
	echo "Failed crawler test!"
	exit 1
fi