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
#include <memory>
#include "kd_math.h"
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/base_class.hpp>

// Data structure for individual nodes of the KD-tree
template <typename T=double>
struct KdTreeNode {
    size_t depth;
    size_t split_axis;
    T split_position;
    Point<T> point;
    std::shared_ptr<KdTreeNode<T>> left_child;
    std::shared_ptr<KdTreeNode<T>> right_child;

    bool isLeaf() const {
        return (left_child == nullptr && right_child == nullptr);
    }

    // Constructors/Destructor
    KdTreeNode() = default;
    KdTreeNode(const int& depth, const std::shared_ptr<KdTreeNode>& left = nullptr,
               const std::shared_ptr<KdTreeNode>& right = nullptr) : depth(depth) {}
    ~KdTreeNode() = default;

    // Serialization function
    template<class Archive>
    void serialize(Archive & archive) {
			archive(CEREAL_NVP(depth), CEREAL_NVP(split_axis), CEREAL_NVP(split_position),
                    CEREAL_NVP(point), CEREAL_NVP(left_child), CEREAL_NVP(right_child));
    }
};

// Parent class for the KD-tree
template <typename T=double>
class KdTree {
private:
    std::shared_ptr<KdTreeNode<T>> root_;
public:
    enum class SplitMethod_t {CYCLE, VARIANCE, RANGE};
    static SplitMethod_t split_method_;

    // Constructors/Destructor
    KdTree() = default;
    KdTree(const std::shared_ptr<KdTreeNode<T>> root_node);
    ~KdTree() = default;

    // Member functions
    KdTreeNode<T> getRootNode() const;
    KdTree<T> getLeftSubtree() const;
    KdTree<T> getRightSubtree() const;
    bool isEmpty() const;

    // Start building KD-Tree from a set of Points
    static KdTree<T> buildKdTree(const std::vector<Point<T>*>& input_points);

    // Recursively build KD-Tree
    static shared_ptr<KdTreeNode<T>> treeBuild(const std::vector<Point<T>*>& input_points,
                                               const size_t depth);

    // Find appropriate splitting axis for given set of Points
    static size_t getSplitAxis(const std::vector<Point<T>>& distro_params,
                               const size_t& depth);

    // Find pivot point (closest to median)
    static Point<T> getPivot(const std::vector<Point<T>*>& input_points,
                             const size_t& split_axis,
                             const T& split_position);

    // Query KD tree for a set of points
    static void queryKdTree(const KdTree<T>& tree, const std::vector<Point<T>*>& query_points);

    // Recursively find nearest neighbor in tree for a given point
    static void getNearestNeighbor(const KdTreeNode<T>& node,
                                   const Point<T>& query,
                                   const std::shared_ptr<KdTreeNode<T>>& bestNode,
                                   const std::shared_ptr<T>& bestDist);

    // Serialization function
    template<class Archive>
    void serialize(Archive & archive) {
			archive(CEREAL_NVP(root_), CEREAL_NVP(split_method_));
    }

    // Read/Write KD-tree to .json file using Cereal
    static void WriteKDTreeToFile(const KdTree<T>& tree, const std::string& file="tree.json");
    static void ReadKDTreeFromFile(KdTree<T>& tree, const std::string& file="data/sample_tree.json");

};


#include "kd_tree.cpp"

#endif /* KD_TREE_H_ */
