#include "conjuntos.h"
#include "comandos.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void test();

void LeerArchivo();

int main()
{
    //LeerArchivo();
    //test();
    //test2();
    LeerComandos();
    return 0;
}

void test(){

    //Siempre inicializar argumentos de ListasConjuntos en NULL para correcto funcionamiento.
    ListaConjuntos clist;
    clist.ultimo = NULL;
    clist.universo = NULL;

    char *universo[] = {"A","B","C","D"};
    char *conjA[] = {"A","B"};
    char *conjB[] = {"B","D"};

    int tamUniverso = (sizeof(universo)/sizeof(char *)),
        tamConjA    = (sizeof(conjA)/sizeof(char *)),
        tamConjB    = (sizeof(conjB)/sizeof(char *));

    crearConjunto(&clist,"universo",universo,tamUniverso);
    imprimirConjunto(clist,"universo");
    printf("\n");

    crearConjunto(&clist,"A",conjA,tamConjA);
    imprimirConjunto(clist,"A");
    printf("\n");

    crearConjunto(&clist,"B",conjB,tamConjB);
    imprimirConjunto(clist,"B");
    printf("\n");

    /*
    unirConjunto(&clist,"B","A");
    imprimirConjunto(clist,"BUA");
    printf("\n");
    */

    unirConjunto(&clist,"A","B");
    imprimirConjunto(clist,"AuB");
    printf("\n");

    intersectarConjunto(&clist,"A","B");
    imprimirConjunto(clist,"AxB");
    printf("\n");

    invertirConjunto(&clist,"AxB");
    imprimirConjunto(clist,"-AxB");
    printf("\n");


}

void test2(){

   ListaConjuntos clist;
   clist.ultimo = NULL;
   clist.universo = NULL;

   LeerArchivo(&clist);

   imprimirConjunto(clist,"universo");
   printf("\n");

   imprimirConjunto(clist, "A");


}

void LeerArchivo(ListaConjuntos *lc){
   char NombreArchivo[40] = "file.txt";
   printf("Ingrese el nombre del archivo que desea abrir: \n");
   printf("\n");

   //scanf("%s",NombreArchivo);
   char linea[1024];
   FILE *fpuntero = NULL;
   fpuntero = fopen(NombreArchivo, "r");

   if(!fpuntero){
    printf("No se encontro el archivo %s \n",NombreArchivo);
    printf("\n");
    return;
   }


   lc->ultimo = NULL;
   lc->universo = NULL;


   while(fgets(linea, 1024, fpuntero)){
      char *inicio, *fin, *cname;

      linea[strlen(linea)-1]='\0'; //Esto corrige el caracter '\n' al final de la linea

      cname = (char *) malloc(sizeof(char)*26);

      inicio = fin = linea;
      fin = strstr(fin,":");
      strncpy(cname,inicio,fin-inicio);
      fin += 2;


      int cantElem;
      char **elementsC = str2elementos(fin,&cantElem);

      crearConjunto(lc,cname,elementsC,cantElem);
   }
   fclose(fpuntero);
   /*
   fscanf(fpuntero, "%s %s", str1, str2);
   string2elementos(str2); //Este lee el universo, no se a quien se lo quieras pasar

   while(feof(fpuntero) == 0){
      char str3[40];
      fscanf(fpuntero, "%s %s %s", str1, str2, str3);
      string2elementos(str3); //Este lee los conjuntos, no se a quien se lo quieras pasar
   }
   fflush(fpuntero);
   fclose(fpuntero); //Da error aca

   return;*/
}
