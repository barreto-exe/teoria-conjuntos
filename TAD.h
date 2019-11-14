#ifndef TAD_H
#define TAD_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_PILA 50

typedef struct{
   char elem[MAX_PILA];
   int tope;
} Pila;

typedef struct{
   Conjunto *ini;
   Conjunto *fin;
   char c;
} Cola;

/*Operaciones de pila*/

int push(Pila *pilap,char dato){
   if(pilap->tope==MAX_PILA-1)
      return 0;
   pilap->elem[++pilap->tope]=dato;
   return 1;
}

int top(Pila *pilap,char *dato){
   if(pilap->tope==-1)
      return 0;
   *dato=pilap->elem[pilap->tope];
   return 1;
}

int pop(Pila *pilap,char *dato){
   if(pilap->tope==-1)
      return 0;
   *dato=pilap->elem[pilap->tope--];
   return 1;
}

int vacia(Pila *pilap){
   return pilap->tope==-1;
}

void anula(Pila *pilap){
   pilap->tope=-1;
}

/*Operaciones de cola*/

Cola *NuevaCola(){
   Cola *q;
   if((q = (Cola *)malloc(sizeof(Cola))) == NULL)
      exit(1);
   q->ini = q->fin = NULL;
   return q;
};

void AnulaCola(Cola *q){
   Conjunto *curp;
   if(!q)
      return;
   for(curp = q->ini ; curp ; curp = q->ini){
      q->ini = curp->next;
      free(curp);
   }
   q->fin = NULL;
}

int frente(Cola *q, char *car){
   if(q && q->ini){
      *car = q->ini->nombre;
      return 1;
   }
   return 0;
}

int Desencolar(Cola *q){
   if(q && q->ini){
      Conjunto* aux = q->ini;
      q->ini = aux->next;
      if(q->fin == aux)
         q->fin = NULL;
      free(aux);
      return 1;
   }
   return 0;
}

int vaciaCola(Cola *q){
   if(!q || !q->ini)
      return 1;
   return 0;
}

int Encolar(Cola *q, Conjunto *C){
   Conjunto *newp;
   if(!q)
      return 0;
   if((newp = (Conjunto *)malloc(sizeof(Conjunto))) == NULL)
      exit(1);
   newp->next = NULL;
   newp = C ;
   if(!q->ini){
      q->ini = q->fin = newp;
   }else{
      q->fin->next = newp;
      q->fin = newp;
   }
   return 1;
}

#endif
