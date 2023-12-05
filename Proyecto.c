#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Creamos la estructura con los datos del usuario.
typedef struct usuario{
	int ID_usuario;
	char nombre[50];
	char apellido[50];
	int edad;
	char telefono[20];
	char direccion[100];
	char cp [10];
}Usuario;

//Creamos la estructura donde se almacenan todos los datos de cada nodo.
typedef struct lista_usuarios{
	Usuario datos_usuario;
	struct lista_usuarios *sig;
}Lista_usuarios;

//Creamos la estructura con los datos de los libros.
typedef struct libros{
	char ID_libro[5];
	char titulo[50];
	char autor[40];
	char categoria[20];
	char editorial[30];
	char idioma[10];
	int paginas;
	char descripcion[200];
	char fechalanzamiento[25];
}Libros;

//Creamos la estructra donde se almacenan todos los datos de cada nodo de los libros.
typedef struct lista_libros {
    Libros datos_libro;
    struct lista_libros* sig;
}Lista_libros;

typedef struct prestamo {
    int ID_prestamo; 
    int ID_usuario;   
    char ID_libro[5]; 
    time_t fecha_pedido;  // Modificado para usar time_t
    time_t fecha_devolver;  // Modificado para usar time_t
    int multa; 
    int estado; // Estado del préstamo       
} Prestamo;

typedef struct devolucion {
    char ID_libro[5];
    int ID_usuario;
    time_t fecha_devolvio;  // Modificado para usar time_t
    char condicion[50];
} Devolucion;

typedef struct multas {
    int ID_usuario;
    char ID_libro[5];
    int monto;
    time_t fecha_devolver;  // Modificado para usar time_t
    char razon[50];
    char metododepago[20];
} Multas;

typedef struct recordatorio {
    int ID_prestamo;
    char ID_libro[5];
    time_t fecha_devolver;  // Modificado para usar time_t
    char renovacion[10];
    int ID_usuario;
    char contacto[50];
} Recordatorio;



//Declaramos las funciones globales.
int menuprincipal();
int libreria();
int menusuarios();
int usuarios();
int menulibros();
int libros();
int menutransaccion();
int transaccion();
int menuprestamos();
int prestamo();
int menudevolucion();
int devolucion();
int menureserva();
int reserva();
int menumultas();
int multas();
/*Lista_usuarios* buscarUsuarioPorID(Lista_usuarios* lista, int ID) {
    Lista_usuarios* actual = lista;
    while (actual != NULL) {
        if (actual->datos_usuario.ID_usuario == ID) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL; // No se encontró el usuario
}

// Función para buscar un libro por ID
Lista_libros* buscarLibroPorID(Lista_libros* lista, char* ID) {
    Lista_libros* actual = lista;
    while (actual != NULL) {
        if (strcmp(actual->datos_libro.ID_libro, ID) == 0) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL; // No se encontró el libro
}

// Función para modificar datos de un usuario
void modificarUsuario(Lista_usuarios* usuario, char* nuevoNombre, char* nuevoApellido, int nuevaEdad, char* nuevoTelefono, char* nuevaDireccion, char* nuevoCP) {
    if (usuario != NULL) {
        strcpy(usuario->datos_usuario.nombre, nuevoNombre);
        strcpy(usuario->datos_usuario.apellido, nuevoApellido);
        usuario->datos_usuario.edad = nuevaEdad;
        strcpy(usuario->datos_usuario.telefono, nuevoTelefono);
        strcpy(usuario->datos_usuario.direccion, nuevaDireccion);
        strcpy(usuario->datos_usuario.cp, nuevoCP);
    }
}

// Función para modificar datos de un libro
void modificarLibro(Lista_libros* libro, char* nuevoTitulo, char* nuevoAutor, char* nuevaCategoria, char* nuevaEditorial, char* nuevoIdioma, int nuevasPaginas, char* nuevaDescripcion, char* nuevaFechaLanzamiento) {
    if (libro != NULL) {
        strcpy(libro->datos_libro.titulo, nuevoTitulo);
        strcpy(libro->datos_libro.autor, nuevoAutor);
        strcpy(libro->datos_libro.categoria, nuevaCategoria);
        strcpy(libro->datos_libro.editorial, nuevaEditorial);
        strcpy(libro->datos_libro.idioma, nuevoIdioma);
        libro->datos_libro.paginas = nuevasPaginas;
        strcpy(libro->datos_libro.descripcion, nuevaDescripcion);
        strcpy(libro->datos_libro.fechalanzamiento, nuevaFechaLanzamiento);
    }
}

// Función para eliminar un usuario por ID
Lista_usuarios* eliminarUsuarioPorID(Lista_usuarios* lista, int ID) {
    Lista_usuarios* actual = lista;
    Lista_usuarios* anterior = NULL;

    while (actual != NULL) {
        if (actual->datos_usuario.ID_usuario == ID) {
            if (anterior == NULL) {
                // El usuario a eliminar es el primero de la lista
                lista = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            free(actual);
            break;
        }
        anterior = actual;
        actual = actual->sig;
    }

    return lista;
}

// Función para eliminar un libro por ID
Lista_libros* eliminarLibroPorID(Lista_libros* lista, char* ID) {
    Lista_libros* actual = lista;
    Lista_libros* anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->datos_libro.ID_libro, ID) == 0) {
            if (anterior == NULL) {
                // El libro a eliminar es el primero de la lista
                lista = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            free(actual);
            break;
        }
        anterior = actual;
        actual = actual->sig;
    }

    return lista;
}
*/

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
	puts("[4] Reserva.");
	puts("[5] Multas y recordatorios.");
	puts("[6] Notificaciones.");
	puts("[0] SALIR.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &opcion);
	return opcion;
}

