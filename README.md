# KD-Tree Library

This library provides an implementation for building 
KD-Trees and performing nearest-neighbor searches. It
is templated such that it supports float and double 
precision types for any set of k-dimensional points.

## Directory Structure

**kd-tree/**
- **data/** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Sample input, query and tree data
- **include/** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; External header files to be used
- **src/** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; All source files (*.cpp, *.h)
- **LICENSE.txt** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	MIT License boilerplate
- **Makefile** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; To build the package
- **README.txt** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This file

## Build Instructions

This library uses C++11 features and was tested on 
Ubuntu 14.04.05 LTS (trusty) 64-bit using the compiler: 
g++ (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4

To build, clone the package and run the Makefile
in the kd-tree folder: 

```shell
usr@host:kd-tree$ make
```

## Usage Instructions

1. Build KD-Tree:
```shell
$ ./KDTree --build <path/input_file.csv>
```
Sample data can be found in ./data/
Output file "tree.json" is generated

2. Query KD-Tree for Nearest Neighbors:
```shell
$ ./KDTree --query <path/query_file.csv> <path/tree.json>(optional)
```
If tree file is not entered, the default "./data/sample_tree.json" is used. 
Output files "query_results.csv" and "query_results_truth.csv" are generated.

3. Help:
```shell
$ ./KDTree --help
```
Usage instructions can be viewed here.
