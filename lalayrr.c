#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64
#define DEFAULT_NAME "World"

// Function prototypes
void print_header(void);
void print_personalized_greeting(const char *name, int count);
char* get_user_name(void);

int main(void) {
    print_header();

    // Dynamically retrieve name from user
    char *user_name = get_user_name();
    if (user_name == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return EXIT_FAILURE;
    }

    int repeat_count = 1;
    printf("How many times should I greet you? (1-5): ");
    if (scanf("%d", &repeat_count) != 1 || repeat_count < 1 || repeat_count > 5) {
        printf("Invalid input. Defaulting to 1.\n");
        repeat_count = 1;
    }

    print_personalized_greeting(user_name, repeat_count);

    // Clean up allocated memory
    free(user_name);
    user_name = NULL;

    printf("\nProgram completed successfully.\n");
    return EXIT_SUCCESS;
}

void print_header(void) {
    puts("========================================");
    puts("       EXTENDED C HELLO WORLD           ");
    puts("========================================");
}

char* get_user_name(void) {
    char *buffer = (char *)malloc(MAX_NAME_LEN * sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    // Clear input stream before reading string
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter your name (or press Enter for default): ");
    if (fgets(buffer, MAX_NAME_LEN, stdin) != NULL) {
        // Remove trailing newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }

    // Fall back to default if user pressed Enter
    if (strlen(buffer) == 0) {
        strncpy(buffer, DEFAULT_NAME, MAX_NAME_LEN - 1);
        buffer[MAX_NAME_LEN - 1] = '\0';
    }

    return buffer;
}

void print_personalized_greeting(const char *name, int count) {
    puts("\n--- Output ---");
    for (int i = 1; i <= count; i++) {
        printf("[%d/%d] Hello, %s!\n", i, count, name);
    }
}
