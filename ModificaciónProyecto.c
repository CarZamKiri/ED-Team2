#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura con los datos del usuario.
typedef struct usuario {
    int ID_usuario;
    char nombre[50];
    char apellido[50];
    int edad;
    char telefono[20];
    char direccion[100];
    char cp[10];
} Usuario;

// Estructura para la lista de usuarios.
typedef struct lista_usuarios {
    Usuario datos_usuario;
    struct lista_usuarios *sig;
} Lista_usuarios;

// Estructura con los datos de los libros.
typedef struct libros {
    char ID_libro[5];
    char titulo[50];
    char autor[40];
    char categoria[20];
    char editorial[30];
    char idioma[10];
    int paginas;
    char descripcion[200];
    char fechalanzamiento[25];
} Libros;

// Estructura para la lista de libros.
typedef struct lista_libros {
    Libros datos_libro;
    struct lista_libros* sig;
} Lista_libros;
//Estructura para libros prestados
typedef struct lista_libros_prestados {
    Libros datos_libro;
    struct lista_libros_prestados* sig;
} Lista_libros_prestados;


// Estructura con los datos del préstamo.
typedef struct prestamo {
    int ID_prestamo; 
    int ID_usuario;   
    char ID_libro[5]; 
    time_t fecha_pedido;  // Uso de time_t
    time_t fecha_devolver;  // Uso de time_t
} Prestamo;

// Estructura con los datos de la devolución.
typedef struct devolucion {
    char ID_libro[5];
    int ID_usuario;
    time_t fecha_devolvio;  // Uso de time_t
    char condicion[50];
} Devolucion;

// Estructura con los datos de las multas.
typedef struct multas {
    int ID_usuario;
    char ID_libro[5];
    int monto;
    time_t fecha_devolver;  // Uso de time_t
    char razon[50];
    char metododepago[20];
} Multas;

// Estructura para los recordatorios.
typedef struct recordatorio {
    int ID_prestamo;
    char ID_libro[5];
    time_t fecha_devolver;  // Uso de time_t
    char renovacion[10];
    int ID_usuario;
    char contacto[50];
} Recordatorio;


//Declaramos las funciones globales.
int menuprincipal();
int libreria();
int menusuarios();
int usuarios(Lista_usuarios **listaUsuarios);
void agregarUsuario(Lista_usuarios **listaUsuarios);
void eliminarUsuario(Lista_usuarios **listaUsuarios);
void buscarUsuario(Lista_usuarios *listaUsuarios);
void visualizarUsuarios(Lista_usuarios *listaUsuarios);
void visualizarUsuario(Usuario usuario);
void editarUsuario(Lista_usuarios **listaUsuarios);
int menulibros();
int libros();
int menutransaccion();
int transaccion();
int menuprestamos();
int prestamo();
int menudevolucion();
int devolucion();
int menumultas();
int multas();

