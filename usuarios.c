#include "usuarios.h"

Lista_usuarios* agregarUsuario(Lista_usuarios* lista, Usuario nuevoUsuario) {
    Lista_usuarios* nuevoNodo = (Lista_usuarios*) malloc(sizeof(Lista_usuarios));
    nuevoNodo->datos_usuario = nuevoUsuario;
    nuevoNodo->sig = lista;
    return nuevoNodo;
}

void modificarUsuario(Lista_usuarios* usuario, char* nuevoNombre, char* nuevoApellido, int nuevaEdad, char* nuevoTelefono, char* nuevaDireccion, char* nuevoCP) {
    strcpy(usuario->datos_usuario.nombre, nuevoNombre);
    strcpy(usuario->datos_usuario.apellido, nuevoApellido);
    usuario->datos_usuario.edad = nuevaEdad;
    strcpy(usuario->datos_usuario.telefono, nuevoTelefono);
    strcpy(usuario->datos_usuario.direccion, nuevaDireccion);
    strcpy(usuario->datos_usuario.cp, nuevoCP);
}

Lista_usuarios* eliminarUsuarioPorID(Lista_usuarios* lista, int ID) {
    Lista_usuarios *actual = lista, *anterior = NULL;
    while (actual != NULL && actual->datos_usuario.ID_usuario != ID) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == NULL) {
        return lista;
    }
    if (anterior == NULL) {
        lista = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    free(actual);
    return lista;
}

Lista_usuarios* buscarUsuarioPorID(Lista_usuarios* lista, int ID) {
    Lista_usuarios* actual = lista;
    while (actual != NULL) {
        if (actual->datos_usuario.ID_usuario == ID) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

void mostrarUsuario(Usuario usuario) {
    printf("ID Usuario: %d\n", usuario.ID_usuario);
    printf("Nombre: %s\n", usuario.nombre);
    printf("Apellido: %s\n", usuario.apellido);
    printf("Edad: %d\n", usuario.edad);
    printf("Telefono: %s\n", usuario.telefono);
    printf("Direccion: %s\n", usuario.direccion);
    printf("CP: %s\n", usuario.cp);
}

Usuario crearUsuario(int ID_usuario, char* nombre, char* apellido, int edad, char* telefono, char* direccion, char* cp) {
    Usuario nuevoUsuario;
    nuevoUsuario.ID_usuario = ID_usuario;
    strcpy(nuevoUsuario.nombre, nombre);
    strcpy(nuevoUsuario.apellido, apellido);
    nuevoUsuario.edad = edad;
    strcpy(nuevoUsuario.telefono, telefono);
    strcpy(nuevoUsuario.direccion, direccion);
    strcpy(nuevoUsuario.cp, cp);
    return nuevoUsuario;
}
