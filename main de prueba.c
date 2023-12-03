#include "usuarios.h"

int main() {
    // Crear una lista de usuarios vacía.
    Lista_usuarios* listaUsuarios = NULL;

    // Crear un usuario.
    Usuario nuevoUsuario = crearUsuario(1, "Juan", "Pérez", 30, "555-1234", "Calle Ejemplo 123", "CP1234");

    // Agregar el usuario a la lista.
    listaUsuarios = agregarUsuario(listaUsuarios, nuevoUsuario);

    // Mostrar el usuario agregado.
    printf("Usuario agregado:\n");
    mostrarUsuario(nuevoUsuario);

    // Buscar y mostrar el usuario por ID.
    Lista_usuarios* usuarioEncontrado = buscarUsuarioPorID(listaUsuarios, 1);
    if (usuarioEncontrado != NULL) {
        printf("\nUsuario encontrado:\n");
        mostrarUsuario(usuarioEncontrado->datos_usuario);
    } else {
        printf("\nUsuario no encontrado.\n");
    }

    // Eliminar el usuario.
    listaUsuarios = eliminarUsuarioPorID(listaUsuarios, 1);

    // Intentar encontrar el usuario después de eliminarlo.
    usuarioEncontrado = buscarUsuarioPorID(listaUsuarios, 1);
    if (usuarioEncontrado != NULL) {
        printf("\nUsuario aún en la lista:\n");
        mostrarUsuario(usuarioEncontrado->datos_usuario);
    } else {
        printf("\nUsuario eliminado correctamente.\n");
    }

    return 0;
}
