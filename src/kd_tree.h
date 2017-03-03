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

#ifndef KD_TREE_H_
#define KD_TREE_H_

#include <vector>
#include "kd_math.h"

template <typename T=double>
class KdTreeNode {
public:
    size_t depth;
    size_t split_axis;
    T split_position;
    Point<T> point;
    std::shared_ptr<KdTreeNode<T>> left_child;
    std::shared_ptr<KdTreeNode<T>> right_child;
    
    bool isLeaf() const {
        return (left_child == nullptr && right_child == nullptr);
    }
    
    // TODO: change constructor according to reqd usage in buildTree
    KdTreeNode() = default;
//    KdTreeNode(const int depth, const std::shared_ptr<KdTreeNode>& left = nullptr,
//               const std::shared_ptr<KdTreeNode>& right = nullptr,
//               const int& split_axis = 0, const T& split_position = 0) :
//                depth(depth), left_child(left), right_child(right) {}
    KdTreeNode(const int& depth, const std::shared_ptr<KdTreeNode>& left = nullptr,
               const std::shared_ptr<KdTreeNode>& right = nullptr) : depth(depth) {}
    virtual ~KdTreeNode() = default;
};

template <typename T=double>
class KdTree {
private:
    std::shared_ptr<KdTreeNode<T>> root_;
    enum SplitMethod {cycleAxes, highestVariance, highestRange};
    enum SplitPosition {spatialMedian, objectMedian};
public:
    
    
    KdTree() = default;
    KdTree(const std::shared_ptr<KdTreeNode<T>> root_node);
    ~KdTree() = default;
    
    KdTree<T> getLeftSubtree() const;
    KdTree<T> getRightSubtree() const;
    bool isEmpty() const;
    
    // TODo: make sure all functions are defined in cpp file
    static KdTree<T> buildKdTree(const std::vector<Point<T>*>& input_points);
    static shared_ptr<KdTreeNode<T>> treeBuild(const std::vector<Point<T>*>& input_points, const size_t depth);
    static size_t getSplitAxis(const std::vector<Point<T>>& distro_params, const size_t& depth); // TODO: Fix this!
    static Point<T> getPivot(const std::vector<Point<T>*>& input_points,
                             const size_t& split_axis, const T& split_position);
    
    static void queryKdTree() {};
    static KdTreeNode<T> getNearestNeighbor();
    
};


#include "kd_tree.cpp"

#endif /* KD_TREE_H_ */
