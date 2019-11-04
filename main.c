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

    char *universo[] = {"A","A","A","A","A"};
    char *conjA[] = {"A","B","A","A"};

    crearConjunto(&clist,"universo",universo,5);
    imprimirConjunto(clist,"universo");

    printf("\n");
    printf("\n");

    crearConjunto(&clist,"A",conjA,5);
    imprimirConjunto(clist,"A");

    printf("\n");
    printf("\n");

}
