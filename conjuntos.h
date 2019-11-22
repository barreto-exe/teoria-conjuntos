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

void copiarConjuntoParentensis(ListaConjuntos *clist, char *cnombre); //Lo pongo aquí porque lo requiere la siguiente función.

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
            printf("No se pudo crear el conjunto %s, porque tiene elementos invalidos\n",nombre);

            return;
        }
    }

    nuevo->nombre = (char *) malloc(sizeof(char)*strlen(nombre)+1);
    strcpy(nuevo->nombre,nombre);

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

   copiarConjuntoParentensis(clist,nombre);
   return;
}

Conjunto *buscarConjunto(ListaConjuntos clist, char *cnombre){
    Conjunto *caux = clist.universo;
    int encontrado = 0;
    while(!encontrado && caux){
        if(strcmp(caux->nombre,cnombre) == 0 ){
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

void copiarConjuntoParentensis(ListaConjuntos *clist, char *cnombre){

    //if(cnombre[0] == '(') return;

    int aux = BuscarMenorPre(cnombre,strlen(cnombre));
    if(aux == -1){
      return cnombre;
    }

   char *nombrecopia = (char *) malloc(strlen(cnombre)+3); //+3: Caracter nulo y dos parentesis
   strcpy(nombrecopia,"(");
   strcat(nombrecopia,cnombre);
   strcat(nombrecopia,")");

   char *vacio[] = {};
   crearConjunto(clist,nombrecopia,vacio,0);
   //El primero del conjunto nuevo tiene el mismo valor que el primero del viejo, igual que el next (NULL).
   Conjunto *copia = buscarConjunto(*clist,nombrecopia);
   Conjunto *original = buscarConjunto(*clist,cnombre);

   if(!original->primero) return; //Si original no tiene primero, la copia tampoco tendrá.n

   char *valor = original->primero->valor;
   copia->primero= crearElemento(valor);

   Elemento *elemA = buscarConjunto(*clist,cnombre)->primero,
            *elemB = buscarConjunto(*clist,nombrecopia)->primero;

   while(elemA->next){
      elemA = elemA->next;
      elemB->next = crearElemento(elemA->valor);
      elemB = elemB->next;
   }
}

void imprimirConjunto(ListaConjuntos clist, char *cnombre){
    Conjunto *caux = buscarConjunto(clist,cnombre);

    //Si el elemento no existe, retorno
    if( !caux ){
        printf("No se pudo imprimir el conjunto %s\n", cnombre);
        return;
    }


    Elemento *eleaux = caux->primero;

    printf("%s: { ", cnombre);
    for(;eleaux!=NULL;eleaux=eleaux->next){
        if(eleaux->next)
            printf("%s - ",eleaux->valor);
        else
            printf("%s",eleaux->valor);
    }
    printf(" }\n");

}

void unirConjunto(ListaConjuntos *clist, char *conja, char *conjb){
    /*
      -Ambos conjuntos deben existir
      -Primero compruebo que exista AUB, sino, creo dicho conjunto.
    */
    char *newname = (char *) malloc(strlen(conja)+strlen(conjb)+1);
    strcpy(newname,conja);
    strcat(newname,"+");
    strcat(newname,conjb);

    Conjunto *a   = buscarConjunto(*clist,conja),
             *b   = buscarConjunto(*clist,conjb),
             *aub = buscarConjunto(*clist,newname);

    if(!(a && b)){
        printf("Fallo al crear el conjunto %s. Hay conjuntos invalidos en la operacion. \n",newname);
        printf("%s: %p | %s: %p \n",conja,a,conjb,b);
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

   copiarConjuntoParentensis(clist,newname);
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
        printf("Fallo al crear el conjunto %s. Hay conjuntos invalidos en la operacion.\n",newname);
        printf("%s: %p | %s: %p \n",conja,a,conjb,b);
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

   copiarConjuntoParentensis(clist,newname);
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

   copiarConjuntoParentensis(clist,newname);
}
