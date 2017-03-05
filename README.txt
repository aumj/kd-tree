////////////////////////////////////////////////////

		KD-TREE LIBRARY

////////////////////////////////////////////////////

Copyright (c) 2017 Aum Jadhav (aum.jadhav@gmail.com)

This library provides an implementation for building 
KD-Trees and performing nearest-neighbor searches. It
is templated such that it supports float and double 
precision types for any set of k-dimensional points.

DIRECTORY STRUCTURE

kd-tree/
|
|--data/	Sample input, query and tree data
|--include/	External header files to be used
|--src/	 	All source files (*.cpp, *.h)
|--LICENSE.txt 	MIT License boilerplate
|--Makefile	To build the package
|--README.txt	This file

BUILD INSTRUCTIONS

This library uses C++11 features and was tested on 
Ubuntu 14.04.05 LTS (trusty) 64-bit using compiler: 
g++ (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4

To build, clone the package and run the Makefile
in the kd-tree folder: usr@host:kd-tree$ make 

USAGE INSTRUCTIONS

1. Build KD-Tree:

	$ ./KDTree --build <path/input_file.csv>

Sample data can be found in ./data/
Output file "tree.json" is generated



2. Query KD-Tree for Nearest Neighbors:

	$ ./KDTree --query <path/query_file.csv> <path/tree.json>(optional)

If tree file is not entered, the default "./data/sample_tree.json" is used. 
Output files "query_results.csv" and "query_results_truth.csv" are generated.



3. Help:

	$ ./KDTree --help

Usage instructions can be viewed here.