//Declaramos el menu principal.
int menuprincipal(){
	int opcion = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t  BIBLIOTECA --EL JARDIN DE LAS LETRAS--  ");
	puts("\t------------------------------------------");
	puts("[1] Usuario.");
	puts("[2] Catalogo de libros.");
	puts("[3] Transaccion");
	puts("[4] Multas y recordatorios.");
	puts("[5] Notificaciones.");
	puts("[0] SALIR.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &opcion);
	return opcion;
}

//Función para manejar la gestión de la librería.
int libreria(Lista_usuarios **listaUsuarios) {
    int op = 0;
    do {
        op = menuprincipal();

        switch (op) {
            case 0:
                puts("Saliendo...");
                system("pause");
                break;
            case 1:
                // Llamamos a la función de gestión de usuarios y pasamos la lista de usuarios como parámetro.
                usuarios(listaUsuarios);
                break;
            case 2:
                libros();
                break;
            case 3:
                transaccion();
                break;
            case 4:
                multas();
                break;
            case 5:
                // Funcionalidad de notificaciones
                break;
            default:
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

//Creamos una funcion para el menu de usuarios.
int menusuarios(){
	int op = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t                USUARIO:                  ");
	puts("\t------------------------------------------");
	puts("[1] Nuevo usuario.");
	puts("[2] Eliminar usuario.");
	puts("[3] Buscar usuario.");
	puts("[4] Visualizar datos de los usuarios.");
	puts("[5] Editar datos del usuario.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: \n");
	scanf("%d", &op);
	return op;
}

//Función para manejar la gestoón de los usuarios
int usuarios(Lista_usuarios **listaUsuarios) {
    system("cls");
    int op = 0;
    do {
        op = menusuarios();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");
                break;
            case 1:
                agregarUsuario(listaUsuarios);
                break;
            case 2:
                eliminarUsuario(listaUsuarios);
                break;
            case 3:
                buscarUsuario(*listaUsuarios);
                break;
            case 4:
                visualizarUsuarios(*listaUsuarios);
                break;
            case 5:
                editarUsuario(listaUsuarios);
                break;
            default:
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

void agregarUsuario(Lista_usuarios **listaUsuarios) {
    system("cls");
    Lista_usuarios *nuevoUsuario = (Lista_usuarios *)malloc(sizeof(Lista_usuarios));

    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevoUsuario->datos_usuario.ID_usuario);
    getchar(); // Limpia el buffer del new line que queda después de scanf

    printf("Ingrese el nombre del usuario: ");
    fgets(nuevoUsuario->datos_usuario.nombre, 50, stdin);
    nuevoUsuario->datos_usuario.nombre[strcspn(nuevoUsuario->datos_usuario.nombre, "\n")] = 0; // Elimina el new line al final

    printf("Ingrese el apellido del usuario: ");
    fgets(nuevoUsuario->datos_usuario.apellido, 50, stdin);
    nuevoUsuario->datos_usuario.apellido[strcspn(nuevoUsuario->datos_usuario.apellido, "\n")] = 0;

    printf("Ingrese la edad del usuario: ");
    scanf("%d", &nuevoUsuario->datos_usuario.edad);
    getchar(); // Limpia el buffer del new line que queda después de scanf

    printf("Ingrese el teléfono del usuario: ");
    fgets(nuevoUsuario->datos_usuario.telefono, 20, stdin);
    nuevoUsuario->datos_usuario.telefono[strcspn(nuevoUsuario->datos_usuario.telefono, "\n")] = 0;

    printf("Ingrese la dirección del usuario: ");
    fgets(nuevoUsuario->datos_usuario.direccion, 100, stdin);
    nuevoUsuario->datos_usuario.direccion[strcspn(nuevoUsuario->datos_usuario.direccion, "\n")] = 0;

    printf("Ingrese el código postal del usuario: ");
    fgets(nuevoUsuario->datos_usuario.cp, 10, stdin);
    nuevoUsuario->datos_usuario.cp[strcspn(nuevoUsuario->datos_usuario.cp, "\n")] = 0;

    nuevoUsuario->sig = *listaUsuarios;
    *listaUsuarios = nuevoUsuario;

    printf("Usuario agregado con éxito.\n");
}

// Función para eliminar un usuario por ID.
void eliminarUsuario(Lista_usuarios **listaUsuarios) {
    system("cls");
    int idUsuario;
    printf("Ingrese el ID del usuario a eliminar: ");
    scanf("%d", &idUsuario);
    
    Lista_usuarios *actual = *listaUsuarios;
    Lista_usuarios *anterior = NULL;

    while (actual != NULL && actual->datos_usuario.ID_usuario != idUsuario) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual == NULL) {
        printf("Usuario no encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        *listaUsuarios = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }

    free(actual);
    printf("Usuario eliminado con éxito.\n");
    system("pause");
}

// Función para buscar un usuario por ID.
void buscarUsuario(Lista_usuarios *listaUsuarios) {
    system("cls");
    int idUsuario;
    printf("Ingrese el ID del usuario a buscar: ");
    scanf("%d", &idUsuario);

    while (listaUsuarios != NULL) {
        if (listaUsuarios->datos_usuario.ID_usuario == idUsuario) {
            printf("ID: %d\nNombre: %s %s\nEdad: %d\nTeléfono: %s\nDirección: %s\nCódigo Postal: %s\n",
                listaUsuarios->datos_usuario.ID_usuario,
                listaUsuarios->datos_usuario.nombre,
                listaUsuarios->datos_usuario.apellido,
                listaUsuarios->datos_usuario.edad,
                listaUsuarios->datos_usuario.telefono,
                listaUsuarios->datos_usuario.direccion,
                listaUsuarios->datos_usuario.cp);
            system("pause");
            return;
        }

        listaUsuarios = listaUsuarios->sig;
    }

    printf("Usuario no encontrado.\n");
    system("pause");
}

// Función para mostrar los datos de un usuario especifico
void visualizarUsuario(Usuario usuario) {
    system("cls");
    printf("ID: %d\n", usuario.ID_usuario);
    printf("Nombre: %s\n", usuario.nombre);
    printf("Apellido: %s\n", usuario.apellido);
    printf("Edad: %d\n", usuario.edad);
    printf("Teléfono: %s\n", usuario.telefono);
    printf("Dirección: %s\n", usuario.direccion);
    printf("Código Postal: %s\n", usuario.cp);
}

// Función para visualizar todos los usuarios.
void visualizarUsuarios(Lista_usuarios *listaUsuarios) {
    system("cls");
    while (listaUsuarios != NULL) {
        visualizarUsuario(listaUsuarios->datos_usuario);
        printf("\n");
        listaUsuarios = listaUsuarios->sig;
    }
    system("pause");
}

// Función para editar los datos de un usuario por ID.
void editarUsuario(Lista_usuarios **listaUsuarios) {
    system("cls");
    int idUsuario;
    printf("Ingrese el ID del usuario a editar: ");
    scanf("%d", &idUsuario);

    Lista_usuarios *actual = *listaUsuarios;

    while (actual != NULL) {
        if (actual->datos_usuario.ID_usuario == idUsuario) {

            // Imprimimos los datos actuales del usuario
            printf("Datos actuales del usuario:\n");
            visualizarUsuario(actual->datos_usuario);

            // Preguntamos al usuario si desea editar todos los datos o un dato específico
            int opcionEdicion;
            printf("Seleccione la opción de edición:\n");
            printf("[1] Todos los datos\n");
            printf("[2] Dato específico\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcionEdicion);

            // Limpiamos el búfer del teclado
            while (getchar() != '\n');

            if (opcionEdicion == 1) {
                // Edición de todos los datos
                printf("Ingrese el nuevo nombre: ");
                fgets(actual->datos_usuario.nombre, sizeof(actual->datos_usuario.nombre), stdin);
                actual->datos_usuario.nombre[strcspn(actual->datos_usuario.nombre, "\n")] = 0;  // Elimina el salto de línea al final

                printf("Ingrese el nuevo apellido: ");
                fgets(actual->datos_usuario.apellido, sizeof(actual->datos_usuario.apellido), stdin);
                actual->datos_usuario.apellido[strcspn(actual->datos_usuario.apellido, "\n")] = 0;  // Elimina el salto de línea al final

                printf("Ingrese la nueva edad: ");
                scanf("%d", &actual->datos_usuario.edad);

                printf("Ingrese el nuevo teléfono: ");
                fgets(actual->datos_usuario.telefono, sizeof(actual->datos_usuario.telefono), stdin);
                actual->datos_usuario.telefono[strcspn(actual->datos_usuario.telefono, "\n")] = 0;

                printf("Ingrese la nueva dirección: ");
                fgets(actual->datos_usuario.direccion, sizeof(actual->datos_usuario.direccion), stdin);
                actual->datos_usuario.direccion[strcspn(actual->datos_usuario.direccion, "\n")] = 0;

                printf("Ingrese el nuevo código postal: ");
                fgets(actual->datos_usuario.cp, sizeof(actual->datos_usuario.cp), stdin);
                actual->datos_usuario.cp[strcspn(actual->datos_usuario.cp, "\n")] = 0;
                
            } else if (opcionEdicion == 2) {
                int opcionCampo;
                printf("Seleccione el campo a editar:\n");
                printf("[1] Nombre\n");
                printf("[2] Apellido\n");
                printf("[3] Edad\n");
                printf("[4] Teléfono\n");
                printf("[5] Dirección\n");
                printf("[6] Código Postal\n");

                printf("Ingrese una opcion: ");
                scanf("%d", &opcionCampo);

                // Limpiamos el búfer del teclado
                while (getchar() != '\n');

                // Variable temporal para almacenar la nueva información
                char nuevaInfo[100];

                // Realizamos la edición según la opción seleccionada
                switch (opcionCampo) {
                    case 1:
                        printf("Ingrese el nuevo nombre: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;  // Elimina el salto de línea al final
                        strncpy(actual->datos_usuario.nombre, nuevaInfo, sizeof(actual->datos_usuario.nombre) - 1);
                        break;
                    case 2:
                        printf("Ingrese el nuevo apellido: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;  // Elimina el salto de línea al final
                        strncpy(actual->datos_usuario.apellido, nuevaInfo, sizeof(actual->datos_usuario.apellido) - 1);
                        break;
                    case 3:
                        printf("Ingrese la nueva edad: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        actual->datos_usuario.edad = atoi(nuevaInfo);
                        break;
                    case 4:
                        printf("Ingrese el nuevo teléfono: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.telefono, nuevaInfo, sizeof(actual->datos_usuario.telefono) - 1);
                        break;
                    case 5:
                        printf("Ingrese la nueva dirección: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.direccion, nuevaInfo, sizeof(actual->datos_usuario.direccion) - 1);
                        break;
                    case 6:
                        printf("Ingrese el nuevo código postal: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.cp, nuevaInfo, sizeof(actual->datos_usuario.cp) - 1);
                        break;
                    default:
                        printf("Opción no válida.\n");
                        break;
                }
            } else {
                printf("Opción no válida.\n");
                return;
            }

            printf("Usuario editado con éxito.\n");
            return;
        }

        actual = actual->sig;
    }

    printf("Usuario no encontrado.\n");
}



//Creamos una función para el menú de los libros.
int menulibros(){
	int op = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t                LIBROS:                   ");
	puts("\t------------------------------------------");
	puts("[1] Nuevo libro.");
	puts("[2] Eliminar libro.");
	puts("[3] Buscar libro.");
	puts("[4] Editar libro.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &op);
	return op;
}	

//Función para manejar la gestión de los libros.
int libros() {
    int op = 0;
    do {
        op = menulibros();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.   
                break;
            case 1:
                //Agregar nuevo libro.
                break;
            case 2:
            	//Eliminar libro.
                break;
            case 3:
            	//Buscar libro.
                break;
            case 4:
                //Editar libro.
                break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);

    return 0;
}

//Creamos una función para el menú de la transacción.
int menutransaccion(){
	int op = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t               TRANSACCION:               ");
	puts("\t------------------------------------------");
	puts("[1] Prestamo.");
	puts("[2] Devolucion.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &op);	
	return op;
}

//Función para manejar la gestión de la transacción.
int transaccion(){
    int op = 0;
    do {
        op = menutransaccion();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.   
                break;
            case 1:
            	prestamo();
                break;
            case 2:
            	devolucion();
            	break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);

    return 0;
}

//Función para mostrar el menú de gestión de préstamos.
int menuprestamos(){
	int opc = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t                 PRESTAMO                 ");
	puts("\t------------------------------------------");
	puts("[1] Nuevo prestamo.");
	puts("[2] Libros prestados.");
	puts("[3] Cancelar prestamo.");
	puts("[0] Volver al menu de transaccion.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &opc);
	return opc;
}

//Función para manejar la gestión de préstamos.
int prestamo(){
    int opc = 0;
    do {
        opc = menuprestamos();

        switch (opc) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.   
                break;
            case 1:
            	//Nuevo prestamo.
                break;
            case 2:
            	//Libros prestados
            	break;
            case 3:
            	//Devolver prestamo
            	break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (opc != 0);

    return 0;
}

//Función para mostrar el menú de gestión de devoluciones
int menudevolucion(){
	int opo = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t               DEVOLUCION:                ");
	puts("\t------------------------------------------");
    puts("[1] Registrar devolucion.");
    puts("[2] Mostrar todas las devoluciones.");
    puts("[3] Buscar devolucion por ID de usuario.");
    puts("[0] Volver al menu principal.");
    printf("Ingrese una opcion: ");
    scanf("%d", &opo);
	return opo;
}

//Función para manejar la gestión de devoluciones.
int devolucion(){
    int opo = 0;
    do {
        opo= menudevolucion();

        switch (opo) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.   
                break;
            case 1:
            	//Registrar devolucion
                break;
            case 2:
            	//Mostrar devoluciones
            	break;
            case 3:
            	//Buscar devolución.
            	break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (opo != 0);

    return 0;
}


//Función para mostrar el menú de gestión de multas
int menumultas() {
    int op = 0;
    system("cls");
	puts("\t------------------------------------------");
	puts("\t                 MULTA:                   ");
	puts("\t------------------------------------------");
    puts("[1] Registrar nueva multa.");
    puts("[2] Mostrar todas las multas.");
    puts("[3] Pagar multa.");
	puts("[0] Volver al menu principal.\n");
    printf("Ingrese una opción: ");
    scanf("%d", &op);
    return op;
}

//FFunción para manejar la gestión de multas.
int multas(){
    int op = 0;
    do {
        op = menumultas(); //Llamar a la función de menú y obtener la elección del usuario.
        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.          
                break;
            case 1:
            	//Nueva multa.
                break;
            case 2:
            	//Mostrar todas las multas.
            	break;
            case 3:
            	//Pagar multa.
            	break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);
    return 0;
}


int main(int argc, char** argv) {
    Lista_usuarios *listaUsuarios = NULL;

    // Llamamos a la función de gestión de usuarios desde el menú principal.
    libreria(&listaUsuarios);

    // Liberamos la memoria al final del programa.
    while (listaUsuarios != NULL) {
        Lista_usuarios *temp = listaUsuarios;
        listaUsuarios = listaUsuarios->sig;
        free(temp);
    }

    return 0;
}