//Función para manejar la gestión de la librería.
int libreria() {
    int op = 0;
    do {
        op = menuprincipal();

        switch (op) {
            case 0:
                puts("Saliendo...");
                system("pause");  
                exit(0);
            case 1:
                usuarios(); //llamamos a la función de los usuarios
                break;
            case 2:
            	libros(); //llamamos a la función de los libros.
                break;
            case 3:
                transaccion(); //llamamos a la función de la transacción.
                break;
            case 4:
                reserva(); //llamamos a la función de la reserva.
                break;
            case 5:
                multas(); //llamamos a la función de las multas;
		//recordatorios();
                break;
            case 6:
                // Funcionalidad de notificaciones
                break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.;
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
int usuarios() {
    int op = 0;
    do {
        op = menusuarios();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.    
                break;
            case 1:
                //Agregar nuevo usuario.
                break;
            case 2:
            	//Eliminar usuario.
                break;
            case 3:
            	//Buscar usuario.
                break;
            case 4:
                //Visualizar datos del usuario.
                break;
            case 5:
                //Editar datos del usuario.
                break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);

    return 0;
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
	puts("[3] Devolver prestamo.");
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

//Función para mostrar el menú de gestión de reservas.
int menureserva(){
	int op = 0;
	system("cls");
	puts("\t------------------------------------------");
	puts("\t               RESERVA:                   ");
	puts("\t------------------------------------------");
	puts("[1] Nueva reserva.");
	puts("[2] Libros reservados.");
	puts("[3] Cancelar reserva.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &op);
	return op;
}

//Función para manejar la gestión de reservas.
int reserva(){
    int op = 0;
    do {
        op = menureserva();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.                  
                break;
            case 1:
            	//Nueva reserva.
                break;
            case 2:
            	//Libros reservados
            	break;
            case 3:
            	//Cancelar reserva.
            	break;
            default:
                puts("ERROR. Opcion desconocida."); //opción desconocida.
                system("pause"); //pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);

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
	libreria(); //mandamos  llamar a la función librería para que se pueda ejecutar nuestro programa,
}
