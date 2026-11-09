#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    char buffer[1000];
    char msg[1000];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);
    printf("Enter a msg :\n");
    fgets(msg,sizeof(msg),stdin);
    sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&server, sizeof(server));
    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server, &len);
    if (n > 0)
    {
        buffer[n] = '\0';
        printf("\nFrom Server :%s", buffer);
    }
    close(sock);
    return 0;
}
