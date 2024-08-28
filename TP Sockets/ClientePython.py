import socket
PORT = 8080
def main():
    flag=True
    while True:
        try:
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_addr = ('127.0.0.1', PORT)
            client_socket.connect(server_addr)
            while flag:
                print("Elija una opcion:")
                print("1. Generar nombre de usuario")
                print("2. Generar contrasena")
                print("3. Salir")
                opcion = int(input())
                if opcion in [1, 2]:
                    longitud = int(input("Ingrese la longitud deseada: "))
                    client_socket.sendall(opcion.to_bytes(4, 'little'))
                    client_socket.sendall(longitud.to_bytes(4, 'little'))
                    buffer = client_socket.recv(1024).decode()
                    print(f"Respuesta del servidor: {buffer}")
                    client_socket.close()
                    flag=False
                    main()
                elif opcion == 3:
                    break
                else:
                    print("Opcion no valida.")
            client_socket.close()
            break
        except socket.error as e:
            print(f"Error al conectar con el servidor: {e}")
            client_socket.close()
            break
if __name__ == "__main__":
    main()