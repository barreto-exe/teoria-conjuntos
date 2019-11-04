#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int ContarLetras(char str[],int inicio){
    int Cont;
    for(int i=inicio;i>-1 || str[i]=='-' ;i--){
         Cont++;
    }
    return Cont;
}
