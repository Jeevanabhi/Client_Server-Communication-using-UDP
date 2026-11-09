#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

int main()
{
    int server_fd;
    char buffer[1000];
    char result[1000] = "";
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    printf("UDP Server is Listening \n");
    int n = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client, &len);
    buffer[n]='\0';
    printf("Recieved text : %s",buffer);
    for (int i = 0; buffer[i]; i++)
    {
        buffer[i] = tolower((unsigned char)buffer[i]);
    }
    char *word = strtok(buffer, " \n");
    while(word!=NULL){
        if (strcmp(word, "tbh") == 0)
            strcat(result, "to be honest ");
        else if (strcmp(word, "rn") == 0)
            strcat(result, "right now ");
        else if (strcmp(word, "idk") == 0)
            strcat(result, "I do not know ");
        else
        {
            strcat(result, word);
            strcat(result, " ");
        }

        word = strtok(NULL, " \n");
    }
    printf("Translated Text : %s",result);
    sendto(server_fd,result,strlen(result),0,(struct sockaddr*)&client,len);
    close(server_fd);
    return 0;
    
}

