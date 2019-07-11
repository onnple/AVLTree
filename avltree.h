//
// Created by Once on 2019/7/11.
//

#ifndef DATALGORITHM_AVLTREE_H
#define DATALGORITHM_AVLTREE_H

// 数据对象
typedef struct user{
    unsigned int id; // 关键字
    char username[128];
    char password[128];
} User;

// 结点
typedef struct avlnode{
    User user; // 数据域
    struct avlnode *left; // 左右儿子
    struct avlnode *right;
    int height; // 高度
} AVLNode;

// AVL树ADT对外接口
typedef struct avltree{
    AVLNode *root;
    unsigned int size;
} AVLTree;

// 算法声明
extern AVLTree *avltree_init();
extern int avltree_is_full(AVLTree *avltree);
extern int avltree_is_empty(AVLTree *avltree);
extern int avltree_add(AVLTree *avltree, User *user);
extern int avltree_delete_by_id(AVLTree *avltree, unsigned int id);
extern AVLNode *avltree_get_by_id(AVLTree *avltree, unsigned int id);
extern void avltree_traverse(AVLTree *avltree, void (*traverse)(AVLNode*));
extern int avltree_clear(AVLTree *avltree);

#endif //DATALGORITHM_AVLTREE_H
