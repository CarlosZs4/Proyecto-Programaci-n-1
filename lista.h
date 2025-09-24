#ifndef LISTA_H
#define LISTA_H
#include "nodo.h"
#include <stdio.h>

// Declaración de estructuras
typedef struct Lista {
    int longitud;
    Nodo *listar;
} Lista;

// Declaración de los tipos para las funciones de comparación y recorrido
typedef int (*FuncionComparacion)(void*, void*);
typedef void (*FuncionAccion)(void*);
typedef void (*FuncionImpresion)(void*);
typedef int (*FuncionIgualdad)(void*, void*);
typedef void (*FuncionImpresionArch)(void*,FILE*);

// Declaración de las funciones públicas
void crearL(Lista *lista);
void insertarL(Lista *lista, int pos, void* num);
void eliminarL(Lista *lista, int pos);
void* consultarL(Lista *lista, int pos);
size_t longitudL(Lista* lista);
void liberarL(Lista *lista);
void ordenarL(Lista *lista, FuncionComparacion comparar);
void imprimirL(Lista *lista, FuncionAccion imprimir_elemento);
void imprimirArchL(Lista *lista,const char* nombre_archivo,FuncionImpresionArch imprimir_arch);
int busquedaL(Lista *lista,void *objetivo,FuncionIgualdad igualdad);
Lista* busquedaTodasL(Lista *lista,void *objetivo,FuncionIgualdad igualdad);
// ... y cualquier otra función que quieras usar
int comparar_cadenas(void* a, void* b);
int comparar_caracteres(void* a, void* b);
int comparar_enteros(void* a, void* b);
void imprimir_entero(void* dato);
void imprimir_caracter(void* dato);
int son_iguales_enteros(void* a, void* b);
int son_iguales_caracteres(void* a,void* b);
int son_iguales_string(void* a,void* b);
#endif