#include "ProjectHeader.h"

CandidateList buildPriorityAndLocation(int numComputers, CandidateNode*** outLocation) {
    CandidateList priority = { NULL, NULL };
    CandidateNode** location = (CandidateNode**)malloc(sizeof(CandidateNode*) * numComputers);
    checkAllocation(location);

    for (int i = 0; i < numComputers; i++) {
        CandidateNode* node = (CandidateNode*)malloc(sizeof(CandidateNode));
        checkAllocation(node);
        node->c.computer = i;
        node->c.min = INT_MAX;
        node->next = NULL;
        node->prev = priority.tail;
        if (priority.tail) {
            priority.tail->next = node;
        }
        else {
            priority.head = node;
        }
        priority.tail = node;
        location[i] = node;
    }

    *outLocation = location;
    return priority;
}

int DeleteMin(CandidateList* q) {
    CandidateNode* best = q->head;
    for (CandidateNode* cur = q->head->next; cur; cur = cur->next) {
        if (cur->c.min < best->c.min) best = cur;
    }
    int u = best->c.computer;
    if (best->prev) best->prev->next = best->next;
    else q->head = best->next;
    if (best->next) best->next->prev = best->prev;
    else q->tail = best->prev;
    free(best);
    return u;
}

void decreaseKey(CandidateNode* node, int newMin) {
    node->c.min = newMin;
}

int* build_prim_tree(EdgeList net[], int n) {
    int bytesForInT = (n + 7) / 8;
    unsigned char* inT = (char*)calloc(bytesForInT, sizeof(unsigned char));
    checkAllocation(inT);

    int* Prim = (int*)malloc(sizeof(int) * n);
    int* min = (int*)malloc(sizeof(int) * n);
    checkAllocation(Prim);
    checkAllocation(min);

    for (int v = 0; v < n; v++) {
        Prim[v] = -1;
        min[v] = INT_MAX;
    }

    CandidateNode** location;
    CandidateList priority = buildPriorityAndLocation(n, &location);

    min[0] = 0;
    decreaseKey(location[0], 0);

    while (priority.head != NULL) {
        int u = DeleteMin(&priority);
        if (min[u] == INT_MAX) {
            free(location);
            free(Prim);
            free(min);
            free(inT);
            printf("No spanning tree available.\n");
            exit(EXIT_FAILURE);

        }

        inT[u / 8] |= (unsigned char)(1 << (u % 8));

        for (EdgeNode* p = net[u].head; p != NULL; p = p->next) {
            int v = p->e.neighbor;
            bool isInT = (inT[v / 8] >> (v % 8)) & 1;
            if (!isInT && p->e.cost < min[v]) {
                min[v] = p->e.cost;
                Prim[v] = u;
                decreaseKey(location[v], p->e.cost);
            }
        }
    }

    free(location);
    free(min);
    free(inT);
    return Prim;
}
