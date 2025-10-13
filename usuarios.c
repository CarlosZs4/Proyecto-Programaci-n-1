#include "usuarios.h"
#include "AsistenteIA.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
void registrarUsuario()
{
    FILE *usuarios = fopen("Usuarios.txt", "a+");
    char *nombre = (char *)malloc(100 * sizeof(char)), *apellido = (char *)malloc(100 * sizeof(char));
    long int cedula;
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    if (nuevoUsuario == NULL)
    {
        printf("Error: No se pudo asignar memoria.\n");
        free(nuevoUsuario);
        free(nombre);
        free(apellido);
        fclose(usuarios);
        return;
    }
    system("clear");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);

    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);

    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    nuevoUsuario->esAdministrador = false;
    int i = 0;
    bool usuarioValido = true;
    while (nuevoUsuario->nombre[i] != '\0' && usuarioValido)
    {
        if (!isalpha(nuevoUsuario->nombre[i]))
        {
            usuarioValido = false;
        }
        i++;
    }

    if (usuarioValido)
    {
        i = 0;
        while (nuevoUsuario->apellido[i] != '\0' && usuarioValido)
        {
            if (!isalpha(nuevoUsuario->apellido[i]))
            {
                usuarioValido = false;
            }
            i++;
        }
    }
    bool existeUsuario = false;
    if (usuarioValido)
    {
        rewind(usuarios);
        while (fscanf(usuarios, "%ld %s %s", &cedula, nombre, apellido) == 3 && !existeUsuario)
        {
            if (cedula == nuevoUsuario->cedula && strcmp(nombre, nuevoUsuario->nombre) == 0 && strcmp(apellido, nuevoUsuario->apellido) == 0)
            {
                printf("El usuario ya está registrado.\n");
                sleep(1);
                existeUsuario = true;
                return;
            }
        }
    }

    if (usuarioValido && !existeUsuario)
    {
        fprintf(usuarios, "\n%ld %s %s", nuevoUsuario->cedula, nuevoUsuario->nombre, nuevoUsuario->apellido);
        printf("Usuario registrado con éxito!.\n");
        sleep(1);
    }
    else
    {
        printf("Error: El nombre o apellido contienen caracteres no válidos.\n");
        sleep(1);
    }

    free(nuevoUsuario);
    free(nombre);
    free(apellido);
    fclose(usuarios);
}
void registrarUsuarioAdministrador()
{
    FILE *administradores = fopen("Administradores.txt", "a+");
    char *nombre = (char *)malloc(100 * sizeof(char)), *apellido = (char *)malloc(100 * sizeof(char));
    long int cedula;
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    if (nuevoUsuario == NULL)
    {
        printf("Error: No se pudo asignar memoria.\n");
        free(nuevoUsuario);
        free(nombre);
        free(apellido);
        fclose(administradores);
        return;
    }
    system("clear");
    printf("\tCrear Usuario Administrador\n");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);

    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);

    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    int i = 0;
    bool usuarioValido = true;
    while (nuevoUsuario->nombre[i] != '\0' && usuarioValido)
    {
        if (!isalpha(nuevoUsuario->nombre[i]))
        {
            usuarioValido = false;
        }
        i++;
    }

    if (usuarioValido)
    {
        i = 0;
        while (nuevoUsuario->apellido[i] != '\0' && usuarioValido)
        {
            if (!isalpha(nuevoUsuario->apellido[i]))
            {
                usuarioValido = false;
            }
            i++;
        }
    }
    bool existeUsuario = false;
    if (usuarioValido)
    {
        rewind(administradores);
        while (fscanf(administradores, "%ld %s %s", &cedula, nombre, apellido) == 3 && !existeUsuario)
        {
            if (cedula == nuevoUsuario->cedula && strcmp(nombre, nuevoUsuario->nombre) == 0 && strcmp(apellido, nuevoUsuario->apellido) == 0)
            {
                printf("El usuario ya está registrado.\n");
                sleep(1);
                existeUsuario = true;
                return;
            }
        }
    }

    if (usuarioValido && !existeUsuario)
    {
        fprintf(administradores, "%ld %s %s\n", nuevoUsuario->cedula, nuevoUsuario->nombre, nuevoUsuario->apellido);
        printf("Usuario registrado con éxito!.\n");
        sleep(1);
    }
    else
    {
        printf("Error: El nombre o apellido contienen caracteres no válidos.\n");
        sleep(1);
    }

    free(nuevoUsuario);
    free(nombre);
    free(apellido);
    fclose(administradores);
}
usuario *iniciarSesion()
{
    FILE *listaUsuarios = fopen("Usuarios.txt", "r");
    if (!listaUsuarios)
    {
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    system("clear");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);
    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);
    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->sesionActiva = false;
    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    nuevoUsuario->esAdministrador = false;
    long int cedula;
    char nombre[100], apellido[100];

    while (fscanf(listaUsuarios, "%ld %s %s", &cedula, nombre, apellido) == 3 && !nuevoUsuario->sesionActiva)
    {
        // Verificar si TODOS los datos coinciden en la MISMA línea
        if (nuevoUsuario->cedula == cedula &&
            strcmp(nombre, nuevoUsuario->nombre) == 0 &&
            strcmp(apellido, nuevoUsuario->apellido) == 0)
        {

            nuevoUsuario->sesionActiva = true;
        }
    }

    fclose(listaUsuarios);
    return nuevoUsuario;
}
usuario *iniciarSesionAdministrador()
{
    FILE *administradores = fopen("Administradores.txt", "r");
    if (!administradores)
    {
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    usuario *nuevoUsuario = (usuario *)malloc(sizeof(usuario));
    system("clear");
    printf("\tInicia sesión como administrador\n");
    printf("Ingrese el nombre: ");
    scanf("%99s", nuevoUsuario->nombre);
    printf("Ingrese el apellido: ");
    scanf("%99s", nuevoUsuario->apellido);
    printf("Ingrese la cedula: ");
    scanf("%ld", &nuevoUsuario->cedula);

    nuevoUsuario->sesionActiva = false;
    nuevoUsuario->cantidadConsultas = 0;
    nuevoUsuario->cantidadConsultasSinRespuesta = 0;
    nuevoUsuario->esAdministrador = true;
    long int cedula;
    char nombre[100], apellido[100];

    while (fscanf(administradores, "%ld %s %s", &cedula, nombre, apellido) == 3 && !nuevoUsuario->sesionActiva)
    {
        // Verificar si TODOS los datos coinciden en la MISMA línea
        if (nuevoUsuario->cedula == cedula &&
            strcmp(nombre, nuevoUsuario->nombre) == 0 &&
            strcmp(apellido, nuevoUsuario->apellido) == 0)
        {

            nuevoUsuario->sesionActiva = true;
        }
    }

    fclose(administradores);
    return nuevoUsuario;
}
int menuAdministrador()
{
    char *menu[] = {"1. Ver cola de pendientes.", "2. Añadir una pregunta al asistente.", "3. Eliminar una pregunta", "4. Cerrar sesión."};
    char *recuadro = "*--------------------------------------------------*\n";
    int op;
    system("clear");
    printf("%s", recuadro);
    printf("\t\tMenu Administrador\n");
    for (int i = 0; i < 4; i++)
    {
        printf("\t%s\n", menu[i]);
    }
    printf("%s", recuadro);
    printf("Elija una opción: ");
    scanf("%d", &op);
    return op;
}
void accionesAdministrador()
{
    int continuar;
   
    do
    {
        continuar = menuAdministrador();
        switch (continuar)
        {
        case 1:
            mostrarPendientes("Pendientes.txt");
            printf("\nPresione Enter para continuar...");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            getchar();
            break;
        case 2:
        Lista *baseDatos = (Lista *)malloc(sizeof(Lista));
        crearL(baseDatos);
            actualizarBaseDatos(baseDatos);
            guardarBaseConocimiento(baseDatos, "BaseConocimiento.txt");
            free(baseDatos);
            break;
        case 3:
            int n, a;
            Lista *datos = (Lista *)malloc(sizeof(Lista));
            crearL(datos);
            cargarBaseConocimiento(datos, "BaseConocimiento.txt");
            imprimirL(datos, mostrarString);
            printf("Ingrese el número de la pregunta a eliminar: ");
            scanf("%d", &n);
            while((a = getchar()) != '\n' && a != EOF);
            eliminarL(datos, n);
            printf("Pregunta y respuesta eliminada correctamente!\n\npresione una tecla para continuar...");
            while((a = getchar()) != '\n' && a != EOF);
            actualizarBaseConocimiento(datos, "BaseConocimiento.txt");
            free(datos);
            break;
        case 4:
            system("clear");
            mensajeSalida("Cerrando sesión", "...");
            break;
        default:
            system("clear");
            printf("ingrese una opción válida!\n");
            sleep(1);
            break;
        }
    } while (continuar != 4);
}
void mostrarString(void *elemento)
{
    ConocimientoIA *conocimiento = (ConocimientoIA *)elemento;
    if (conocimiento != NULL)
    {
        if (conocimiento->preguntas != NULL)
        {
            printf("%s", conocimiento->preguntas);
        }
        if (conocimiento->respuesta != NULL && strlen(conocimiento->respuesta) > 0)
        {
            printf(" %s", conocimiento->respuesta);
        }
        printf("\n");
    }
    else
    {
        printf("Elemento nulo\n");
    }
}
void cargarEstadistica(estadisticasG *estadisticas,const char *nombreArchivo){
    FILE *arch=fopen(nombreArchivo,"r");
    char auxnombre[100],auxapellido[100];
    estadisticas->nombre=NULL;
    estadisticas->apellido=NULL;
    if(arch==NULL){
        estadisticas->consultasSinRes=0;
        estadisticas->consultasTotales=0;
        estadisticas->cedula=0;
        estadisticas->usuarioMasConsultas=0;
        return;
    }
    fscanf(arch,"Totales de consultas: %d",&estadisticas->consultasTotales);
    fscanf(arch,"Consultas sin responder: %d",&estadisticas->consultasSinRes);
    fscanf(arch,"Usuario con mas consultas: %d %99s %99s (consultas: %d)",&estadisticas->cedula,auxnombre,auxapellido,&estadisticas->usuarioMasConsultas);

    estadisticas->nombre=strdup(auxnombre);
    estadisticas->apellido=strdup(auxapellido);
    if (!estadisticas->nombre || !estadisticas->apellido) {
        fprintf(stderr, "Error al asignar memoria para nombre/apellido.\n");
    }
    fclose(arch);
}
void actualizarEstadisticas(usuario Actual,estadisticasG *estadisticas){
    estadisticas->consultasSinRes=Actual.cantidadConsultasSinRespuesta+estadisticas->consultasSinRes;
    estadisticas->consultasTotales=Actual.cantidadConsultas+estadisticas->consultasTotales;
    if(estadisticas->usuarioMasConsultas<Actual.cantidadConsultas){
         if (estadisticas->nombre != NULL) {
            free(estadisticas->nombre);
        }
        if (estadisticas->apellido != NULL) {
            free(estadisticas->apellido);
        }
        estadisticas->cedula=Actual.cedula;
        estadisticas->usuarioMasConsultas=Actual.cantidadConsultas;
        estadisticas->nombre=strdup(Actual.nombre);
        estadisticas->apellido=strdup(Actual.apellido);
        if (!estadisticas->nombre || !estadisticas->apellido) {
            fprintf(stderr, "Error al asignar memoria para nombre/apellido.\n");
        }
    }
}
void verEstadisticas(usuario Actual,estadisticasG estadisticasGlobales){
    
    printf("\n=== ESTADISTICAS USUARIO ACTUAL ===\n");

    printf("Interacciones Totales en esta Sesión:\n");
    printf("Nombre: %s\n",Actual.nombre);
    printf("Apellido: %s\n",Actual.apellido);
    printf("Consultas: %d\n",Actual.cantidadConsultas);
    printf("Consultas sin responder: %d",Actual.cantidadConsultasSinRespuesta);

    printf("\n===========================\n");
    printf("=== ESTADISTICAS GLOBALES ===\n");
    printf("Consultas Totales: %d\n",estadisticasGlobales.consultasTotales);
    printf("Consultas sin responder: %d\n",estadisticasGlobales.consultasSinRes);
    if(estadisticasGlobales.nombre!=NULL&&estadisticasGlobales.apellido!=NULL){
        printf("Usuario con mas consulta: %d %s %s (Consultas: %d)",estadisticasGlobales.cedula,estadisticasGlobales.nombre,estadisticasGlobales.apellido,estadisticasGlobales.usuarioMasConsultas);
    }
    
    printf("\n===========================\n");
    printf("\nPresione cualquier tecla para continuar...");
    int c;
    while ((c = getchar())!= '\n' && c != EOF);
    system("clear");
}
void guardarEstadistica(estadisticasG estadisticas,const char *nombreArchivo){
    FILE *arch=fopen(nombreArchivo,"w");
    if (arch == NULL) {
        perror("Error al abrir el archivo de estadísticas para escribir");
        return;
    }
    fprintf(arch,"Totales de consultas: %d\n",estadisticas.consultasTotales);
    fprintf(arch,"Consultas sin responder: %d\n",estadisticas.consultasSinRes);
    if(estadisticas.nombre!=NULL&&estadisticas.apellido!=NULL){
        
        fprintf(arch,"Usuario con mas consultas: %d %s %s (consultas: %d)",estadisticas.cedula,estadisticas.nombre,estadisticas.apellido,estadisticas.usuarioMasConsultas);
    }
    
    fclose(arch);
}