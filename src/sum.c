#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int sum(const int *arr, int size) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        result += arr[i];
    }

    return result;
}

int p1_sum(const int *arr, int size) {
    int result = 0;
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        int partial_result = 0;

        #pragma omp for
        for (int i = 0; i < size; i++) {
            partial_result += arr[i];
        }

        #pragma omp critical
        result += partial_result;
    }

    return result;
}

int p2_sum(const int *arr, int size) {
    int result = 0;

    #pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < size; i++) {
        result += arr[i];
    }

    return result;
}

int main() {
    srand(time(NULL));

    int size = 100000000;
    int *arr = malloc(size * sizeof(*arr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }

    double start, delta;
    int result;

    // ===================================
    printf("non-parallel\n");

    start = omp_get_wtime();
    result = sum(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %d\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v1\n");

    start = omp_get_wtime();
    result = p1_sum(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %d\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v2\n");

    start = omp_get_wtime();
    result = p2_sum(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %d\n", result);
    printf("took %lf seconds\n", delta / 1000);

    return 0;
}