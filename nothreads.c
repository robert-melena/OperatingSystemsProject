//Robert Melena
//CS4440 - Operating Systems
//Synchronous Multithreading Project (Sequential Version)

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<wchar.h>
#include<stdlib.h>
#include<math.h>

// global variables
const int size = 5000000;
int numbers[size];  // global array available to all threads
int sum;
double mean; //done
double standardDeviation; //done
double median; //done
int mode; //done
int max; //done

// FUNCTION PROTOTYPES

//helper functions
void randomNumbers();
void writeToFile();
void calcTotalSum();
int compare(const void *element1, const void *element2);


//FUNCTIONS
//MEAN function
void calcMean();
//STANDARD DEVIATION function
void calcStandardDeviation();
//MEDIAN function
void calcMedian();
//MODE function
void calcMode();
//MAX function
void calcMax();


// ===========================
// MAIN
// ===========================

int main(){
    printf("\n\n");
    //generate random numbers
    randomNumbers();
    //sorting the numbers here
    qsort(numbers,size,sizeof(int),compare);
    //write numbers to file
    writeToFile();
    //Calculate total sum
    calcTotalSum();

    calcMean();
    calcStandardDeviation();
    calcMedian();
    calcMode();
    calcMax();
   

    printf("----- SEQUENTIAL VERSION ----\n");
    printf("Size: %d\n", size);
    printf("Mean: %.2lf\n",mean);
    printf("Standard Deviation: %.2lf\n",standardDeviation);
    printf("Median: %.2lf\n",median);
    printf("Mode: %d\n",mode);
    printf("Max: %d\n",max);


    printf("\n\n");
    return 0;
}

void calcMax(){
    //since all sorted, max is the last number
    max = numbers[size - 1];
}



void calcMode(){
    int freq[101] = {0};

    // Count occurrences
    for (int i = 0; i < size; i++)
        freq[numbers[i]]++;

    int maxCount = 0;

    for (int i = 1; i <= 100; i++) {
        if (freq[i] > maxCount) {
            maxCount = freq[i];
            mode = i;
        }
    }

}


// ===========================
// Function IMPLEMENTATIONS
// ===========================
void calcMedian(){
    median = (numbers[size/2 - 1] + numbers[size/2]) / 2.0;
}

//calculate standard deviation
void calcStandardDeviation(){
double variance = 0;

    for (int i = 0; i < size; i++) {
        double diff = numbers[i] - mean;

        for (int j = 0; j < 50; j++) {
            variance += pow(diff,2);
        }
    }

    standardDeviation = sqrt(variance / (size * 50));
}


//calculate the mean
void calcMean(){
    mean =  (double) sum / size;

}

//sort array
int compare(const void *element1, const void *element2){
    int first = *((int *) element1);
    int second = *((int *) element2);

    if(first > second) return 1;
    if(first < second) return -1;
    return 0;

}

//calculate the sum (get input from file)
void calcTotalSum() {
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
}


//write numbers to file
void writeToFile(){
   FILE *fptr = fopen("numbers.txt","w");
    for(int i = 0; i < size; i++){
        fprintf(fptr, "%d\n", numbers[i]);
    }
    fclose(fptr);
        printf("Data written to file and is now closed\n");
}

//generate the random numbers
void randomNumbers() {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        numbers[i] = (rand() % 100) + 1;
    }
}
