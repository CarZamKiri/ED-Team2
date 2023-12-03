#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario{
    int ID_usuario;
    char nombre[50];
    char apellido[50];
    int edad;
    char telefono[20];
    char direccion[100];
    char cp[10];
} Usuario;

typedef struct lista_usuarios{
    Usuario datos_usuario;
    struct lista_usuarios *sig;
} Lista_usuarios;

Lista_usuarios* agregarUsuario(Lista_usuarios* lista, Usuario nuevoUsuario);
void modificarUsuario(Lista_usuarios* usuario, char* nuevoNombre, char* nuevoApellido, int nuevaEdad, char* nuevoTelefono, char* nuevaDireccion, char* nuevoCP);
Lista_usuarios* eliminarUsuarioPorID(Lista_usuarios* lista, int ID);
Lista_usuarios* buscarUsuarioPorID(Lista_usuarios* lista, int ID);
void mostrarUsuario(Usuario usuario);
Usuario crearUsuario(int ID_usuario, char* nombre, char* apellido, int edad, char* telefono, char* direccion, char* cp);

#endif
