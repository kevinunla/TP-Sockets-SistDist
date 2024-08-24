#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <unistd.h>
#define PORT 8080
#define MAX_CLIENTS 5
using namespace std;
int es_vocal(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
void generar_nombre_usuario(char *nombre, int longitud) {
    char vocales[] = "aeiou";
    char consonantes[] = "bcdfghjklmnpqrstvwxyz";
    int empieza_vocal = rand() % 2;
    for (int i = 0; i < longitud; i++) {
        if ((i % 2 == 0 && empieza_vocal) || (i % 2 != 0 && !empieza_vocal)) {
            nombre[i] = vocales[rand() % 5];
        } else {
            nombre[i] = consonantes[rand() % 21];
        }
    }
    nombre[longitud] = '\0';
}
void generar_contrasena(char *contrasena, int longitud) {
    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < longitud; i++) {
        contrasena[i] = caracteres[rand() % 62];
    }
    contrasena[longitud] = '\0';
}
void manejar_cliente(SOCKET client_socket) {
    int opcion, longitud;
    recv(client_socket, (char*)&opcion, sizeof(opcion), 0);
    recv(client_socket, (char*)&longitud, sizeof(longitud), 0);
    if (opcion == 1) {
        if (longitud < 5 || longitud > 15) {
            char *mensaje_error = "Error: La longitud del nombre de usuario debe ser entre 5 y 15.\n";
            send(client_socket, mensaje_error, strlen(mensaje_error), 0);
        } else {
            char nombre[16];
            generar_nombre_usuario(nombre, longitud);
            send(client_socket, nombre, strlen(nombre), 0);
        }
    } else if (opcion == 2) {
        if (longitud < 8 || longitud >= 50) {
            char *mensaje_error = "Error: La longitud de la contrasena debe ser entre 8 y 49.\n";
            send(client_socket, mensaje_error, strlen(mensaje_error), 0);
        } else {
            char contrasena[50];
            generar_contrasena(contrasena, longitud);
            send(client_socket, contrasena, strlen(contrasena), 0);
        }
    }
}
int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_size;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error al inicializar Winsock.\n");
        exit(EXIT_FAILURE);
    }
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Error al crear el socket.\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Error al enlazar el socket.\n");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Error al escuchar.\n");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    printf("Servidor escuchando en el puerto %d...\n", PORT);
    srand(time(NULL));
    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket == INVALID_SOCKET) {
            printf("Error al aceptar la conexión.\n");
            continue;
        }
        printf("Cliente conectado.\n");
        manejar_cliente(client_socket);
        closesocket(client_socket);
        printf("Cliente desconectado.\n");
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
