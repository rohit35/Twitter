#include<stdio.h>
#include"linked_list.h"
#include"users.h"
#include "tweet.h"
int main()
{
    int choice;
    list_t *users = create_list();
    users->size=0;
    while(1)
    {
        fflush(stdout);
        system("color 04");
        printf("\n");
        printf("\t \t \tWELCOME TO TWEETER\n\n");
        printf("\t \t \t  <<<MENU>>>\n");
        printf("\t \t \tpress 1 for signup\n");
        printf("\t \t \tpress 2 for login\n");
        printf("\t \t \tpress 3 for help\n");
        printf("\t \t \tpress 4 for exit\n");
        printf("\t \t \tenter your choice\n\t \t \t");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            signup(users);
            break;
        case 2:
            login(users);
            system("cls");
            break;
        case 3:
            help(users);
            break;
        case 4:
            printf("\t \t \tThank You For Visiting\n");
            exit(NULL);
            case 5:users_print(users);
            break;
        default:
            status();
            break;
        }
    }
    pritnf("\t \t \tThank you for visiting\n");
    return 0;
}
void status()
{
    printf("\t \t \tplease enter valid choice\n");
}
void signup(list_t *users)
{
    system("cls");
    printf("\n");
    printf("\t \t \t<<<Welcome to signup>>>\n");
    char *name =(char*)malloc(512*sizeof(char));
    char *password = (char*)malloc(512*sizeof(char));
    printf("\n");
    printf("\t \t \tEnter the name\n\t \t \t");
    fflush(stdin);
    gets(name);
    fflush(stdin);
    printf("\t \t \tenter the password\n\t \t \t");
    gets(password);
    if(!user_create(users,name,password))
    {
        printf("\t \t \tFailed\n");
    }
    else
    {
        printf("\t \t \tYou have succesfully singup\n");;
    }
    clear();
    free(password);
    free(name);
    system("cls");
}
void login(list_t *users)
{
    system("cls");
    printf("\n");
    printf("\t \t \t<<<welcome to login>>>\n\n");
    char name[512];
    char password[512];
    printf("\t \t \tEnter the name\n\t \t \t");
    fflush(stdin);
    gets(name);
    fflush(stdin);
    printf("\t \t \tenter the password\n\t \t \t");
    gets(password);
    if(strlen(name) !=0 && strlen(password)!=0)
    {user_search(users,name,password);}
    else
    {
        printf("\t \t \tFill the required details\n");
    }
    clear();
}
void help(list_t *users)
{
    system("cls");
    int choice,key=1;
    while(key!=3)
    {
        printf("\n");
        printf("\t \t \t<<Help Section>>>\n\n");
        printf("\t \t \tPress 1 for forgot password\n");
        printf("\t \t \tPress 2 for Back\n");
        printf("\t \t \tEnter your choice\n");
        printf("\t \t \t");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            forgot_password(users);
            break;
        case 2:
            key=3;
            break;
        default:
            status();
            break;
        }
        system("cls");
    }
}
void forgot_password(list_t *users)
{
    if (users->head == NULL)
    {
        printf("\t \t \tThe list is Empty\n");
    }
    else
    {
        system("cls");
        char name[512],id[512];
        printf("\t \t \t<<<Forgot Password>>>\n\n");
        printf("\t \t \tEnter your username\n");
        printf("\t \t \t");
        fflush(stdin);
        gets(name);
        printf("\t \t \tEnter your id Number\n");
        printf("\t \t \t");
        fflush(stdin);
        gets(id);
        node_t *li = NULL;
        user_t *user = NULL;
        int flag=0;
        printf("\n");
        printf("\t \t \tYour Account Details \n");
        printf("\t \t \tId : username : password\n");
        for (li = users->head ; li != NULL ; li = li->next)
        {
            user = (user_t *)li->data;
            if(compare_name(li,name) && compare_id(li,id))
            {
                flag++;
                printf("\t \t \t%s  : %s   :  %s\n",((char*) user->id),((char*) user->name),((char*)user->password));
                break;
            }
        }
        if(flag==0)
        {
            printf("\t \t \tNULL :    NULL   :   NULL\n");
        }
    }
    clear();
}
void clear()
{
    char any;
    printf("\t \t \tPress any Key\n");
    printf("\t \t \t");
    fflush(stdin);
    scanf("%c",&any);
}
