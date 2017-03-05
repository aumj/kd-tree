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

#ifndef FILE_HANDLER_CPP_
#define FILE_HANDLER_CPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "file_handler.h"
#include "kd_math.h"

using namespace std;

template <typename T>
vector<Point<T>*> FileHandler<T>::csvReadInput(const string& file_name) {
    vector<Point<T>*> input_points;
    vector<T> single_point;
    ifstream input_file(file_name);
    string line;
    int line_count = 0;

    while (input_file.good() && !input_file.eof()) {
       if (!getline(input_file, line))
           continue;
        getline(input_file, line);
        stringstream lineStream(line);
        string cell;

        while(getline(lineStream, cell, ',')) {
            single_point.push_back(T(stod(cell)));
        }
        Point<T>* pt = new Point<T>(single_point, line_count);
        input_points.push_back(pt);
        single_point.clear();
        ++line_count;
    }
    input_file.close();
    return input_points;
}

template <typename T>
void FileHandler<T>::csvWriteNnResults(const vector<size_t>& pointId,
                                      const vector<T>& dist,
                                      const string& file_name) {

    cout << "Writing search results to "<< file_name << endl;
    ofstream output_file(file_name);

    auto iter_d = dist.begin();
    for (auto iter_pt = pointId.begin(); iter_pt != pointId.end(); ++iter_pt, ++iter_d) {
        output_file << *iter_pt << "," << *iter_d << endl;
    }
    output_file.close();
}

template class FileHandler<float>;
template class FileHandler<double>;

#endif // FILE_HANDLER_CPP //
