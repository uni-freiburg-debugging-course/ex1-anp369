//
// Created by andi on 19.10.24.
//

#include <common/astnode.h>

// ---------------------------------------------------------------------------------------------------------------------
ASTNode::ASTNode() = default;

// ---------------------------------------------------------------------------------------------------------------------
//ASTNode::ASTNode(std::shared_ptr<ASTNode> parent) {
//    this->parent = std::move(parent);
//}

// ---------------------------------------------------------------------------------------------------------------------
//ASTNode::ASTNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) {
//    this->parent = std::move(parent);
//    this->left = std::move(left);
//    this->right = std::move(right);
//}


// ---------------------------------------------------------------------------------------------------------------------
bool ASTNode::isLeaf() const {
    return this->mLeft == nullptr && this->mRight == nullptr;
}
