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

    char *universo[] = {"Hoola","Mundo","Todo","Bien","AAAAA"};
    char *conjA[] = {"AAAAA","Todo","Todo","Bien","Bien"};

    crearConjunto(&clist,"universo",universo,5);
    imprimirConjunto(clist,"universo");

    printf("\n");
    printf("\n");

    crearConjunto(&clist,"A",conjA,5);
    imprimirConjunto(clist,"A");

    printf("\n");
    printf("\n");

}
