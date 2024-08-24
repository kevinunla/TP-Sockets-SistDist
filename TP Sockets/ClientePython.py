import socket
def main():
    host = '127.0.0.1' # ip
    port = 8080 #puerto
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((host, port)) #Abrir conexion
        print("1. Generar nombre de usuario")
        print("2. Generar contraseña")
        opcion = int(input("Elija una opción: "))
        if (opcion==1 or opcion==2):
            longitud = int(input("Ingrese la longitud deseada: "))
            client_socket.sendall(opcion.to_bytes(4, byteorder='little'))  # Enviar la opción (4 bytes)
            client_socket.sendall(longitud.to_bytes(4, byteorder='little'))  # Enviar la longitud (4 bytes)
            respuesta = client_socket.recv(1024).decode()
            print(f"Respuesta del servidor: {respuesta}")
    except ConnectionRefusedError:
        print("No se pudo conectar al servidor.")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close() #Cerrar Conexion
if __name__ == "__main__":
    main()