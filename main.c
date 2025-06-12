#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_USERNAME_LEN 20
#define MAX_PASS_LEN 20

//TODO: Refine prints to terminal. Make sign-in and log-out function. Make withdrawal and depositing money work.

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

struct bankUser *currentUser = NULL;

struct bankUser* signIn(struct bankUser *users, int userCount){
    char username[MAX_USERNAME_LEN], password[MAX_PASS_LEN];

    printf("Enter username: ");
    takeInput(username, MAX_USERNAME_LEN);
    printf("Enter password: ");
    takeInput(password, MAX_PASS_LEN);

    for(int i = 0; i < userCount; i++){
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0){
            printf("Login Successful");
            return &users[i];
        }
    }

    printf("Login failed. Invalid credentials.\n");
    return NULL;
}

void logOut(struct bankUser *users, int userCount){
    currentUser = NULL;
    printf("Logged out successfully!");
}

void listAccounts (struct bankUser *users, int userCount){
    for(int i = 0; i < userCount; i++){
       printf("%d. Username: %s | Balance: %.2f\n", i + 1, users[i].username, users[i].balance);
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

struct bankUser* depositMoney(struct bankUser *users, int userCount){
    double moneyAmount;

    if(currentUser == NULL){
        printf("You must be signed in to deposit money.");
        return users;
    }

    printf("Enter amount you want to deposit:");
    scanf("%lf", &moneyAmount);

    currentUser->balance += moneyAmount;
    printf("Deposit successful! New balance. %.2f\n", currentUser->balance);
    
    return users;
}

struct bankUser* withdrawMoney(struct bankUser *users, int userCount){
    double moneyAmount;

    if(currentUser == NULL){
        printf("You must be signed in to withdraw money.");
        return users;
    }

    printf("Enter amount you want to withdraw");
    scanf("%lf", &moneyAmount);

      if(moneyAmount > currentUser->balance){
        printf("Insufficient funds. Available balance: %.2f\n", currentUser->balance);
    } else {
        currentUser->balance -= moneyAmount;
        printf("Withdrawal successful. New balance: %.2f\n", currentUser->balance);
    }

    return users;
}

void pauseScreen() {
    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n'); 
    getchar();                  
}


int main(){
    int choice;
    int running = 1;

    while(running){
    printf("\n\tBank System CLI Project\n");
    printf("Choose your options by inputting a number\n");
    printf("1. Create an account\n");
    printf("2: Sign in\n");
    printf("3: Log out\n");
    printf("4. List accounts\n");
    printf("5. Close an account\n");
    printf("6. Deposit money to an account\n");
    printf("7. Withdraw money from an account\n");
    printf("8. Exit\n");
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
            currentUser = signIn(users, userCount);
            break;

            case 3:
            system("cls");
            logOut(users, userCount);
            break;

            case 4:
            system("cls");
            listAccounts(users, userCount);
            pauseScreen();
            break;

            case 5:
            system("cls");
            users = closeAccounts(users, &userCount);
            break;

            case 6:
            system("cls");
            users = depositMoney(users, userCount);
            pauseScreen();
            break;

            case 7:
            system("cls");
            users = withdrawMoney(users, userCount);
            pauseScreen();
            break;
            
            case 8:
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