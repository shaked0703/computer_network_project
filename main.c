#include "ProjectHeader.h"

int main() {
    int n;
    EdgeList* Net;
    int* Prim;
    EdgeList* PrimPath;
    int first, last;

    scanf("%d", &n);
    Check_n(n);
        
    Net = build_net(n);
    Prim = build_prim_tree(Net, n);
    PrimPath = build_paths(Prim, n);

    scanf("%d %d", &first, &last);
    Check_first_and_last(first, last, n);

    find_and_print_path(PrimPath, n, first, last);

    free(Net);
    free(Prim);
    free(PrimPath);
    return 0;
}
