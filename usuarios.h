#ifndef USUARIOS_H
#define USUARIOS_H
#include <stdbool.h>
typedef struct usuario
{
     int cantidadConsultas;
     int cantidadConsultasSinRespuesta;
     long cedula;
     char nombre[100], apellido[100];
     bool sesionActiva;
     bool esAdministrador;
}usuario;
typedef struct estadisticasG
{
     int consultasTotales,consultasSinRes,usuarioMasConsultas,cedula;
     char *nombre,*apellido;
}estadisticasG;

void registrarUsuario();
void registrarUsuarioAdministrador();
usuario* iniciarSesion();
usuario* iniciarSesionAdministrador();
void accionesAdministrador();
int menuAdministrador();
void mostrarString(void* string);
void cargarEstadistica(estadisticasG *estadisticas,const char *nombreArchivo);
void actualizarEstadisticas(usuario Actual,estadisticasG *estadisticas);
void verEstadisticas(usuario Actual,estadisticasG estadisticasGlobales);
void guardarEstadistica(estadisticasG estadisticas,const char *nombreArchivo);
#endif