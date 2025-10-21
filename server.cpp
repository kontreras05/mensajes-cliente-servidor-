#include "utils.h"
#include <iostream>
#include <vector>
#include <string>

// Declaramos la función que manejará a cada cliente. La definiremos más adelante.
void manejarCliente(int clientID) {
    bool conectado = true;
    while (conectado) {
        // 1. Comprobar si hemos recibido un mensaje de este cliente.
        // checkPendingMessages() nos dice si hay algo en el buffer de entrada.
        if (checkPendingMessages(clientID)) {
            std::vector<char> data;
            // Obtenemos el mensaje con getMSG().
            getMSG(clientID, data);

            // Si el mensaje está vacío, puede que el cliente se haya desconectado de forma abrupta.
            if (data.empty()) {
                conectado = false;
                continue;
            }

            // Convertimos el mensaje a un string para poder mostrarlo.
            std::string msg(data.begin(), data.end());
            std::cout << "Mensaje del cliente " << clientID << ": " << msg << std::endl;

            // 2. Preparamos y enviamos una respuesta al cliente.
            std::string response_str = "Servidor: mensaje recibido correctamente.";
            std::vector<char> response(response_str.begin(), response_str.end());
            sendMSG(clientID, response);
        }
    }

    // 3. El bucle ha terminado, así que el cliente se ha desconectado.
    std::cout << "Cliente " << clientID << " se ha desconectado." << std::endl;
    closeConnection(clientID);
}

int main() {
    // 1. Inicializar el servidor en el puerto 5000
    // La función initServer() viene de utils.cpp y nos prepara todo lo necesario.
    int server_fd = initServer(5000);
    std::cout << "Servidor escuchando en el puerto 5000..." << std::endl;

    // 2. Bucle infinito para aceptar clientes
    // El servidor nunca debe parar de escuchar, por eso usamos un bucle infinito.
    while (true) {
        // La función checkClient() de utils.cpp nos dice si hay un nuevo cliente esperando.
        if (checkClient()) {
            // Si hay un cliente, obtenemos su ID único con getLastClientID().
            int clientID = getLastClientID();
            std::cout << "Nuevo cliente conectado con ID: " << clientID << std::endl;
            
            // ¡Aquí está la magia de la concurrencia!
            // Creamos un hilo nuevo que ejecutará la función manejarCliente.
            // Le pasamos el ID del cliente para que ese hilo sepa a quién atender.
            // .detach() hace que el hilo se ejecute en segundo plano y no tengamos que esperar a que termine.
            std::thread(manejarCliente, clientID).detach();
        }
    }

    // El código nunca llegará aquí, pero es una buena práctica cerrar el socket.
    close(server_fd);

    return 0;
}