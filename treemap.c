#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap* newMap = malloc(sizeof (TreeMap));

  newMap->root = NULL;
  newMap->current = NULL;
  newMap->lower_than = lower_than;

  return newMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode* currentNode = tree->root;
  TreeNode* parentNode = NULL;

  // Arbol vacio case
  if (currentNode == NULL) {
    tree->root = createTreeNode(key, value);
    tree->current = tree->root;// Actualizar current**
    return;
  }

  while (currentNode != NULL) {
      if (is_equal(tree, key, currentNode->pair->key)) {
        currentNode->pair->value = value;
        tree->current = currentNode; // Actualizar current**
        return;
      }
      parentNode = currentNode;

      // CMP keys, insert key < current key = insertar como hijo IZQ
      if (tree->lower_than(key, currentNode->pair->key)) {
          currentNode = currentNode->left;

          if (currentNode == NULL) {
            parentNode->left = createTreeNode(key, value);
            parentNode->left->parent = parentNode;
            tree->current = parentNode->left; // Actualizar current**
            return;
          }
      } else {
          // CMP keys, insert key > current key = insertar como hijo DER
          currentNode = currentNode->right;

          if (currentNode == NULL) {
            parentNode->right = createTreeNode(key, value);
            parentNode->right->parent = parentNode;
            tree->current = parentNode->right; // Actualizar current**
            return;
          }
      }
  } 
}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL) x = x->left;
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode* aux = tree->root;

  while(aux != NULL){
    if(is_equal(tree,key,aux->pair->key)){
      tree->current = aux;
      return aux->pair;
    }
    else if(tree->lower_than(key, aux->pair->key)) aux = aux->left;

    else  aux = aux->right;
  }
  
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if(tree->root == NULL) return NULL;

  TreeNode* first = minimum(tree->root);
  return first->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree != NULL && tree->current != NULL) {
        TreeNode* nex = NULL;
        if (tree->current->right != NULL) next = minimum(tree->curent->right);
 
        else {
            TreeNode* parent = tree->current->parent;
            while (parent != NULL && tree->current == parent->right) {
                tree->current = parent;
                parent = parent->parent;
            }
            next = parent;
        }
        if (next != NULL) {
            tree->current = successor;
            return next->pair;
        }
    }
    return NULL;
}