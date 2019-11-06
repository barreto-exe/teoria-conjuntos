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

