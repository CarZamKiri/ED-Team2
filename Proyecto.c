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
    int cantidad; // Añadir campo de cantidad
} Libros;

// Nodo para el árbol AVL
typedef struct NodoAVL {
    Libros datos_libro;
    struct NodoAVL* izquierda;
    struct NodoAVL* derecha;
    int altura;
} NodoAVL;

// Estructura con los datos del préstamo.
typedef struct prestamo {
    int ID_prestamo; 
    int ID_usuario;   
    char ID_libro[5];                                       
    time_t fecha_pedido;  // Uso de time_t
    time_t fecha_devolver;  // Uso de time_t
} Prestamo;

//Lista de Prestamos
typedef struct lista_prestamos {
    Prestamo datos_prestamo;
    struct lista_prestamos* sig;
} Lista_prestamos;

// Estructura con los datos de la devolución.
typedef struct devolucion {
    int ID_devolucion;
    int ID_prestamo; 
    int ID_usuario;   
    char ID_libro[5];
    time_t fecha_devolucion; 
} Devolucion;

typedef struct lista_devoluciones {
    Devolucion datos_devolucion;
    struct lista_devoluciones *sig;
} Lista_devoluciones;


typedef struct multas {
    int ID_prestamo;
    int monto;
    time_t fecha_devolver;  // Uso de time_t
    int diasatraso;
    int precioxdia;
    char razon[50];
    char metododepago[20];
    struct multas *anterior;
    struct multas *siguiente;
}Multas;

// Estructura de la cola doble
typedef struct cola_multas {
    Multas *frente;
    Multas *final;
}Cola_multas;


// Estructura para los recordatorios.
typedef struct recordatorio {
    int ID_prestamo;
    char ID_libro[5];
    time_t fecha_devolver;  // Uso de time_t
    int ID_usuario;
    char contacto[50];
} Recordatorio;

typedef struct reserva {
	int ID_reserva;
    int ID_usuario;
    char ID_libro[5];
    struct reserva *siguiente;
} Reserva;

typedef struct cola_reservas {
    Reserva *inicio;
    Reserva *final;
} ColaReservas;


//Declaramos las funciones y variables globales.
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
void imprimirDatosUsuario(Usuario *usuario);
void iniciarcoladoble(Cola_multas *cola_multas);
int coladoble(Cola_multas *cola_multas);
void encolarfrente(Cola_multas *cola_multas, Multas **nuevaMulta);
void encolarfinal(Cola_multas *cola_multas, Multas *nuevaMulta);
Multas *desencolarfrente(Cola_multas *cola_multas);
Multas *desencolarfinal(Cola_multas *cola_multas);
void mostrarmulta(Multas *multa);
void multanumero(Cola_multas *cola_multas);
void registrarmulta(Cola_multas *cola_multas, Lista_prestamos *listaPrestamos);
int menulibros();
int libros();
int menutransaccion();
int transaccion();
int menuprestamos();
int prestamo();
int menudevolucion();
int devolucion();
int reserva();
int menumultas();
int multas();
void notificaciones(Lista_prestamos *listaPrestamos); //Funcion para mostrar las notificaciones
int difDias(time_t fecha1, time_t fecha2); //Funcion para calcular la diferencia de dias 

//Funciones del arbol declaradas
NodoAVL* agregarLibroAVL(NodoAVL* raiz, Libros libro);
int altura(NodoAVL* N);
int max(int a, int b);
int obtenerFactorBalance(NodoAVL* N);
NodoAVL* rotarDerecha(NodoAVL* y);
NodoAVL* rotarIzquierda(NodoAVL* x);
NodoAVL* nuevoNodoLibro(Libros libro);
NodoAVL* libroEncontrado = NULL;

//Funciones para prestamos
Usuario* buscarUsuarioPorID(Lista_usuarios *listaUsuarios, int ID_usuario);
int crearPrestamo(Lista_usuarios *listaUsuarios, NodoAVL *raizLibros, Lista_prestamos **listaPrestamos, int ID_prestamo, int ID_usuario, char *ID_libro);
void agregarPrestamo(Lista_prestamos **listaPrestamos, Prestamo nuevoPrestamo);
void GestionarNuevoPrestamo(Lista_usuarios *listaUsuarios, NodoAVL *raizLibros, Lista_prestamos **listaPrestamos);
Prestamo* buscarPrestamoPorID(Lista_prestamos *listaPrestamos, int ID_prestamo);
void eliminarPrestamo(Lista_prestamos **listaPrestamos, NodoAVL **raizLibros, int ID_prestamo);

//Funciones para devoluciones
int devolucion(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_devoluciones **listaDevoluciones, ColaReservas **colaReservas);
void realizarDevolucion(Lista_usuarios **listaUsuarios, Lista_prestamos **listaPrestamos, NodoAVL **raizLibros, Lista_devoluciones **listaDevoluciones, ColaReservas **colaReservas, int ID_prestamo);
void mostrarTodasLasDevoluciones(Lista_devoluciones *listaDevoluciones);
Devolucion* buscarDevolucionPorID(Lista_devoluciones *listaDevoluciones, int ID_devolucion);
void imprimirFecha(time_t tiempo);
void mostrarDetallesDevolucionPorID(Lista_devoluciones *listaDevoluciones, int ID_devolucion);


//Funciones para reservas
void agregarReserva(ColaReservas **cola, int ID_reserva, int ID_usuario, char *ID_libro);
void procesarReserva(ColaReservas **colaReservas, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_usuarios *listaUsuarios);
void eliminarReserva(ColaReservas **colaReservas);
void mostrarReservas(ColaReservas *cola);
int hayReservasParaLibro(ColaReservas *cola, char *ID_libro);

//Datos precargados
void inicializarDatosEstaticos(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros) {
    Usuario usuarioEstatico = {
        .ID_usuario = 1,
        .nombre = "Juan",
        .apellido = "Perez",
        .edad = 30,
        .telefono = "1234567890",
        .direccion = "Calle Falsa 123",
        .cp = "00000"
    };

    // Agregar el usuario a la lista
    Lista_usuarios *nuevoUsuario = (Lista_usuarios *)malloc(sizeof(Lista_usuarios));
    if (nuevoUsuario != NULL) {
        nuevoUsuario->datos_usuario = usuarioEstatico;
        nuevoUsuario->sig = *listaUsuarios;
        *listaUsuarios = nuevoUsuario;
    }

    // Crear un libro estático
    Libros libroEstatico = {
        .ID_libro = "L1",
        .titulo = "Programacion en C",
        .autor = "Brian Kernighan",
        .categoria = "Educacion",
        .editorial = "Prentice Hall",
        .idioma = "Español",
        .paginas = 272,
        .descripcion = "Un libro clasico sobre programacion en C.",
        .fechalanzamiento = "1988-02-22",
        .cantidad = 1  
    };

    // Agregar el libro al árbol AVL
    *raizLibros = agregarLibroAVL(*raizLibros, libroEstatico);
}


//Crear nodo
NodoAVL* nuevoNodoLibro(Libros libro) {
    NodoAVL* nodo = (NodoAVL*) malloc(sizeof(NodoAVL));
    nodo->datos_libro = libro;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    nodo->altura = 1;
    return nodo;
}
//Rotar a la derecha
NodoAVL* rotarDerecha(NodoAVL *y) {
    NodoAVL *x = y->izquierda;
    NodoAVL *T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}
//Rotar a la izquierda
NodoAVL* rotarIzquierda(NodoAVL *x) {
    NodoAVL *y = x->derecha;
    NodoAVL *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}
