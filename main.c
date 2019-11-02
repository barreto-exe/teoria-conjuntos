#include "conjuntos.h"

void test();

int main()
{
    test();
    return 0;
}

void test(){

    ListaConjuntos clist = NULL;

    char *universo[] = { "Hola","Mundo","Todo", "Bien" };

    crearConjunto(clist,"A",universo,4);

}
