#include "conjuntos.h"
#include "comandos.h"
void test();

void LeerArchivo();

int main()
{
    LeerArchivo();
    test();
    return 0;
}

void test(){

    //Siempre inicializar argumentos de ListasConjuntos en NULL para correcto funcionamiento.
    ListaConjuntos clist;
    clist.ultimo = NULL;
    clist.universo = NULL;

    char *universo[] = {"Hola","Mundo","Todo","Bien","AAAAA"};
    char *conjA[] = {"A","B","C","D","E"};

    crearConjunto(&clist,"universo",universo,5);
    imprimirConjunto(clist,"universo");

    printf("\n");
    printf("\n");

    crearConjunto(&clist,"A",conjA,5);
    imprimirConjunto(clist,"A");

    printf("\n");
    printf("\n");

}
void LeerArchivo(){
   char NombreArchivo[40];
   printf("%s",NombreArchivo);
   char str1[10], str2[40];
   FILE *fpuntero;
   fpuntero = fopen (NombreArchivo, "r");
   fscanf(fpuntero, "%s %s", str1, str2);
   Elementos(str2); //Este lee el universo, no se a quien se lo quieras pasar
   while(!feof(fpuntero)){
      fscanf(fpuntero, "%s %s", str1, str2);
      Elementos(str2); //Este lee los conjuntos, no se a quien se lo quieras pasar
   }

}
