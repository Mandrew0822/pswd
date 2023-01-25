#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/rand.h>

#define MIN_PASSWORD_LENGTH 4
#define MAX_PASSWORD_LENGTH 20

int main() {
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 for null terminator
    int length, i;
    char specialChars;

    // ask the user for the desired password length
    do {
        printf("Enter password length [between %d and %d]: ", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
        scanf("%d", &length);
    } while (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH);

    // ask the user if they want to include special characters in the password
    printf("Special characters? [y/n]: ");
    scanf(" %c", &specialChars);

    // seed the PRNG
    if(!RAND_load_file("/dev/random", 32)) {
        printf("Error seeding the PRNG\n");
        exit(1);
    }

    // generate random characters for the password
    for (i = 0; i < length; i++) {
        if (specialChars == 'y' || specialChars == 'Y') {
            // ASCII range for special characters is 33-47 and 58-64
            // ASCII range for upper case letters is 65-90
            // ASCII range for lower case letters is 97-122
            unsigned char randomChar = 0;
            if(!RAND_bytes(&randomChar, 1)) {
                printf("Error generating random number\n");
                exit(1);
            }
            password[i] = randomChar % (122 - 33 + 1) + 33;
        } else {
            // ASCII range for upper case letters is 65-90
            unsigned char randomChar = 0;
            if(!RAND_bytes(&randomChar, 1)) {
                printf("Error generating random number\n");
                exit(1);
            }
            password[i] = randomChar % 26 + 65;
        }
    }
    password[length] = '\0'; // null terminate the password string

    printf("Password: %s\n", password);

    return 0;
}
