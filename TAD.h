#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
   char cad[1024];
   struct nodo *next;
}Nodo;

typedef struct{
   Nodo *top;
}Pila;

typedef struct{
   Nodo *ini;
   Nodo *fin;
}Cola;

/*Operaciones de pila*/

Pila *NuevaPila(){
   Pila *s;
   if(((s = (Pila *)malloc(sizeof(Pila)))) == NULL)
      exit(1);
   s->top = NULL;
   return s;
}

void BorrarPila(Pila *s){
   Nodo *aux;
   if(!s)
      return;
   for(aux = s->top ; aux ; aux = s->top){
      s->top = aux->next;
      free(aux);
   }
}

int vaciaPila(Pila *s){
   if(!s || !s->top)
      return 1;
   return 0;
}

int top(Pila *s, char *cadena){
   if(s && s->top){
      strcpy(cadena,s->top->cad);
      return 1;
   }
   return 0;
}

int pop(Pila *s, char *cadena){
   if(s && s->top){
      Nodo * aux = s->top;
      s->top = aux->next;
      strcpy(cadena,aux->cad);
      free(aux);
      return 1;
}
return 0;
}

int push(Pila *s, char *cadena){
   Nodo *newp;
   if(!s)
      return 0;
   if((newp = (Nodo*)malloc(sizeof(Nodo))) == NULL)
      exit(1);
   newp->next = s->top;
   strcpy(newp->cad,cadena);
   s->top = newp;
   return 1;
}

/*Operaciones de Cola*/

Cola *NuevaCola(){
   Cola *q;
   if((q = (Cola *)malloc(sizeof(Cola))) == NULL)
      exit(1);
   q->ini = q->fin = NULL;
   return q;
}

void BorrarCola(Cola *q){
   Nodo *aux;
   if(!q)
      return;
   for(aux = q->ini ; aux ; aux = q->ini){
      q->ini = aux->next;
      free(aux);
   }
   q->fin = NULL;
}

int vaciaCola(Cola *q){
   if(!q || !q->ini)
      return 1;
   return 0;
}

int frente(Cola *q, char *cadena){
   if(q && q->ini){
      strcpy(cadena,q->ini->cad);
      return 1;
   }
   return 0;
}

int Encolar(Cola *q, char *cadena){
   Nodo *newp;
   if(!q)
      return 0;
   if((newp = (Nodo*)malloc(sizeof(Nodo))) == NULL)
      exit(1);
   newp->next = NULL;
   strcpy(newp->cad,cadena);
   if(!q->ini){
      q->ini = q->fin = newp;
   }else{
      q->fin->next = newp;
      q->fin = newp;
   }
   return 1;
}

int Descolar(Cola *q, char *cadena){
   if(q && q->ini){
      Nodo *aux = q->ini;
      q->ini = aux->next;
   if(q->fin == aux)
      q->fin = NULL;
   strcpy(cadena,aux->cad);
   free(aux);
   return 1;
   }
   return 0;
}

