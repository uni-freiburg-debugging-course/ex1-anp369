//
// Created by andi on 19.10.24.
//

#ifndef ASTNODE_H
#define ASTNODE_H
#include <boost/optional/optional.hpp>

#include "token.h"

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

    Token action;
    boost::optional<ASTNode&> parent;
    boost::optional<ASTNode&> left;
    boost::optional<ASTNode&> right;
};
#endif //ASTNODE_H
