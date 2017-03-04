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

#include <vector>
#include <numeric>
#include "kd_math.h"
#include "csv_handler.h"

using namespace std;

template <typename T>
void nnBruteForce(const vector<Point<T>*>& query_points, vector<Point<T>*>& sample_points) {
    vector<size_t> pointId;
    pointId.reserve(query_points.size());
    vector<T> dist;
    dist.reserve(query_points.size());
    for (auto iter1 = query_points.begin(); iter1 != query_points.end(); ++iter1) {
//        Point<T> query = *iter1;
        size_t bestNode = numeric_limits<size_t>::max();
        T bestDist = numeric_limits<T>::max();
        for(auto iter2 = sample_points.begin(); iter2 != sample_points.end(); ++iter2) {
            T dist = getDistance(**iter1, **iter2);
            if (dist < bestDist){
                bestNode = (**iter2).getIndex();
                bestDist = dist;
            }
        }
        pointId.push_back(bestNode);
        dist.push_back(bestDist);
    }
    CsvHandler<T>::csvWriteNnResults(pointId, dist, "query_results_truth.csv");
}



