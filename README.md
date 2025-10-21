Explicacíon:

Hay dos programas principales:
El Servidor (server): Es el jefe de la operación. Lo dejas corriendo y se queda esperando a que la gente se conecte.
El Cliente (client): Es el programa que usa cada persona para unirse al chat, escribir y ver los mensajes.
La gracia está en que el servidor puede atender a un montón de clientes a la vez sin hacerse un lío.

Abre una terminal en la carpeta donde tienes los archivos.
Compila todo con estos dos comandos (primero uno, y luego el otro):
code
Bash
cmake .
make

En la Terminal 1, arranca el servidor:
code
Bash
./server

Verás un mensaje que dice que está "escuchando". Déjalo ahí tranquilamente.
En la Terminal 2, conecta un cliente:
code
Bash
./client

¡Y ya está! Escribe algo y pulsa Enter. Verás la respuesta del servidor. Puedes abrir más terminales y conectar más clientes para ver cómo hablan todos a la vez.
Para salir, escribe exit en cada ventana de cliente. Para parar el servidor, ve a su terminal y pulsa Ctrl + C.

server.cpp: La lógica del programa servidor.
client.cpp: La lógica del programa cliente.
utils.h y utils.cpp: Son unos archivos de ayuda que nos ha dado el profe para no tener que programar desde cero toda la parte complicada de las conexiones de red. ¡Un detallazo!
CMakeLists.txt: Las instrucciones para que cmake y make sepan cómo compilar todo.
