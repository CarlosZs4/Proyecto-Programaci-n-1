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
void actualizarBaseDatos(Lista *baseDatos);
void actualizarBaseConocimiento(Lista *baseDatos, const char *nombreArchivo);
void guardarBaseConocimiento(Lista *baseDatos, const char *nombreArchivo);
void mostrarPendientes(const char *nombreArchivo);
void guardarPendientes(Pila *pilaPendientes, const char *nombreArchivo);
void mensajeSalida(char* msg1, char* msg2);
int menu();
int loginInterface();
#endif // ASISTENTEIA_H