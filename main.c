// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "./config/config-menu.c"
#include "./scripts/RARP.c"

/* 1) show my pc specs like whoami na komponenty */

#define MAX_INPUT 256

const char *options[] = {
    "soon", "soon", "soon", "RARP", "soon",
    "soon", "soon", "soon", "soon", "soon"
};

// RARP - reverse adress resolution protocol  




void prompt_ip_url(char *ip_buf) {
    clear_screen();
    printf("%s", map_banner);
    printf("\n%s[%sINPUT%s] IP -> %s", WHITE, CYAN, WHITE, RESET);
    log_action("waiting for ip");
    fgets(ip_buf, MAX_INPUT, stdin);
    ip_buf[strcspn(ip_buf, "\n")] = '\0';
    if (!ip_validate(ip_buf)) {
        display_error("Invalid IP or URL. Returning to main menu.");
        log_action("Invalid IP or URL. Returning to main menu.");
        ip_buf[0] = '\0';
    }
}

void print_menu() {
    log_action("Printing menu...");
    // Vytiskneme ASCII
    printf("%s", menu_banner);
    printf("%s", GREEN);

    printf(
        "\n"
        "                                %s┌────────%s[Q] quit <           > help [H]%s─────┐\n"
        "                                │                                            │\n"
        "                                │                 │%s > MENU <  %s│              │\n"
        "                                ├─────────────────┘───────────└──────────────┤\n",
        WHITE, YELLOW, WHITE, GREEN, WHITE
    );

    //                                       možnost 1 - 5               možnost 6 - 10
    printf("                                ├─ %s[%s01%s]%s %-10s ─┤    ├─ %s[%s06%s]%s %-10s ─┤\n", 
           GREEN, BLUE, GREEN, WHITE, options[0], GREEN, WHITE, GREEN, WHITE, options[5]);
    printf("                                ├─ %s[%s02%s]%s %-10s ─┤    ├─ %s[%s07%s]%s %-10s ─┤\n", 
           GREEN, BLUE, GREEN, WHITE, options[1], GREEN, WHITE, GREEN, WHITE, options[6]);
    printf("                                ├─ %s[%s03%s]%s %-10s ─┤    ├─ %s[%s08%s]%s %-10s ─┤\n", 
           GREEN, BLUE, GREEN, WHITE, options[2], GREEN, WHITE, GREEN, WHITE, options[7]);
    printf("                                ├─ %s[%s04%s]%s %-10s ─┤    ├─ %s[%s09%s]%s %-10s ─┤\n", 
           GREEN, BLUE, GREEN, WHITE, options[3], GREEN, WHITE, GREEN, WHITE, options[8]);
    printf("                                ├─ %s[%s05%s]%s %-10s ─┤    ├─ %s[%s10%s]%s %-10s ─┤\n", 
           GREEN, WHITE, GREEN, WHITE, options[4], GREEN, WHITE, GREEN, WHITE, options[9]);

    printf("                                └────────────────────────────────────────────┘\n");
    log_action("Menu has been printed.");
}


void handle_choice(const char *choice) {
    if (strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0) {
        log_action("Exiting...");
        printf("%sExiting...%s\n", GREEN, RESET);
        exit(0);
        return;
    }

    if (strcmp(choice, "h") == 0 || strcmp(choice, "H") == 0) {
        log_action("choice Help selected.");
        printf(
            "%stoto menu je napsané v C a funguje takto: \n"
            "-> zadej h pro help \n"
            "-> zadej q pro vypnuti \n"
            "-> pri erroru zmacknout enter dvakrat \n"
            "-> #1 soon \n"
            "-> #2 soon \n"
            "-> #3 soon \n"
            "-> #4 RARP = ziskani IP podle domeny (napr => www.google.com), reverse adress resolution protocol + souradnice zadane domeny \n"
            "-> #5 soon \n"
            "-> #6 soon \n"
            "-> #7 soon \n"
            "-> #8 soon \n"
            "-> #9 soon \n"
            "-> #10 soon \n"
            "-> konec lol %s\n", GREEN, RESET);
        response_await();
        clear_screen();
        return;
    }


    int index = atoi(choice) - 1;
        
        switch (index) {
            case 0:
                // soon
                log_action("in handle choice: case 0 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 1:
                // soon
                log_action("in handle choice: case 1 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 2:
                // soon
                log_action("in handle choice: case 2 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 3:
                // RARP + IP lookup
                log_action("in handle choice: case 3 selected => choice IP lookup started.");
                char ip_buf[0];
                char ip[INET_ADDRSTRLEN];
                prompt_ip_url(ip_buf);
                resolve_domain_to_ip(ip_buf, ip, sizeof(ip));
                log_action("domain has been succussefully resolved to ip.");
                printf("Resolved IP: %s\n", ip);
                fetch_ip_info(ip);
                printf("File succussefully saved\n");
                log_action("IP info File succussefully saved.");
                FILE* file = fopen("ip_info.json", "r");
                if (!file) {
                    perror("Failed to open file");
                    log_action("Failed to open file");
                    
                }
                else {
                    log_action("IP info File opened.");
                }
                char json[MAX_JSON_SIZE];
                size_t len = fread(json, 1, MAX_JSON_SIZE - 1, file);
                json[len] = '\0'; // null terminate
                fclose(file);
                print_pretty_json(json);
                response_await();
                clear_screen();
                break;

            case 4:
                // soon
                log_action("in handle choice: case 4 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 5:
                // soon
                log_action("in handle choice: case 5 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 6:
                // soon
                log_action("in handle choice: case 6 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 7:
                // soon
                log_action("in handle choice: case 7 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 8:
                // soon
                log_action("in handle choice: case 8 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 9:
                // soon
                log_action("in handle choice: case 9 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;

            case 10:
                // soon
                log_action("in handle choice: case 10 selected => choice soon started.");
                printf("%stest%s \n", RED, RESET);
                response_await();
                clear_screen();
                break;
                

            default:
                display_error("Invalid choice.");
                log_action("Invalid choice.");
                response_await();
                clear_screen();
                break;
        }
} 
    



int main() {
    char input[MAX_INPUT];
    char *username = getenv("USER");
    if (!username) username = "user";

    while (1) {
        clear_screen();
        print_menu();
        printf("%s(%sLester@%s%s)->> %s", GREEN, YELLOW, username, GREEN, RESET);
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0';
        for (int i = 0; input[i]; i++) input[i] = toupper(input[i]);
        handle_choice(input);
    }

    return 0;
}