//Funcion del max
int max(int a, int b) {
    return (a > b) ? a : b;
}
//Funcion que cuenta la altura
int altura(NodoAVL *N) {
    if (N == NULL) {
        return 0;
    }
    return N->altura;
}
//Balancear información
int obtenerFactorBalance(NodoAVL *N) {
    if (N == NULL) {
        return 0;
    }
    return altura(N->izquierda) - altura(N->derecha);
}


//Agregar libros
NodoAVL* agregarLibroAVL(NodoAVL* raiz, Libros libro) {
    if (raiz == NULL) 
    {
        return nuevoNodoLibro(libro);
    }

    if (strcmp(libro.ID_libro, raiz->datos_libro.ID_libro) < 0) 
    {
        raiz->izquierda = agregarLibroAVL(raiz->izquierda, libro);
    } else if (strcmp(libro.ID_libro, raiz->datos_libro.ID_libro) > 0) 
    {
        raiz->derecha = agregarLibroAVL(raiz->derecha, libro);
    } else 
    {
        printf("Ya existe un libro con el mismo ID.\n");
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));

    int balance = obtenerFactorBalance(raiz);

    if (balance > 1 && strcmp(libro.ID_libro, raiz->izquierda->datos_libro.ID_libro) < 0)
        return rotarDerecha(raiz);

    if (balance < -1 && strcmp(libro.ID_libro, raiz->derecha->datos_libro.ID_libro) > 0)
        return rotarIzquierda(raiz);

    if (balance > 1 && strcmp(libro.ID_libro, raiz->izquierda->datos_libro.ID_libro) > 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && strcmp(libro.ID_libro, raiz->derecha->datos_libro.ID_libro) < 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }
    return raiz;
}


//MOSTRAR DATOS DE LOS LIBROS
void mostrarLibro(Libros libro){
    system("cls");
	printf("ID Libro: %s\n",libro.ID_libro);
	printf("Titulo: %s\n", libro.titulo);
	printf("Autor: %s\n", libro.autor);
	printf("Categoria: %s\n", libro.categoria);
	printf("Editorial: %s\n", libro.editorial);
	printf("Idioma: %s\n", libro.editorial);
	printf("Paginas: %d\n", libro.paginas);
	printf("Descripcion: %s\n",libro.descripcion);
	printf("Fecha de Lanzamiento: %s\n", libro.fechalanzamiento);
	printf("Cantidad: %d\n", libro.cantidad);
	
}

//Muestra todos los libros
void mostrarTodosLosLibros(NodoAVL* raiz) {
    if (raiz == NULL) {
        printf("No existen libros en el inventario.\n");
        return; // Sale de la función si el árbol está vacío.
    }
    
    // Si la raíz no es NULL, procede a mostrar los libros.
    if (raiz->izquierda != NULL) {
        mostrarTodosLosLibros(raiz->izquierda);
    }

    mostrarLibro(raiz->datos_libro);

    if (raiz->derecha != NULL) {
        mostrarTodosLosLibros(raiz->derecha);
    }
}

//BUSCAR LIBRO Y MOSTRARLO

NodoAVL *buscarLibro(NodoAVL *raiz, char *ID_libro){
	if(raiz == NULL){
		return NULL;
	}
	
	if(strcmp(ID_libro, raiz->datos_libro.ID_libro)<0){
		return buscarLibro(raiz->izquierda, ID_libro);
	}else if(strcmp(ID_libro,raiz->datos_libro.ID_libro) > 0) {
        return buscarLibro(raiz->derecha, ID_libro);
    } else {
        mostrarLibro(raiz->datos_libro);
        return raiz;
    }
}

//Valor MindelNodo
NodoAVL* minValueNode(NodoAVL* node) {
    NodoAVL* current = node;

    // loop down to find the leftmost leaf
    while (current && current->izquierda != NULL) {
        current = current->izquierda;
    }

    return current;
}


