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

#include "kd_math.h"
#include <functional>
#include <numeric>

using namespace std;

template <typename T>
Point<T>::Point(const vector<T>& vect,int idx) :
                point_vect_(vect), index_(idx) {}

template <typename T>
Point<T>::Point(const initializer_list<T>& elem_list, int idx) :
                point_vect_(elem_list), index_(idx) {}

template <typename T>
vector<T> Point<T>::getPointVector() const {
    return point_vect_;
}

template <typename T>
size_t Point<T>::getIndex() const {
    return index_;
}

template <typename T>
size_t Point<T>::getDimension() const {
    return point_vect_.size();
}

template <typename T>
T Point<T>::getDistance(const Point<T>& pt1, const Point<T>& pt2) {
    vector<T> diff = pt1 - pt2;
    T dist = sqrt(inner_product(diff.begin(), diff.end(), 0 ));
    return dist;
}

template <typename T>
bool operator== (const Point<T>& pt1, const Point<T>& pt2) {
    return equal(pt1.begin(), pt1.end(), pt2.begin());
}

template <typename T>
bool operator!= (const Point<T>& pt1, const Point<T>& pt2) {
    return !(pt1 == pt2);
}

template <typename T>
vector<T> operator+ (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getSize() == pt2.getSize());
    vector<T> pt_sum;
    pt_sum.reserve(pt1.getSize());
    transform(pt1.begin(), pt1.end(), pt2.begin(),
              back_inserter(pt_sum), plus<T>());
    return pt_sum;
}

template <typename T>
vector<T> operator- (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getSize() == pt2.getSize());
    vector<T> pt_diff;
    pt_diff.reserve(pt1.getSize());
    transform(pt1.begin(), pt1.end(), pt2.begin(),
              back_inserter(pt_diff), minus<T>());
    return pt_diff;
}






