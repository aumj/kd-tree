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

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "kd_math.h"
#include "csv_handler.h"

#include <iostream>

using namespace std;

template <typename T>
vector<vector<T>> CsvHandler::CsvReadInput(const string& file_name) {
    vector<vector<T>> input_points;
    vector<T> single_point;
    ifstream input_file(file_name);
    string line;
    cout << "Enetered this function" << endl;

    while (input_file.good() && !input_file.eof()) {
        cout << "File is good" << endl;
       if (!getline(input_file, line))
           continue;
        getline(input_file, line);
        std::stringstream lineStream(line);
        cout << "line is " << line << endl;
        string cell;

        // TODO: explore emplace_back for more efficiency

        while(std::getline(lineStream, cell, ',')) {
            cout << cell << "    " << std::stof(cell) << endl ;
                        single_point.push_back(std::stof(cell));
        }
        std::cout << "Size of each point = " << single_point.size() << std::endl;
        input_points.push_back(single_point);
        single_point.clear();
    }
    return input_points;
}