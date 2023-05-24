#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>

#define BUFFER_SIZE 1024
#define REQUEST_SIZE 8

void generate_random_numbers(int* buffer, int n);

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in server_addr;
    srand(time(NULL));

    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Send a request to the server
    int request[REQUEST_SIZE];

    for(;;){
        generate_random_numbers(request, REQUEST_SIZE);
        write(sockfd, request, sizeof (request));
        printf("Send packet\n");
        sleep(1);
    }

    close(sockfd);

    return 0;
}

void generate_random_numbers(int* buffer, int n){
    for(int i=0;i<n;i++){
        buffer[i] = rand() % 9;
    }
}
