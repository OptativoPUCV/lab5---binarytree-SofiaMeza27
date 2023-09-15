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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap *createTreeMap(int(*lower_than)(void *key1, void *key2));
    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    if(map == NULL)
    {
        return NULL;
    }
    
    map -> root = NULL;
    map -> current = NULL;
    map -> lower_than = lower_than;

    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    Pair *aux = searchTreeMap(tree, key);

    if(aux != NULL)
    {
        return;
    }

    int rightOrLeft = 1;

    tree -> current = tree -> root;
    TreeNode *search = tree -> current;

    while(search != NULL)
    {
        int result = tree -> lower_than(tree -> current -> pair -> key, key);
        if(result == 1)
        {
            if(tree -> current -> right == NULL)
            {
                search = NULL;
                rightOrLeft = 1;
            }
            else
            {
                tree -> current = tree -> current -> right;
            }
            
        }
        else
        {
            if(result == 0)
            {
                if(tree -> current -> left = NULL)
                search = NULL;
                rightOrLeft = 0;
            }
            else
            {
                tree -> current = tree -> current -> left;
            }
        }
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    int keyComp = is_equal(tree, tree -> root -> pair -> key, key);
    if(keyComp == 1)
    {
        tree -> current = tree -> root;
        return tree -> root -> pair;
    }
    else
    {
        tree -> current = tree -> root;
    }

    while(keyComp < 1)
    {
        int result = tree -> lower_than(tree -> current -> pair -> key, key);

        if(result == 1)
        {
            if(tree -> current -> left == NULL)
            {
                return NULL;
            }
            tree -> current = tree -> current -> right;
        }
        else if (result == 0)
        {
            if(tree -> current -> left == NULL)
            {
                return NULL;
            }
            tree -> current = tree -> current -> left;
        }
        keyComp = is_equal(tree, tree -> current -> pair -> key, key);
    }
    return tree -> current -> pair;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
