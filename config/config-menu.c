#define CONFIG_H
#define CONFIG_H
#define MAX_JSON_SIZE 512

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h> // Linux only
#include <time.h>

// Barvy
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

// Prefixy
#define BEFORE       GREEN "<<" WHITE
#define AFTER        GREEN ">>"
#define BEFORE_GREEN GREEN "[" WHITE
#define AFTER_GREEN  GREEN "]"
#define INPUT        BEFORE "Lester" AFTER " $"
#define INFO         BEFORE "!" AFTER " $"
#define ERROR        BEFORE "x" AFTER " $"
#define ADD          BEFORE "+" AFTER " $"
#define WAIT         BEFORE "~" AFTER " $"
#define INFO_ADD     GREEN "[" YELLOW "$" GREEN "]" GREEN

// ASCII bannery
static const char* menu_banner =
    GREEN BOLD
    "\n\n"
    "                ░▒▓█▓▒░      ░▒▓████████▓▒░░▒▓███████▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░  \n"
    "                ░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░         ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n"
    "                ░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░         ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n"
    "                ░▒▓█▓▒░      ░▒▓██████▓▒░  ░▒▓██████▓▒░   ░▒▓█▓▒░   ░▒▓██████▓▒░ ░▒▓███████▓▒░  \n"
    "                ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n"
    "                ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░  ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ \n"
    "                ░▒▓████████▓▒░▒▓████████▓▒░▒▓███████▓▒░   ░▒▓█▓▒░   ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ \n"
    RESET;
/*
static const char* option_1_banner =
    GREEN BOLD
    "                                (    (        )  (     \n"
    "                                )\\ ) )\\ )  ( /(  )\\ )  \n"
    "                                (()/((()/(  )\\())(()/(  \n"
    "                                /(_))/(_))((_\\  /(_)) \n"
    "                                (_))_(_))_   ((_)(_))   \n"
    "                                |   \\|   \\ / _ \\/ __|  \n"
    "                                | |) | |) | (_) \\__ \\  \n"
    "                                |___/|___/ \\___/|___/   \n"
    RESET;
*/
static const char* map_banner =
    "                                                                        \n"
    "                ,--.,------.     ,--.              ,--.                \n"
    "                |  ||  .--. '    |  | ,---.  ,---. |  |,-.,--.,--. ,---.\n"
    "                |  ||  '--' |    |  || .-. || .-. ||     /|  ||  || .-. |\n"
    "                |  ||  | --'     |  |' '-' '' '-' '|  \\  '\\  ''  '| '-' '\n"
    "                `--'`--'         `--' `---'  `---' `--'`--'`----' |  |-' \n"
    "                                                                `--'    \n";


void log_action(const char *message) {
    
    FILE *log_file = fopen("log.txt", "a"); // opens file
    if (log_file == NULL) {
        perror("error while opening file.");
        return;
    }

    // získání aktuálního času
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    if (time_str == NULL) {
        perror("error while getting time.");
        fclose(log_file);
        return;
    }

    // odstranění nového řádku z ctime
    time_str[strcspn(time_str, "\n")] = '\0';

    // zápis zprávy do souboru
    fprintf(log_file, "[%s] %s\n", time_str, message);
    fclose(log_file);
}

void slow_print(const char* text, float delay_sec) {
    for (const char* p = text; *p; p++) {
        putchar(*p);
        fflush(stdout);
        usleep(delay_sec * 1000000);
    }
    putchar('\n');
}


void clear_screen() {
    system("clear || cls");
}

void display_error(const char *message) {
    printf("\n%s%s%s\n", RED, message, RESET);
    //sleep(2);
}

// await na Enter aby se to hned neresetovalo
void response_await() {
    printf("\n%sPress Enter to continue...%s", GREEN, RESET);
    while (getchar() != '\n'); 
    getchar(); 
    log_action("Returning to main menu.");
}

// validace IPv4
int ip_validate(const char* ip) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex,
                   "^((25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\.){3}"
                   "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)$",
                   REG_EXTENDED);
    if (reti) return 0;
    reti = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

// validace URL
int url_validate(const char* url) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex,
                   "^(http|https)://[^\\s/$.?#].[^\\s]*$",
                   REG_EXTENDED);
    if (reti) return 0;
    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

