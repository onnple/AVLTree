#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avltree.h"

void traverse_tree(AVLNode *node){
    printf("%d (%d) - ", node->user.id, node->height);
}

void avltree(void){
    AVLTree *avltree = avltree_init();
    for (int i = 0; i < 8; ++i) {
        User user;
        user.id = i + 1;
        strcpy(user.username, "AVL");
        strcpy(user.password, "AVL");
        avltree_add(avltree, &user);
    }
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 5); // 删除树叶，RR单旋转
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    User u1;
    u1.id = 10;
    strcpy(u1.username, "AVL");
    strcpy(u1.password, "AVL");
    avltree_add(avltree, &u1);
    User u2;
    u2.id = 5;
    strcpy(u2.username, "AVL");
    strcpy(u2.password, "AVL");
    avltree_add(avltree, &u2);
    User u3;
    u3.id = 0;
    strcpy(u3.username, "AVL");
    strcpy(u3.password, "AVL");
    avltree_add(avltree, &u3); // LL单旋转
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 7); // 删除有两个儿子的结点
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 4); // 删除有两个儿子的结点
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 6);
    avltree_delete_by_id(avltree, 5);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    u1.id = 6;
    avltree_add(avltree, &u1);
    u1.id = 7;
    avltree_add(avltree, &u1);
    u1.id = 5;
    avltree_add(avltree, &u1);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 1);
    avltree_delete_by_id(avltree, 2);
    avltree_delete_by_id(avltree, 8);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_clear(avltree);
}

int main() {
    avltree();
    return 0;
}