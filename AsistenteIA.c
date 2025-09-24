#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "pila.h"
#include "AsistenteIA.h"
AsistenteIA registrarse(){
    AsistenteIA usuario;
    crearP(usuario.mensaje);
    crearP(usuario.respuestaIA);

    printf("\n---------------------------\n");
    printf("*Ingrese su nombre:\n");
    scanf("%s",usuario.nombre);
    printf("\n*Ingrese su apellido:\n");
    scanf("%s",usuario.apellido);
    printf("\n*Ingrese su cedula:\n");
    scanf("%d",usuario.cedula);

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
    
    return usuario;

}