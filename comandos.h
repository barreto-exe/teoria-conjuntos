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
char **str2elementos(char str[], int *cantElem){

   char **puntero = NULL;

   if(!strstr(str,"-") && strlen(str)>0){
      puntero = (char **)malloc(sizeof(char*));
      puntero[0] = (char*)malloc(strlen(str)*sizeof(char)+1);
      strcpy(puntero[0],str);
      *cantElem = 1;
      return puntero;
   }

   int ContPalabras=0, i;
   for(i=0 ; str[i]!='\0' ;i++){
         if(str[i]=='-'){
            ContPalabras++;
         }
   }

   if(i>0) ContPalabras++; //Si la cadena es vacía, se queda en 0.

   int j=0;
   puntero = (char **)malloc(ContPalabras*sizeof(char*));
   for( i=0 ; i<strlen(str)+2 ; i++){
      if(str[i] == '-' || str[i] == '\0' ){
         puntero[j] = (char*)malloc(ContarLetras(str,i)*sizeof(char)+1);
         j++;
      }
   }

   char *inicio, *fin;
   inicio = str;
   fin = strstr(str,"-");
   if(!fin){
      fin = inicio + strlen(inicio);
   }

   for(i=0 ; i<ContPalabras ; i++){
      strncpy(puntero[i],inicio,fin-inicio);
      inicio=++fin;
      fin=strstr(inicio,"-");

      if(!fin){
         fin = str + strlen(str);
      }

      //printf("%s-",puntero[i]);
   }

   *cantElem = ContPalabras;
   return puntero;
}
void NuevoConjuntoCom(ListaConjuntos *clist){
   char *Cadena, *NombreConj;
   char c;
   int i=0;

   Cadena = (char*)malloc(sizeof(char));
   int auxbandera=0;
   while(c != '\n'){
      c = getchar();
      Cadena = (char*)realloc(Cadena, sizeof(char));
      Cadena[i++] = c; //Da error aqui
      if(c == ':' && auxbandera==0){
         i--;
         Cadena[i]='\0';
         NombreConj = (char*)malloc(i*sizeof(char));
         strcpy(NombreConj,Cadena);
         strcpy(Cadena,"");
         i=0;
         auxbandera=1;
      }
   }
   char **var = str2elementos(Cadena,&i);
   crearConjunto(clist,NombreConj,var,i);

}
void LeerComandos(ListaConjuntos *clist){ //Leer comandos realmente debe ir en el int main

   char *Cadena;
   char c;
   int i=0;

   Cadena = (char*)malloc(sizeof(char));
   //nombreConj = (char *) malloc(sizeof(char)*???????);

   while(c != '\n'){
      c = getchar();
      Cadena = (char*)realloc(Cadena, sizeof(char));
      Cadena[i++] = c;
      if(strcmp("new ",Cadena) == 0){ //Se esta metiendo a pesar de no tener la cadena new
         NuevoConjuntoCom(clist);
         break;
      }
   }


   return;
}



