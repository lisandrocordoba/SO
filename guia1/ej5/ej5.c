#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bart(){
    printf("Bart\n");
}

void lisa(){
    printf("Lisa\n");
}

void maggie(){
    printf("Maggie\n");
}

void homero(){
    if (fork() == 0){
        bart();
        lisa();
        maggie();
    } else {
        printf("Homero\n");
    }
}

void abraham(){
    if (fork() == 0){
        homero();
    } else{
        printf("Abraham\n");
    }
}

int main(){
    abraham();
    return 0;
}