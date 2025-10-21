#include "utils.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    // 1. Conectarse al servidor.
    // Usamos la IP "127.0.0.1" (que significa "este mismo ordenador") y el puerto 5000.
    connection_t connection = initClient("127.0.0.1", 5000);

    // 2. Comprobar si la conexión funcionó.
    // Si el socket es -1, significa que hubo un error.
    if (connection.socket == -1) {
        std::cout << "No se pudo conectar al servidor." << std::endl;
        return 1; // Termina el programa con un código de error.
    }

    std::cout << "Conectado al servidor. Escribe 'exit' para salir." << std::endl;

    // 3. Bucle para enviar y recibir mensajes.
    std::string line;
    while (std::getline(std::cin, line)) { // Lee una línea de lo que escribe el usuario.
        if (line == "exit") {
            break; // Si el usuario escribe "exit", salimos del bucle.
        }

        // Convertimos el string a un vector de caracteres para poder enviarlo con nuestras funciones.
        std::vector<char> msg(line.begin(), line.end());
        
        // Enviamos el mensaje al servidor.
        sendMSG(connection.serverId, msg);

        // Esperamos una respuesta del servidor.
        if(checkPendingMessages(connection.serverId)){
            std::vector<char> response;
            getMSG(connection.serverId, response);
            std::string response_str(response.begin(), response.end());
            std::cout << response_str << std::endl;
        }
    }

    // 4. Cerrar la conexión.
    closeConnection(connection.serverId);
    std::cout << "Conexión cerrada." << std::endl;

    return 0;
}