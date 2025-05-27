#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// #define MAX_USER 10
// #define MAX_USERNAME 20
// #define MAX_PASSWORD 20 (Commenting out to see if these are necessary)

 struct bankUser{
    char username [20];
    char password [20];
    float balance;
};


int length = 0;

void takeInput(char ch[50]){
    fgets(ch,50, stdin);
    ch[strlen(ch) - 1] = 0;
}

void createAccount(struct bankUser *user, char *username, char *password){
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->balance = 0;

    printf("Account created for user %s\n", user->username);
}

int main(){
    struct bankUser user;
    int choice;
    int running = 1;

    while(running){
    printf("\n\tBank System CLI Project\n");
    printf("Choose your options by inputting a number\n");
    printf("1. Create an account\n");
    printf("2. Close an account\n");
    printf("3. Deposit money to an account\n");
    printf("4. Withdraw money from an account\n");
    printf("5. Exit\n");
        printf("Enter your choice here:");
        scanf("%d", &choice);

        switch (choice){
            case 1:
            system("cls");
            printf("Create a username");
            scanf("%s", user.username);
            printf("Create a password");
            scanf("%s", user.password);

            createAccount(&user, user.username,user.password);
            break;

            case 5:
            running = 0;
            break;

            default: 
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}