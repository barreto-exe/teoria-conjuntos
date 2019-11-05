
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
int main () {
   char str1[10], str2[40];
   FILE * fp;
   fp = fopen ("file.txt", "r");
   fscanf(fp, "%s %s", str1, str2);
   int ContPalabras=0;
   for(int i=0 ; str2[i]!='\0' ;i++){ //Tengo que cambiar ese  'i' por /0
         if(str2[i]=='-'){
            ContPalabras++;
         }
   }
   ContPalabras++;
   int contador=strlen(str2);
   char **puntero = NULL;
   int i,j=0;
   puntero = (char **)malloc(ContPalabras*sizeof(char*)); //Reservar memoria
   for( i=0 ; i<contador+2 ; i++){
      if(str2[i] == '-' || str2[i] == '\0' ){ //Tengo que cambiar ese  'i' por /0
         puntero[j] = (char*)malloc(ContarLetras(str2,i)*sizeof(char)+1);
         j++;
      }
   }

   char *inicio, *fin;
   inicio = str2;
   fin = strstr(str2,"-");

   for(i=0 ; i<ContPalabras ; i++){
      strncpy(puntero[i],inicio,fin-inicio);
      inicio=++fin;
      fin=strstr(inicio,"-");

      if(!fin){
         fin = str2 + strlen(str2);
      }
      printf("%s", puntero[i]);
   }
   fclose(fp);
   return(0);
}
//Validar cuando la cadena esta vacia, es decir, cuando es nulo y validar que cuando la cadena tenga solo una palabra

/*
conjA:
conjB: hola
(VALIDAR)
*/
