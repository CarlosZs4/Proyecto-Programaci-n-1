#include "usuarios.h"
#include "AsistenteIA.h"
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
    char *menu[] = {"1. Ver cola de pendientes.", "2. Actualizar base de conocimiento.", "3. Eliminar una pregunta", "4. Cerrar sesión."};
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