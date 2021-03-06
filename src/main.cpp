// MIT License
//
// Copyright (c) 2017 Aum Jadhav (aum.jadhav@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <string>
#include "kd_math.h"
#include "kd_tree.h"
#include "file_handler.h"
#include "nn_test.cpp"

using namespace std;

int main(int argc, char * argv[]) {

    if (strcmp(argv[1], "--build")==0 && argc==3) {
        vector<Point<double>*> input_data = FileHandler<double>::csvReadInput(argv[2]);
        cout << "CSV Parsing complete" << endl << "Building KD-Tree..." << endl;
        KdTree<double> tree = KdTree<double>::buildKdTree(input_data);
        cout << "KD-Tree built!" << endl;
        KdTree<double>::WriteKDTreeToFile(tree);
    }
    else if (strcmp(argv[1], "--query")==0 && argc >= 3) {
        KdTree<double> saved_tree;
        if (argc == 4)
            KdTree<double>::ReadKDTreeFromFile(saved_tree, argv[3]);
        else
            KdTree<double>::ReadKDTreeFromFile(saved_tree);

        cout << "Reading query data" << endl;
        vector<Point<double>*> query_data = FileHandler<double>::csvReadInput(argv[2]);
        cout << "Finding nearest neighbors..." << endl;
        KdTree<double>::queryKdTree(saved_tree, query_data);

        cout << "Finding nearest neighbors using brute force (for sample_data.csv)..." << endl;
        vector<Point<double>*> input_data = FileHandler<double>::csvReadInput("data/sample_data.csv");
        nnBruteForce(query_data, input_data);
        cout << "Done";
    }
    else if (strcmp(argv[1], "--help")==0) {
        cout << "///////////////////////////////////////////////////////////" << endl;
        cout << "KD-Tree Library" << endl << "Copyright (c) 2017 Aum Jadhav" << endl << endl;
        cout << "Usage:" << endl;
        cout << "1. Build KD-Tree: $./KDTree --build <path/input_file.csv>" << endl;
        cout << "2. Query KD-Tree for Nearest Neighbors: ";
        cout << "$./KDTree --query <path/query_file.csv> <path/tree.json>(optional, default=data/sample_tree.json)" << endl;
        cout << "///////////////////////////////////////////////////////////" << endl;
    }
    else {
        cerr << "Invalid options and/or arguments! Check usage using: $./KDTree --help" << endl;
    }


    return 0;
}
