#include "ProjectHeader.h"

EdgeList* build_paths(int* Prim, int n) {
    EdgeList* PrimPaths = (EdgeList*)malloc(sizeof(EdgeList) * n);
    checkAllocation(PrimPaths);

    for (int v = 0; v < n; v++) {
        PrimPaths[v].head = PrimPaths[v].tail = NULL;
    }

    for (int v = 0; v < n; v++) {
        int p = Prim[v];
        if (p != -1) {
            appendEdge(&PrimPaths[v], p, 0);
            appendEdge(&PrimPaths[p], v, 0);
        }
    }
    return PrimPaths;
}

void find_and_print_path(EdgeList PrimPath[], int n, int first, int last) {
    if (first < 0 || first >= n || last < 0 || last >= n) {
        error_and_exit();
    }

    int* Color = (int*)malloc(sizeof(int) * n);
    int* Parent = (int*)malloc(sizeof(int) * n);
    checkAllocation(Color);
    checkAllocation(Parent);

    for (int v = 0; v < n; v++) {
        Color[v] = WHITE;
        Parent[v] = -1;
    }

    FindPath(first, last, PrimPath, Color, Parent);

    if (Parent[last] == -1 && first != last) {
        error_and_exit();
    }
    else {
        PrintPath(last, first, Parent);
        printf("\n");
    }

    free(Color);
    free(Parent);
}

static void FindPath(int u, int last, EdgeList PrimPath[], int Color[], int Parent[]) {
    Color[u] = GRAY;
    for (EdgeNode* p = PrimPath[u].head; p != NULL; p = p->next) {
        int v = p->e.neighbor;
        if (Color[v] == WHITE) {
            Parent[v] = u;
            if (v == last) {
                return;
            }
            FindPath(v, last, PrimPath, Color, Parent);
            if (Color[last] != WHITE) {
                return;
            }
        }
    }
    Color[u] = BLACK;
}

static void PrintPath(int v, int first, int Parent[]) {
    if (v == first) {
        printf("%d ", v);
    }
    else {
        PrintPath(Parent[v], first, Parent);
        printf("%d ", v);
    }
}
