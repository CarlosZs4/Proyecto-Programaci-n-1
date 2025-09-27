#ifndef ASISTENTEIA_H
#define ASISTENTEIA_H
#include "lista.h"
#include "pila.h"
#include "usuarios.h"
#include <stdbool.h>

typedef struct AsistenteIA
{
    Pila *mensaje;
    Pila *respuestaIA;
}AsistenteIA;

#endif // ASISTENTEIA_H