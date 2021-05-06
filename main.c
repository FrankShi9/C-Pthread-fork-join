#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int a = 20, b = 100, result1 = 0, result2 = 0, result3 = 0;

struct Param{
    int* A;
    int* B;
};

void* plus(struct Param input){
    result1 = *input.A + *input.B;
    printf("First thread calculates a + b. The result 1 is: %d\n", result1);
    return NULL;
}

void* times(struct Param input){
    result2 = *input.A * *input.B;
    printf("Second thread calculates a * b. The result 2 is: %d\n", result2);
    return NULL;
}

void* minus(struct Param input){
    result3 =  *input.B - *input.A;
    printf("Third thread calculates a - b. The result 3 is: %d\n", result3);
    return NULL;
}



int main(){
    struct Param argument = {&a, &b};
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, (void *(*)(void *)) plus, (void*)(&argument));
    pthread_create(&tid[1], NULL, (void *(*)(void *)) times,(void*)(&argument));
    pthread_create(&tid[2], NULL, (void *(*)(void *)) minus,(void*)(&argument));
    
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    printf("Let's combine the results like this: result 1 + result 2 - result 3.\n");
    printf("The final value is: %d\n",result1+result2-result3);
    return 0;
}