//Robert Melena
//CS4440 - Operating Systems
//Synchronous Multithreading Project

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<wchar.h>
#include<stdlib.h>
#include<math.h>

// global variables
int size = 1000;
int sum;
double mean;
double standardDeviation;
double median;
int mode;
int max;

//prototypes

//helper functions
int *randomNumbers();
void writeToFile(int *numbers);
void calcTotalSum();
void sortNumbers();

//MEAN function
void *calcMean(void *arg);
//Standard Deviation
void *calcStandardDeviation(void *arg);


int main(){
    printf("\n\n");
    //generate random numbers
    int *numbers = randomNumbers();
    //write numbers to file
    writeToFile(numbers);
    //Calculate total sum
    calcTotalSum();

    //creating 5 pthread_t variable
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;

    //Giving threads tasks
    pthread_create(&thread1,NULL,calcMean,NULL);
    //wait for mean to finish
    pthread_join(thread1, NULL);

    pthread_create(&thread2,NULL,calcStandardDeviation,NULL);
    //waits for the standardDeviation to finish
    pthread_join(thread2, NULL);
   

    printf("Mean: %.2lf\n",mean);
    printf("Standard Deviation: %.2lf\n",standardDeviation);


    printf("\n\n");
    return 0;
}

void *calcStandardDeviation(void *arg){

    FILE *fptr = fopen("numbers.txt","r");
    double num;
    double variance = 0;
    double deviationSum = 0;

    if(fptr == NULL){
        printf("Error reading file!");
        exit(0);
    } 

    while (fscanf(fptr, "%lf", &num) == 1) {
        deviationSum += pow(num - mean,2);
    }
    variance = deviationSum / size;

    standardDeviation = sqrt(variance);

    fclose(fptr);
    pthread_exit(NULL);
}


void sortNumbers(){
    FILE *fptr = fopen("numbers.txt","w");
    

}



//calculate the mean
void* calcMean(void* arg){
    mean =  (double) sum / size;
    pthread_exit(NULL);

}

//calculate the sum (get input from file)
void calcTotalSum(){  
    FILE *fptr = fopen("numbers.txt","r");
    int num;

    if(fptr == NULL){
        printf("Error reading file!");
        exit(0);
    } 

    while (fscanf(fptr, "%d", &num) == 1) {
        sum += num;
        
    }

    fclose(fptr);
    printf("Sum has been calculated -> %d \n",sum);

}


//write numbers to file
void writeToFile(int *numbers){

    FILE *fptr;
    fptr = fopen("numbers.txt","w");
    if(fptr == NULL){
        printf("Unable to open file\n");
        exit(0);
    }else{
        //write to file
        for(int i = 0; i < size; i++){
            //on last input, dont print new line
            if(i == size - 1){
                fprintf(fptr,"%d",numbers[i]);
                break;
            }
            fprintf(fptr,"%d\n",numbers[i]);
        }

        //close file
        fclose(fptr);
        printf("Data written to file and is now closed\n");
    }


}


//generate the random numbers
int *randomNumbers(){
    //allocate memory for 1000 numbers
    int *numbers = (int *) malloc(sizeof(int) * size);
    //use current time as seed for random numbers
    srand(time(0));

    for(int i = 0; i < size; i++){
        int number = (rand() % 100) + 1;
        numbers[i] = number;
    }

    return numbers;
}







// //print numbers
// void printNumbers(int* numbers){
//     for(int i = 0; i < 1000; i++){
//         printf("%d\n",numbers[i]);
//     }

// }

//returns a pointer to an int
