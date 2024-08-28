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
int main() {
    f:
    fflush(stdin);
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    int opcion, longitud;
    bool flag=true;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error al inicializar Winsock.\n");
        exit(EXIT_FAILURE);
    }
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Error al crear el socket.\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error al conectar con el servidor.\n");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    while(flag){
        printf("Elija una opcion:\n");
        printf("1. Generar nombre de usuario\n");
        printf("2. Generar contrasena\n");
        printf("3. Salir\n");
        scanf("%d", &opcion);
        if(opcion==1){
                printf("Ingrese la longitud deseada: ");
                scanf("%d", &longitud);
                send(client_socket, (char*)&opcion, sizeof(opcion), 0);
                send(client_socket, (char*)&longitud, sizeof(longitud), 0);
                recv(client_socket, buffer, sizeof(buffer), 0);
                printf("Respuesta del servidor: %s\n", buffer);
                goto f;
        }else if(opcion==2){
                printf("Ingrese la longitud deseada: ");
                scanf("%d", &longitud);
                send(client_socket, (char*)&opcion, sizeof(opcion), 0);
                send(client_socket, (char*)&longitud, sizeof(longitud), 0);
                recv(client_socket, buffer, sizeof(buffer), 0);
                printf("Respuesta del servidor: %s\n", buffer);
                goto f;
        }else if(opcion==3){
                flag=false;
        }else{
                printf("Opcion no valida.\n");
    }}
    closesocket(client_socket);
    WSACleanup();
    return 0;
}
