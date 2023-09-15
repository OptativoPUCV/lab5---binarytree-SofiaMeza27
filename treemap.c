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
        else if(result == 0)
        {
           if(tree -> current -> left == NULL)
           {
                search = NULL;
                rightOrLeft = 0; 
           }
           else
           {
                tree -> current = tree -> current -> left;
           }
        }
    }
    TreeNode *new = createTreeNode(key, value);
    new -> parent = tree -> current;

    if(rightOrLeft == 1)
    {
        tree -> current -> right = new;
    }
    else
    {
        tree -> current -> left = new;
    }
    tree -> current = new;
}

TreeNode * minimum(TreeNode * x)
{

    while(x -> left != NULL)
    {
        x = x -> left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    //Nodo sin hijos:
    if(node -> left == NULL && node -> right == NULL)
    {
        if(tree -> lower_than(node -> parent -> pair -> key, node -> pair -> key) == 1)
        {
            node -> parent -> right = NULL;
        }else
        {
            node -> parent -> left = NULL;
        }
        return;
    }

    //Nodo con  1 hijo:
    if(node -> left == NULL && node -> right != NULL)
    {
        if(tree -> lower_than(node -> parent -> pair -> key, node -> pair -> key) == 1)
        {
            node -> parent -> right = node -> right;
            node -> right -> parent = node -> parent;
        }
        return;

    }else if(node -> left != NULL && node -> right == NULL)
    {
        if(tree -> lower_than(node -> parent -> pair -> key, node -> pair -> key) == 1)
        {
            node -> parent -> right = node -> left;
            node -> left -> parent = node -> parent;
        } else
        {
            node -> parent -> left = node -> left;
            node -> left -> parent = node -> parent;
        }
        return ;
    }
    //Nodo coon 2 hijos:
    if(node -> left != NULL && node -> right != NULL)
    {
        TreeNode *aux = minimum(node -> right);
        node -> pair -> key = aux -> pair -> key;
        node -> pair -> value = aux -> pair -> value;
        removeNode(tree, aux);
    }
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

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode *x = tree -> root;
    tree -> current = minimum(x);
    if(tree -> current == NULL)
    {
        return NULL;
    } 
    return tree -> current -> pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    if(tree -> current -> right != NULL)
    {
        tree -> current = minimum(tree -> current -> right);
        return tree -> current -> pair;
    }

    TreeNode *aux = tree -> current -> parent;

    while(aux != NULL)
    {
        if(tree -> lower_than(tree -> current -> pair -> key, aux -> pair -> key) == 1);
        {
            tree -> current = aux;
            return tree -> current -> pair;
        }
    }
}
