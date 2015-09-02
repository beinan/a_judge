#pragma once

#include <vector>
#include <cstdlib>

struct IAVLTreeNode {
  IAVLTreeNode() { }
  virtual ~IAVLTreeNode() { }
  virtual void setLeft(IAVLTreeNode * left) = 0;
  virtual void setRight(IAVLTreeNode * right) = 0;
  virtual void setKey(int key) = 0;
  virtual IAVLTreeNode * getLeft() = 0;
  virtual IAVLTreeNode * getRight() = 0;
  virtual int getKey() = 0;
};

struct IAVLTree {
  IAVLTree() { }
  virtual ~IAVLTree() { }
  virtual void insert(int key) = 0;
  virtual void remove(int key) = 0;
  virtual int kthMin(int k) = 0;
  virtual IAVLTreeNode * getRoot() = 0;
};

struct IBTreeNode {
  IBTreeNode() {}
  virtual ~IBTreeNode() {}
  virtual int getKey(int index) = 0;  
  virtual void setKey(int index, int key) = 0;
  virtual int getKeySize() = 0;
  virtual void setKeySize(int size) = 0;
  virtual int getChildSize() = 0;
  virtual void setChildSize(int size) = 0;
  virtual IBTreeNode * getChild(int index) = 0;
  virtual void setChild(int index, IBTreeNode * child) = 0;
  virtual bool isLeaf() = 0;
};

struct IBTree { 
  IBTree() { }
  virtual ~IBTree() { }
  virtual void insert(int key, int num_keys) = 0;
  virtual void remove(int key, int num_keys) = 0;
  virtual int kthMin(int k) = 0;
  virtual IBTreeNode * getRoot() = 0;
};
