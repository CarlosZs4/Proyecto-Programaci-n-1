#ifndef ASISTENTEIA_H
#define ASISTENTEIA_H
#include "lista.h"
#include "pila.h"
#include "usuarios.h"
#include <stdbool.h>


typedef struct AsistenteIA
{
    bool sesionActiva;
    Pila *mensaje;
    Pila *respuestaIA;
}AsistenteIA;
typedef struct ConocimientoIA
{
    char *preguntas;
    char *respuesta;
}ConocimientoIA;

int conversacion(AsistenteIA *usuario,Lista *baseDatos);
void cargarBaseConocimiento(Lista *baseDatos,const char *nombreArchivo);
void imprimir_baseDatos(void *a);


#endif // ASISTENTEIA_H