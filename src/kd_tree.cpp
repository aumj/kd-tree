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

#include <fstream>
#include <vector>
#include <limits>
#include <memory>
#include "file_handler.h"
#include "kd_math.h"
#include "kd_tree.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

using namespace std;

// SET SPLITTING AXIS POLICY HERE
// Options are {CYCLE, VARIANCE, RANGE}
template <typename T>
typename KdTree<T>::SplitMethod_t KdTree<T>::split_method_ = SplitMethod_t::VARIANCE;

template <typename T>
KdTree<T>::KdTree(const shared_ptr<KdTreeNode<T>> root_node) : root_(root_node) {}

template <typename T>
KdTreeNode<T> KdTree<T>::getRootNode() const {
    return *root_;
}

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
size_t KdTree<T>::getSplitAxis(const vector<Point<T>>& distro_params,
                               const size_t& depth) {

    size_t split_axis;
    switch(KdTree<T>::split_method_) {
    case KdTree<T>::SplitMethod_t::VARIANCE : {
        vector<T> var = distro_params[4].getPointVector();
        split_axis = max_element(var.begin(), var.end()) - var.begin();
        break;
    }

    case KdTree<T>::SplitMethod_t::RANGE : {
        vector<T> var = distro_params[2].getPointVector();
        split_axis = max_element(var.begin(), var.end()) - var.begin();
        break;
    }

    case KdTree<T>::SplitMethod_t::CYCLE : {
        size_t dimensions = distro_params[0].getDimension();
        split_axis = depth % dimensions;
    }
    }

    return split_axis;
}

template <typename T>
Point<T> KdTree<T>::getPivot(const vector<Point<T>*>& input_points, const size_t& split_axis,
                                                        const T& split_position) {

    Point<T> medianNode = **input_points.begin();
    T distToMedian = numeric_limits<T>::max();
    for (auto iter = input_points.begin(); iter != input_points.end(); ++iter) {
        if (abs((**iter)[split_axis] - split_position) < distToMedian) {
            medianNode = **iter;
            distToMedian = (**iter)[split_axis] - split_position;
        }
    }
    return medianNode;
}

template <typename T>
shared_ptr<KdTreeNode<T>> KdTree<T>::treeBuild(const vector<Point<T>*>& input_points,
                                               const size_t depth) {

    if (input_points.size() == 0) {
        return nullptr;
    }
    if (input_points.size() == 1) {
        shared_ptr<KdTreeNode<T>> leaf = make_shared<KdTreeNode<T>>(depth);
        leaf->point = *input_points[0];
        return leaf;
    }

    shared_ptr<KdTreeNode<T>> root = make_shared<KdTreeNode<T>>();
    root->depth = depth;

    // Dimension-wise parameters are {min, max, range, mean, variance};
    vector<Point<T>> distro_params = getDistributionParams(input_points);

    root->split_axis = KdTree<T>::getSplitAxis(distro_params, depth);
    root->split_position =  getApproxMedian(input_points, root->split_axis,
                                           distro_params[3], distro_params[4]);
    root->point = KdTree<T>::getPivot(input_points, root->split_axis, root->split_position);

    // Split data into halfspaces
    vector<Point<T>*> l_subset, r_subset;
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
KdTree<T> KdTree<T>::buildKdTree(const vector<Point<T>*>& input_points) {
    KdTree<T> tree(treeBuild(input_points,0));
    return tree;
}

template <typename T>
void KdTree<T>::queryKdTree(const KdTree<T>& tree, const vector<Point<T>*>& query_points) {
    vector<size_t> pointId;
    pointId.reserve(query_points.size());
    vector<T> dist;
    dist.reserve(query_points.size());
    for (auto iter = query_points.begin(); iter != query_points.end(); ++iter) {
        shared_ptr<KdTreeNode<T>> bestNodePtr = make_shared<KdTreeNode<T>>();
        shared_ptr<T> bestDistPtr = make_shared<T>(numeric_limits<T>::max());
        KdTree<T>::getNearestNeighbor(tree.getRootNode(), **iter, bestNodePtr, bestDistPtr);
        pointId.push_back((bestNodePtr->point).getIndex());
        dist.push_back(*bestDistPtr);
    }

    FileHandler<T>::csvWriteNnResults(pointId, dist);
}

template <typename T>
void KdTree<T>::getNearestNeighbor(const KdTreeNode<T>& node,
                                   const Point<T>& query,
                                   const shared_ptr<KdTreeNode<T>>& bestNode,
                                   const shared_ptr<T>& bestDist) {

    T distance = getDistance(node.point, query);
    if (distance < *bestDist) {
        *bestNode = node;
        *bestDist = distance;
    }
    if (node.isLeaf())
        return;

    // Recursively compare nodes and find nearest neighbor
    if (query[node.split_axis] < node.split_position && node.left_child != nullptr) {
        getNearestNeighbor(*(node.left_child), query, bestNode, bestDist);
        if (abs(node.split_position - query[node.split_axis]) < *bestDist
            && node.right_child != nullptr) {
            getNearestNeighbor(*(node.right_child), query, bestNode, bestDist);
        }
    }
    else if (node.right_child != nullptr) {
        getNearestNeighbor(*(node.right_child), query, bestNode, bestDist);
        if (abs(node.split_position - query[node.split_axis]) < *bestDist
            && node.left_child != nullptr) {
            getNearestNeighbor(*(node.left_child), query, bestNode, bestDist);
        }
    }
    return;
}

template <typename T>
void KdTree<T>::WriteKDTreeToFile(const KdTree<T>& tree, const string& file) {
    ofstream out_stream(file);
    cereal::JSONOutputArchive archive(out_stream);
    archive(cereal::make_nvp("kdtree", tree));
}

template <typename T>
void KdTree<T>::ReadKDTreeFromFile(KdTree<T>& tree, const string& file) {
    ifstream in_stream(file);
    cereal::JSONInputArchive archive(in_stream);
    archive(cereal::make_nvp("kdtree", tree));
}

template class KdTree<float>;
template struct KdTreeNode<float>;
template class KdTree<double>;
template struct KdTreeNode<double>;


#endif /* KD_TREE_CPP_ */
