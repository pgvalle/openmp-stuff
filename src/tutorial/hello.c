#include "../common.h"

int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("hello %d\n", id);
    }

    return 0;
}