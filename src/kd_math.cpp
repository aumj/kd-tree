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

#ifndef KD_MATH_CPP_
#define KD_MATH_CPP_


#include "kd_math.h"
#include <functional>
#include <numeric>
#include <cmath>
#include <vector>
#include <cassert>
#include <algorithm>

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
typename Point<T>::iterator Point<T>::begin() {
    return  &point_vect_[0];;
}

template <typename T>
typename Point<T>::const_iterator Point<T>::begin() const{
    return  &point_vect_[0];
}

template <typename T>
typename Point<T>::iterator Point<T>::end() {
    return  (begin() + getDimension()-1);
}

template <typename T>
typename Point<T>::const_iterator Point<T>::end() const {
    return  (begin() + getDimension()-1);
}

template <typename T>
T& Point<T>::operator[] (size_t index) {
    return point_vect_[index];
}

template <typename T>
T Point<T>::operator[] (size_t index) const {
    return point_vect_[index];
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
Point<T> operator+ (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getDimension() == pt2.getDimension());
    vector<T> pt_sum;
    pt_sum.reserve(pt1.getDimension());
    transform(pt1.begin(), pt1.end(), pt2.begin(),
              back_inserter(pt_sum), std::plus<T>());
    return Point<T>(pt_sum);
}

template <typename T>
Point<T> operator- (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getDimension() == pt2.getDimension());
    auto p1 = pt1.getPointVector();
    auto p2 = pt2.getPointVector();
    vector<T> pt_diff;
    pt_diff.reserve(pt1.getDimension());
    transform(p1.begin(), p1.end(), p2.begin(),
                  back_inserter(pt_diff), std::minus<T>());
    return Point<T>(pt_diff);
}

template <typename T>
Point<T> operator* (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getDimension() == pt2.getDimension());
    vector<T> pt_prod;
    pt_prod.reserve(pt1.getDimension());
    transform(pt1.begin(), pt1.end(), pt2.begin(),
              back_inserter(pt_prod), std::multiplies<T>());
    return Point<T>(pt_prod);
}


template <typename T>
Point<T> operator/ (const Point<T>& pt1, const Point<T>& pt2) {
    assert(pt1.getDimension() == pt2.getDimension());
    vector<T> pt_div;
    pt_div.reserve(pt1.getDimension());
    transform(pt1.begin(), pt1.end(), pt2.begin(),
              back_inserter(pt_div), std::divides<T>());
    return Point<T>(pt_div);
}

template <typename T>
Point<T> elemwiseMin (const Point<T>& pt1, const Point<T>& pt2){
    assert(pt1.getDimension() == pt2.getDimension());
    vector<T> elem_min;
    elem_min.reserve(pt1.getDimension());
    auto iter2 = pt2.begin();
    for (auto iter1 = pt1.begin(); iter1!=pt1.end(); ++iter1, ++iter2) {
        elem_min.push_back((*iter1<*iter2 ? *iter1 : *iter2));
    }
    return Point<T>(elem_min);
}

template <typename T>
Point<T> elemwiseMax (const Point<T>& pt1, const Point<T>& pt2){
    assert(pt1.getDimension() == pt2.getDimension());
    vector<T> elem_max;
    elem_max.reserve(pt1.getDimension());
    auto iter2 = pt2.begin();
    for (auto iter1 = pt1.begin(); iter1!=pt1.end(); ++iter1, ++iter2) {
        elem_max.push_back((*iter1>*iter2 ? *iter1 : *iter2));
    }
    return Point<T>(elem_max);
}

template <typename T>
T getDistance(const Point<T>& pt1, const Point<T>& pt2) {
    Point<T> d = pt1 - pt2;
    vector<T> diff = d.getPointVector();
    T dist = sqrt(inner_product(diff.begin(), diff.end(), diff.begin(), T(0.0)));
    return dist;
}

// Properties of a set of Points for each dimension
// Output parameters are {min, max, range, mean, variance};
template <typename T>
std::vector<Point<T>> getDistributionParams(const std::vector<Point<T>*>& data) {
    typename vector<Point<T>*>::const_iterator iter;

    size_t dimension = (*data.begin())->getDimension();
    size_t data_size = data.size();
    vector<T> zeros(dimension, 0);
    vector<T> total_pts(dimension, data_size);

    Point<T> data_min((*data.begin())->getPointVector());
    Point<T> data_max((*data.begin())->getPointVector());
    Point<T> data_range(zeros);
    Point<T> data_mean(zeros);
    Point<T> data_variance(zeros);
    Point<T> total_points(total_pts);

    // Calculate Min, Max and Mean of each dimension of the dataset
    for (iter = data.begin(); iter != data.end(); ++iter) {
        data_mean = data_mean + (**iter);
        data_min = elemwiseMin(data_min, (**iter));
        data_max = elemwiseMax(data_max, (**iter));
    }
    data_mean = data_mean / total_points;
    data_range = data_max - data_min;

    // Calculate variance of the dataset
    for (iter = data.begin(); iter != data.end(); ++iter) {
        data_variance = data_variance + ((**iter - data_mean)*(**iter - data_mean));
    }
    data_variance = data_variance/total_points;

    vector<Point<T>> distro_params = {data_min, data_max, data_range, data_mean,
                                                                data_variance};

    return distro_params;
}

// Calculates the approximate median using binapprox algorithm
template <typename T>
T getApproxMedian(const vector<Point<T>*>& data, const size_t& split_axis,
                  const Point<T>& data_mean, const Point<T>& data_variance) {

    T mean = data_mean[split_axis];
    T std_deviation = std::sqrt(data_variance[split_axis]);
    T lower_limit = mean - std_deviation;
    size_t sample_count = data.size();

    if (sample_count <= 2) {
        vector<T> test = (*data.begin())->getPointVector();
        return test[split_axis];
    }

    // Build histrogram for the Point distribution
    int bin_id;
    int bin_count = 128;
    T bin_size = (2*std_deviation)/bin_count;
    vector<int> histogram(bin_count,0);
    vector<T> sample;

    typename vector<Point<T>*>::const_iterator iter;
    for (iter = data.begin(); iter != data.end(); ++iter) {
        sample = (*iter)->getPointVector();
        bin_id = std::round((sample[split_axis]-lower_limit) / bin_size);
        if (bin_id < 0)
            bin_id = 0;
        else if (bin_id > bin_count-1)
            bin_id = bin_count-1;
        ++histogram[bin_id];
    }

    int lower_half = 0;
    int median_bin;
    for (median_bin = 0; median_bin < histogram.size(); ++median_bin ) {
        lower_half += *(histogram.begin()+median_bin);
        if (lower_half > sample_count/2)
            break;
    }

    T median = lower_limit + median_bin*bin_size + bin_size/2;
    return median;
}

template class Point<float>;
template class Point<double>;


#endif // KD_MATH_CPP_ //
