#include <stdio.h>


int isPerfect(int num);
void printPerfect(int start, int end);



int main(){

    int start, end;
    
    printf("Enter lower limit: ");
    scanf("%d", &start);
    printf("Enter upper limit: ");
    scanf("%d", &end);
    
    printPerfect(start, end);
    
    return 0;
}


int isPerfect(int num){

    int sum = 0;
    
    for(int i = 1; i < num; i++){
    
        if(num % i == 0){
            sum += i;
        }
    }
   return sum == num;
}


void printPerfect(int start, int end){

    for (int i = start; i <= end; i++){
    
        if(isPerfect(i)){
            printf("%d\n", i);
        }
    }
}
