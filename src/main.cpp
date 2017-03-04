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
#include "csv_handler.h"
#include "kd_tree.h"


using namespace std;

int main(int argc, char * argv[]) {

//    if (argc != 4) {
//        cerr << "Invalid arguments! User entered " << argc-1 << " argument(s), but 3 are required." << endl;
//        cout << "usage: kdtree <input_file.csv> <query_file.csv> <results_file.csv>" << endl;
        // return 0;
//    }
     cout << "Hello World" << endl;

    string s = argv[1];
    vector<Point<double>*> input_data = CsvHandler<double>::CsvReadInput(s);
    cout << "CSV Parsing complete" << endl << "Building KD-Tree..." << endl;
    KdTree<double> tree = KdTree<double>::buildKdTree(input_data);
    cout << "KD-Tree built!" << endl;

    return 0;
}
