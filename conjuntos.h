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
        //printf("%p %p",clist->universo,clist->ultimo);
        if(!elementosPertenecen(clist->universo,elementos,cantElem)){
            free(nuevo);
            printf("No se pudo crear el conjunto %s, porque tiene elementos invalidos %s\n",nombre);
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

Conjunto *buscarConjunto(ListaConjuntos clist, char *cnombre){
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

    if(!encontrado) return NULL;

    return caux;
}

Elemento *buscarElemento(Conjunto c, char *enombre){
    Elemento *aux = c.primero;
    int encontrado = 0;

    while(!encontrado && aux){
        if( strcmp(aux->valor,enombre) == 0 ){
            encontrado = 1;
        }
        else{
            aux = aux->next;
        }
    }

    if(!encontrado){
        return NULL;
    }

    return aux;
}

void imprimirConjunto(ListaConjuntos clist, char *cnombre){
    Conjunto *caux = buscarConjunto(clist,cnombre);

    //Si el elemento no existe, retorno
    if( !caux ){
        printf("No se encontro el conjunto %s\n", cnombre);
        return;
    }


    Elemento *eleaux = caux->primero;

    printf("%s: ", cnombre);
    for(;eleaux!=NULL;eleaux=eleaux->next){
        if(eleaux->next)
            printf("%s - ",eleaux->valor);
        else
            printf("%s \n",eleaux->valor);
    }

}

void unirConjunto(ListaConjuntos *clist, char *conja, char *conjb){
    /*
      -Ambos conjuntos deben existir
      -Primero compruebo que exista AUB, sino, creo dicho conjunto.
    */
    char *newname = (char *) malloc(strlen(conja)+strlen(conjb)+1);
    strcpy(newname,conja);
    strcat(newname,"u");
    strcat(newname,conjb);

    Conjunto *a   = buscarConjunto(*clist,conja),
             *b   = buscarConjunto(*clist,conjb),
             *aub = buscarConjunto(*clist,newname);

    if(!(a && b)){
        printf("Fallo al crear el conjunto %s. Hay conjuntos invalidos en la operacion. \n",newname);
        return;
    }

    if(aub) return;

    char *newElem[] = {};
    crearConjunto(clist,newname,newElem,0);

    if(!a->primero && !b->primero) return;



    Elemento *auxA = a->primero, *auxB = b->primero, *eleAux;
    Conjunto *newC= buscarConjunto(*clist,newname);

    if(a->primero){
        do{
            if(!newC->primero){
                newC->primero = eleAux = crearElemento(auxA->valor);
            }else if(!buscarElemento(*newC,auxA->valor)){
                eleAux->next = crearElemento(auxA->valor);
                eleAux = eleAux->next;
            }
            auxA = auxA->next;
        }while(auxA);
    }

    if(b->primero){
        do{
            if(!newC->primero){
                newC->primero = eleAux = crearElemento(auxB->valor);
            }else if(!buscarElemento(*newC,auxB->valor)){
                eleAux->next = crearElemento(auxB->valor);
                eleAux = eleAux->next;
            }
            auxB = auxB->next;
        }while(auxB);
    }
}

void intersectarConjunto(ListaConjuntos *clist, char *conja, char *conjb){
    /*
      -Ambos conjuntos deben existir.
      -Primero compruebo que exista AxB, sino, lo creo.
    */

    char *newname = (char *) malloc(strlen(conja)+strlen(conjb)+1);
    strcpy(newname,conja);
    strcat(newname,"x");
    strcat(newname,conjb);

    Conjunto *a   = buscarConjunto(*clist,conja),
             *b   = buscarConjunto(*clist,conjb),
             *axb = buscarConjunto(*clist,newname);

    if(!(a && b)){
        printf("Fallo al crear el conjunto %s. Hay conjuntos invalidos en la operacion. \n",newname);
        return;
    }

    if(axb) return;

    char *newElem[] = {};
    crearConjunto(clist,newname,newElem,0);

    if(!(a->primero && b->primero)) return;

    Elemento *auxA = a->primero, *eleAux;
    Conjunto *newC= buscarConjunto(*clist,newname);

    do{
        if(buscarElemento(*b,auxA->valor) && !newC->primero){
            newC->primero = eleAux = crearElemento(auxA->valor);
        }else if(buscarElemento(*b,auxA->valor)){
            eleAux->next = crearElemento(auxA->valor);
            eleAux = eleAux->next;
        }

        auxA = auxA->next;
    }while(auxA);

}

void invertirConjunto(ListaConjuntos *clist, char *namec){
    /*
      -Si no existe -A, lo creo.
      -El inverso de un conjunto vacío es universo.
    */

    char *newname = (char *) malloc(strlen(namec)+1);
    strcpy(newname,"-");
    strcat(newname,namec);

    Conjunto *c      = buscarConjunto(*clist,namec),
             *menosc = buscarConjunto(*clist,newname);

    if(!c){
        printf("Fallo al crear el conjunto %s. No existe el conjunto %s. \n",newname,namec);
        return;
    }

    if(menosc) return;

    char *newElem[] = {};
    crearConjunto(clist,newname,newElem,0);
    Elemento *univAux = clist->universo->primero, *eleAux;
    Conjunto *newC= buscarConjunto(*clist,newname);

    do{
        //Si el elemento del universo no existe en C, entonces se añade al nuevo conjunto.
        if( !buscarElemento(*c,univAux->valor) && !newC->primero ){
            newC->primero = eleAux = crearElemento(univAux->valor);
        }else if (!buscarElemento(*c,univAux->valor)){
            eleAux->next = crearElemento(univAux->valor);
            eleAux = eleAux->next;
        }
        univAux = univAux->next;
    }while(univAux);
}
