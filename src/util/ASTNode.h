//
// Created by andi on 19.10.24.
//

#ifndef ASTNODE_H
#define ASTNODE_H
#include <boost/optional/optional.hpp>
class ASTNode {
    public:
    ASTNode();
    ASTNode(ASTNode& parent);
    ASTNode(ASTNode& parent, ASTNode& left, ASTNode& right);

    /// 
    /// @return returns whether the node is the root of a tree. True if parent is null
    bool isRoot() const;

    /// 
    /// @return returns whether this node is a leaf. True if both left and right are null
    bool isLeaf() const;

    ///
    /// @return returns the parent node of this node, if it exists
    boost::optional<ASTNode&> getParent() const;

    ///
    /// @return returns the left child of this node if it exists
    boost::optional<ASTNode&> getLeft() const;

    ///
    /// @return returns the right child of this node if it exists
    boost::optional<ASTNode&> getRight() const;

private:
    boost::optional<ASTNode&> _parent;
    boost::optional<ASTNode&> _left;
    boost::optional<ASTNode&> _right;
};
#endif //ASTNODE_H
