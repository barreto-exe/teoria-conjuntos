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

void removerCaracteres(char *cadena, char *caracteres) {
  int indiceCadena = 0, indiceCadenaLimpia = 0;
  int deberiaAgregarCaracter = 1;
  // Recorrer cadena carácter por carácter
  while (cadena[indiceCadena]) {
    // Primero suponemos que la letra sí debe permanecer
    deberiaAgregarCaracter = 1;
    int indiceCaracteres = 0;
    // Recorrer los caracteres prohibidos
    while (caracteres[indiceCaracteres]) {
      // Y si la letra actual es uno de los caracteres, ya no se agrega
      if (cadena[indiceCadena] == caracteres[indiceCaracteres]) {
        deberiaAgregarCaracter = 0;
      }
      indiceCaracteres++;
    }
    // Dependiendo de la variable de arriba, la letra se agrega a la "nueva
    // cadena"
    if (deberiaAgregarCaracter) {
      cadena[indiceCadenaLimpia] = cadena[indiceCadena];
      indiceCadenaLimpia++;
    }
    indiceCadena++;
  }
  // Al final se agrega el carácter NULL para terminar la cadena
  cadena[indiceCadenaLimpia] = 0;
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

      puntero[i][fin-inicio]='\0';

      inicio=++fin;
      fin=strstr(inicio,"-");

      if(!fin){
         fin = str + strlen(str);
      }

      //printf("%s-",puntero[i]);
   }
      //printf("\n");

   *cantElem = ContPalabras;
   return puntero;
}

int esCrearConj(char *cad){

   char *aux = strstr(cad,":");

   if(aux){
      char *auxNew = strstr(cad,"new");

      if(auxNew && auxNew[3] == ' '){
         return 1;
      }
   }

   return 0;
}

int esOpAlgebra(char *cad){
   //Esta funcion verifica que la cadena tenga parentesis balanceados.

   int contAbre = 0, contCierra = 0;

   for(int i=0; i<strlen(cad); i++)
      if(cad[i] == '(') contAbre++;

   for(int i=0; i<strlen(cad); i++)
      if(cad[i] == ')') contCierra++;

   return contAbre == contCierra;
}

void LeerComandos(ListaConjuntos *clist){
   char cad[1024];
   printf("/*********Teoria de Conjuntos*********/ \n");
   printf("-Operaciones algebraicas. \n");
   printf("-Crear conjuntos. \n");
   printf("-Para salir escriba 'exit'. \n");
   printf("-");
   imprimirConjunto(*clist,"universo");
   printf("\n");

   do{
      scanf(" %[^\n]",cad);
      printf("\n");

      if(esCrearConj(cad)){
         char *strElementos = strstr(cad, ":"), *iniName = cad + 4;

         char *cnombre = (char *) malloc(sizeof(char)*26);
         strncpy(cnombre,iniName,strElementos-iniName);

         cnombre[strElementos-iniName] = '\0';

         int cantElem = 0;
         strElementos += 2;

         removerCaracteres(strElementos," ");

         char **elementos = str2elementos(strElementos,&cantElem);

         if(!buscarConjunto(*clist,cnombre)){
            crearConjunto(clist,cnombre,elementos,cantElem);
            imprimirConjunto(*clist,cnombre);
            printf("\n");
         }else{
            printf("El conjunto %s ya existe. \n",cnombre);
            free(cnombre);
         }

         printf("\n");
      }
      else if (esOpAlgebra(cad)){


      }
      else if (strcmp(cad,"exit")){ //Si no es exit, es op invalida.
         printf("Operacion o sintaxis invalida. \n");
         printf("\n");
      }

   }while(strcmp(cad,"exit")); //Mientras la cadena sea distinta de exit

}
