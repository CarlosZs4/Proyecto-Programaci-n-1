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
int menu();

int main()
{
  AsistenteIA asistente;
  Lista baseDatos;
  usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
  int op;
  crearL(&baseDatos);
  cargarBaseConocimiento(&baseDatos, "BaseConocimiento.txt");
  asistente.mensaje = (Pila *)malloc(sizeof(Pila));
  asistente.respuestaIA = (Pila *)malloc(sizeof(Pila));
  asistente.pendientes = (Pila *)malloc(sizeof(Pila));
  if (asistente.mensaje == NULL || asistente.respuestaIA == NULL || asistente.pendientes == NULL) {
      fprintf(stderr, "Error: No se pudo asignar memoria para las pilas.\n");
 
      if (asistente.mensaje) free(asistente.mensaje);
      if (asistente.respuestaIA) free(asistente.respuestaIA);
      exit(1);
  }
  crearP(asistente.mensaje);
  crearP(asistente.respuestaIA);
  crearP(asistente.pendientes);
  do
  {
    op = menu();
    while(op < 1 || op >6){
    
      system("clear");
      printf("ingrese una opción válida!\n");
      sleep(1);
      op = menu();
    };
    switch (op)
    {
    case 1:
    registrarUsuario();
    break;
    case 2:
    nuevoUsuario = iniciarSesion();
    if (nuevoUsuario->sesionActiva)
    {
      system("clear");
      printf("Bienvenido/a %s, ya puedes usar el asistente!\n",nuevoUsuario->nombre);
      sleep(1);
    }else{
      system("clear");
      printf("Datos incorrectos\n");
      sleep(1);
    }
    
    break;
    case 3:
    if (nuevoUsuario->sesionActiva || nuevoUsuario == NULL)
    {
      int continuar_conversacion = 1;
      char resp[10];
      system("clear");
      printf("--- Asistente IA Iniciado ---\n");
      printf("Escribe 'salir' para terminar la conversación.\n\n");
      
      while (continuar_conversacion) {
          continuar_conversacion = conversacion(&asistente, &baseDatos,nuevoUsuario);
      }
      printf("\n--- Conversación Finalizada ---\n");
      printf("Desea Deshacer su ultima peticion?\nNo\nSi\n");
      printf("Elige una opcion: ");
      scanf("%10s",resp);
      if(strcmp(resp, "si") == 0 || strcmp(resp, "Si") == 0){
          eliminarUltimaPeticion(&asistente);
      }
      system("clear");
      printf("¡Hasta pronto!\n");
      guardarHistorial(&asistente,nuevoUsuario,"Conversaciones.txt");
      sleep(1);
    }else
    {
      system("clear");
      printf("La sesión debe estar activa!\n");
      sleep(1);
    }
    
    break;
    case 4:
    if (nuevoUsuario->sesionActiva){
        mostrarHistorial(nuevoUsuario->cedula,"Conversaciones.txt");
    }
    else{
      system("clear");
      printf("La sesión debe estar activa!\n");
      sleep(1);
    }
    break;
    case 5:
    break;
    break;
    case 6:
    //preferiblemente esta respuesta debe ser del asistente
    liberarL(&baseDatos);
    liberarP(asistente.mensaje);
    liberarP(asistente.respuestaIA);
    liberarP(asistente.pendientes);
    system("clear");
    printf("Saliendo.\n");
    usleep(700000);
    system("clear");
    printf("Saliendo..\n");
    usleep(700000);
    system("clear");
    printf("Saliendo...\n");
    usleep(700000);

    break;
    default:
      break;
    }
  } while (op != 6);
  return 0;
}
int menu()
{
  int opcion;
  char *menu[] = {"1. Registrar usuario", "2. Iniciar sesión", "3. Realizar consulta",
     "4. Ver historial de conversaciones", "5. Ver estadísticas", "6. Salir"};
     printf("\t Menu\n");
  for (int i = 0; i < 6; i++)
  {
    printf("%s\n", menu[i]);
  }
  printf("Elige una opción: ");
  scanf("%d", &opcion);
  int c;

    while ((c = getchar()) != '\n' && c != EOF);
  return opcion;
  
}