// MIT License
//
// Copyright © 2017 Aum Jadhav (aum.jadhav@gmail.com)
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

#ifndef KD_MATH_H_
#define KD_MATH_H_

#include <vector>
#include <stddef.h>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

// This file provides all the support classes and methods
// for using K-dimensional points

template <class T = double>
class Point{
private:
    std::vector<T> point_vect_; // K-d point vector
    size_t index_;              // Index of point in input file
public:
    // Constructors/Destructor
    Point() = default;
    Point(const std::vector<T>& vect, int idx=-1);
    Point(const std::initializer_list<T>& elem_list, int idx=-1);
    ~Point() = default;

    // Iterator for traversing individual coordinates of a point
    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Overloaded operators[] for accessing individual elements
    T& operator[] (size_t index);
    T operator[] (size_t index) const;

    // Accessor Functions
    std::vector<T> getPointVector() const;

    size_t getIndex() const;

    size_t getDimension() const;

    // Serialization Function
    template<class Archive>
    void serialize(Archive & archive) {
			archive(CEREAL_NVP(point_vect_), CEREAL_NVP(index_));
    }

};

// Operator overloads for Point type

template <typename T = double>
bool operator== (const Point<T>& pt1, const Point<T>& pt2);

template <typename T = double>
bool operator!= (const Point<T>& pt1, const Point<T>& pt2);

template <typename T = double>
Point<T> operator+ (const Point<T>& pt1, const Point<T>& pt2);

template <typename T = double>
Point<T> operator- (const Point<T>& pt1, const Point<T>& pt2);

template <typename T = double>
Point<T> operator* (const Point<T>& pt1, const Point<T>& pt2);

template <typename T = double>
Point<T> operator/ (const Point<T>& pt1, const Point<T>& pt2);

// Element-wise minimum of two Points
template <typename T = double>
Point<T> elemwiseMin (const Point<T>& pt1, const Point<T>& pt2);

// Element-wise maximum of two Points
template <typename T = double>
Point<T> elemwiseMax (const Point<T>& pt1, const Point<T>& pt2);

// Euclidean distance between two Points
template <typename T = double>
T getDistance(const Point<T>& pt1, const Point<T>& pt2);

// Properties of a set of Points for each dimension
// Output parameters are {min, max, range, mean, variance};
template <typename T = double>
std::vector<Point<T>> getDistributionParams(const std::vector<Point<T>*>& data);

// Calculates the approximate median using binapprox algorithm
template <typename T = double>
T getApproxMedian(const std::vector<Point<T>*>& data, const size_t& split_axis,
                         const Point<T>& data_mean, const Point<T>& data_variance);


#include "kd_math.cpp"

#endif // KD_MATH_H_ //
