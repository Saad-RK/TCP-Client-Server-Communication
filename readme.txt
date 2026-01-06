A. Setup Instructions:

1.Open Dev-C++.

2. Open server.cpp and client.cpp files separately.

3. Go to: Tools → Compiler Options → Parameters → Linker

4. Add the following line: -lws2_32

5. Click OK.

Now compile both client.cpp and server.cpp if exe files do not work.


B. How to Run?

Run server.cpp/exe first.
The server will display:
"Server is waiting for client connection..."

Run client.cpp/exe in a new console window.
The client will display:
"Connected to server."

Enter a message in the client console.

The server will display the received message.

The client will receive the response:
"Message received"

To stop communication, type:
exit