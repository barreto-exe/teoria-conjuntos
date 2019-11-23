#include "conjuntos.h"
#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test();

void LeerArchivo();

int main(){
    ListaConjuntos clist;
    clist.ultimo = NULL;
    clist.universo = NULL;
    LeerArchivo(&clist);
    printf("\n");

    system("clear");
    imprimirHeader(&clist);
    LeerComandos(&clist);

    return 0;
}

void LeerArchivo(ListaConjuntos *lc){
   char NombreArchivo[40] = "file.txt", linea[1024];
   FILE *fpuntero = NULL;

   do{
      printf("Ingrese el nombre del archivo que desea abrir: \n");
      scanf("%s",NombreArchivo);
      printf("\n");

      fpuntero = fopen(NombreArchivo, "r");

      if(!fpuntero){
         printf("No se encontro el archivo %s \n",NombreArchivo);
         printf("\n");
      }
   }while(!fpuntero);

   lc->ultimo = NULL;
   lc->universo = NULL;


   while(fgets(linea, 1024, fpuntero)){
      if(strstr(linea,":")){
         char *inicio, *fin, *cname;

         linea[strlen(linea)-1]='\0'; //Esto corrige el caracter '\n' al final de la linea

         cname = (char *) malloc(sizeof(char)*26);

         inicio = fin = linea;
         fin = strstr(fin,":");
         strncpy(cname,inicio,fin-inicio);
         fin += 2;

         removerCaracteres(fin," ");

         int cantElem;
         char **elementsC = str2elementos(fin,&cantElem);

         crearConjunto(lc,cname,elementsC,cantElem);
      }
   }
   fclose(fpuntero);
}

int main()
{
    ListaConjuntos clist;
    clist.ultimo = NULL;
    clist.universo = NULL;

    LeerArchivo(&clist);
    printf("\n");

    //sleep(3);
    system("clear");

    LeerComandos(&clist);
    return 0;
}
