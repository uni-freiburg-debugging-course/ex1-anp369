//
// Created by andi on 19.10.24.
//

#ifndef ASTNODE_H
#define ASTNODE_H
#include <memory>
#include <boost/optional/optional.hpp>

#include "token.h"

class ASTNode {
public:
    ASTNode();

    //ASTNode(std::shared_ptr<ASTNode> parent, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right);

    /// 
    /// @return returns whether the node is the root of a tree. True if parent is null
 //   bool isRoot() const;

    /// 
    /// @return returns whether this node is a leaf. True if both left and right are null
    bool isLeaf() const;


    Token mAction;

    std::unique_ptr<ASTNode> mLeft;
    std::unique_ptr<ASTNode> mRight;
};
#endif //ASTNODE_H
