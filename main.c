/*librerias estandar de C*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h> 
/*-------------------------*/
/*librerias del proyecto*/
#include "AsistenteIA.h"
/*-------------------------*/
int menu();

int main()
{
  usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
  AsistenteIA usuario;
  Lista baseDatos;
  bool sesionEstaActiva = false;
  int op;
  crearL(&baseDatos);
  cargarBaseConocimiento(&baseDatos, "BaseConocimiento.txt");
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
    break;
    case 2:
    system("clear");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);
    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);
    printf("Ingrese la cédula: ");
    scanf("%ld", &nuevoUsuario->cedula);
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    sesionEstaActiva = iniciarSesion(nuevoUsuario);
    if (sesionEstaActiva)
    {
      system("clear");
      printf("Bienvenido/a, ya puedes usar el asistente!\n");
      sleep(1);
    }else{
      system("clear");
      printf("Datos incorrectos\n");
      sleep(1);
    }
    
    break;
    case 3:
    sesionEstaActiva=true;
    if (sesionEstaActiva)
    {
      int continuar_conversacion = 1;
      system("clear");
      printf("Probando...\n");
      usuario.mensaje = (Pila *)malloc(sizeof(Pila));
      usuario.respuestaIA = (Pila *)malloc(sizeof(Pila));
      if (usuario.mensaje == NULL || usuario.respuestaIA == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para las pilas.\n");
 
        if (usuario.mensaje) free(usuario.mensaje);
        if (usuario.respuestaIA) free(usuario.respuestaIA);
        exit(1);
        }
      crearP(usuario.mensaje);
      crearP(usuario.respuestaIA);
      printf("--- Asistente IA Iniciado ---\n");
      printf("Escribe 'salir' para terminar la conversación.\n\n");
      
      while (continuar_conversacion) {
          continuar_conversacion = conversacion(&usuario, &baseDatos);
      }
      printf("\n--- Conversación Finalizada ---\n");
      
      free(usuario.mensaje);
      free(usuario.respuestaIA);
      sleep(1);
    }else
    {
      system("clear");
      printf("La sesión debe estar activa!\n");
      sleep(1);
    }
    
    break;
    case 4:
    break;
    case 5:
    break;
    case 6:
    //preferiblemente esta respuesta debe ser del asistente
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
  char *menu[] = {"1. Registrarse", "2. Iniciar sesión", "3. Realizar consulta",
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