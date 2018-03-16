#ifndef _MY_TWEET_LIST
#define _MY_TWEET_LIST 1
typedef struct tweet_t
{
    void *content;
    void *likes;
    void *date;
    void *active;
    struct tweet_t *next_tweet;
} tweet_t;
typedef struct liked_by
{
    void *data;
    struct liked_by *next;
} liked_by;
int *likes_inc(void *likes);
liked_by* create_liked_by()
{
    liked_by *line = (liked_by*)calloc(1,sizeof(liked_by));
    return line;
}
tweet_t *create_userpage()
{
    tweet_t *cur=(tweet_t*)calloc(1,sizeof(tweet_t));
    cur->next_tweet=NULL;
    cur->active=create_liked_by();
    return cur;
}
void userpage(void *idx,list_t *users)
{
    node_t *a= idx;
    system("color 07");
    user_t *acc =(user_t*)a->data;
    char *cur =(char*)acc->name;
    printf("\t \t \twelcome %s\n\n",cur);
    int choice,active=0;
    char c='y';
    while(c=='y' ||c=='Y')
    {
        printf("\t \t \tUserpage\t \tOnline:%d Members\n\n",users->size);
        printf("\t \t \tpress 1 for entering a Tweet\n");
        printf("\t \t \tpress 2 for viewing all tweets\n");
        printf("\t \t \tpress 3 for tweet by username\n");
        printf("\t \t \tpress 4  for liking a tweet\n");
        printf("\t \t \tpress 5 for settings\n");
        printf("\t \t \tpress 6 for logout\n");
        printf("\t \t \tEnter your choice\n");
        printf("\t \t \t");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            entering_tweet(acc);
            break;
        case 2:
            viewing_tweets(users);
            break;
        case 3:
            tweet_by_username(users,acc);
            break;
        case 4:
            liking_tweet(users,acc);
            break;
        case 5:
            active=setting(users,acc);
            if(active==1)
            {
                c='N';
            }
            break;
        case 6:
            c='N';
            break;
        default:
            status();
            break;
        }
    }
    fflush(stdin);
    clear();
    system("cls");
}
void entering_tweet(user_t *acc)
{
    system("cls");
    printf("\t \t \t<<Entering Tweet>>>\n\n");
    tweet_t *cur=(tweet_t*)calloc(1,sizeof(tweet_t));
    char *content = (char*)malloc(512*sizeof(char));
    char *date = (char*)malloc(512*sizeof(char));
    printf("\t \t \tEnter the content\n");
    printf("\t \t \t");
    fflush(stdin);
    gets(content);
    printf("\t \t \tEnter the date\n");
    printf("\t \t \t");
    fflush(stdin);
    gets(date);
    if(strlen(content) == 0)
    {
        printf("\t \t \tplease enter the content \n");
        printf("\t \t \t");
        gets(content);
    }
    if(strlen(date)==0)
    {
        printf("\t \t \tplease Enter the date\n");
        printf("\t \t \t");
        gets(date);
    }
    cur->content = word(content);
    cur->date = word(date);
    cur->active=NULL;
    cur->next_tweet = NULL;
    if(acc->pointer==NULL)
    {
        acc->pointer=cur;
    }
    else
    {
        tweet_t *p=(tweet_t*)acc->pointer;
        while(p->next_tweet!=NULL)
        {
            p=p->next_tweet;
        }
        p->next_tweet=cur;
    }
    system("cls");
}
void viewing_tweets(list_t *users)
{
    system("cls");
    system("color 09");
    printf("\t \t \t<<<Viewing All Tweets>>>\n\n");
    display(users);
    clear();
    system("cls");
}
void tweet_by_username(list_t *users,user_t *yourid)
{
    system("cls");
    system("color 01");
    char name[512];
    int flag=0;
    printf("\t \t \t<<<Tweet By Username>>>\n\n");
    printf("\t \t \tEnter the username\n");
    printf("\t \t \t");
    scanf("%s",name);
    node_t *li = NULL;
    user_t *user = NULL;
    int idx=0,pos=0;
    char *character;
    for(li = users->head; li!=NULL ; li =li->next)
    {
        user = (user_t*)li->data;
        if(compare_name(li,name))
        {
            system("cls");
            flag++;
            printf("\t \t \t<<<Tweet By Username>>>\n\n");
            printf("\t \t \tUsername:%s\n",((char*)user->name));
            printf("\t \t \tUser Id:%s\n",((char*)user->id));
            tweet_t *page=(tweet_t*)user->pointer;
            liked_by *current = NULL;
            while(page!=NULL)
            {
                printf("\t \t \t%d)Content:%s\n",(idx+1),((char*)page->content));
                character = (char*)page->date;
                printf("\t \t \tDate:");
                for(pos = 0; character[pos] !='\0'; pos++)
                {
                    if(pos == 2 || pos ==4)
                    {
                        printf("-%c",character[pos]);
                    }
                    else
                    {
                        printf("%c",character[pos]);
                    }
                }
                printf("\n");
                printf("\t \t \tLikes:%d\n",((int*)page->likes));
                printf("\t \t \tLiked By:");
                current =(liked_by*)page->active;
                if(current==NULL)
                {
                    printf("NULL\n");
                }
                else
                {
                    while(current!=NULL)
                    {
                        printf("%s,",((char*)current->data));
                        current=current->next;
                    }
                    printf("others\n");
                }
                page=page->next_tweet;
                idx+=1;
            }

        }
        if(flag!=0)
        {
            break;
        }
    }
    if(idx==0 && flag==0)
    {
        printf("\t \t \tNOt Available\n");
    }
    else if(idx ==0)
    {
        printf("\t \t \tNo Tweets to display\n");
    }
    fflush(stdout);
    clear();
    system("cls");
}
void liking_tweet(list_t *users,user_t *acc)
{
    system("cls");
    system("color 03");
    printf("\t \t \t<<<Liking a Tweet>>>\n\n");
    display(users);
    if(tweet_list(users))
    {
        char number[512];
        printf("\t \t \tEnter the id number of the user\n");
        printf("\t \t \tYou want to like a tweet\n");
        printf("\t \t \t");
        scanf("%s",number);
        void *pos=search_user_tweets(number,users);
        if(pos==NULL)
        {
            printf("\t \t \tInvalid id\n");
        }
        else
        {
            system("cls");
            int choice;
            int total=all_contents(pos);
            if(total!=0)
            {
                printf("\t \t \tEnter The Content Number You Want to Like\n");
                printf("\t \t \t");
                scanf("%d",&choice);
                if(choice!=0 && choice<=total )
                {
                    user_t *cur=(user_t*)pos;
                    tweet_t *store=(tweet_t*)cur->pointer;
                    choice-=1;
                    while(store!=NULL && choice--)
                    {
                        store=store->next_tweet;
                    }
                    if(check_user(store,acc))
                    {
                        store->likes=likes_inc(store->likes);
                        liked_by *current =(liked_by*)calloc(1,sizeof(liked_by));
                        current->data=acc->name;
                        current->next=NULL;
                        if(store->active == NULL)
                        {
                            store->active=current;
                        }
                        else
                        {
                            liked_by *pos = (liked_by*)store->active;
                            current->next = pos;
                            store->active= current;
                        }
                    }
                    else
                    {
                        printf("\t \t \tYou have already liked That Tweet\n");
                    }

                }
            }
            else
            {
                printf("\n\t \t \tThere are no tweets\n");
            }
        }
    }
    else
    {
        printf("\t \t \tNo tweets to like\n");
    }
    clear();
    system("cls");
}
int *likes_inc(void *likes)
{
    int *idx=(int*)malloc(sizeof(int)*1);
    if(((int*)likes ) == 0)
    {
        idx=1;
        return idx;
    }
    else
    {
        int num=((int*)likes);
        idx= (num)+1;
        return idx;
    }
}
int tweet_list(list_t *users)
{
    int flag=0;
    node_t *li = NULL;
    user_t *user = NULL;
    tweet_t *page = NULL;
    liked_by *cur = NULL;
    for(li=users->head; li!=NULL; li=li->next)
    {
        user=(user_t*)li->data;
        page =(tweet_t*)user->pointer;
        while(page!=NULL)
        {
            if(((char*)page->content) != NULL)
            {
                flag++;
            }
            page=page->next_tweet;
        }
    }
    return flag;
}
int compare(void *str1,void *str2)
{
    char *s =(char*)str1;
    char *p =(char*)str2 ;
    if(strcmp(s,p)==0)
        return 1;
    else
        return 0;
}
int check_user(tweet_t *store,user_t *acc)
{
    liked_by *current =(liked_by*)store->active;
    while(current!=NULL)
    {
        if(compare(current->data,acc->name))
        {
            return 0;
        }
        current=current->next;
    }
    return 1;
}
int all_contents(void *pos)
{
    int idx=0,position=0;
    user_t *cur=(user_t*)pos;
    printf("\t \t \t User Details\n\n");
    printf("\t \t \tUsername:%s\n",((char*)cur->name));
    printf("\t \t \tId:%s\n",((char*)cur->id));
    tweet_t *data=(tweet_t*)cur->pointer;
    liked_by *names;
    char *character;
    printf("\t \t \tContent Num:Content\n");
    while(data!=NULL)
    {
        printf("\t \t \t  %d        :%s\n",(idx+1),((char*)data->content));
        character = ((char*)data->date);
        printf("\t \t \tDate:");
        for(position =0; character[position] !='\0'; position++)
        {
            if(position ==2 || position ==4)
            {
                printf("-%c",character[position]);
            }
            else
            {
                printf("%c",character[position]);
            }
        }
        printf("\n");
        printf("\t \t \tLikes:%d\n",((int*)data->likes));
        printf("\t \t \tLIked By:");
        idx++;
        names=(liked_by*)data->active;
        if(names==NULL)
        {
            printf("NULL\n");
        }
        else
        {
            while(names!=NULL)
            {
                printf("%s,",((char*)names->data));
                names=names->next;
            }
            printf("others\n");
        }
        data=data->next_tweet;
    }
    if(idx==0)
    {
        printf("\t \t \tNULL  :NULL");
    }
    return idx;
}
void display(list_t *users)
{
    node_t *idx = NULL;
    user_t *acc = NULL;
    tweet_t *page = NULL;
    liked_by *current =NULL;
    int i=0,pos=0;
    char *character;
    for(idx=users->head; idx!=NULL; idx=idx->next)
    {
        acc=(user_t*)idx->data;
        printf("\t \t \tUsername:%s\n",((char*)acc->name));
        printf("\t \t \tUser Id:%s\n",((char*)acc->id));
        page=(tweet_t*)acc->pointer;
        while(page!=NULL)
        {
            printf("\t \t \t%d)Content:%s\n",(i+1),((char*)page->content));
            printf("\t \t \tDate:");
            character = (char*)page->date;
            for(pos =0; character[pos] !='\0'; pos++)
            {
                if(pos ==2 || pos ==4)
                {
                    printf("-%c",character[pos]);
                }
                else
                {
                    printf("%c",character[pos]);
                }
            }
            printf("\n");
            printf("\t \t \tLikes:%d\n",((int*)page->likes));
            printf("\t \t \tLiked By:");
            current =(liked_by*)page->active;
            if(current==NULL)
            {
                printf("NULL\n");
            }
            else
            {
                while(current!=NULL)
                {
                    printf("%s,",((char*)current->data));
                    current=current->next;
                }
                printf("others\n");
            }
            page=page->next_tweet;
            i+=1;
        }
        if(i==0)
        {
            printf("\t \t \tContent:NULL\n");
            printf("\t \t \tDate:NULL\n");
            printf("\t \t \tLikes:0\n");
            printf("\t \t \tLiked By:NULL\n");
        }
        i=0;
        printf("\n");
    }
}
int setting(list_t *Users,user_t *Acc)
{
    system("color 05");
    int choice,loop=1,act=0;
    while(loop)
    {
        printf("\n");
        system("cls");
        printf("\t \t \t<<< Settings>>>\n\n");
        printf("\t \t \tEnter 1 for Account Settings\n");
        printf("\t \t \tPress 2 for privacy Settings\n");
        printf("\t \t \tPress 3 for Back\n");
        printf("\t \t \tEnter your choice\n");
        printf("\t \t \t");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            system("color 09");
            act=Account_settings(Users,Acc);
            if(act==1)
            {
                loop=0;
            }
            break;
        case 2:
            system("color 07");
            privacy_settings(Acc);
            break;
        case 3:
            loop=0;
            break;
        default:
            status();
            break;
        }
    }
    system("cls");
    return act;
}
int Account_settings(list_t*Users,user_t *Acc)
{
    printf("\n");
    int choice,loop=1,active;
    while(loop)
    {
        printf("\n");
        system("cls");
        printf("\t \t \t<<<Account Settings>>>\n\n");
        printf("\t \t \tpress 1 for your profile\n");
        printf("\t \t \tpress 2 for Deleteing All your Tweets\n");
        printf("\t \t \tpress 3 for Deleteing your Account\n");
        printf("\t \t \tpress 4 for Back\n");
        printf("\t \t \tEnter your choice\n");
        printf("\t \t \t");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            profile(Acc);
            break;
        case 2:
            Deleting_your_Tweets(Acc);
            break;
        case 3:
            active=Deleting_your_Account(Users,Acc);
            loop=0;
            //       return 1;
            break;
        case 4:
            loop=0;
            break;
        default:
            status();
            break;
        }
    }
    clear();
    system("cls");
    return active;
}
void profile(user_t *Acc)
{
    printf("\t \t \t<<<Profile>>>\n\n");
    printf("\t \t \tName:%s\n",((char*)Acc->name));
    printf("\t \t \tId:%s\n",((char*)Acc->id));
    printf("\t \t \tPassword:%s\n",((char*)Acc->password));
    clear();
    fflush(stdout);
    system("cls");
}
void Deleting_your_Tweets(user_t *Acc)
{
    printf("\t \t \t<<Deleting Tweets>>>\n\n");
    char var[]="NULL";
    Acc->pointer = NULL;
    printf("\n");
    printf("\t \t \t All Tweets have Been Deleted\n");
    clear();
    system("cls");
}
int Deleting_your_Account(list_t *Users,user_t *Acc)
{
    printf("\t \t \t<<<Deleting Account>>>\n\n");
    node_t* li = NULL,*pos =Users->head;
    user_t *user = NULL,*cur;
    char *id =(user_t*)Acc->id;
    char *name =(user_t*)Acc->name;
    char *password = (user_t*)Acc->password;
    char *word;
    for (li = Users->head ; li != NULL ; li = li->next)
    {
        user = li->data;
        cur = li;
        if(compare_id(li,id) && compare_name(li,name) && compare_pass(li,password))
        {
            printf("\t \t \t<<<Profile>>>\n\n");
            printf("\t \t \tName:%s\n",((char*)Acc->name));
            printf("\t \t \tId:%s\n",((char*)Acc->id));
            printf("\t \t \tPassword:%s\n",((char*)Acc->password));
            if(cur==Users->head)
            {
                Users->head=li->next;
                Users->size--;
                break;
            }
            else if(li->next==NULL)
            {
                while(pos->next!=li)
                {
                    pos=pos->next;
                }
                pos->next = NULL;
                free(li);
                Users->size--;
                break;
            }
            else
            {
                while(pos->next!=li)
                {
                    pos=pos->next;
                }
                pos->next=li->next;
                free(li);
                Users->size--;
                break;
            }
        }
    }
    printf("\t \t \tYour Account Has Been Deleted\n");
    return 1;
}
void privacy_settings(user_t *Acc)
{
    printf("\n");
    int choice,loop=1;
    while(loop)
    {
        system("cls");
        printf("\t \t \t<<<Privacy Settings>>>\n\n");
        printf("\t \t \tPress 1 for Changing Username\n");
        printf("\t \t \tpress 2 for Changing password\n");
        printf("\t \t \tpress 3 for Back\n");
        printf("\t \t \tEnter your choice\n");
        printf("\t \t \t");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            changing_username(Acc);
            break;
        case 2:
            changing_password(Acc);
            break;
        case 3:
            loop=0;
            break;
        default:
            status();
            break;
        }
    }
    clear();
    system("cls");
}
void changing_username(user_t *Acc)
{
    char *New_name=(char*)malloc(512*sizeof(char));
    printf("\t \t \t<<<Username>>>\n\n");
    printf("\t \t \tEnter your new Username\n");
    printf("\t \t \t");
    fflush(stdin);
    gets(New_name);
    Acc->name=word(New_name);
    printf("\t \t \tSuccessfully Changed\n");
    printf("\n");
    clear();
    system("cls");
}
void changing_password(user_t *Acc)
{
    printf("\t \t \t<<<Username>>>\n\n");
    printf("\t \t \tPlease Enter your current password\n");
    char cur_password[512];
    printf("\t \t \t");
    fflush(stdin);
    gets(cur_password);
    if(compare_password(Acc,cur_password))
    {
        printf("\t \t \tEnter your new password\n");
        char *New_password = (char*)malloc(512*sizeof(char));
        printf("\t \t \t");
        fflush(stdin);
        gets(New_password);
        Acc->password = word(New_password);
        printf("\t \t \tSuccessfully Changed\n");
        free(New_password);
    }
    else
    {
        printf("\t \t \tWrong Password\n");
    }
    printf("\n");
    clear();
    system("cls");
}
int compare_password(user_t *str,char *str2)
{
    user_t *str1=NULL;
    str1=(user_t*)str;
    char *pass =(char*)str1->password;
    int i,str1_length=strlen(pass);
    int flag=0,str2_length=strlen(str2);
    if(str1_length==str2_length)
    {
        for(i=0; i<str1_length; i++)
        {
            if(pass[i]==str2[i])
                flag++;
        }
    }
    if(flag==str2_length)
        return 1;
    else
        return 0;
}
#endif

