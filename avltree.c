//
// Created by Once on 2019/7/11.
//

#include "avltree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

AVLTree *avltree_init(){
    AVLTree *avltree = (AVLTree*)malloc(sizeof(AVLTree));
    if(!avltree){
        perror("init avl tree error.");
        return NULL;
    }
    avltree->root = NULL;
    avltree->size = 0;
    return avltree;
}

int avltree_is_full(AVLTree *avltree){
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    if(!node)
        return 1;
    free(node);
    return 0;
}

int avltree_is_empty(AVLTree *avltree){
    if(avltree == NULL)
        return 1;
    return avltree->size == 0;
}

static int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

// 计算结点高度
static int height(AVLNode *node){
    if(!node)
        return -1; // 空树为-1
    return node->height;
}

// 更新节点高度
static void update_height(AVLNode *node){
    node->height = max(height(node->left), height(node->right)) + 1;
}

// LL单右旋转，root为失衡结点，情况（1）
static AVLNode *rotate_left_single(AVLNode *root){
    AVLNode *node = root->left;
    root->left = node->right;
    node->right = root;
    update_height(root);
    update_height(node);
    printf("[left] - ");
    return node;
}

// RR单左旋转，root为失衡结点，情况（4）
static AVLNode *rotate_right_single(AVLNode *root){
    AVLNode *node = root->right;
    root->right = node->left;
    node->left = root;
    update_height(root);
    update_height(node);
    printf("[right] - ");
    return node;
}

// LR双旋转，root为失衡结点，情况（2）
static AVLNode *rotate_left_double(AVLNode *root){
    root->left = rotate_right_single(root->left);
    printf("{left double} - ");
    return rotate_left_single(root);
}

// RL双旋转，root为失衡结点，情况（3）
static AVLNode *rotate_right_double(AVLNode *root){
    root->right = rotate_left_single(root->right);
    printf("{right double} - ");
    return rotate_right_single(root);
}

static AVLNode *add_node(AVLTree *avltree, AVLNode *root, User *user){
    if(!root){
        AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
        if(!node){
            perror("init avl node error.");
            return NULL;
        }
        node->user.id = user->id;
        strcpy(node->user.username, user->username);
        strcpy(node->user.password, user->password);
        node->left = node->right = NULL;
        node->height = 0;
        avltree->size++;
        return node;
    }
    else if(root->user.id > user->id){
        root->left = add_node(avltree, root->left, user);
        if(height(root->left) - height(root->right) == 2){
            if(user->id < root->left->user.id)
                root = rotate_left_single(root);
            else
                root = rotate_left_double(root);
        }
        update_height(root);
        return root;
    }
    else if(root->user.id < user->id){
        root->right = add_node(avltree, root->right, user);
        if(height(root->right) - height(root->left) == 2){
            if(user->id > root->right->user.id)
                root = rotate_right_single(root);
            else
                root = rotate_right_double(root);
        }
        update_height(root);
        return root;
    }
    else{
        strcpy(root->user.username, user->username);
        strcpy(root->user.password, user->password);
        return root;
    }
}

int avltree_add(AVLTree *avltree, User *user){
    if(avltree == NULL || user == NULL)
        return 0;
    avltree->root = add_node(avltree, avltree->root, user);
    return 1;
}

static AVLNode *find_min(AVLNode *root){
    if(root->left)
        return find_min(root->left);
    else
        return root;
}

static AVLNode *delete_node(AVLTree *avltree, AVLNode *root, unsigned int id){
    if(!root)
        return NULL;
    if(root->user.id == id){
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
            avltree->size--;
            return root;
        }
        else if((unsigned int)(root->left == NULL) ^ (unsigned int)(root->right == NULL)){
            AVLNode *node = root->left == NULL ? root->right : root->left;
            free(root);
            avltree->size--;
            return node;
        }
        else{
            AVLNode *node = find_min(root->right);
            root->user.id = node->user.id;
            strcpy(root->user.username, node->user.username);
            strcpy(root->user.password, node->user.password);
            root->right = delete_node(avltree, root->right, node->user.id);
        }
    }
    else if(root->user.id > id){
        root->left = delete_node(avltree, root->left, id);
    }
    else{
        root->right = delete_node(avltree, root->right, id);
    }

    if(height(root->left) - height(root->right) == 2){
        if(height(root->left->left) - height(root->left->right) > 0)
            root = rotate_left_single(root);
        else
            root = rotate_left_double(root);
    }
    else if(height(root->right) - height(root->left) == 2){
        if(height(root->right->right) - height(root->right->left) > 0)
            root = rotate_right_single(root);
        else
            root = rotate_right_double(root);
    }
    update_height(root);
    return root;
}

int avltree_delete_by_id(AVLTree *avltree, unsigned int id){
    if(avltree == NULL || avltree->size == 0)
        return 0;
    avltree->root = delete_node(avltree, avltree->root, id);
    return 1;
}

static AVLNode *get_node(AVLNode *root, unsigned int id){
    if(!root)
        return NULL;
    if(root->user.id == id)
        return root;
    else if(root->user.id > id)
        return get_node(root->left, id);
    else
        return get_node(root->right, id);
}

AVLNode *avltree_get_by_id(AVLTree *avltree, unsigned int id){
    if(avltree == NULL || avltree->size == 0)
        return NULL;
    return get_node(avltree->root, id);
}

static void traverse_tree(AVLNode *root, void (*traverse)(AVLNode*)){
    if(!root)
        return;
    traverse_tree(root->left, traverse);
    traverse(root);
    traverse_tree(root->right, traverse);
}

void avltree_traverse(AVLTree *avltree, void (*traverse)(AVLNode*)){
    if(avltree == NULL || avltree->size == 0 || traverse == NULL)
        return;
    traverse_tree(avltree->root, traverse);
}

static int clear_node(AVLNode *root){
    if(!root)
        return 0;
    clear_node(root->left);
    clear_node(root->right);
    free(root);
    return 1;
}

int avltree_clear(AVLTree *avltree){
    if(avltree == NULL)
        return 0;
    clear_node(avltree->root);
    free(avltree);
    return 1;
}
