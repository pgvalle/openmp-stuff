#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double avg(const int *arr, int size) {
    double result = 0, inv_size = 1.0 / size;

    for (int i = 0; i < size; i++) {
        result += arr[i] * inv_size;
    }

    return result;
}

double p1_avg(const int *arr, int size) {
    double result = 0, inv_size = 1.0 / size;
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        double partial_result = 0;

        #pragma omp for
        for (int i = 0; i < size; i++) {
            partial_result += arr[i] * inv_size;
        }

        #pragma omp critical
        result += partial_result;
    }

    return result;
}

double p2_avg(const int *arr, int size) {
    double result = 0, inv_size = 1.0 / size;

    #pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < size; i++) {
        result += arr[i] * inv_size;
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

    double start, delta, result;

    // ===================================
    printf("non-parallel\n");

    start = omp_get_wtime();
    result = avg(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %lf\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v1\n");

    start = omp_get_wtime();
    result = p1_avg(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %lf\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v2\n");

    start = omp_get_wtime();
    result = p2_avg(arr, size);
    delta = omp_get_wtime() - start;

    printf("result = %lf\n", result);
    printf("took %lf seconds\n", delta / 1000);

    return 0;
}