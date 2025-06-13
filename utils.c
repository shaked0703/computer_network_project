#include "ProjectHeader.h"

void checkAllocation(void* ptr) {
    if (ptr == NULL) {
        printf("Invalid input.\n");
        exit(EXIT_FAILURE);
    }
}

void error_and_exit() {
    printf("Invalid input.\n");
    exit(EXIT_FAILURE);
}

void Check_n(int n) {
    if (n < 0){
        error_and_exit();
    }
}

void Check_first_and_last(int first, int last, int n) {
    if (first < 0 || first >= n || last < 0 || last >= n) {
        error_and_exit();
    }
}
