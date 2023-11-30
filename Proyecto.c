#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Lista_libros;

//Creamos la estructura con los datos del prestamo.
typedef struct prestamo {
    int ID_prestamo; 
    int ID_usuario;   
    char ID_libro[5];      
    char fecha_pedido[25]; 
    char fecha_devolver[25];
    int multa; 
    int estado; //estado del préstamo,puede ser pendiente, devuelto, vencido, etc.       
} Prestamo;

//Cremos la estructura con los datos de la reserva.
typedef struct reserva{
	int ID_reserva;
	int ID_usuario;
    char ID_libro[5];
    char fecha_reserva[25]; 
    int estado;
}Reserva;

typedef struct devolucion{
	char ID_libro[5];
	int ID_usuario;
	char fecha_devolvio[25];
	char condicion[50];
}Devolucion;

typedef struct multas{
	int ID_usuario;
	char ID_libro[5];
	int monto;
	char fecha_devolver[25];
	char razon[50];
	char metododepago[20];
}Multas;

typedef struct recordatorio{
	int ID_prestamo;
	char ID_libro[5];
	char fecha_devolver[25];
	char renovacion[10];
	int ID_usuario;
	char contacto[50];
}Recordatorio;

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
                usuarios(); //Llamamos a la función de usuarios
                break;
            case 2:
            	libros();
                break;
            case 3:
                transaccion();
                break;
            case 4:
                reserva();
                break;
            case 5:
                multas();
                break;
            case 6:
                // Funcionalidad de notificaciones
                break;
            default:
                printf("ERROR. Opcion desconocida. \n");
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

int usuarios() {
    int op = 0;
    do {
        op = menusuarios();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");  
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

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

int libros() {
    int op = 0;
    do {
        op = menulibros();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");  
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

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

int transaccion(){
    int op = 0;
    do {
        op = menutransaccion();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");  
                break;
            case 1:
            	prestamo();
                break;
            case 2:
            	devolucion();
            	break;
            default:
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

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


int prestamo(){
    int opc = 0;
    do {
        opc = menuprestamos();

        switch (opc) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause"); 
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (opc != 0);

    return 0;
}


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

int devolucion(){
    int opo = 0;
    do {
        opo= menudevolucion();

        switch (opo) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause"); 
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (opo != 0);

    return 0;
}

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

int reserva(){
    int op = 0;
    do {
        op = menureserva();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");                
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}

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

int multas(){
    int op = 0;
    do {
        op = menumultas();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");                
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
                puts("ERROR. Opcion desconocida.");
                system("pause");
                break;
        }
    } while (op != 0);

    return 0;
}
int main(int argc, char** argv) {
	libreria();
	usuarios();
	libros();
	transaccion();
	prestamo();
	reserva();

}