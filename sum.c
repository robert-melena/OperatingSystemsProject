#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int sum; //this is shared by the threads
void *runner(void *param); //threads call this function

int main(){
    pthread_t tid; //thread identifier
    //represents the attributes for the thread
    //each thread has attributes such as stack size and scheduling info
    pthread_attr_t attr; //set of thread attributes

    int value = 5;


    //set default attributes of the thread
    pthread_attr_init(&attr);
    //create thread
    pthread_create(&tid,&attr,runner,(void *)&value);
    //wait for the thread to exit
    pthread_join(tid,NULL);


    printf("sum = %d\n",sum);
    




    return 0;
}


void *runner(void* param){
    int *upper = (int *) param;
    sum = 0;
    for(int i = 1;  i <= *upper; i++){
        sum += i;
    }

    pthread_exit(0);
}