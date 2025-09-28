#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"

int son_iguales_string(void *a,void *b){
    char* str1 = (char*)a;
    char* str2 = (char*)b;
    return(strcmp(str1, str2));
}
int son_iguales_preguntas(void *parConocimiento, void *preguntaBusqueda) {
    ConocimientoIA* par = (ConocimientoIA*)parConocimiento;
    char* pregunta_usuario_sin_q = (char*)preguntaBusqueda; 

    if (pregunta_usuario_sin_q == NULL || *pregunta_usuario_sin_q == '\0') {
        return 0; // Falso (No son iguales)
    }
    size_t len_db_q = strlen(par->preguntas);
    if (len_db_q > 0 && par->preguntas[len_db_q - 1] == '?') {
        if (strlen(pregunta_usuario_sin_q) == len_db_q - 1) { 
            return (strncmp(pregunta_usuario_sin_q, par->preguntas, len_db_q - 1) == 0);
        }
        return 0; // Falso (No son iguales)
    }

    return (strcmp(par->preguntas, pregunta_usuario_sin_q) == 0);
}
void imprimir_baseDatos(void *a){
    ConocimientoIA *Pardatos=(ConocimientoIA*)a;
    printf("%s  .",Pardatos->preguntas);
    printf("%s  .",Pardatos->respuesta);
}
void cargarBaseConocimiento(Lista *baseDatos,const char *nombreArchivo){
    char linea[1024]; 
    char *respuesta_leida;
    char *pregunta_leida;
    
    FILE *arch=fopen(nombreArchivo,"r");
    if (arch == NULL) {
        perror("Error al abrir el archivo de la base de datos");
        return;
    }
    while (fgets(linea, sizeof(linea), arch) != NULL) {
        linea[strcspn(linea, "\n")] = 0;
    
        pregunta_leida = strtok(linea, "?");
        if (pregunta_leida == NULL) {
            continue; 
        }

        respuesta_leida = strtok(NULL, "");
        if (respuesta_leida == NULL) {
            continue; 
        }

        while (*respuesta_leida == ' ') {
            respuesta_leida++;
        }
        ConocimientoIA *parDatos=(ConocimientoIA *)malloc(sizeof(ConocimientoIA));
        size_t len_pregunta = strlen(pregunta_leida);
        parDatos->preguntas = (char*)malloc(len_pregunta + 2);
        if(parDatos==NULL){
            printf("Error: No se pudo asignar memoria a la base de datos.\n");
            exit(1);
        }
        strcpy(parDatos->preguntas, pregunta_leida);
        parDatos->preguntas[len_pregunta] = '?'; // Añade el delimitador
        parDatos->preguntas[len_pregunta + 1] = '\0';

        parDatos->respuesta=strdup(respuesta_leida);
        if (parDatos->respuesta == NULL) {
            fprintf(stderr, "Error: Falló strdup para la respuesta.\n");
            free(parDatos->preguntas);
            free(parDatos);
            fclose(arch);
            exit(1);
        }
        insertarL(baseDatos,1,parDatos);
    }
    fclose(arch);
}
int conversacion(AsistenteIA *asistente,Lista *baseDatos,usuario *Datousuario) {
    char temp_mensaje[1024];
    char *mensaje=NULL;
    char *auxbusqueda=NULL;
    int pos=-1;
    printf("\nUsuario: ");
    
    if (fgets(temp_mensaje, sizeof(temp_mensaje), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return 1;
    }
    temp_mensaje[strcspn(temp_mensaje, "\n")] = '\0';

    char comando_temp[1024];
    size_t i;
    for (i = 0; temp_mensaje[i] && i < 1023; i++) {
        comando_temp[i] = tolower((unsigned char)temp_mensaje[i]);
    }

    comando_temp[i] = '\0';
    
    if (strcmp(comando_temp, "salir") == 0 || strcmp(comando_temp, "cerrar") == 0) {
        return 0; // Indica al main que debe salir del bucle
    }

    mensaje=strdup(temp_mensaje);
     if (!mensaje) { 
        fprintf(stderr, "Error: Falló strdup para el historial.\n"); 
        return 1; 
    }

    auxbusqueda=strdup(temp_mensaje);
     if (!auxbusqueda) {
        fprintf(stderr, "Error: Falló strdup para la búsqueda.\n");
        free(mensaje); // Limpieza
        return 1; 
    }
    size_t len = strlen(auxbusqueda);
    if (len > 0 && auxbusqueda[len - 1] == '?') {
        auxbusqueda[len - 1] = '\0';
    }   
    pos=busquedaL(baseDatos,auxbusqueda,son_iguales_preguntas);
    if(pos!=-1){
        ConocimientoIA *parDatos = consultarL(baseDatos, pos);
        printf("Respuesta: %s",parDatos->respuesta);
        insertarP(asistente->mensaje,mensaje);
        insertarP(asistente->respuestaIA,parDatos->respuesta);
        Datousuario->cantidadConsultas++;
    }
    else{
        printf("Lo siento no tenemos esa respuesta");
        Datousuario->cantidadConsultasSinRespuesta++;
        insertarP(asistente->pendientes,mensaje);
    }
    free(auxbusqueda);
    return 1; 
}