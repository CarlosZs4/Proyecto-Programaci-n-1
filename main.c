/*librerias estandar de C*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
/*-------------------------*/
/*librerias del proyecto*/
#include "AsistenteIA.h"
/*-------------------------*/
int main()
{
  AsistenteIA asistente;
  Lista baseDatos;
  usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
  int op;
  int continuar;
  crearL(&baseDatos);
  cargarBaseConocimiento(&baseDatos, "BaseConocimiento.txt");
  asistente.mensaje = (Pila *)malloc(sizeof(Pila));
  asistente.respuestaIA = (Pila *)malloc(sizeof(Pila));
  asistente.pendientes = (Pila *)malloc(sizeof(Pila));
  if (asistente.mensaje == NULL || asistente.respuestaIA == NULL || asistente.pendientes == NULL)
  {
    fprintf(stderr, "Error: No se pudo asignar memoria para las pilas.\n");

    if (asistente.mensaje)
      free(asistente.mensaje);
    if (asistente.respuestaIA)
      free(asistente.respuestaIA);
    exit(1);
  }
  crearP(asistente.mensaje);
  crearP(asistente.respuestaIA);
  crearP(asistente.pendientes);
  do
  {
    continuar = loginInterface();
    while (continuar < 1 || continuar > 4)
    {

      system("clear");
      printf("ingrese una opción válida!\n");
      sleep(1);
      continuar = loginInterface();
    };
    switch (continuar)
    {
    case 1:
      registrarUsuario();
      break;
    case 2:
      nuevoUsuario = iniciarSesion();
      if (nuevoUsuario->sesionActiva)
      {
        system("clear");
        printf("Bienvenido/a %s, ya puedes usar el asistente!\n", nuevoUsuario->nombre);
        sleep(1);
        do
        {
          op = menu();
          while (op < 1 || op > 4)
          {

            system("clear");
            printf("ingrese una opción válida!\n");
            sleep(1);
            op = menu();
          };
          switch (op)
          {
          case 1:
            if (nuevoUsuario->sesionActiva)
            {
              int continuar_conversacion = 1;
              char resp[2];
              system("clear");
              printf("--- Asistente IA Iniciado ---\n");
              printf("Escribe 'salir' para terminar la conversación.\n\n");

              while (continuar_conversacion)
              {
                continuar_conversacion = conversacion(&asistente, &baseDatos, nuevoUsuario);
              }
              printf("\n--- Conversación Finalizada ---\n");
              printf("Desea Deshacer su ultima peticion?\nNo\nSi\n");
              printf("Elige una opcion: ");
              scanf("%2s", resp);
              if (strcmp(resp, "si") == 0 || strcmp(resp, "Si") == 0)
              {
                eliminarUltimaPeticion(&asistente);
              }
              system("clear");
              printf("¡Hasta pronto!\n");
              guardarHistorial(&asistente, nuevoUsuario, "Conversaciones.txt");
              sleep(1);
            }
            else
            {
              system("clear");
              printf("La sesión debe estar activa!\n");
              sleep(1);
            }
            break;
          case 2:
            if (nuevoUsuario->sesionActiva)
            {
              mostrarHistorial(nuevoUsuario->cedula, "Conversaciones.txt");
            }
            else
            {
              system("clear");
              printf("La sesión debe estar activa!\n");
              sleep(1);
            }
            break;
          case 3:
            // TULIO DEBE IMPLEMENTAR LAS ESTADISTICAS AQUI, debe validar si  el nuevoUsuario->sesionActiva es true, obviamente jsjs
            break;
          case 4:
            system("clear");
            mensajeSalida("Cerrando sesión", "...");
            free(nuevoUsuario);
            nuevoUsuario = (usuario *)malloc(sizeof(usuario));
            break;
          default:
            break;
          }
        } while (op != 4);
      }
      else
      {
        system("clear");
        printf("Datos incorrectos\n");
        sleep(1);
      }
      break;
    case 3:
    char op[2];
      system("clear");
      printf("¿Tiene cuenta de administrador? Si/No\n");
      scanf("%10s", op);
      if (strcmp(op, "no") == 0 || strcmp(op, "No") == 0 || strcmp(op, "NO") == 0)
      {
        registrarUsuarioAdministrador();
      }else if(strcmp(op, "si") == 0 || strcmp(op, "Si") == 0 || strcmp(op, "SI") == 0){
      nuevoUsuario = iniciarSesionAdministrador();
      if (nuevoUsuario->sesionActiva && nuevoUsuario->esAdministrador)
      {
        mensajeSalida("Bienvenido."," ");
        accionesAdministrador();
      }
      else
      {
        system("clear");
        printf("Datos incorrectos\n");
        sleep(1);
      }
    }else{
      system("clear");
      printf("Ingrese una opción válida\n");
      sleep(1);
    }
      break;
    case 4:
      liberarL(&baseDatos);
      liberarP(asistente.mensaje);
      liberarP(asistente.respuestaIA);
      liberarP(asistente.pendientes);
      system("clear");
      mensajeSalida("Saliendo", "...");
      system("clear");
      break;

    default:
      break;
    }
  } while (continuar != 4);
  return 0;
}
