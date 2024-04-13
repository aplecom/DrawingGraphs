#ifndef TREENODE_H
#define TREENODE_H
template <typename T>
class TreeNode {

private:
    TreeNode<T> *left;
    TreeNode<T> *right;
public:
    T data;

    TreeNode(const T& item, TreeNode<T> *lptr = nullptr,
             TreeNode<T> *rptr = nullptr){
        this->data = item;
        this->left = lptr;
        this->right = rptr;
    }

    TreeNode<T>* getLeft() const{return left;}
    TreeNode<T>* getRight() const{return right;}
    void setLeft(TreeNode<T>* lptr){left=lptr;}
    void setRight(TreeNode<T>* rptr){right=rptr;}

};

#endif // TREENODE_H
