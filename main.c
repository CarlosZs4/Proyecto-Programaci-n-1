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
  
  bool sesionEstaActiva = false;
  int op;
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
    case 2:
    break;
    case 3:
    if (sesionEstaActiva)
    {
      /* code */
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
  return opcion;
}