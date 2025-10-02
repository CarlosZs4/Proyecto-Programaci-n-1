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
    Pila *pendientes;
}AsistenteIA;
typedef struct ConocimientoIA
{
    char *preguntas;
    char *respuesta;
}ConocimientoIA;

int conversacion(AsistenteIA *asistente,Lista *baseDatos,usuario *Datousuario);
void cargarBaseConocimiento(Lista *baseDatos,const char *nombreArchivo);
void guardarHistorial(AsistenteIA *asistente, usuario *datosUsuario, const char *nombreArchivo);
void mostrarHistorial(long cedulaUsuario, const char *nombreArchivo);
void eliminarUltimaPeticion(AsistenteIA *asistente);

#endif // ASISTENTEIA_H