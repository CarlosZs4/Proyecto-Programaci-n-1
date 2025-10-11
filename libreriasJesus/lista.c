#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Nodo* crear_nodo(void* dato) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.");
        exit(1);
    }
    nuevo_nodo->info = dato;
    nuevo_nodo->prox = NULL;
    return nuevo_nodo;
}
static void liberar_nodo(Nodo* nodo) {
    if (nodo != NULL) {
        free(nodo);
    }
}
void crearL(Lista *lista){
    lista->longitud=0;
    lista->listar=NULL;
}
void insertarL(Lista *lista,int pos,void* num){
    if((pos>=1)&&(pos<=lista->longitud+1)){
        Nodo *nuevo_nodo,*aux;
        nuevo_nodo=crear_nodo(num);
        if(pos==1){
            nuevo_nodo->prox=lista->listar;
            lista->listar=nuevo_nodo;
        }
        else{
            aux=lista->listar;
            for (int i = 1; i < pos-1;i++)
            {
                aux=aux->prox;
            }
            nuevo_nodo->prox=aux->prox;
            aux->prox=nuevo_nodo;
        }
        lista->longitud++;
    }
}
void eliminarL(Lista *lista,int pos){
    Nodo *aux,*ant;
    if((pos>=1)&&(pos<=lista->longitud)){
        aux=lista->listar;
        if(pos==1){
            lista->listar=aux->prox;
            liberar_nodo(aux);
        }
        else{
            for (int i = 1; i < pos;i++)
            {
                ant=aux;
                aux=aux->prox;
            }
            ant->prox=aux->prox;
            liberar_nodo(aux);            
        }
        lista->longitud--;
    }
}
void* consultarL(Lista *lista,int pos){
    Nodo *aux;
    if((pos>=1)&&(pos<=lista->longitud)){
        if(pos==1){
            return lista->listar->info;
        }
        else{
            aux = lista->listar;
            for (int i = 1; i < pos;i++)
            {
                aux=aux->prox;
            }
            return aux->info;
        }
    }
    return NULL; 
}
size_t longitudL(Lista* lista) {
    if (lista == NULL) {
        return 0;
    }
    return lista->longitud;
}
void liberarL(Lista *lista) {
    if (lista == NULL || lista->listar == NULL) {
        return;
    }
    Nodo *actual = lista->listar;
    Nodo *siguiente;

    while (actual != NULL) {
        siguiente = actual->prox;
        free(actual->info);
        free(actual);
        actual = siguiente;
    }
}

void ordenarL(Lista *lista, FuncionComparacion comparar) {
    if (lista == NULL || lista->longitud < 2) {
        return;
    }

    int intercambios;
    Nodo *anterior = NULL;
    Nodo *actual = NULL;
    
    do {
        intercambios = 0;
        anterior = NULL;
        actual = lista->listar;

        while (actual != NULL && actual->prox != NULL) {
            Nodo *siguiente = actual->prox;

            if (comparar(actual->info, siguiente->info) > 0) {
                // Intercambio
                if (anterior == NULL) {
                    lista->listar = siguiente;
                } else {
                    anterior->prox = siguiente;
                }
                
                actual->prox = siguiente->prox;
                siguiente->prox = actual;
                
                // Después del intercambio, actualizamos el puntero 'actual'
                // para que apunte al nuevo nodo en esta posición.
                actual = siguiente;
                intercambios = 1;
            }
            
            // Avanzamos los punteros
            anterior = actual;
            actual = actual->prox;
        }
    } while (intercambios);
}
int busquedaL(Lista *lista,void *objetivo,FuncionIgualdad igualdad){    
    Nodo *auxL=lista->listar;
    int i=1;
    while (auxL!=NULL)
    {
        if(igualdad(auxL->info, objetivo)){
            return i;
        }
        auxL=auxL->prox;
        i++;
    }
    return -1;
}
Lista* busquedaTodasL(Lista *lista,void *objetivo,FuncionIgualdad igualdad){
    Lista *Coincidencias=(Lista*)malloc(sizeof(Lista));
    if(Coincidencias==NULL){
        return NULL;
    }
    crearL(Coincidencias);
    Nodo *aux=lista->listar;
    int pos=1;
    while (aux!=NULL)
    {
        if(igualdad(aux->info,objetivo)){
            insertarL(Coincidencias,pos,aux->info);
            pos++;
        }
        aux=aux->prox;
    }
    return Coincidencias;
}
void imprimirL(Lista *lista, FuncionImpresion imprimir_elemento) {
    Nodo *temp = lista->listar;
    printf("Lista: ");
    while (temp != NULL) {
        imprimir_elemento(temp->info);
       // printf(" -> ");
        temp = temp->prox;
    }
    printf("\n");
}
void imprimirArchL(Lista *lista,const char* nombre_archivo,FuncionImpresionArch imprimir_arch){
    Nodo *tem =lista->listar;
    FILE *arch=fopen(nombre_archivo,"w");
    if (arch == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fprintf(arch,"%d\n",lista->longitud);
    while (tem!=NULL)
    {
        imprimir_arch(tem->info,arch);
        tem=tem->prox;
    }
    fclose(arch);
}