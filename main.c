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

    char *universo[] = { "Hola","Mundo","Todo", "Bien" };

    crearConjunto(clist,"A",universo,4);
    imprimirConjunto(clist,"A");

}
