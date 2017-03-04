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

#ifndef KD_TREE_CPP_
#define KD_TREE_CPP_

#include <vector>
#include "kd_math.h"
#include "kd_tree.h"
#include <iostream>
using namespace std;

template <typename T>
KdTree<T>::KdTree(const std::shared_ptr<KdTreeNode<T>> root_node) : root_(root_node) {}

template <typename T>
KdTree<T> KdTree<T>::getLeftSubtree() const {
    return KdTree<T>(root_->left_child);
}

template <typename T>
KdTree<T> KdTree<T>::getRightSubtree() const {
    return KdTree<T>(root_->right_child);
}

// Choose splitting axis depending on policy
template <typename T>
size_t KdTree<T>::getSplitAxis(const std::vector<Point<T>>& distro_params, const size_t& depth) {
    // TODO: implement other splitting methods
    
    size_t dimensions = distro_params[0].getDimension();
    size_t split_axis = depth % dimensions;
    
    return split_axis;
}

// TODO: Fix this!
template <typename T>
Point<T> KdTree<T>::getPivot(const vector<Point<T>*>& input_points, const size_t& split_axis,
                                                        const T& split_position) {
    return *input_points[0];
}

template <typename T>
shared_ptr<KdTreeNode<T>> KdTree<T>::treeBuild(const vector<Point<T>*>& input_points, const size_t depth) {
    
    if (input_points.size() == 0) {
        cout << "No points!" << endl;
        return nullptr;
    }
    if (input_points.size() == 1) {
        shared_ptr<KdTreeNode<T>> leaf = make_shared<KdTreeNode<T>>(depth);
        leaf->point = *input_points[0];
        return leaf;
    }
    cout << "Depth = " << depth << endl << "Point (x) = " << *input_points[0]->begin() << endl;

    shared_ptr<KdTreeNode<T>> root = make_shared<KdTreeNode<T>>();
//    shared_ptr<KdTreeNode<T>> root(new KdTreeNode<T>);
    root->depth = depth;
    
    
    // Dimension-wise parameters are {min, max, range, mean, variance};
    vector<Point<T>> distro_params = getDistributionParams(input_points);
    
    root->split_axis = KdTree<T>::getSplitAxis(distro_params, depth); // TODO: FIX THIS!!!!!
    root->split_position =  getApproxMedian(input_points, root->split_axis,
                                           distro_params[3], distro_params[4]);
//    TODO: Fix getPivot linker error
    root->point = KdTree<T>::getPivot(input_points, root->split_axis, root->split_position);
    
    vector<Point<T>*> l_subset, r_subset;
//    for (auto pt : input_points) {
    for (auto iter = input_points.begin()+1; iter != input_points.end(); ++iter) {
        vector<T> pt_vect = (*iter)->getPointVector();
        if (pt_vect[root->split_axis] < root->split_position)
            l_subset.push_back(*iter);
        else
            r_subset.push_back(*iter);
    }
    
    root->left_child = KdTree<T>::treeBuild(l_subset, depth+1);
    root->right_child = KdTree<T>::treeBuild(r_subset, depth+1);
    
    return root;
}

template <typename T>
KdTree<T> KdTree<T>::buildKdTree(const std::vector<Point<T>*>& input_points) {
    shared_ptr<KdTreeNode<T>> root_node = treeBuild(input_points,0);
    KdTree<T> tree(root_node);
    return tree;
}

template class KdTree<float>;
template class KdTreeNode<float>;
template class KdTree<double>;
template class KdTreeNode<double>;


#endif /* KD_TREE_CPP_ */


















