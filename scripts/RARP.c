#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <netdb.h>     // Linux only
#include <arpa/inet.h> // Linux only


void resolve_domain_to_ip(char *domain, char *ip_buffer, size_t buffer_size) {
    struct addrinfo hints, *res;
    struct sockaddr_in *addr;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // IPv4 only

    if ((status = getaddrinfo(domain, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    addr = (struct sockaddr_in *)res->ai_addr;
    strncpy(ip_buffer, inet_ntoa(addr->sin_addr), buffer_size);

    freeaddrinfo(res);
}

void fetch_ip_info(const char *ip) {
    char command[256];
    snprintf(command, sizeof(command), "curl -s http://ip-api.com/json/%s > ip_info.json", ip);
    system(command);
    
}
void print_pretty_json(const char* json) {
    
    bool in_key = false, in_string_value = false, in_number_value = false;
    char key[256] = {0};
    char value[256] = {0};
    int ki = 0, vi = 0;

    for (int i = 0; json[i]; i++) {
        char c = json[i];

        // handle string key
        if (c == '"' && !in_key && !in_string_value && !in_number_value) {
            if (json[i - 1] == '{' || json[i - 1] == ',' || json[i - 1] == ':') {
                in_key = true;
                ki = 0;
                memset(key, 0, sizeof(key));
                continue;
            }
        } else if (c == '"' && in_key) {
            in_key = false;
            continue;
        } else if (in_key) {
            key[ki++] = c;
            continue;
        }

        // handle string value
        if (c == '"' && !in_string_value && json[i - 1] == ':') {
            in_string_value = true;
            vi = 0;
            memset(value, 0, sizeof(value));
            continue;
        } else if (c == '"' && in_string_value) {
            in_string_value = false;
            printf("$ %s => %s\n", key, value);
            continue;
        } else if (in_string_value) {
            value[vi++] = c;
            continue;
        }

        // handle numeric value
        if (!in_string_value && !in_key && json[i - 1] == ':' && (isdigit(c) || c == '-' || c == '.')) {
            in_number_value = true;
            vi = 0;
            memset(value, 0, sizeof(value));
            value[vi++] = c;
            continue;
        } else if (in_number_value && (isdigit(c) || c == '.' || c == 'e' || c == '-')) {
            value[vi++] = c;
            continue;
        } else if (in_number_value) {
            in_number_value = false;
            printf("$ %s => %s\n", key, value);
        }
    }
}
