#pragma once

#include "../binarytree.h"
#include "TreeTraversal.h"

#include <iterator>
#include <stack>

/**
 * A derived, templatized class for inorder traversal algorithms on trees.
 *
 * Simulates an iterative traversal of a given tree using a stack
 * and a given root node.
 */
template <typename T>
class InorderTraversal : public TreeTraversal<T> {
  public:
    /**
     * Initializes a Inorder TreeTraversal of a tree,
     * with the traversal storing the tree's root.
     * Hint: See lab handout for guidance
     *
     * @param root The root node of the tree
     */
    InorderTraversal(typename BinaryTree<T>::Node* root)
	    : root(root)
    {
     //stack.push(root);
      // your code here
      typename BinaryTree<T>::Node *current = root;

    //  InorderTraversal(current->left);
     //while (!stack.empty()){
      // while (current != NULL) {
      //   stack.push(current);
      //   current = current->right;
      // }

      //if (current == NULL && !stack.empty()) {
      //  if (current->right != NULL) {
        //  current = current->right;
        //  stack.pop();
        //  continue;
        // current = root;
          while (current != NULL) {
            stack.push(current);
            current = current->left;
          }
        //  stack.push(root);
      //  }
    //  }
    //  }

		// 	while (root != NULL){

			//root = root->right;
		// }
		// if (root->right != NULL) {
		// 	stack.push(root->right);
		// }
		//stack.push(root);
			// if (root->left != NULL) {
			// 	stack.push(root->left);
			// }

			// while (root->left->left != NULL) {
			//	root = root->left;
			// }
		//	stack.push(root->left);
			//stack.push(root->left);
		//	stack.push(root);
		//	while ()
	//	stack.push(root->right);
		//	stack.push(root->left);
    }

    /**
     * Returns an iterator for the traversal starting at the root node.
     * Important for sake of looping through an iterator's contents.
     *
     * @return The iterator object pointing to the first node in the traversal
     */
    typename TreeTraversal<T>::Iterator begin() {
      return typename TreeTraversal<T>::Iterator(this, root);
    }

    /**
     * Returns an iterator for the traversal pointing to the
     * element one past the end of the traversal.
     * Important for the sake of looping through an iterator's contents
     *
     * @return The iterator object pointing to the elemnt after the end of the traversal.
     */
    typename TreeTraversal<T>::Iterator end() {
      return typename TreeTraversal<T>::Iterator();
    }

    /**
     * Given a node in the tree, add the next appropriate
     * nodes to the stack such that when popped, and inorder
     * traversal is simulated.
     * Hint: See lab handout for guidance
     *
     * @param treeNode The subroot that determines what next nodes
     *        should be added to the traversal
     */
    void add(typename BinaryTree<T>::Node *& treeNode) {
      // your code here
		//	if (treeNode->right != NULL)
    typename BinaryTree<T>::Node *current = treeNode->right;
    if (current!= NULL) {

    if (current->left != NULL) {
    while (current != NULL) {
      stack.push(current);
      current = current->left;

    }

  } else {
    stack.push(current);
  }
}
  //  InorderTraversal(current->left);
   //while (!stack.empty()){
    // while (current != NULL) {
    //   stack.push(current);
    //   current = current->right;
    //
    // while (current->right->right != NULL) {
    //   current = current->right;
    // }
		// if (current->right != NULL) {
		// 	 stack.push(current->right);
	 // }
	 // if (treeNode != NULL) {
		 // stack.push(treeNode);
	 // }
		 // if (current->left != NULL) {
			//  //stack.push(treeNode);
		 // 		stack.push(current->left);
		 // }
		// stack.push(treeNode);

    //   return;
    }

    /**
     * Removes and returns the current node in the traversal.
     *
     * @return The current node in the traversal
     */
    typename BinaryTree<T>::Node* pop() {
      typename BinaryTree<T>::Node* topNode = stack.top();
      stack.pop();
      return topNode;
    }

    /**
     * Returns the current node in the traversal or
     * NULL if the stack is empty.
     *
     * @return The current node in the traversal
     */
    typename BinaryTree<T>::Node* peek() const {
      return empty() ? NULL : stack.top();
    }

    /**
     * Returns true if the traversal is empty.
     *
     * @return true if the traversal is empty.
     */
    bool empty() const {
      return stack.empty();
    }

  private:
    std::stack<typename BinaryTree<T>::Node*> stack;
    typename BinaryTree<T>::Node* root;
};
