#include "ProjectHeader.h"


EdgeList* build_net(int n) {
    int nLine;
    if (scanf("%d", &nLine) != 1) error_and_exit();

    EdgeList* Net = (EdgeList*)malloc(sizeof(EdgeList) * n);
    checkAllocation(Net);
    for (int i = 0; i < n; i++) {
        Net[i].head = Net[i].tail = NULL;
    }

    for (int i = 0; i < nLine; i++) {
        int a, b, price;
        if (scanf("%d %d %d", &a, &b, &price) != 3) {
            error_and_exit();
        }
        if (a < 0 || a >= n || b < 0 || b >= n || price < 0 || a == b) {
            error_and_exit();
        }
        appendEdge(&Net[a], b, price);
        appendEdge(&Net[b], a, price);
    }
    return Net;
}

void insertEdgeSorted(EdgeList* lst, EdgeNode* node) {
    if (lst->head == NULL) {
        lst->head = lst->tail = node;
        node->next = NULL;
        return;
    }
    if (node->e.neighbor < lst->head->e.neighbor) {
        node->next = lst->head;
        lst->head = node;
        return;
    }
    EdgeNode* cur = lst->head;
    while (cur->next != NULL && cur->next->e.neighbor < node->e.neighbor) {
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
    if (node->next == NULL) {
        lst->tail = node;
    }
}

void appendEdge(EdgeList* lst, int neighbor, int cost) {
    EdgeNode* node = malloc(sizeof(EdgeNode));
    checkAllocation(node);
    node->e.neighbor = neighbor;
    node->e.cost = cost;
    node->next = NULL;
    insertEdgeSorted(lst, node);
}
