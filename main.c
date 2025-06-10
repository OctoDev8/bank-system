#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_USERNAME_LEN 20
#define MAX_PASS_LEN 20

//TODO: Refine prints to terminal

//Note to self: Use arrow operator to access structs
 struct bankUser{
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASS_LEN];
    double balance;
};

struct bankUser *users = NULL;
int userCount = 0;

void takeInput(char *ch, int size){
    fgets(ch, size, stdin);
    ch[strcspn(ch,"\n")] = 0;
}

struct bankUser* createAccount(struct bankUser *users, int *userCount){
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASS_LEN];
    
    printf("Enter username: ");
    takeInput(username, MAX_USERNAME_LEN);
    printf("Enter password: ");
    takeInput(password, MAX_PASS_LEN);

    users = realloc(users, (*userCount + 1)* sizeof(struct bankUser));

    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);
    users[*userCount].balance = 0.0;

    printf("Account created for %s.\n", users[*userCount].username);
    (*userCount)++;

    return users;
}

void listAccounts (struct bankUser *users, int userCount){
    for(int i = 0; i < userCount; i++){
        printf("%d. %s\n", i+1, users[i].username);
        if(users[i].balance == 0){
            printf("No balance.");
        } else {
            printf("%d. %s\n", i+1, users[i].balance);
        }
    }
}

struct bankUser* closeAccounts (struct bankUser *users, int *userCount){
    int indexToRemove;

    printf("Enter account number to remove:\n");
    scanf("%d", &indexToRemove);
    indexToRemove--;

    for(int i = indexToRemove; i < *userCount - 1; i++){
        users[i] = users[i + 1];
    }
    (*userCount)--;
    users = realloc(users,(*userCount)* sizeof(struct bankUser));
    printf("Successfully closed account!");

    return users;
}

struct bankUser* depositMoney(struct bankUser *users, int *userCount){
    double moneyAmount;

    printf("Enter amount you want to deposit.");
    scanf("%d", &moneyAmount);

    users[*userCount].balance += moneyAmount;
    
    return users;
}

struct bankUser* withdrawMoney(struct bankUser *users, int *userCount){
    double moneyAmount;

    printf("Enter amount you want to withdraw");
    scanf("%d", &moneyAmount);

      if(moneyAmount > users[*userCount].balance){
        printf("Invalid amount, you can only withdraw what you have.");
    } else {
        users[*userCount].balance -= moneyAmount;
    }

    return users;
}

int main(){
    int choice;
    int running = 1;

    while(running){
    printf("\n\tBank System CLI Project\n");
    printf("Choose your options by inputting a number\n");
    printf("1. Create an account\n");
    printf("2. List accounts\n");
    printf("3. Close an account\n");
    printf("4. Deposit money to an account\n");
    printf("5. Withdraw money from an account\n");
    printf("6. Exit\n");
        printf("Enter your choice here:");
        scanf("%d", &choice);
        getchar();


        switch (choice){
            case 1:
            system("cls");
            users = createAccount(users, &userCount);
            break;

            case 2:
            system("cls");
            listAccounts(users, userCount);
            break;

            case 3:
            system("cls");
            users = closeAccounts(users, &userCount);
            break;

            case 4:
            system("cls");
            users = depositMoney(users, &userCount);
            break;

            case 5:
            system("cls");
            users = withdrawMoney(users, &userCount);
            break;
            
            case 6:
            running = 0;
            break;

            default: 
            printf("Invalid choice\n");
            break;
        }
    }
    free(users);
    return 0;
}