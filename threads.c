//Robert Melena
//CS4440 - Operating Systems
//Synchronous Multithreading Project (Multithreaded Version)

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int size = 5000000;  
int numbers[size];

int sum = 0;
double mean;
double standardDeviation;
double median;
int mode;
int max;

// FUNCTION PROTOTYPES
void randomNumbers();
void writeToFile();
void calcTotalSum();
int compare(const void *a, const void *b);

// THREAD FUNCTIONS
void* calcMean(void *arg);
void* calcStandardDeviation(void *arg);
void* calcMedian(void *arg);
void* calcMode(void *arg);
void* calcMax(void *arg);


// ===========================
// MAIN
// ===========================
int main() {

    printf("\nGenerating random numbers...\n");
    randomNumbers();

    printf("Sorting numbers...\n");
    qsort(numbers, size, sizeof(int), compare);

    writeToFile();
    calcTotalSum();

    pthread_t t1, t2, t3, t4, t5;

    // Creating all worker threads
    pthread_create(&t1, NULL, calcMean, NULL);
    pthread_join(t1, NULL);   //mean must be prepped before stddeviation to prevent race condition

    pthread_create(&t2, NULL, calcStandardDeviation, NULL);
    pthread_create(&t3, NULL, calcMedian, NULL);
    pthread_create(&t4, NULL, calcMode, NULL);
    pthread_create(&t5, NULL, calcMax, NULL);

    // Waiting for the remaining threads to finish 
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    // Final Results printed in the main 
    printf("\n========== MULTITHREADED RESULTS ==========\n");
    printf("Size: %d\n", size);
    printf("Mean: %.2lf\n", mean);
    printf("Standard Deviation: %.2lf\n", standardDeviation);
    printf("Median: %.2lf\n", median);
    printf("Mode: %d\n", mode);
    printf("Max: %d\n", max);
    printf("===========================================\n\n");

    return 0;
}

// ===========================
// THREAD IMPLEMENTATIONS
// ===========================

void* calcMean(void *arg) {
    mean = (double)sum / size;
    pthread_exit(NULL);
}

// added some heavy workload 
void* calcStandardDeviation(void *arg) {
    double variance = 0;

    for (int i = 0; i < size; i++) {
        double diff = numbers[i] - mean;

        for (int j = 0; j < 50; j++) {
            variance += pow(diff,2);
        }
    }

    standardDeviation = sqrt(variance / (size * 50));
    pthread_exit(NULL);
}

void* calcMedian(void *arg) {
    median = (numbers[size/2 - 1] + numbers[size/2]) / 2.0;
    pthread_exit(NULL);
}

void* calcMode(void *arg) {
    int freq[101] = {0};

    for (int i = 0; i < size; i++)
        freq[numbers[i]]++;

    int maxCount = 0;

    for (int i = 1; i <= 100; i++) {
        if (freq[i] > maxCount) {
            maxCount = freq[i];
            mode = i;
        }
    }

    pthread_exit(NULL);
}

void* calcMax(void *arg) {
    max = numbers[size - 1];
    pthread_exit(NULL);
}


// ===========================
// HELPER FUNCTIONS
// ===========================

void randomNumbers() {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        numbers[i] = (rand() % 100) + 1;//printing range 1–100(inclusive)
    }
}

void writeToFile() {
    FILE *f = fopen("numbers.txt", "w");
    for (int i = 0; i < size; i++)
        fprintf(f, "%d\n", numbers[i]);
    fclose(f);
    printf("Data written to file and is now closed.\n");
}

void calcTotalSum() {
    for (int i = 0; i < size; i++)
        sum += numbers[i];
}

int compare(const void *a, const void *b) {
    int first = *((int*)a);
    int second = *((int*)b);
    if (first> second) return  1;
    if (first < second) return -1;
    return 0;
}
