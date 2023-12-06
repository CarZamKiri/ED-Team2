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
void editarUsuario(Lista_usuarios *listaUsuarios);
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
	puts("[4] Visualizar datos del usuario.");
	puts("[5] Editar datos del usuario.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: \n");
	scanf("%d", &op);
	return op;
}

//Función para manejar la gestoón de los usuarios
int usuarios(Lista_usuarios **listaUsuarios) {
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
                editarUsuario(*listaUsuarios);
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
    Lista_usuarios *nuevoUsuario = (Lista_usuarios *)malloc(sizeof(Lista_usuarios));

    // Solicitar al usuario que ingrese los datos o proporcionarlos desde algún otro lugar.
    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevoUsuario->datos_usuario.ID_usuario);

    printf("Ingrese el nombre del usuario: ");
    scanf("%s", nuevoUsuario->datos_usuario.nombre);

    printf("Ingrese el apellido del usuario: ");
    scanf("%s", nuevoUsuario->datos_usuario.apellido);

    printf("Ingrese la edad del usuario: ");
    scanf("%d", &nuevoUsuario->datos_usuario.edad);

    printf("Ingrese el teléfono del usuario: ");
    scanf("%s", nuevoUsuario->datos_usuario.telefono);

    printf("Ingrese la dirección del usuario: ");
    scanf("%s", nuevoUsuario->datos_usuario.direccion);

    printf("Ingrese el código postal del usuario: ");
    scanf("%s", nuevoUsuario->datos_usuario.cp);

    nuevoUsuario->sig = *listaUsuarios;
    *listaUsuarios = nuevoUsuario;

    printf("Usuario agregado con éxito.\n");
    system("pause");
}

// Función para eliminar un usuario por ID.
void eliminarUsuario(Lista_usuarios **listaUsuarios) {
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

// Función para visualizar todos los usuarios.
void visualizarUsuarios(Lista_usuarios *listaUsuarios) {
    while (listaUsuarios != NULL) {
        printf("ID: %d\nNombre: %s %s\nEdad: %d\nTeléfono: %s\nDirección: %s\nCódigo Postal: %s\n\n",
            listaUsuarios->datos_usuario.ID_usuario,
            listaUsuarios->datos_usuario.nombre,
            listaUsuarios->datos_usuario.apellido,
            listaUsuarios->datos_usuario.edad,
            listaUsuarios->datos_usuario.telefono,
            listaUsuarios->datos_usuario.direccion,
            listaUsuarios->datos_usuario.cp);
        listaUsuarios = listaUsuarios->sig; 
    }
    system("pause");  
}

// Función para editar los datos de un usuario por ID.
void editarUsuario(Lista_usuarios *listaUsuarios) {
    int idUsuario;
    printf("Ingrese el ID del usuario a editar: ");
    scanf("%d", &idUsuario);

    while (listaUsuarios != NULL) {
        if (listaUsuarios->datos_usuario.ID_usuario == idUsuario) {
            // Solicitar al usuario que ingrese los nuevos datos o modificarlos desde algún otro lugar.
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", listaUsuarios->datos_usuario.nombre);

            printf("Ingrese el nuevo apellido: ");
            scanf("%s", listaUsuarios->datos_usuario.apellido);

            printf("Ingrese la nueva edad: ");
            scanf("%d", &listaUsuarios->datos_usuario.edad);

            printf("Ingrese el nuevo teléfono: ");
            scanf("%s", listaUsuarios->datos_usuario.telefono);

            printf("Ingrese la nueva dirección: ");
            scanf("%s", listaUsuarios->datos_usuario.direccion);

            printf("Ingrese el nuevo código postal: ");
            scanf("%s", listaUsuarios->datos_usuario.cp);

            printf("Usuario editado con éxito.\n");
            system("pause");
            return;
        }

        listaUsuarios = listaUsuarios->sig;
    }

    printf("Usuario no encontrado.\n");
    system("pause");
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