//Función para eliminar un libro
NodoAVL* eliminarLibro(NodoAVL* raiz, char* ID_libro) {
    // Paso 1: Realizar la eliminación estándar de BST
    if (raiz == NULL) {
        return raiz;
    }

    if (strcmp(ID_libro, raiz->datos_libro.ID_libro) < 0) {
        raiz->izquierda = eliminarLibro(raiz->izquierda, ID_libro);
    } else if (strcmp(ID_libro, raiz->datos_libro.ID_libro) > 0) {
        raiz->derecha = eliminarLibro(raiz->derecha, ID_libro);
    } else {
        // El nodo a eliminar fue encontrado...

        // Casos con un solo hijo o sin hijos
        if ((raiz->izquierda == NULL) || (raiz->derecha == NULL)) {
            NodoAVL *temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;

            // Sin hijos
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                // Un hijo
                *raiz = *temp; // Copiar el contenido del hijo no nulo
            }
            free(temp);
        } else {
            // Nodo con dos hijos: obtener el sucesor inorden (el más pequeño en el subárbol derecho)
            NodoAVL* temp = minValueNode(raiz->derecha);

            // Copiar los datos del sucesor inorden al nodo actual
            raiz->datos_libro = temp->datos_libro;

            // Eliminar el sucesor inorden
            raiz->derecha = eliminarLibro(raiz->derecha, temp->datos_libro.ID_libro);
        }
    }

    // Si el árbol tenía solo un nodo, retornar
    if (raiz == NULL) {
        return raiz;
    }

    // Paso 2: Actualizar la altura del nodo actual
    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));

    // Paso 3: Reequilibrar el árbol
    int balance = obtenerFactorBalance(raiz);

    // Rotaciones...
    // Rotación simple a la derecha
    if (balance > 1 && obtenerFactorBalance(raiz->izquierda) >= 0) {
        return rotarDerecha(raiz);
    }

    // Rotación doble izquierda-derecha
    if (balance > 1 && obtenerFactorBalance(raiz->izquierda) < 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // Rotación simple a la izquierda
    if (balance < -1 && obtenerFactorBalance(raiz->derecha) <= 0) {
        return rotarIzquierda(raiz);
    }

    // Rotación doble derecha-izquierda
    if (balance < -1 && obtenerFactorBalance(raiz->derecha) > 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}
//Editar los libros
void modificarLibro(NodoAVL* raiz, char* ID_libro, Libros nuevoLibro) {
    NodoAVL* libroEncontrado = buscarLibro(raiz, ID_libro);
    if (libroEncontrado != NULL) {
        libroEncontrado->datos_libro = nuevoLibro;
    } else {
        return;
    }
}

//FUNCIONES PARA GESTIONAR EL SISTEMA DE PRESTAMOS

// Busca un usuario por ID y devuelve un puntero a su estructura si lo encuentra.
Usuario* buscarUsuarioPorID(Lista_usuarios *listaUsuarios, int ID_usuario) {
    printf("Buscando usuario con ID: %d\n",ID_usuario); // Agregar para depuración
    while (listaUsuarios != NULL) {
        printf("Revisando usuario con ID: %d\n", listaUsuarios->datos_usuario.ID_usuario);
        if (listaUsuarios->datos_usuario.ID_usuario == ID_usuario) {
            printf("Usuario encontrado.\n");  // Agregar para depuración
            return &listaUsuarios->datos_usuario;
        }
        listaUsuarios = listaUsuarios->sig;
    }
    printf("Usuario no encontrado.\n");  // Agregar para depuración
    return NULL;
}

//Muestra el detalle de un prestamo gracias a su ID
void mostrarDetallesPrestamoPorID(Lista_prestamos* lista, int ID_prestamo) {
    Prestamo* prestamo = buscarPrestamoPorID(lista, ID_prestamo);
    system("cls");
    if (prestamo != NULL) {
        printf("Detalles del prestamo ID %d:\n", ID_prestamo);
        printf("ID Usuario: %d\n", prestamo->ID_usuario);
        printf("ID Libro: %s\n", prestamo->ID_libro);
        printf("Fecha pedido: ");
        imprimirFecha(prestamo->fecha_pedido);
        printf("\nFecha devolver: ");
        imprimirFecha(prestamo->fecha_devolver);
        printf("\n");
    } else {
        printf("Prestamo con ID %d no encontrado.\n", ID_prestamo);
    }
}

//Creamos el nodo prestamo con los datos ya verificados antes y los insertamos
int crearPrestamo(Lista_usuarios *listaUsuarios, NodoAVL *raizLibros, Lista_prestamos **listaPrestamos, int ID_prestamo, int ID_usuario, char *ID_libro) {
    // Verificar si el préstamo ya existe
    if (buscarPrestamoPorID(*listaPrestamos, ID_prestamo) != NULL) {
        printf("Ya existe un prestamo con el ID %d.\n", ID_prestamo);
        return 0; // El préstamo ya existe
    }

    // Verificar si el usuario existe
    Usuario *usuarioEncontrado = buscarUsuarioPorID(listaUsuarios, ID_usuario);
    if (usuarioEncontrado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", ID_usuario);
        return 0; // El usuario no existe
    }

    // Verificar si el libro existe y tiene copias disponibles
    NodoAVL *libroEncontrado = buscarLibro(raizLibros, ID_libro);
    if (libroEncontrado == NULL || libroEncontrado->datos_libro.cantidad <= 0) {
        printf("Libro con ID %s no disponible para prestamo.\n", ID_libro);
        return 0; // El libro no existe o no tiene copias disponibles
    }

    // Crear el préstamo
    Prestamo nuevoPrestamo;
    nuevoPrestamo.ID_prestamo = ID_prestamo;
    nuevoPrestamo.ID_usuario = ID_usuario;
    strcpy(nuevoPrestamo.ID_libro, ID_libro);

    // Establecer las fechas de pedido y devolución
    time(&nuevoPrestamo.fecha_pedido);
    struct tm tiempoEstructurado = *localtime(&nuevoPrestamo.fecha_pedido);
    tiempoEstructurado.tm_mday += 14; // Añadir 14 días para la fecha de devolución
    nuevoPrestamo.fecha_devolver = mktime(&tiempoEstructurado);

    // Disminuir la cantidad de libros disponibles
    libroEncontrado->datos_libro.cantidad--;

    // Agregar el préstamo a la lista
    agregarPrestamo(listaPrestamos, nuevoPrestamo);

    printf("Préstamo con ID %d creado con exito. Fecha de devolución: ", ID_prestamo);
    imprimirFecha(nuevoPrestamo.fecha_devolver);
    printf("\n");

    return 1; // Préstamo creado exitosamente
}

//Funcion para agregar el nodo prestamo a la lista prestamo
void agregarPrestamo(Lista_prestamos **listaPrestamos, Prestamo nuevoPrestamo) {
    Lista_prestamos *nuevoNodo = (Lista_prestamos *)malloc(sizeof(Lista_prestamos));
    if (nuevoNodo == NULL) {
        system("cls");
        printf("Error de memoria al intentar agregar un nuevo prestamo.\n");
        return;
    }

    nuevoNodo->datos_prestamo = nuevoPrestamo;
    nuevoNodo->sig = *listaPrestamos;
    *listaPrestamos = nuevoNodo;
}

//Filtros del para procesar los datos del nodo
void GestionarNuevoPrestamo(Lista_usuarios *listaUsuarios, NodoAVL *raizLibros, Lista_prestamos **listaPrestamos) {
    int ID_usuario, ID_prestamo;
    char ID_libro[5]; // Asumiendo que ID_libro tiene una longitud máxima de 5 caracteres + 1 para el carácter nulo

    // Obtener datos del usuario
    printf("Ingrese el ID del usuario para el prestamo: ");
    scanf("%d", &ID_usuario);
    Usuario *usuarioEncontrado = buscarUsuarioPorID(listaUsuarios, ID_usuario);
    if (usuarioEncontrado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", ID_usuario);
        return; // Salir si el usuario no se encuentra
    }

    // Obtener datos del libro
    printf("Ingrese el ID del libro para el prestamo: ");
    scanf("%5s", ID_libro); // Usar %5s para limitar el tamaño de la entrada y evitar desbordamientos
    NodoAVL *libroEncontrado = buscarLibro(raizLibros, ID_libro);
    if (libroEncontrado == NULL || libroEncontrado->datos_libro.cantidad <= 0) {
        printf("Libro no disponible para prestamo.\n");
        return; // Salir si el libro no se encuentra o no tiene copias disponibles
    }

    // Obtener el ID del préstamo
    printf("Ingrese el ID del prestamo: ");
    scanf("%d", &ID_prestamo);

    // Crear el préstamo
    if (crearPrestamo(listaUsuarios, raizLibros, listaPrestamos, ID_prestamo, ID_usuario, ID_libro)) {
    printf("Préstamo creado con exito.\n");
} else {
    printf("No se pudo crear el prestamo.\n");
}
}

//Buscador de el prestramo ya creado gracias a un ID proporcionado
Prestamo* buscarPrestamoPorID(Lista_prestamos *listaPrestamos, int ID_prestamo) {
    while (listaPrestamos != NULL) {
        if (listaPrestamos->datos_prestamo.ID_prestamo == ID_prestamo) {
            return &listaPrestamos->datos_prestamo;
        }
        listaPrestamos = listaPrestamos->sig;
    }
    return NULL;
}

//Eliminar un prestamo existente 
void eliminarPrestamo(Lista_prestamos **listaPrestamos, NodoAVL **raizLibros, int ID_prestamo){
    Lista_prestamos *actual = *listaPrestamos;
    Lista_prestamos *anterior = NULL;
    while (actual != NULL && actual->datos_prestamo.ID_prestamo != ID_prestamo) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual == NULL) {
        printf("Prestamo no encontrado.\n");
        return;
    }
    
    NodoAVL *libroEncontrado = buscarLibro(*raizLibros, actual->datos_prestamo.ID_libro);
    if (libroEncontrado != NULL) {
        libroEncontrado->datos_libro.cantidad++;
    } else {
        printf("Error: Libro correspondiente al prestamo no encontrado.\n");
    }

    if (anterior == NULL) {
        *listaPrestamos = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    free(actual);
    printf("Prestamo con ID %d eliminado y libro restituido con exito.\n", ID_prestamo);
}

//Imprimir fecha 
void imprimirFecha(time_t tiempoRaw) {
    struct tm *tiempo = localtime(&tiempoRaw);
    printf("%02d/%02d/%04d %02d:%02d:%02d",
           tiempo->tm_mday,       // Día del mes (1-31)
           tiempo->tm_mon + 1,    // Mes (0-11, por eso sumamos 1 para obtener 1-12)
           tiempo->tm_year + 1900, // Años desde 1900, se suman 1900 para obtener el año actual
           tiempo->tm_hour,       // Horas (0-23)
           tiempo->tm_min,        // Minutos (0-59)
           tiempo->tm_sec);       // Segundos (0-60, 60 para bisiestos)
}

// Busca e imprime la información de un usuario.
void buscarUsuario(Lista_usuarios *listaUsuarios) {
    system("cls");
    int idUsuario;
    printf("Ingrese el ID del usuario a buscar: ");
    scanf("%d", &idUsuario);

    Usuario *usuarioEncontrado = buscarUsuarioPorID(listaUsuarios, idUsuario);
    if (usuarioEncontrado != NULL) {
        imprimirDatosUsuario(usuarioEncontrado);
    } else {
        printf("Usuario no encontrado.\n");
    }

    system("pause");
}

//FUNCIÓNES PARA LAS DEVOLUCIONES

Devolucion* buscarDevolucionPorID(Lista_devoluciones *listaDevoluciones, int ID_devolucion) {
    while (listaDevoluciones != NULL) {
        if (listaDevoluciones->datos_devolucion.ID_devolucion == ID_devolucion) {
            return &listaDevoluciones->datos_devolucion;
        }
        listaDevoluciones = listaDevoluciones->sig;
    }
    return NULL;
}

void realizarDevolucion(Lista_usuarios **listaUsuarios, Lista_prestamos **listaPrestamos, NodoAVL **raizLibros, Lista_devoluciones **listaDevoluciones, ColaReservas **colaReservas, int ID_prestamo) {
    // Buscar el préstamo
    Prestamo *prestamoEncontrado = buscarPrestamoPorID(*listaPrestamos, ID_prestamo);
    if (prestamoEncontrado == NULL) {
        printf("Prestamo con ID %d no encontrado.\n", ID_prestamo);
        return;
    }

    // Incrementar cantidad del libro
    NodoAVL *libroEncontrado = buscarLibro(*raizLibros, prestamoEncontrado->ID_libro);
    if (libroEncontrado != NULL) {
        libroEncontrado->datos_libro.cantidad++;
	
	 // Verificar si hay reservas para el libro
        if (hayReservasParaLibro(*colaReservas, libroEncontrado->datos_libro.ID_libro)) {
            procesarReserva(colaReservas, raizLibros, listaPrestamos, *listaUsuarios); // Asegúrate de pasar listaUsuarios si es necesario
        }
    } else {
        printf("Error: Libro correspondiente al préstamo no encontrado.\n");
        return;
    }

    // Crear la devolución
    Devolucion nuevaDevolucion;
    nuevaDevolucion.ID_devolucion = ID_prestamo;  // Utilizando el ID del préstamo como ID de devolución
    nuevaDevolucion.ID_prestamo = ID_prestamo;
    nuevaDevolucion.ID_usuario = prestamoEncontrado->ID_usuario;
    strcpy(nuevaDevolucion.ID_libro, prestamoEncontrado->ID_libro);
    time(&nuevaDevolucion.fecha_devolucion);

    // Agregar la devolución a la lista
    Lista_devoluciones *nuevoNodo = (Lista_devoluciones *)malloc(sizeof(Lista_devoluciones));
    if (nuevoNodo == NULL) {
        printf("Error de memoria al intentar agregar una nueva devolución.\n");
        return;
    }
    nuevoNodo->datos_devolucion = nuevaDevolucion;
    nuevoNodo->sig = *listaDevoluciones;
    *listaDevoluciones = nuevoNodo;

    printf("Devolución registrada con exito.\n");
}

//Mostrar los detalles de una devolución por su ID
void mostrarDetallesDevolucionPorID(Lista_devoluciones *listaDevoluciones, int ID_devolucion) {
    Devolucion* devolucion = buscarDevolucionPorID(listaDevoluciones, ID_devolucion);
    if (devolucion != NULL) {
        printf("Detalles de la devolucion ID %d:\n", ID_devolucion);
        printf("ID Usuario: %d\n", devolucion->ID_usuario);
        printf("ID Libro: %s\n", devolucion->ID_libro);
        printf("Fecha Devolucion: \n");
        imprimirFecha(devolucion->fecha_devolucion);
        printf("\n");
    } else {
        printf("Devolucion con ID %d no encontrada.\n", ID_devolucion);
    }
}

//Mostrar todas las devoluciones
void mostrarTodasLasDevoluciones(Lista_devoluciones *lista) {
    if (lista == NULL) {
        printf("No hay devoluciones registradas.\n");
        return;
    }
    while (lista != NULL) {
        mostrarDetallesDevolucionPorID(lista, lista->datos_devolucion.ID_devolucion);
        lista = lista->sig;
    }
}

//GESTION DE RESERVAS

//--Agregar una Reserva ---

void agregarReserva(ColaReservas **cola, int ID_reserva, int ID_usuario, char *ID_libro) {
    Reserva *nuevaReserva = (Reserva *)malloc(sizeof(Reserva));
    if (nuevaReserva == NULL) {
        printf("Error de memoria al intentar agregar una nueva reserva.\n");
        return;
    }

    nuevaReserva->ID_reserva = ID_reserva; // Usa el ID de préstamo como ID de reserva
    nuevaReserva->ID_usuario = ID_usuario;
    strcpy(nuevaReserva->ID_libro, ID_libro);
    nuevaReserva->siguiente = NULL;

    if ((*cola)->final == NULL) {
        (*cola)->inicio = (*cola)->final = nuevaReserva;
    } else {
        (*cola)->final->siguiente = nuevaReserva;
        (*cola)->final = nuevaReserva;
    }
}

//--- Mostrar todas las reservas--
void mostrarReservas(ColaReservas *cola) {
    if (cola == NULL || cola->inicio == NULL) {
        printf("No hay reservas pendientes.\n");
        return;
    }

    Reserva *actual = cola->inicio;
    while (actual != NULL) {
        printf("Reserva: Usuario ID %d, Libro ID %s\n", actual->ID_usuario, actual->ID_libro);
        actual = actual->siguiente;
    }
}

// -- Funcion para verificar si existen reservas para los libros --
int hayReservasParaLibro(ColaReservas *cola, char *ID_libro) {
    if (cola == NULL || cola->inicio == NULL) {
        return 0; 
    }

    Reserva *actual = cola->inicio;
    while (actual != NULL) {
        if (strcmp(actual->ID_libro, ID_libro) == 0) {
            return 1; // Existe una reserva para el libro
        }
        actual = actual->siguiente;
    }

    return 0; 
}
// --Funcion de EliminarReserva--
void eliminarReserva(ColaReservas **colaReservas) {
    if (*colaReservas == NULL || (*colaReservas)->inicio == NULL) {
        return; // La cola está vacía
    }

    Reserva *reservaAEliminar = (*colaReservas)->inicio;
    (*colaReservas)->inicio = reservaAEliminar->siguiente;

    if ((*colaReservas)->inicio == NULL) {
        (*colaReservas)->final = NULL; // La cola ahora está vacía
    }

    free(reservaAEliminar);
}

// Procesar Reserva

 void procesarReserva(ColaReservas **colaReservas, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_usuarios *listaUsuarios) {
    if (*colaReservas == NULL || (*colaReservas)->inicio == NULL) {
        return; // No hay reservas pendientes
    }

    Reserva *reserva = (*colaReservas)->inicio;

    // Crear préstamo para la primera reserva en la cola
   
        if (crearPrestamo(listaUsuarios, *raizLibros, listaPrestamos, reserva->ID_reserva, reserva->ID_usuario, reserva->ID_libro)) {
            printf("Prestamo creado con exito a partir de la reserva.\n");
        } else {
            printf("No se pudo crear el prestamo desde la reserva.\n");
        }
		eliminarReserva(colaReservas);
        
}

//Gestion de Multas

// Función para inicializar la cola doble
void iniciarcoladoble(Cola_multas *cola_multas) {
    cola_multas->frente = cola_multas->final = NULL;
}

// Función para verificar si la cola doble de multas está vacía
int coladoble(Cola_multas *cola_multas) {
    return (cola_multas->frente == NULL && cola_multas->final == NULL) ? 1 : 0;
}
// Encolar al frente de la cola doble
void encolarfrente(Cola_multas *cola_multas, Multas **nuevaMulta) {
    (*nuevaMulta)->anterior = NULL;
    (*nuevaMulta)->siguiente = cola_multas->frente;

    if (coladoble(cola_multas)) {
        cola_multas->frente = cola_multas->final = *nuevaMulta;
    } else {
        cola_multas->frente->anterior = *nuevaMulta;
        cola_multas->frente = *nuevaMulta;
    }
}

// Encolar al final de la cola doble
void encolarfinal(Cola_multas *cola_multas, Multas *nuevaMulta) {
    nuevaMulta->anterior = cola_multas->final;
    nuevaMulta->siguiente = NULL;

    if (coladoble(cola_multas)) {
        cola_multas->frente = cola_multas->final = nuevaMulta;
    } else {
        cola_multas->final->siguiente = nuevaMulta;
        cola_multas->final = nuevaMulta;
    }
}


// Desencolar del frente de la cola doble
Multas *desencolarfrente(Cola_multas *cola_multas) {
    if (coladoble(cola_multas)) {
        return NULL;
    } else {
        Multas *primeraMulta = cola_multas->frente;
        cola_multas->frente = cola_multas->frente->siguiente;
        if (cola_multas->frente == NULL) {
            cola_multas->final = NULL;
        } else {
            cola_multas->frente->anterior = NULL;
        }
        return primeraMulta;
    }
}

// Desencolar del final de la cola doble
Multas *desencolarfinal(Cola_multas *cola_multas) {
    if (coladoble(cola_multas)) {
        return NULL;
    } else {
        Multas *ultimaMulta = cola_multas->final;
        cola_multas->final = cola_multas->final->anterior;
        if (cola_multas->final == NULL) {
            cola_multas->frente = NULL;
        } else {
            cola_multas->final->siguiente = NULL;
        }
        return ultimaMulta;
    }
}

// Función para mostrar una multa específica
void mostrarmulta(Multas *multa) {
    printf("ID Prestamo: %d\n", multa->ID_prestamo);

    if (strcmp(multa->razon, "Paso de tiempo") == 0) {
        printf("Fecha devolver: %s", ctime(&multa->fecha_devolver));
        printf("Dias de atraso: %d\n", multa->diasatraso);
        printf("Monto: %d\n", multa->monto);
        printf("Razon: %s\n", multa->razon);
        printf("Metodo de pago: %s\n", multa->metododepago);
    } else if (strcmp(multa->razon, "Mal estado") == 0) {
        printf("Monto: %d\n", multa->monto);
        printf("Razon: %s\n", multa->razon);
    }

    printf("--------------------------\n");
}

// Función para mostrar todas las multas en la cola doble
void multanumero(Cola_multas *cola_multas) {
    int contador = 1;
    Multas *actual = cola_multas->frente;

    while (actual != NULL) {
        printf("[%d] ", contador);
        mostrarmulta(actual);
        actual = actual->siguiente;
        contador++;
    }
}


void registrarmulta(Cola_multas *cola_multas, Lista_prestamos *listaPrestamos) {
    Multas *nuevaMulta = (Multas *)malloc(sizeof(Multas));
    int ID_prestamo;
    int opcion;

    // Código para llenar los datos de la multa
    printf("Ingrese ID del prestamo: \n");
    scanf("%d", &ID_prestamo);

    // Verificar si el préstamo existe
    Prestamo *prestamoEncontrado = buscarPrestamoPorID(listaPrestamos, ID_prestamo);
    if (prestamoEncontrado == NULL) {
        printf("No se encontro ningun prestamo con el ID %d.\n", ID_prestamo);
        free(nuevaMulta); // Liberar la memoria asignada antes de salir
        return;
    }

    nuevaMulta->ID_prestamo = ID_prestamo;
    printf("Seleccione el estado del libro:\n");
    printf("[1] Paso de tiempo\n");
    printf("[2] Mal estado\n");
    scanf("%d", &opcion);

    // Consumir el carácter de nueva línea en el búfer
    getchar();

    if (opcion == 1) {
        nuevaMulta->precioxdia = 20;  // Establecer precio por día como 20 pesos mexicanos

        // La fecha de devolución es establecida para 90 días (3 meses) en el pasado
        time_t ahora = time(NULL);
        struct tm *fechaDevolver = localtime(&ahora);
        fechaDevolver->tm_mday -= 90;  // Resta 90 días
        nuevaMulta->fecha_devolver = mktime(fechaDevolver);

        int diasAtraso = 0;
        if (ahora > nuevaMulta->fecha_devolver) {
            diasAtraso = (int)(ahora - nuevaMulta->fecha_devolver) / (24 * 60 * 60);
        }

        nuevaMulta->diasatraso = diasAtraso;
        nuevaMulta->monto = nuevaMulta->diasatraso * nuevaMulta->precioxdia;

        strcpy(nuevaMulta->razon, "Paso de tiempo"); 

        // Llamada a la función para imprimir la información
        printf("Fecha devolver: %s", ctime(&nuevaMulta->fecha_devolver));
        printf("Dias de atraso: %d\n", nuevaMulta->diasatraso);
        printf("Monto: %d\n", nuevaMulta->monto);
        printf("Ingrese el metodo de pago: ");
        scanf("%s", nuevaMulta->metododepago);
    } else if (opcion == 2) {

        strcpy(nuevaMulta->razon, "Mal estado"); 
        // Puedes definir el monto para el mal estado aquí, por ejemplo, 150 pesos
        nuevaMulta->monto = 150;

        printf("Monto: %d\n", nuevaMulta->monto);
        printf("Ingrese el metodo de pago: ");
        scanf("%s", nuevaMulta->metododepago);
    } else {
        printf("Opción no válida.\n");
        free(nuevaMulta); // Liberar la memoria asignada antes de salir
        return;
    }

    encolarfinal(cola_multas, nuevaMulta);
}


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
	puts("[5] Multas.");
	puts("[6] Notificaciones.");
	puts("[0] SALIR.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &opcion);
	return opcion;
}

//Función para manejar la gestión de la librería. 
int libreria(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_devoluciones **listaDevoluciones,ColaReservas **colaReservas, Cola_multas **cola_multas) {
    int op = 0;
    do {
        op = menuprincipal();

        switch (op) {
            case 0:
                puts("Saliendo...");
                system("pause");
                break;
            case 1:
              
                usuarios(listaUsuarios);
                break;
            case 2:
                libros(raizLibros);
                break;
			case 3:
    			transaccion(listaUsuarios, raizLibros, listaPrestamos, listaDevoluciones, colaReservas);
    			break;
    		case 4:
    			reserva(colaReservas);
				break;	
            case 5:
                 multas(&cola_multas, listaPrestamos);
                break;
            case 6:
                notificaciones(*listaPrestamos);
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

//Funcion para agregar Usuarios
void agregarUsuario(Lista_usuarios **listaUsuarios) {
    system("cls");
    Lista_usuarios *nuevoUsuario = (Lista_usuarios *)malloc(sizeof(Lista_usuarios));

    printf("Ingrese el ID del usuario: \n");
    scanf("%d", &nuevoUsuario->datos_usuario.ID_usuario);
    getchar();

    printf("Ingrese el nombre del usuario: \n");
    fgets(nuevoUsuario->datos_usuario.nombre, 50, stdin);
    nuevoUsuario->datos_usuario.nombre[strcspn(nuevoUsuario->datos_usuario.nombre, "\n")] = 0;

    printf("Ingrese el apellido del usuario: \n");
    fgets(nuevoUsuario->datos_usuario.apellido, 50, stdin);
    nuevoUsuario->datos_usuario.apellido[strcspn(nuevoUsuario->datos_usuario.apellido, "\n")] = 0;

    printf("Ingrese la edad del usuario: \n");
    scanf("%d", &nuevoUsuario->datos_usuario.edad);
    getchar(); 

    printf("Ingrese el telefono del usuario: \n");
    fgets(nuevoUsuario->datos_usuario.telefono, 20, stdin);
    nuevoUsuario->datos_usuario.telefono[strcspn(nuevoUsuario->datos_usuario.telefono, "\n")] = 0;

    printf("Ingrese la direccion del usuario: \n");
    fgets(nuevoUsuario->datos_usuario.direccion, 100, stdin);
    nuevoUsuario->datos_usuario.direccion[strcspn(nuevoUsuario->datos_usuario.direccion, "\n")] = 0;

    printf("Ingrese el codigo postal del usuario: \n");
    fgets(nuevoUsuario->datos_usuario.cp, 10, stdin);
    nuevoUsuario->datos_usuario.cp[strcspn(nuevoUsuario->datos_usuario.cp, "\n")] = 0;

    nuevoUsuario->sig = *listaUsuarios;
    *listaUsuarios = nuevoUsuario;

    printf("Usuario agregado con exito.\n");
}

// Función para eliminar un usuario por ID.
void eliminarUsuario(Lista_usuarios **listaUsuarios) {
    system("cls");
    int idUsuario;
    printf("Ingrese el ID del usuario a eliminar: \n");
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
    printf("Usuario eliminado con exito.\n");
    system("pause");
}

// Imprime la información del usuario.
void imprimirDatosUsuario(Usuario *usuario) {
    printf("ID: %d\nNombre: %s %s\nEdad: %d\nTelefono: %s\nDireccion: %s\nCodigo Postal: %s\n",
           usuario->ID_usuario,
           usuario->nombre,
           usuario->apellido,
           usuario->edad,
           usuario->telefono,
           usuario->direccion,
           usuario->cp);
}

// Función para mostrar los datos de un usuario especifico
void visualizarUsuario(Usuario usuario) {
    system("cls");
    printf("ID: %d\n", usuario.ID_usuario);
    printf("Nombre: %s\n", usuario.nombre);
    printf("Apellido: %s\n", usuario.apellido);
    printf("Edad: %d\n", usuario.edad);
    printf("Telefono: %s\n", usuario.telefono);
    printf("Direccion: %s\n", usuario.direccion);
    printf("Codigo Postal: %s\n", usuario.cp);
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
            printf("Seleccione la opcion de edicion:\n");
            printf("[1] Todos los datos\n");
            printf("[2] Dato especifico\n");
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
                while (getchar() != '\n');

                printf("Ingrese el nuevo telefono: ");
                fgets(actual->datos_usuario.telefono, sizeof(actual->datos_usuario.telefono), stdin);
                actual->datos_usuario.telefono[strcspn(actual->datos_usuario.telefono, "\n")] = 0;

                printf("Ingrese la nueva direccion: ");
                fgets(actual->datos_usuario.direccion, sizeof(actual->datos_usuario.direccion), stdin);
                actual->datos_usuario.direccion[strcspn(actual->datos_usuario.direccion, "\n")] = 0;

                printf("Ingrese el nuevo codigo postal: ");
                fgets(actual->datos_usuario.cp, sizeof(actual->datos_usuario.cp), stdin);
                actual->datos_usuario.cp[strcspn(actual->datos_usuario.cp, "\n")] = 0;
                
            } else if (opcionEdicion == 2) {
                int opcionCampo;
                printf("Seleccione el campo a editar:\n");
                printf("[1] Nombre\n");
                printf("[2] Apellido\n");
                printf("[3] Edad\n");
                printf("[4] Telefono\n");
                printf("[5] Direccion\n");
                printf("[6] Codigo Postal\n");

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
                        printf("Ingrese el nuevo telefono: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.telefono, nuevaInfo, sizeof(actual->datos_usuario.telefono) - 1);
                        break;
                    case 5:
                        printf("Ingrese la nueva direccion: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.direccion, nuevaInfo, sizeof(actual->datos_usuario.direccion) - 1);
                        break;
                    case 6:
                        printf("Ingrese el nuevo codigo postal: ");
                        fgets(nuevaInfo, sizeof(nuevaInfo), stdin);
                        nuevaInfo[strcspn(nuevaInfo, "\n")] = 0;
                        strncpy(actual->datos_usuario.cp, nuevaInfo, sizeof(actual->datos_usuario.cp) - 1);
                        break;
                    default:
                        printf("Opcion no valida.\n");
                        break;
                }
            } else {
                printf("Opción no valida.\n");
                return;
            }

            printf("Usuario editado con exito.\n");
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
	puts("[5] Mostrar todos los libros.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &op);
	return op;
}	

//Función para manejar la gestión de los libros.
int libros(NodoAVL **raiz) {
    int op = 0;
    Libros libro;
    char id_libro[5];

    do {
        op = menulibros();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal.");
                system("pause");
                break;
            case 1:
	                getchar(); 
	                printf("Ingrese el ID del libro: ");
	                fgets(libro.ID_libro, sizeof(libro.ID_libro), stdin);
	                libro.ID_libro[strcspn(libro.ID_libro, "\n")] = 0;
	
	                printf("Ingrese el titulo del libro: ");
	                fgets(libro.titulo, sizeof(libro.titulo), stdin);
	                libro.titulo[strcspn(libro.titulo, "\n")] = 0;
	
	                printf("Ingrese el autor del libro: ");
	                fgets(libro.autor, sizeof(libro.autor), stdin);
	                libro.autor[strcspn(libro.autor, "\n")] = 0;
	
	                printf("Ingrese la categoria del libro: ");
	                fgets(libro.categoria, sizeof(libro.categoria), stdin);
	                libro.categoria[strcspn(libro.categoria, "\n")] = 0;
	
	                printf("Ingrese la editorial del libro: ");
	                fgets(libro.editorial, sizeof(libro.editorial), stdin);
	                libro.editorial[strcspn(libro.editorial, "\n")] = 0;
	
	                printf("Ingrese el idioma del libro: ");
	                fgets(libro.idioma, sizeof(libro.idioma), stdin);
	                libro.idioma[strcspn(libro.idioma, "\n")] = 0;
	
	                printf("Ingrese el numero de paginas del libro: ");
	                scanf("%d", &libro.paginas);
	                getchar(); 
	
	                printf("Ingrese la descripcion del libro: ");
	                fgets(libro.descripcion, sizeof(libro.descripcion), stdin);
	                libro.descripcion[strcspn(libro.descripcion, "\n")] = 0;
	
	                printf("Ingrese la fecha de lanzamiento del libro (formato AAAA-MM-DD): ");
	                fgets(libro.fechalanzamiento, sizeof(libro.fechalanzamiento), stdin);
	                libro.fechalanzamiento[strcspn(libro.fechalanzamiento, "\n")] = 0;
	                
					printf("Ingrese la cantidad de copias del libro: ");
					scanf("%d", &libro.cantidad);
					getchar(); 

	                *raiz = agregarLibroAVL(*raiz, libro);
	                printf("Libro agregado exitosamente.\n");
	                system("pause");
	                break;
            case 2: // Eliminar libro
				    getchar(); // Limpiar buffer después de scanf
				    printf("Ingrese el ID del libro que desea eliminar: ");
				    fgets(id_libro, sizeof(id_libro), stdin);
				    id_libro[strcspn(id_libro, "\n")] = 0; // Remover salto de línea
				
				    *raiz = eliminarLibro(*raiz, id_libro);
				    printf("Libro eliminado (si existia).\n");
				    system("pause");
				    break;

            case 3: // Buscar libro
				    getchar(); // Limpiar buffer después de scanf
				    printf("Ingrese el ID del libro que desea buscar: ");
				    fgets(id_libro, sizeof(id_libro), stdin);
				    id_libro[strcspn(id_libro, "\n")] = 0; // Remover salto de línea
				
				    libroEncontrado = buscarLibro(*raiz, id_libro);
				    if (libroEncontrado == NULL) {
				        printf("Libro no encontrado.\n");
				    } // Si el libro se encuentra, mostrarLibro será llamado dentro de buscarLibro
				    system("pause");
				    break;
            case 4: // Editar libro
				    getchar(); // Limpiar el buffer del stdin
				    printf("Ingrese el ID del libro que desea editar: ");
				    fgets(id_libro, sizeof(id_libro), stdin);
				    id_libro[strcspn(id_libro, "\n")] = 0; // Remover el salto de línea al final
				
				    libroEncontrado = buscarLibro(*raiz, id_libro);
				    if (libroEncontrado != NULL) {
				        printf("Editar los datos del libro:\n");
				        
				        printf("Ingrese el nuevo título del libro: ");
				        fgets(libro.titulo, sizeof(libro.titulo), stdin);
				        libro.titulo[strcspn(libro.titulo, "\n")] = 0;
				
				        printf("Ingrese el nuevo autor del libro: \n");
				        fgets(libro.autor, sizeof(libro.autor), stdin);
				        libro.autor[strcspn(libro.autor, "\n")] = 0;
				
				        printf("Ingrese la nueva categoría del libro: \n");
				        fgets(libro.categoria, sizeof(libro.categoria), stdin);
				        libro.categoria[strcspn(libro.categoria, "\n")] = 0;
				
				        printf("Ingrese la nueva editorial del libro: ");
				        fgets(libro.editorial, sizeof(libro.editorial), stdin);
				        libro.editorial[strcspn(libro.editorial, "\n")] = 0;
				
				        printf("Ingrese el nuevo idioma del libro: \n");
				        fgets(libro.idioma, sizeof(libro.idioma), stdin);
				        libro.idioma[strcspn(libro.idioma, "\n")] = 0;
				
				        printf("Ingrese el nuevo numero de paginas del libro: \n");
				        scanf("%d", &libro.paginas);
				        getchar(); // Limpiar el buffer del stdin después de scanf
				
				        printf("Ingrese la nueva descripcion del libro: \n");
				        fgets(libro.descripcion, sizeof(libro.descripcion), stdin);
				        libro.descripcion[strcspn(libro.descripcion, "\n")] = 0;
				
				        printf("Ingrese la nueva fecha de lanzamiento del libro (formato AAAA-MM-DD): \n");
				        fgets(libro.fechalanzamiento, sizeof(libro.fechalanzamiento), stdin);
				        libro.fechalanzamiento[strcspn(libro.fechalanzamiento, "\n")] = 0;
				        
				        printf("Ingrese la nueva cantidad de libros: \n");
        				scanf("%d", &libro.cantidad);
        				getchar();
				
				        // Aquí asumimos que la función modificarLibro reemplaza el libro en el nodo encontrado
				        printf("\n");	
				        printf("DATOS ANTERIORES\n");
				        modificarLibro(*raiz, id_libro, libro);
				        printf("Libro modificado con éxito.\n");
				    } else {
				        printf("Libro con ID %s no encontrado.\n", id_libro);
				    }
				    system("pause");
				    break;
			case 5: // Mostrar todos los libros
				    system("cls");
				    printf("Listado de todos los libros:\n");
				    mostrarTodosLosLibros(*raiz);
				    system("pause");
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

int transaccion(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_devoluciones **listaDevoluciones, ColaReservas **colaReservas) {
    int op;
    do {
        op = menutransaccion();

        switch (op) {
        	case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.                  
                break;
            case 1:
                prestamo(listaUsuarios, raizLibros, listaPrestamos, colaReservas);
                break;
            case 2:
                devolucion(listaUsuarios, raizLibros, listaPrestamos, listaDevoluciones, colaReservas);
                break;
            default:
                puts("ERROR. Opcion desconocida.");
                system("pause");
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
	puts("[4] Buscar prestamo por ID.");
	puts("[0] Volver al menu de transaccion.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &opc);
	return opc;
}

int prestamo(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos,ColaReservas **colaReservas) {
    int opc;
    int ID_prestamo, ID_usuario;
    char ID_libro[5];

    do {
        opc = menuprestamos();

        switch (opc) {
        	case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.                  
                break;
            case 1: // Nuevo préstamo
			    printf("Ingrese el ID del prestamo: \n");
			    scanf("%d", &ID_prestamo);
			    if (buscarPrestamoPorID(*listaPrestamos, ID_prestamo) != NULL) {
        		printf("Ya existe un prestamo con el ID %d.\n", ID_prestamo);
        		system("pause");
        		return 0; // El préstamo ya existe
    				}
    			getchar();
			
			    printf("Ingrese el ID del usuario: \n");
			    scanf("%d", &ID_usuario);
			    getchar(); // Limpiar buffer
			
			    printf("Ingrese el ID del libro: \n");
			    fgets(ID_libro, sizeof(ID_libro), stdin);
			    ID_libro[strcspn(ID_libro, "\n")] = 0; // Eliminar newline
			
			    NodoAVL* libroEncontrado = buscarLibro(*raizLibros, ID_libro);
			    if (libroEncontrado != NULL && libroEncontrado->datos_libro.cantidad > 0) {
			        if (crearPrestamo(*listaUsuarios, *raizLibros, listaPrestamos, ID_prestamo, ID_usuario, ID_libro)) {
			            printf("Préstamo creado con exito.\n");
			        } else {
			            printf("No se pudo crear el prestamo.\n");
			        }
			    } else if (libroEncontrado != NULL && libroEncontrado->datos_libro.cantidad <= 0) {
			        char respuesta;
			        printf("El libro no esta disponible para prestamo. ¿Desea reservarlo? (S/N): \n");
			        scanf(" %c", &respuesta);
			        if (respuesta == 'S' || respuesta == 's') {
			            agregarReserva(colaReservas, ID_prestamo, ID_usuario, ID_libro);
			            printf("Reserva realizada con exito.\n");
			        } else {
			            printf("Reserva no realizada.\n");
			        }
			    } else {
			        printf("Libro no encontrado.\n");
			    }
			    system("pause");
			    break;

            case 2: // Mostrar todos los préstamos
    			system("cls");  // Limpia la pantalla para mostrar la lista de préstamos
    			printf("Listado de todos los prestamos:\n\n");
    
    			if (*listaPrestamos == NULL) {
        		printf("No hay prestamos registrados.\n");
   				 } else {
        		Lista_prestamos *actual = *listaPrestamos;
        			while (actual != NULL) {
		            printf("ID Prestamo: %d\n", actual->datos_prestamo.ID_prestamo);
		            printf("ID Usuario: %d\n", actual->datos_prestamo.ID_usuario);
		            printf("ID Libro: %s\n", actual->datos_prestamo.ID_libro);
		            printf("Fecha Pedido: ");
		            imprimirFecha(actual->datos_prestamo.fecha_pedido);  // Asegúrate de tener esta función definida
		            printf("\nFecha Devolucion: ");
		            imprimirFecha(actual->datos_prestamo.fecha_devolver);
		            printf("\n\n");
		            actual = actual->sig;
		       								 }
		    								}
		    		system("pause");  // Pausa para que el usuario pueda leer la información
		    		break;

            case 3: // Cancelar préstamo
			    printf("Ingrese el ID del prestamo a cancelar: ");
			    scanf("%d", &ID_prestamo);
			    eliminarPrestamo(listaPrestamos, raizLibros, ID_prestamo); // Asegúrate de pasar la raíz del árbol aquí
			    system("pause");
			    break;
			case 4: // Buscar préstamo por ID
                printf("Ingrese el ID del prestamo a mostrar: ");
                scanf("%d", &ID_prestamo);
                getchar(); // Limpiar buffer
                mostrarDetallesPrestamoPorID(*listaPrestamos, ID_prestamo);
                system("pause");
                break;
            default:
                printf("ERROR. Opción desconocida.\n");
                system("pause");
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
    puts("[3] Buscar devolucion por ID de devolucion.");  // Corregido para ser consistente
    puts("[0] Volver al menu principal.");
    printf("Ingrese una opcion: ");
    scanf("%d", &opo);
    return opo;
}

//Función para manejar la gestión de devoluciones.
//Función para manejar la gestión de devoluciones.
int devolucion(Lista_usuarios **listaUsuarios, NodoAVL **raizLibros, Lista_prestamos **listaPrestamos, Lista_devoluciones **listaDevoluciones, ColaReservas **colaReservas) {
    int opo, ID_devolucion;
    int ID_prestamo;

    do {
        opo = menudevolucion();

        switch (opo) {
        case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.                  
                break;
            case 1: // Registrar devolución
                printf("Ingrese el ID del prestamo a devolver: ");
                scanf("%d", &ID_prestamo);
                getchar();  // Limpiar buffer de entrada
                realizarDevolucion(listaUsuarios,listaPrestamos, raizLibros, listaDevoluciones, colaReservas, ID_prestamo);
                system("pause");
                break;
            case 2: // Mostrar todas las devoluciones
                mostrarTodasLasDevoluciones(*listaDevoluciones);
                system("pause");
                break;
            case 3: // Buscar devolución por ID de devolución
			    printf("Ingrese el ID de la devolucion a buscar: ");
			    scanf("%d", &ID_devolucion);
			    getchar();  // Limpiar buffer de entrada
			    mostrarDetallesDevolucionPorID(*listaDevoluciones, ID_devolucion);
			    system("pause");
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
	puts("[1] Libros reservados.");
	puts("[0] Volver al menu principal.\n");
	printf("Ingrese una opcion: ");
	scanf("%d", &op);
	return op;
}

//Función para manejar la gestión de reservas.
int reserva(ColaReservas **colaReservas){
    int op = 0;
    do {
        op = menureserva();

        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.                  
                break;
            case 1:
            	mostrarReservas(*colaReservas);
            	system("pause");
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
    printf("Ingrese una opcion: ");
    scanf("%d", &op);
    return op;
}

//FFunción para manejar la gestión de multas.
int multas(Cola_multas *cola_multas, Lista_prestamos **listaPrestamos){
    iniciarcoladoble(cola_multas);
    int op = 0;
    do {
        op = menumultas();
        switch (op) {
            case 0:
                puts("Volviendo al menu principal."); //regresando al menú principal.
                system("pause"); //pausa para permitir al usuario leer el mensaje.          
                break;
            case 1:
                registrarmulta(cola_multas, *listaPrestamos);
                system("pause");
                break;
            case 2:
                // Mostrar todas las multas numeradas
                multanumero(cola_multas);
                system("pause");
                break;
            case 3:
                // Pagar multa
                {
                    if (!coladoble(cola_multas)) {
                        // Mostrar todas las multas numeradas
                        multanumero(cola_multas);

                        // Solicitar al usuario seleccionar una multa para pagar
                        int seleccion;
                        printf("Seleccione la multa que desea pagar (ingrese el numero): \n");
                        scanf("%d", &seleccion);

                        // Desencolar la multa seleccionada
                        Multas *multaPagar = NULL;
                        if (seleccion >= 1) {
                            multaPagar = desencolarfrente(cola_multas);
                            for (int i = 1; i < seleccion && multaPagar != NULL; i++) {
                                encolarfinal(cola_multas, multaPagar);
                                multaPagar = desencolarfrente(cola_multas);
                            }
                        }

                        // Procesar el pago de la multa
                        if (multaPagar != NULL) {
                            printf("Multa pagada con exito.\n");
                            free(multaPagar); // Liberar memoria de la multa pagada
                        } else {
                            printf("Seleccion invalida o no hay multas pendientes.\n");
                        }
                    } else {
                        printf("No hay multas pendientes.\n");
                    }
                }
                system("pause");
                break;
            default:
                puts("ERROR. Opcion desconocida."); // Opción desconocida.
                system("pause"); // Pausa para permitir al usuario leer el mensaje de error.
                break;
        }
    } while (op != 0);
 
      return 0;
}

//LIMPIEZA 

void notificaciones(Lista_prestamos *listaPrestamos) {
    time_t now;
    time(&now);

    printf("\nNotificaciones de Préstamos:\n");
    while (listaPrestamos != NULL) {
        int diasRestantes = difDias(now, listaPrestamos->datos_prestamo.fecha_devolver);
        if (diasRestantes >= 0) {
            printf("ID Préstamo: %d - Días restantes para devolución: %d\n",
                   listaPrestamos->datos_prestamo.ID_prestamo, diasRestantes);
        }
        
        listaPrestamos = listaPrestamos->sig;
    }
    system("pause");
}

int difDias(time_t fecha1, time_t fecha2) {
    return (int)difftime(fecha2, fecha1) / (60 * 60 * 24);
}

void liberarMemoriaListaUsuarios(Lista_usuarios *lista) {
    while (lista != NULL) {
        Lista_usuarios *temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

void liberarMemoriaArbol(NodoAVL *raiz) {
    if (raiz != NULL) {
        liberarMemoriaArbol(raiz->izquierda);
        liberarMemoriaArbol(raiz->derecha);
        free(raiz);
    }
}

void liberarMemoriaListaPrestamos(Lista_prestamos *lista) {
    while (lista != NULL) {
        Lista_prestamos *temp = lista;
        lista = lista->sig;
        free(temp);
    }
}
void liberarMemoriaListaDevoluciones(Lista_devoluciones *lista) {
    while (lista != NULL) {
        Lista_devoluciones *temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

void liberarMemoriaColaReservas(ColaReservas *cola) {
    Reserva *actual = cola->inicio;
    while (actual != NULL) {
        Reserva *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(cola);
}
// Liberar la memoria de todas las multas en la cola doble
void liberarmemoriamulta(Cola_multas *cola_multas) {
    while (!coladoble(cola_multas)) {
        Multas *multa = desencolarfrente(cola_multas);
        free(multa);
    }
}

int main() {
    // Inicializar todas las estructuras de datos
    Lista_usuarios *listaUsuarios = NULL;
    NodoAVL *raizLibros = NULL;
    Lista_prestamos *listaPrestamos = NULL;
    Lista_devoluciones *listaDevoluciones = NULL;
    Cola_multas *cola_multas = (Cola_multas *)malloc(sizeof(Cola_multas));
    cola_multas->frente = NULL;
    cola_multas->final = NULL;
    ColaReservas *colaReservas = (ColaReservas *)malloc(sizeof(ColaReservas));

    if (colaReservas == NULL) {
        // Manejo de error de asignación de memoria para colaReservas
        printf("Error al asignar memoria para cola de reservas.\n");
        return 1;
    }
    colaReservas->inicio = colaReservas->final = NULL;

    // Inicializar datos estáticos o cargar datos de archivos, base de datos, etc.
    inicializarDatosEstaticos(&listaUsuarios, &raizLibros);

    // Llamar al menú principal de la aplicación
   libreria(&listaUsuarios, &raizLibros, &listaPrestamos, &listaDevoluciones , &colaReservas, &cola_multas); 

    // Liberar todas las estructuras de datos antes de terminar el programa
    liberarMemoriaListaUsuarios(listaUsuarios);
    liberarMemoriaArbol(raizLibros);
    liberarMemoriaListaPrestamos(listaPrestamos);
    liberarMemoriaListaDevoluciones(listaDevoluciones);
    liberarMemoriaColaReservas(colaReservas);
    liberarmemoriamulta(cola_multas);

    // Ya que colaReservas fue asignada con malloc, se libera al final
    free(colaReservas);

    return 0;
}