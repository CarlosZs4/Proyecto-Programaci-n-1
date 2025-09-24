#ifndef ASISTENTEIA_H
#define ASISTENTEIA_H
#include "lista.h"
#include "pila.h"

typedef struct AsistenteIA
{
    char nombre[50],apellido[50];
    int cedula;
    Pila *mensaje;
    Pila *respuestaIA;
}AsistenteIA;

AsistenteIA registrarse();


#endif // ASISTENTEIA_H
