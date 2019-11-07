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
char **str2elementos(char str[]){
   char **puntero = NULL;

   /*if(!strstr(str,'-')){
      if(strlen(str)>0){
         puntero = (char **)malloc(sizeof(char*));
         puntero[0] = (char*)malloc(strlen(str)*sizeof(char)+1);
         strcpy(puntero[0],str);
         return puntero;
      }else{
         puntero=' ';
         return puntero;
      }
   }*/

   int ContPalabras=0;
   for(int i=0 ; str[i]!='\0' ;i++){
         if(str[i]=='-'){
            ContPalabras++;
         }
   }
   ContPalabras++;

   int i,j=0;
   puntero = (char **)malloc(ContPalabras*sizeof(char*)); //Reservar memoria
   for( i=0 ; i<strlen(str)+2 ; i++){
      if(str[i] == '-' || str[i] == '\0' ){ //Tengo que cambiar ese  'i' por /0
         puntero[j] = (char*)malloc(ContarLetras(str,i)*sizeof(char)+1);
         j++;
      }
   }

   char *inicio, *fin;
   inicio = str;
   fin = strstr(str,"-");

   for(i=0 ; i<ContPalabras ; i++){
      strncpy(puntero[i],inicio,fin-inicio);
      inicio=++fin;
      fin=strstr(inicio,"-");

      if(!fin){
         fin = str + strlen(str);
      }
   }
   return puntero;
}
