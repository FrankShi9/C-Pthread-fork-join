#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int a = 20, b = 100, result1 = 0, result2 = 0, result3 = 0;

struct Param{
    int* A;
    int* B;
};

void* plus(void* arg){
    result1 = a + b;
    // We will store the result in heap memory.
    //We will allocate a block of memory in heap of a size equal to the size of an integer (4 Bytes).
    printf("First thread calculates a + b. The result 1 is: %d\n", result1);
    int *pointer1 = (int *) malloc(sizeof(int));
    *pointer1 = result1;
    return pointer1;
}

void* times(void* arg){
    result2 = a * b;
    printf("Second thread calculates a * b. The result 2 is: %d\n", result2);
    int *pointer2 = (int *) malloc(sizeof(int));
    *pointer2 = result2;
    return result2;
}

void* minus(void* arg){
    result3 =  b - a;
    printf("Third thread calculates a - b. The result 3 is: %d\n", result3);
    int *pointer3 = (int *) malloc(sizeof(int));
    *pointer3 = result3;
    return pointer3;
}



int main(){
//    struct Param argument = {&a, &b};
    pthread_t tid[3];

    int *ptr1, *ptr2, *ptr3;

    pthread_create(&tid[0], NULL, plus, NULL);
    pthread_create(&tid[1], NULL, times,NULL);
    pthread_create(&tid[2], NULL, minus,NULL);
    
    pthread_join(tid[0],(void*)&ptr1);
    pthread_join(tid[1],(void*)&ptr2);
    pthread_join(tid[2],(void*)&ptr3);


    printf("First thread calculates a + b. The result 1 is: %d\n", *ptr1);
    printf("Second thread calculates a * b. The result 2 is: %d\n", *ptr2);
    printf("Third thread calculates a - b. The result 3 is: %d\n", *ptr3);

    printf("Let's combine the results like this: result 1 + result 2 - result 3.\n");
    printf("The final value is: %d\n",result1+result2-result3);
    return 0;
}