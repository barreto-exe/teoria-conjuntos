#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento {
    char *valor;
    struct elemento *next;
} Elemento;

typedef struct conjunto {
    char *nombre;
    struct elemento *primero;
                    //*ultimo;
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

int elementosPertenecen(Conjunto *c, char **elementos, int cantElem){
    /*
        Si el conjunto es vacío (tiene 0 elementos), entonces siempre
        es subconjunto de cualquier conjunto.
    */
    for(int i=0; i < cantElem; i++){
        Elemento *aux = c->primero;
        int encontrado = 0;

        while(aux && !encontrado){
            if(strcmp(elementos[i],aux->valor) == 0){
                encontrado = 1;
            }
            else{
                aux = aux->next;
            }
        }

        if(!encontrado) return 0;
    }

    return 1;
}

void crearConjunto(ListaConjuntos *clist, char *nombre, char **elementos, int cantElem){
    /*
        -elementos es un arreglo de strings. Cada string es un elemento.
        -El nuevo conjunto se le asigna como next al ultimo de la lista conjunto
    */

    Conjunto *nuevo = (Conjunto *) malloc(sizeof(Conjunto));

    if (!clist->universo)
        clist->universo = nuevo;
    else{
        if(!elementosPertenecen(clist->universo,elementos,cantElem)){
            free(nuevo);
            printf("No se pudo crear el conjunto %s, porque tiene elementos invalidos \n",nombre);
            return;
        }
    }

    nuevo->nombre = nombre;
    //El nuevo conjunto será el ultimo
    if (clist->ultimo)
        clist->ultimo->next = nuevo;
    clist->ultimo = nuevo;
    nuevo->next = NULL;

    //Validación de que el conjunto sea vacío o no.
    if(cantElem){
        Elemento *aux = nuevo->primero = crearElemento(elementos[0]);

        for(int i=1; i<cantElem; i++){
            char *eleaux[]={elementos[i]};

            //Crea el elemento sólo si no existe previamente
            if(!elementosPertenecen(nuevo,eleaux,1)){
                aux->next = crearElemento(elementos[i]);
                if(i+1<cantElem)
                    aux=aux->next;
            }
        }
    }else{
        nuevo->primero = NULL;
    }

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
        printf("No se encontro el conjunto %s\n", cnombre);
        return;
    }

    Elemento *eleaux = caux->primero;

    printf("%s: ", cnombre);
    for(;eleaux!=NULL;eleaux=eleaux->next){
        if(eleaux->next)
            printf("%s - ",eleaux->valor);
        else
            printf("%s",eleaux->valor);
    }

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
