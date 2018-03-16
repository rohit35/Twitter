#include<stdio.h>
#include<process.h>
#include<string.h>
typedef struct Tweet
{
    int tweet_id;
    char username[10];
    char date[10];
    char content[100];
    int likes;
} tweet;

tweet tw[10];
int i=0;
char user[10];
int like[10]={0};

int main()
{
    //tweet tw[10];
    //char *ptr;
    int value;

    while(1)
    {
        printf(" ........TWITTER MENU.......\n");
        printf("Enter 1 to enter content\n");
        printf("Enter 2 to view content\n");
        printf("Enter 3 to view by username\n");
        printf("Enter 4 to view no of matched users\n");
        printf("Click 5 to like a tweet\n");
        printf("Enter 6 to exit\n");
        scanf("%d",&value);
        switch(value)
        {
        case 1:
            printf("\n<<<--->>>\n");
            enter_content();
            break;
        case 2:
            printf("\n<<<--->>>\n");
            view_content();
            break;
        case 3:
            printf("\n<<<--->>>\n");
            print_by_username();
        case 4:
            printf("\n<<<--->>>\n");
            no_matched();
            break;
        case 5:
            printf("\n<<<--->>>\n");
            like_tweet();
            break;
        case 6:
            exit(0);
            break;
        }
    }
    return 0;
}


void  enter_content()
{
    tweet ptr;
    printf("Enter username\n");
    scanf("%s",ptr.username);
    printf("Enter date\n");
    scanf("%s",ptr.date);
    printf("Enter content\n");
    scanf("%s",ptr.content);
    ptr.likes=like[i];
    ptr.tweet_id=100+i;
    tw[i]=ptr;
    i++;

}

void view_content()
{
    int j;
    for(j=0; j<i; j++)
    {
        printf("TWEET_ID : ");
        printf("%d\n",tw[j].tweet_id);
        printf("%s\n%s\n%s\n",tw[j].username,tw[j].date,tw[j].content);
        printf("Likes : ");
        printf("%d\n",tw[j].likes);
        printf("------------------\n");
    }
}

void print_by_username()
{
    int k;
    int match=0;
    printf("\nenter username to match :");
    scanf("%s",user);
    for(k=0; k<i; k++)
    {

        if(strcmp(user,tw[k].username))
        {
            printf("\nThe content is : \n");
            printf("%s",tw[k].content);
            match=1;
        }
    }
    if(match=0)
    {
        printf("\nGiven name did not match...!!!!\n");
    }
}


void no_matched()
{
    int count=0,q;
    char user_1[10];
    printf("\nEnter the names to display no. of matchings\n");
    scanf("%s",user_1);
    for(q=0; q<i; q++)
    {
        if(strcmp(user_1,tw[q].username))
        {
            count++;
        }
    }
    printf("\n%d\n",count);
}

void like_tweet()
{
    int input,r;
    printf("Enter the TWEET ID : ");
    scanf("%d",&input);
    for(r=0; r<i; r++)
    {
        if(input==tw[r].tweet_id)
        {
            tw[r].likes=like[r]+1;
            printf("%d",tw[r].likes);
            printf("\nTweet Liked...\n");
            break;
        }
    }
    if(r==i)
    {
        printf("\nTweet ID did not match\n");
    }
}
