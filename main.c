#include "conjuntos.h"

void test();

int main()
{
    test();
    return 0;
}

void test(){

    //Siempre inicializar argumentos de ListasConjuntos en NULL para correcto funcionamiento.
    ListaConjuntos clist;
    clist.ultimo = NULL;
    clist.universo = NULL;

    char *universo[] = {"A","B","C","1","2"};
    char *conjA[] = {"A","B","C"};
    char *conjB[] = {"2","1"};
    char *conjAB[] = {"A","B","C","2","1"};

    int tamUniverso = (sizeof(universo)/sizeof(char *)),
        tamConjA    = (sizeof(conjA)/sizeof(char *)),
        tamConjB    = (sizeof(conjB)/sizeof(char *)),
        tamConjAB    = (sizeof(conjAB)/sizeof(char *));

    crearConjunto(&clist,"universo",universo,tamUniverso);
    imprimirConjunto(clist,"universo");
    printf("\n");

    crearConjunto(&clist,"A",conjA,tamConjA);
    imprimirConjunto(clist,"A");
    printf("\n");

    crearConjunto(&clist,"C",conjB,tamConjB);
    //imprimirConjunto(clist,"C");
    printf("\n");

    crearConjunto(&clist,"-C",conjAB,tamConjAB);
    //imprimirConjunto(clist,"AUB");
    printf("\n");

    invertirConjunto(&clist,"C");




}
