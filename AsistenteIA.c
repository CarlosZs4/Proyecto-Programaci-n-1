#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"

AsistenteIA registrarse(){
    AsistenteIA usuario;
    FILE *arch;
    printf("\n---------------------------\n");
    printf("REGISTRO");
    printf("\n---------------------------\n");
    printf("*Ingrese su nombre:\n");
    scanf("%s",usuario.nombre);
    printf("\n*Ingrese su apellido:\n");
    scanf("%s",usuario.apellido);
    printf("\n*Ingrese su cedula:\n");
    scanf("%d",&usuario.cedula);
    printf("\n------------------------------\n");
    arch = fopen("Usuarios.txt", "r");
    if (arch != NULL) {
        int cedulaLeida;
        // "%*s" le indica a fscanf que lea y descarte las cadenas (nombre y apellido)
        while (fscanf(arch, "%d %*s %*s\n", &cedulaLeida) != EOF) {
            if (cedulaLeida == usuario.cedula) {
                printf("\nError: La cedula ya se encuentra registrada.\n");
                fclose(arch);
                // En una aplicación completa, podrías devolver un código de estado
                exit(1);
            }
        }
        fclose(arch);
    }
    arch = fopen("Usuarios.txt", "a");
    if(arch==NULL){
        perror("Error al abrir el archivo");
         exit(1);
    }
    
    usuario.mensaje = (Pila *)malloc(sizeof(Pila));
    usuario.respuestaIA = (Pila *)malloc(sizeof(Pila));

    if (usuario.mensaje == NULL || usuario.respuestaIA == NULL) {
        printf("Error: No se pudo asignar memoria para las pilas.\n");
        free(usuario.mensaje);
        free(usuario.respuestaIA);
        exit(1);
    }
    
    crearP(usuario.mensaje);
    crearP(usuario.respuestaIA);

    fprintf(arch, "%d %s %s\n", usuario.cedula, usuario.nombre, usuario.apellido);
    printf("Usuario registrado exitosamente!\n");
    fclose(arch);
    
    return usuario;
}
void conversacion(AsistenteIA *usuario) {
    char temp_mensaje[1024];
    char linea[1024]; 
    char *respuesta_leida;
    char *pregunta_leida;
    int coincidencia=0;

    printf("Escribe tu mensaje: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    
    if (fgets(temp_mensaje, sizeof(temp_mensaje), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return;
    }
    temp_mensaje[strcspn(temp_mensaje, "\n")] = '\0';

    char *mensaje = malloc(strlen(temp_mensaje) + 1);
    if (mensaje == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    strcpy(mensaje, temp_mensaje);

    FILE *archivo = fopen("base_datos.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de la base de datos");
        return;
    }
    insertarP(usuario->mensaje, mensaje);
    
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Elimina el salto de línea al final de la línea leída por fgets
        linea[strcspn(linea, "\n")] = 0;
        
        // Busca el separador "? " o "? "
        pregunta_leida = strtok(linea, "?");
        if (pregunta_leida == NULL) {
            continue; // Si no hay separador, pasa a la siguiente línea
        }

        respuesta_leida = strtok(NULL, "");
        if (respuesta_leida == NULL) {
            continue; // Si no hay respuesta, pasa a la siguiente línea
        }

        // Elimina espacios en blanco al inicio de la respuesta
        while (*respuesta_leida == ' ') {
            respuesta_leida++;
        }

        // Compara la pregunta del usuario con la pregunta leída del archivo
        if (strcmp(mensaje, pregunta_leida) == 0) {
            printf("Respuesta: %s\n", respuesta_leida);
            coincidencia = 1; // Establece la bandera en 1 si se encuentra una coincidencia
            break; 
            
        }
    }

    printf("Lo siento, no tengo una respuesta para esa pregunta.\n");
     fclose(archivo);
}

