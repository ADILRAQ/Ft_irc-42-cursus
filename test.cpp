#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

const char* API_HOST = "api.weatherapi.com";
const char* API_PATH = "/v1/current.json";
const char* API_KEY = "3240efe1d82a44d798b123556231811";  // Replace with your OpenWeatherMap API key

int main() {
    const char* cityName = "tetouan";

    // Resolve the host name to an IP address
    struct hostent* host = gethostbyname(API_HOST);
    if (!host) {
        cerr << "Error: Unable to resolve host" << endl;
        return 1;
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cerr << "Error: Unable to create socket" << endl;
        return 1;
    }

    // Fill in the sockaddr_in structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // HTTP port
    memcpy(&server.sin_addr, host->h_addr, host->h_length);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        cerr << "Error: Unable to connect to the server" << endl;
        close(sock);
        return 1;
    }

    // Construct the HTTP request
    ostringstream request;
    request << "GET " << API_PATH << "?key=" << API_KEY << "&q=" << cityName << " HTTP/1.1\r\n";
    request << "Host: " << API_HOST << "\r\n";
    request << "Connection: close\r\n\r\n";

    const string& requestStr = request.str();
    if (send(sock, requestStr.c_str(), requestStr.length(), 0) == -1) {
        cerr << "Error: Unable to send request" << endl;
        close(sock);
        return 1;
    }

    // Receive and print the response
    char buffer[4096];
    int bytesRead;
    while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        cout << buffer;
    }

    // Close the socket
    close(sock);

    return 0;
}
