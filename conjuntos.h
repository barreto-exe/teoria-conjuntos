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
    struct elemento *primero,
                    *ultimo;
    struct conjunto *next;
} Conjunto;

typedef struct ListaConjuntos {
    struct conjunto *universo, //El primer conjunto de la lista.
                    *ultimo;
} ListaConjuntos;

Elemento *crearElemento(char *valor){
    Elemento *aux = (Elemento *) malloc(sizeof(Elemento));
    aux->valor = valor;
    aux->next = NULL;

    return aux;
}

void crearConjunto(ListaConjuntos *clist, char *nombre, char **elementos, int cantElem){
    /*
        -elementos es un arreglo de strings. Cada string es un elemento.
        -El nuevo conjunto se le asigna como next al ultimo de la lista conjunto
    */

    Conjunto *nuevo = (Conjunto *) malloc(sizeof(Conjunto));

    nuevo->nombre = nombre;
    Elemento *aux = nuevo->primero = crearElemento(elementos[0]);

    for(int i=1; i<cantElem; i++){
        aux->next = crearElemento(elementos[i]);
        if(i+1<cantElem)
            aux=aux->next;
    }

    nuevo->ultimo = aux;
    nuevo->next = NULL;

    if (!clist->universo)
        clist->universo = nuevo;

    if (clist->ultimo)
        clist->ultimo->next = nuevo;

    clist->ultimo = nuevo;
}

void imprimirConjunto(ListaConjuntos clist, char *cnombre){
    Conjunto *caux = clist.universo;
    int encontrado = 0;

    while(!encontrado && caux){
        if( strcmp(caux->nombre,cnombre) == 0 ){
            encontrado = 1;
        }
        else{
            caux = caux->next;
        }
    }

    if(!encontrado){
        printf("No se encontro el conjunto");
        return;
    }

    Elemento *eleaux = caux->primero;


    for(;eleaux!=NULL;eleaux=eleaux->next){
        if(eleaux->next)
            printf("%s - ",eleaux->valor);
        else
            printf("%s",eleaux->valor);
    }

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
      -El inverso de un conjunto vacío es universo.
    */

}
