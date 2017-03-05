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

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <vector>
#include "kd_math.h"

template <typename T=double>
class FileHandler {
public:
    // Reads input file and stores data as a vector of Points
    static std::vector<Point<T>*> csvReadInput(const std::string& file_name="data/sample_data.csv");

    // Writes Nearest-Neighbor search results to file
    // in the format: point_index,distance
    static void csvWriteNnResults(const std::vector<size_t>& pointId,
                                  const std::vector<T>& dist,
                                  const std::string& file_name="query_results.csv");
};

#endif // FILE_HANDLER_H //
