#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../ascii/ascii.h"

#define NAME_MAX 30

#define IMPRIMIR_FIN flags.flag.bit0
#define TACHAR_FIN flags.flag.bit1
#define ELIMINAR_FIN flags.flag.bit2

union {
    struct {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
    }flag;

    uint8_t byte;
}flags;

typedef struct product {
    char name[NAME_MAX];
    uint8_t cant;
    struct product *next;
}product_t;

typedef enum {
    AGREGAR = 1,
    IMPRIMIR,
    TACHAR,
    ELIMINAR,
    FIN
}menuState_t;

void welcome(void);
void menu(menuState_t *);
void addProduct(void);
void printList(void);
void delProduct(void);
void freeMemory(void);
void delList(void);

product_t *list = NULL;



int main() {
    menuState_t menuState;

    welcome();
    do { menu(&menuState); } while(menuState != FIN);
    if(list != NULL) freeMemory();

    return 0;
}

void welcome() {
    printf("Bienvenido al programa\n");
    printf(
        "Este c%cdigo realiza la funci%cn de una lista de compras\n",
        oACENTO,
        oACENTO
    );
}

void menu(menuState_t *menuState) {
    printf("\n     -----   MENU   -----\n\n");
    printf(
        "Opci%cn %u: Agrega un producto al inicio de la lista (nombre y cantidad)\n",
        oACENTO,
        AGREGAR
    );
    printf(
        "Opci%cn %u: Anota todos los productos de la lista\n",
        oACENTO,
        IMPRIMIR
    );
    printf(
        "Opci%cn %u: Tacha un producto de la lista\n",
        oACENTO,
        TACHAR
    );
    printf(
        "Opci%cn %u: Elimina todos los productos de la lista\n",
        oACENTO,
        ELIMINAR
    );
    printf(
        "Opci%cn %u: Finaliza el c%cdigo\n\n",
        oACENTO,
        FIN,
        oACENTO
    );
    printf("Selecciona una opci%cn: ", oACENTO);
    scanf(" %u", menuState);
    printf("\n");

    switch (*menuState) {
    case AGREGAR:
        addProduct();
        break;

    case IMPRIMIR:
        printList();
        break;

    case TACHAR:
        delProduct();
        break;

    case ELIMINAR:
        delList();
        break;

    case FIN:
        printf("%cHasta luego!", EXCLAMACION);

        break;

    default:
        printf("La opci%cn elegida no existe. Inserte otra opci%cn\n", oACENTO, oACENTO);
        printf("Ser%c redirigido al men%c\n", aACENTO, uACENTO);

        break;
    }
}

void addProduct() {
    product_t *newProduct;
    newProduct = malloc(sizeof(product_t));

    printf("Anote el nombre del producto: ");
    scanf(" %[^\n]%*c", newProduct->name);

    printf("Anote la cantidad a comprar: ");
    scanf(" %hhu", &newProduct->cant);

    newProduct->next = list;
    list = newProduct;

    printf(
        "\nEl producto '%s' fue a%cadido\n",
        newProduct->name,
        nTILDE
    );
}

void printList() {
    IMPRIMIR_FIN = 0;

    if(list == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    product_t *iProduct;
    iProduct = list;

    printf("LISTA:\n");

    while(!IMPRIMIR_FIN) {
        printf("Producto: %s\n", iProduct->name);
        printf("Cantidad: %d\n", iProduct->cant);

        iProduct = iProduct->next;

        if(iProduct == NULL) IMPRIMIR_FIN = 1;
        else printf("\n");
    }
}

void delProduct() {
    TACHAR_FIN = 0;

    if(list == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    char search[NAME_MAX];
    product_t *iProduct, *beforeProduct;
    iProduct = list;
    beforeProduct = NULL;

    printf(
        "%cQu%c producto quiere tachar?: ",
        INTERROGACION,
        eACENTO
    );
    scanf(" %[^\n]%*c", search);
    printf("\n");

    while(!TACHAR_FIN) {
        if(strcmp(iProduct->name, search)) {
            beforeProduct = iProduct;
            iProduct = iProduct->next;

            if(iProduct != NULL) continue;

            printf("No se encontr%c el producto\n", oACENTO);
            return;
        } else {
            if(iProduct == list) list = iProduct->next;
            if(beforeProduct != NULL) beforeProduct->next = iProduct->next;

            printf("El producto '%s' ha sido tachado\n", iProduct->name);
            free(iProduct);

            TACHAR_FIN = 1;
        }
    }
}

void delList() {
    if(list == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    freeMemory();
    printf("La lista ha sido eliminada\n");
}

void freeMemory() {
    ELIMINAR_FIN = 0;

    while(!ELIMINAR_FIN) {
        product_t *delProduct;
        delProduct = list;
        list = delProduct->next;

        free(delProduct);

        if(list == NULL) ELIMINAR_FIN = 1;
    }
}