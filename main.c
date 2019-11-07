#include "conjuntos.h"
#include "comandos.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void test();

void LeerArchivo();

int main()
{
    LeerArchivo();
    //test();
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
void LeerArchivo(){
   char NombreArchivo[40] = "file.txt";
   printf("Ingrese el nombre del archivo que desea abrir: \n");
   printf("\n");

   //scanf("%s",NombreArchivo);
   //char str1[50], str2[256];
   char linea[1000];
   FILE *fpuntero = NULL;
   fpuntero = fopen(NombreArchivo, "r");

   if(!fpuntero){
    printf("No se encontro el archivo %s \n",NombreArchivo);
    printf("\n");
    return;
   }

   while(fgets(linea, 1024, fpuntero)){
      printf("%s \n",linea);
      //fscanf(fpuntero, "%s %s", str1, str2);
      //str2elementos(str2); //Este lee los conjuntos, no se a quien se lo quieras pasar
   }

   fclose(fpuntero);

   return;
}
