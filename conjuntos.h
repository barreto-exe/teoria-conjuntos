//Prototipos de funciones
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento {
    char *valor;
    struct elemento *next;
} Elemento;

typedef struct conjunto {
    char *nombre;
    Elemento *primero,
             *ultimo; //El valor del ultimo elemento siempre debe ser null.
} Conjunto;

typedef struct ListaConjuntos {
    Conjunto *universo, //El primer conjunto de la lista.
             *ultimo,
             *actual,
             *next;
} ListaConjuntos;

void crearConjunto(ListaConjuntos clist, char *nombre, char **elementos){
    /*
        -elementos es un arreglo de strings. Cada string es un elemento.
        -El nuevo conjunto se le asigna como next al ultimo de la lista conjunto
    */

}

void imprimirConjunto(ListaConjuntos clist, char *cnombre){
}

int existeElemento(ListaConjuntos clist, Conjunto c, Elemento e){
    /*
      -El conjunto debe existir
    */
}

void unirConjunto(ListaConjuntos clist, Conjunto a, Conjunto b){
    /*
      -Ambos conjuntos deben existir
      -Primero compruebo que exista AUB, sino, creo dicho conjunto.
    */
}

void intersectarConjunto(ListaConjuntos clist, Conjunto a, Conjunto b){
    /*
      -Ambos conjuntos deben existir.
      -Primero compruebo que exista AxB, sino, lo creo.
    */

}

void invertirConjunto(ListaConjuntos clist, Conjunto a){
    /*
      -Si no existe -A, lo creo.
    */

}
