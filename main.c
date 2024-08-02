#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Guest {
    char *name;
    char rsvp;
    char *dietaryRestrictions;
};

void getGuestCount(int *);//this function is useful for number of guests
void getGuestNames(struct Guest *, int);//this function is useful for we enter name of guests
void getRSVPs(struct Guest *, int);
int findGuestByName(struct Guest *, char *, int);//this function is useful for if we want to search guest,it finds with name
void getDietaryRestrictions(struct Guest *, int);//this function is useful for information dietary of guest with  name
void generateInvitations(struct Guest *, int);
void printGuests(struct Guest *, int);//this function is useful for printing information of guest
int menu();

int main(void) {
    int numGuests;
    getGuestCount(&numGuests);
                        //malloc is used to allocate space in memory, so it will remain registered even if we turn it off
    struct Guest *guests = (struct Guest *)malloc(numGuests * sizeof(struct Guest));
    if (guests == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    getGuestNames(guests, numGuests);
    int choice;
    while ((choice = menu()) != 0) {
        switch (choice) {
            case 1:
                getRSVPs(guests, numGuests);
                break;
            case 2:
                getDietaryRestrictions(guests, numGuests);
                break;
            case 3:
                generateInvitations(guests, numGuests);
                break;
            case 4:
                printGuests(guests, numGuests);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    for (int i = 0; i < numGuests; i++) {
        free(guests[i].name);
        free(guests[i].dietaryRestrictions);
    }
    free(guests);
    return 0;
}

int menu() {
    int choice;
    printf("Pick a menu item:\n");
    printf("0. Exit\n");
    printf("1. Enter RSVPs\n");
    printf("2. Enter Dietary Restrictions\n");
    printf("3. Generate Invitations\n");
    printf("4. Print\n");
    scanf("%d", &choice);
    return choice;
}

void getGuestCount(int *numGuests) {
    printf("How many guests are you inviting to the party? ");
    scanf("%d", numGuests);
}

int findGuestByName(struct Guest *guests, char *name, int numGuests) {
    for (int i = 0; i < numGuests; i++) {
        if (strcmp(name, guests[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void getGuestNames(struct Guest *guests, int numGuests) {
    for (int i = 0; i < numGuests; i++) {
        guests[i].dietaryRestrictions = (char *)malloc(50 * sizeof(char));
        if (guests[i].dietaryRestrictions == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        strcpy(guests[i].dietaryRestrictions, "None");

        printf("Enter the name of guest %d: ", i + 1);
        guests[i].name = (char *)malloc(50 * sizeof(char));
        if (guests[i].name == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        scanf("%s", guests[i].name);
    }
}

void getRSVPs(struct Guest *guests, int numGuests) {
    char name[50];
    int i;
    printf("Name of the guest: ");
    scanf("%s", name);
    i = findGuestByName(guests, name, numGuests);
    if (i != -1) {
        printf("RSVP for %s (Y/N): ", name);
        scanf(" %c", &guests[i].rsvp);  // Note the space before %c to consume any newline
    } else {
        printf("Guest not found.\n");
    }
}

void getDietaryRestrictions(struct Guest *guests, int numGuests) {
    char name[50];
    int i;
    printf("Name of the guest: ");
    scanf("%s", name);
    i = findGuestByName(guests, name, numGuests);
    if (i != -1) {
        printf("Dietary restrictions for %s: ", name);
        scanf("%s", guests[i].dietaryRestrictions);
    } else {
        printf("Guest not found.\n");
    }
}

void generateInvitations(struct Guest *guests, int numGuests) {
    printf("\nGenerating personalized invitations...\n");
    for (int i = 0; i < numGuests; i++) {
        printf("Dear %s,\n", guests[i].name);
        printf("You're invited to a surprise party!\n");
        printf("Please RSVP to keep the secret.\n");
        printf("See you there!\n\n");
    }
}

void printGuests(struct Guest *guests, int numGuests) {
    for (int i = 0; i < numGuests; i++) {
        if (guests[i].rsvp == 'Y' || guests[i].rsvp == 'y') {
            printf("%s\tDietary Restrictions: %s\n", guests[i].name, guests[i].dietaryRestrictions);
        }
    }
}
