#include <iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")   // Link WinSock library

int main() {
    WSADATA wsa;                     // Structure for WinSock information
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrSize;
    char buffer[1024];

    // Initialize WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);      // Fixed port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket with IP and port
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Start listening for client request
    listen(serverSocket, 1);
    cout << "Server is waiting for client connection..." << endl;

    addrSize = sizeof(clientAddr);

    // Accept client connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    cout << "Client connected successfully." << endl;

    // Loop to receive multiple messages from client
    while (true) {
        memset(buffer, 0, sizeof(buffer));  // Clear buffer before receiving data

        recv(clientSocket, buffer, sizeof(buffer), 0);
        // If client types "exit", end communication
        if (strcmp(buffer, "exit") == 0) {
            cout << "Client ended the connection." << endl;
            break;
        }
        
        // Display received message
        cout << "Message received from client: " << buffer << endl;
        // Send confirmation response to client
        char response[] = "Message received";
        send(clientSocket, response, strlen(response), 0);
    }

    // Close sockets and clean up
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    // Keep server console open
    cout << "\nPress any key to close server...";
    cin.get();
    return 0;
}
