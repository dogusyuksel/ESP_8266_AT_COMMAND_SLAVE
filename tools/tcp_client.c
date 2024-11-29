#include <arpa/inet.h>
#include <fcntl.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "cJSON.h"

#define BUF_SIZE    256

void chat(int sockfd)
{
    char buff[BUF_SIZE];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

char * reconstruct_config(char *IP, uint16_t port)
{
    char *string = NULL;
    cJSON *reconstructed_conf_cjson = cJSON_CreateObject();

    if (cJSON_AddStringToObject(reconstructed_conf_cjson, "IP", IP) == NULL) {
        goto end;
    }
    if (cJSON_AddNumberToObject(reconstructed_conf_cjson, "PORT", port) == NULL) {
        goto end;
    }

    string = cJSON_Print(reconstructed_conf_cjson);
    if (string == NULL) {
        fprintf(stderr, "Failed to print reconstructed_conf_cjson.\n");
    }

end:
    cJSON_Delete(reconstructed_conf_cjson);
    return string;
}

void reconstruct_config_check(char *IP, uint16_t port)
{
    char *str = reconstruct_config(IP, port);

    if (str) {
        printf("--> %s\n", str);
        free(str);
    } else {
        fprintf(stderr, "failed\n");
    }
}

char* read_file(const char *filename)
{
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        goto cleanup;
    }

    /* get the length */
    if (fseek(file, 0, SEEK_END) != 0)
    {
        goto cleanup;
    }
    length = ftell(file);
    if (length < 0)
    {
        goto cleanup;
    }
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        goto cleanup;
    }

    /* allocate content buffer */
    content = (char*)malloc((size_t)length + sizeof(""));
    if (content == NULL)
    {
        goto cleanup;
    }

    /* read the file into memory */
    read_chars = fread(content, sizeof(char), (size_t)length, file);
    if ((long)read_chars != length)
    {
        free(content);
        content = NULL;
        goto cleanup;
    }
    content[read_chars] = '\0';


cleanup:
    if (file != NULL)
    {
        fclose(file);
    }

    return content;
}

int main(int argc, char *argv[]) {
    int option = 0;
    char port[32] = {0};
    char file[BUF_SIZE] = {0};

    memset(port, 0, sizeof(port));
    memset(file, 0, sizeof(file));

    while ((option = getopt(argc, argv, "hf:")) != -1) {
        switch (option) {
        case 'h':
            // "optarg" variable is used to get option itself
            perror("read the source code\n");
            exit(EXIT_SUCCESS);
        case 'f':
            strncpy(file, optarg, sizeof(file) - 1);
            break;
        default:
            perror("unknown argument\n");
            return 2;
        }
    }

/////// CJSON RELATED
    uint16_t PORT = 0;
    char *IP = NULL;
    cJSON *file_content = NULL;
    cJSON *PORT_json = NULL;
    cJSON *IP_json = NULL;
    char *content = read_file(file);
    file_content = cJSON_Parse(content);
    if (!file_content) {
        fprintf(stderr, "cJSON_Parse() failed\n");
        goto cleanup;
    }

    PORT_json = cJSON_GetObjectItemCaseSensitive(file_content, "PORT");
    if (PORT_json && cJSON_IsNumber(PORT_json)) {
        PORT = (uint32_t)PORT_json->valuedouble;
    } else {
        fprintf(stderr, "PORT did not specified in the config json\n");
        goto cleanup;
    }

    IP_json = cJSON_GetObjectItemCaseSensitive(file_content, "IP");
    if (IP_json && cJSON_IsString(IP_json)) {
        IP = (uint8_t *)strdup(IP_json->valuestring);
        if (!IP) {
            fprintf(stderr, "IP did not specified in the config json\n");
            goto cleanup;
        }
    } else {
        fprintf(stderr, "IP did not specified in the config json\n");
        goto cleanup;
    }
    printf("PORT: %u, IP: %s\n", PORT, IP);
    reconstruct_config_check(IP, PORT);


/////// SOCKET RELATED
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP);
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    chat(sockfd);

    // close the socket
    close(sockfd);
cleanup:
    if (file_content) {
        cJSON_Delete(file_content);
    }
    if (IP) {
        free(IP);
    }
}
