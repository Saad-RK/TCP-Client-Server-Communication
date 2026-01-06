#include <iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")   // Link WinSock library

int main() {
    WSADATA wsa;                     // Structure for WinSock initialization
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Initialize WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Set server IP address and port number
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);               // Same port as server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

    // Connect to server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    cout << "Connected to server.\n";
    cout << "Type 'exit' to stop.\n\n";

    // Loop to send multiple messages to server
    while (true) {
        memset(buffer, 0, sizeof(buffer));  // Clear buffer

        // Take message input from user
        cout << "Enter message: ";
        cin.getline(buffer, 1024);

        // Send message to server
        send(clientSocket, buffer, strlen(buffer), 0);

        // If user types "exit", end communication
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Receive response from server
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        cout << "Server response: " << buffer << endl << endl;
    }

    // Close socket and cleanup
    closesocket(clientSocket);
    WSACleanup();

    // Keep client console open
    cout << "\nPress any key to close client...";
    cin.get();

    return 0;
}

