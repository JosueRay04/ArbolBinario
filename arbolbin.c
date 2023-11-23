#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int dato;
    struct TreeNode *izquierda;
    struct TreeNode *derecha;
    int nodeId;
};
// Variable int para contar los nodos del programa
int nodeIdCounter = 1; 
void AsignarID_Nodo(struct TreeNode *raiz) {
    // Esta funcion le otorga un id a cada nodo
    if (raiz != NULL) {
        raiz->nodeId = nodeIdCounter++;
        
        AsignarID_Nodo(raiz->izquierda);
        AsignarID_Nodo(raiz->derecha);
    }
}

struct TreeNode *crearNodo(int valor) {
    // Crear nuevo nodo
    struct TreeNode *nuevoNodo = (struct TreeNode *)malloc(sizeof(struct TreeNode));

    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;

    return nuevoNodo;
}

// Insertar nuevo nodo
struct TreeNode *insertar(struct TreeNode *raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }

    if (valor < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        raiz->derecha = insertar(raiz->derecha, valor);
    }

    return raiz;
}

void agregarDato(struct TreeNode **raiz) {
    //agergar dato
    int valor;
    
    char eleccion;

    do {
        printf("Ingrese un valor: ");
        scanf("%d", &valor);

        *raiz = insertar(*raiz, valor);

        printf("¿Agregar otro dato? (s/n): ");
        scanf(" %c", &eleccion);

    } while (eleccion == 's' || eleccion == 'S');

}

// Display inorden
void mostrar(struct TreeNode *raiz) {

    if (raiz != NULL) {
        mostrar(raiz->izquierda);
        printf("%d ", raiz->dato);
        mostrar(raiz->derecha);
    }

}

// Busqueda
struct TreeNode *busqueda(struct TreeNode *raiz, int valor) {
    if (raiz == NULL || raiz->dato == valor) {
        return raiz;
    }

    if (valor < raiz->dato) {
        return busqueda(raiz->izquierda, valor);

    } else {
        return busqueda(raiz->derecha, valor);

    }
}

//hacer la verificacion de que exista un nodo
int verificar(struct TreeNode *raiz) {
    if (raiz == NULL) {
        return 1; 
    }

    if ((raiz->izquierda != NULL && raiz->dato < raiz->izquierda->dato) ||
        (raiz->derecha != NULL && raiz->dato > raiz->derecha->dato)) {

        return 0; 

    }

    if (!verificar(raiz->izquierda) || !verificar(raiz->derecha)) {
        return 0;

    }
    return 1;
}

int main() {

    struct TreeNode *raiz = NULL;
    int caso = 1;

    printf("selecciona una opcion.\n");
    printf("1.-Caso con ejemplo de error con la verificacion.\n");
    printf("2.-Caso normal para probar el arbol en inorden.\n");
    scanf("%d", &caso);

    if (caso == 1){
    //Caso para comprobar la verificacion
    raiz = insertar(raiz, 5);
    insertar(raiz, 3);
    insertar(raiz, 2);
    insertar(raiz, 4);
    insertar(raiz, 7);
    insertar(raiz, 6);
    insertar(raiz, 8);

    raiz->izquierda->izquierda->dato = 9; 

    if (verificar(raiz)) {
        printf("El arbol binario de busqueda es valido.\n");

    } else {
        printf("El arbol binario de busqueda no es valido\n");
        
    }

    } else if (caso == 2){

    //Caso normal
    printf("Ingrese valores para agregar al arbol (Ingrese 'n' para terminar):\n");
    agregarDato(&raiz);

    printf("arbol de búsqueda binaria resultante: ");
    mostrar(raiz);
    printf("\n");

    AsignarID_Nodo(raiz);

    printf("Introduce el valor a busqueda: ");
    int valorBuscado;
    scanf("%d", &valorBuscado);

    struct TreeNode *nodoResultado = busqueda(raiz, valorBuscado);
    if (nodoResultado != NULL) {
        printf("%d encontrado en el nodo %d.\n", valorBuscado, nodoResultado->nodeId);

        if (nodoResultado->izquierda != NULL) {
            printf("Nodo izquierdo: %d\n", nodoResultado->izquierda->nodeId);
        } else {
            printf("No hay nodo izquierdo.\n");
        }

        if (nodoResultado->derecha != NULL) {
            printf("Nodo derecho: %d\n", nodoResultado->derecha->nodeId);
        } else {
            printf("No hay nodo derecho.\n");
        }
    } else {
        printf("%d no encontrado en el arbol.\n", valorBuscado);
    }
    }

    return 0;
}
