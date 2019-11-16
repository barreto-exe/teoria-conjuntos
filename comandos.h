#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Union +
#define Interseccion x
#define Complemento -

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

void LimpiarCadena(char *cad,int tam){
   for(int i=0; i<tam ; i++)
      cad[i]='\0';
}

void AddParentesis(char *cad){
      int i=strlen(cad)+1;
      cad[i]=')';
      for(i=0; i<strlen(cad);i++){
         cad[i]=cad[i+1];
      }
      cad[0]=' ';
      for(i = strlen(cad); i>0 ; i--){
         cad[i+1]=cad[i];
      }
      cad[0]='(';
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
      //

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

int BuscarMenorPre(char cad[], int tam){
   int Pivote=-1, pivoteAux = 4;
   for(int i = 0; i<tam ; i++){
      int aux=0;
      if(cad[i] == '('){
            for( ; cad[i] != ')' ; i++);
      }
      if(cad[i] == '-'){
         aux=3;
         if(pivoteAux>aux){
            pivoteAux=aux;
            Pivote=i;
         }
      }
      if(cad[i] == 'x'){
         aux=2;
         if(pivoteAux>aux){
            pivoteAux=aux;
            Pivote=i;
         }
      }
      if(cad[i] == '+'){
         aux=1;
         if(pivoteAux>aux){
            pivoteAux=aux;
            Pivote=i;
         }
      }
   }
   return Pivote;
}

char *OpAlgebra(ListaConjuntos *clist,char cad[]){
   char CadIzqui[512], CadDere[512];
   LimpiarCadena(CadIzqui,512);
   LimpiarCadena(CadDere,512);
   int Men = BuscarMenorPre(cad,strlen(cad));
   int i,j;

   for(i=0 ; i<Men; i++){
      CadIzqui[i]=cad[i];
   }
   for(j=0,i=Men+1 ; cad[i] != '\0' ;i++,j++){
      CadDere[j] = cad[i];
   }
   if(cad[Men] == '+'){
      char *ConjA =  OpAlgebra(clist, CadIzqui);
      char *ConjB =  OpAlgebra(clist, CadDere);
      unirConjunto(clist,ConjA,ConjB);
      return cad;
   }
   if(cad[Men] == 'x'){
      char *ConjA =  OpAlgebra(clist, CadIzqui);
      char *ConjB =  OpAlgebra(clist, CadDere);
      intersectarConjunto(clist,ConjA,ConjB);
      return cad;
   }
   if(cad[Men] == '-'){
      if(cad[Men+1] == '('){
         char CadAux[256];
         LimpiarCadena(CadAux,256);
         for(int k=0,i=Men+2 ; cad[i] != ')' ; i++, k++){
            CadAux[k]=cad[i];
         }
         char *Conj = OpAlgebra(clist,CadAux); //AddParentesis(OpAlgebra(clist,CadAux));
        // AddParentesis(Conj);         (AxB) /= AxB
         invertirConjunto(clist,Conj);
         return cad;
      }
      char *ConjA =  OpAlgebra(clist, CadDere);
      invertirConjunto(clist,ConjA);
      return cad;
   }
   /*Si no cumple ninguna de las condiciones*/
   return cad;
}

void LeerComandos(ListaConjuntos *clist){
   char cad[1024];
   printf("   _________________________________    \n");
   printf(" _/|:::::|TEORIA DE CONJUNTOS|:::::|\\_  \n");
   printf("|                                     | \n");
   printf("| -Crear conjuntos.                   | \n");
   printf("|                                     | \n");
   printf("| -Operaciones algebraicas            | \n");
   printf("|  de conjuntos.                      | \n");
   printf("|_____________________________________| \n\n");
   //printf("-Para salir escriba 'exit'. \n");
   //printf("-");
   imprimirConjunto(*clist,"universo");


   do{
      printf("\n");
      scanf(" %[^\n]",cad);

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

         }else{
            printf("El conjunto %s ya existe. \n",cnombre);
            free(cnombre);
         }


      }
      else if (esOpAlgebra(cad)){
         OpAlgebra(clist,cad);
         imprimirConjunto(*clist,cad);
     }
   }while(1); //Mientras siempre

}
