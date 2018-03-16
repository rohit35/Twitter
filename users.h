#ifndef _MY_USERS
#define _MY_USERS 1
#include <string.h>
int compare_name(node_t *str,char *str2);
int compare_pass(node_t *str,char *str2);
int compare_id(node_t *str,char *str2);
char *int_char(int src);
char *unique_id(int id_num,list_t * users);
char *word(char *source);
typedef struct user_t
{
    void *name;
    void *id;
    void *password;
    void *pointer;
} user_t;
user_t *create_users()
{

    return create_list();
}
int user_insert(list_t *users, user_t *new_user)
{
    return list_insert(users, (void *)new_user);
}
int user_create(list_t *users, char *name,char *password)
{
    if(strlen(name) !=0 && strlen(password)!=0)
    {
        user_t *new_user = NULL;
        int rc;
        new_user = (user_t *)calloc(1, sizeof(user_t));
        if (new_user == NULL) return 0;
        new_user->name = word(name);
        new_user->password = word(password);
        char *res_id=unique_id(users->size+1,users);
        new_user->id = res_id;
        new_user->pointer=NULL;
        rc=users_check(users,name,res_id,password);
        if(rc)
        {
            rc = user_insert(users, new_user);
        }
        return rc;
    }
    else
    {
        return 0;
    }
}
char *unique_id(int id_num,list_t * users)
{
    char *id =int_char(id_num);
    node_t *li = NULL;
    user_t *user = NULL;
    for (li = users->head ; li != NULL ; li = li->next)
    {
        user = (user_t *)li->data;
        if(compare_id(li,id))
            return unique_id(char_to_int(id)+1,users);
    }
    return id;
}
char * word(char *source)
{
    int idx;
    char *array = (char*)malloc(512*sizeof(char));
    for(idx=0; source[idx] !='\0'; idx++)
    {
        array[idx] = source[idx];
    }
    array[idx]='\0';
    return array;
}
int users_check(list_t *users,char *name,char *id,char *password)
{
    node_t *idx = NULL;
    user_t *check = NULL;
    if(users == NULL) return 1;
    int flag=1;
    for(idx=users->head; idx!=NULL ; idx=idx->next)
    {
        check = (user_t*)idx->data;
        if(compare_name(idx,name))
        {
            flag=2;
        }
        if(compare_pass(idx,password))
        {
            flag=3;
        }
        if(compare_id(idx,id))
        {
            flag=4;
        }
    }
    if(flag==2)
    {
        printf("\t \t \tPlease enter a new name\n");
        printf("\t \t \t");
        puts(name);
        printf(" Already exists\n");
        return 0;
    }
    else if(flag==3)
    {
        printf("\t \t \tPlease enter a new password\n");
        puts(password);
        printf("\t \t \tAlready exists\n");
        return 0;
    }
    else if(flag==4)
    {
        printf("\t \t \tPlease enter a new id number\n");
        puts(id);
        printf("\t \t \t Already exists\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
void user_search(list_t *users,char *name,char *password)
{
    system("cls");
    node_t *idx = NULL;
    user_t *acc = NULL;
    if(users==NULL)
    {
        printf("\t \t \tThe list is empty\n");
    }
    else
    {
        int flag=1;
        for(idx=users->head; idx!=NULL ; idx=idx->next)
        {
            if(compare_name(idx,name) && compare_pass(idx,password))
            {
                flag=0;
                userpage((void*)idx,users);
                break;
            }
        }
        if(flag==1)
        {
            printf("\t \t \tInvalid username or password\n");
        }
    }
}
user_t* search_user_tweets(char *id,list_t *users)
{

    node_t *idx = NULL;
    user_t *check = NULL;
    void *pos = NULL;
    char *cur;
    for(idx=users->head; idx!=NULL ; idx=idx->next)
    {
        check = (user_t*)idx->data;
        pos = idx->data;
        cur =(char*)check->id;
        if(strcmp(cur,id) ==0)
        {
            return pos;
        }
    }
    return NULL;
}

int compare_name(node_t *str,char *str2)
{
    node_t *user=str;
    user_t *str1=NULL;
    str1=(user_t*)user->data;
    char *cur =((char*)str1->name);
    int i,str1_length=strlen(cur);
    int flag=0,str2_length=strlen(str2);
    if(str1_length==str2_length)
    {
        for(i=0; i<str1_length; i++)
        {
            if(cur[i]==str2[i])
                flag++;
        }
    }
    if(flag==str2_length)
        return 1;
    else
        return 0;
}
int compare_id(node_t *str,char *str2)
{
    node_t *user=str;
    user_t *str1=NULL;
    str1=(user_t*)user->data;
    char *cur = ((char*)str1->id);
    int i,str1_length=strlen(cur);
    int flag=0,str2_length=strlen(str2);
    if(str1_length==str2_length)
    {
        for(i=0; i<str1_length; i++)
        {
            if(cur[i]==str2[i])
                flag++;
        }
    }
    if(flag==str2_length)
        return 1;
    else
        return 0;
}
int compare_pass(node_t *str,char *str2)
{
    node_t *user=str;
    user_t *str1=NULL;
    str1=(user_t*)user->data;
    char *cur =((char*)str1->password);
    int i,str1_length=strlen(cur);
    int flag=0,str2_length=strlen(str2);
    if(str1_length==str2_length)
    {
        for(i=0; i<str1_length; i++)
        {
            if(cur[i]==str2[i])
                flag++;
        }
    }
    if(flag==str2_length)
        return 1;
    else
        return 0;
}
void users_print(list_t *users)
{
    node_t *li = NULL;
    user_t *user = NULL;
    void *s,*p;
    if (users == NULL) return;
    printf("\t \t \tId : username : password\n");
    for (li = users->head ; li != NULL ; li = li->next)
    {
        user = (user_t *)li->data;
        p=user->name;
        s=user->password;
        printf("\t \t \t%s : %s :%s\n", ((char*)user->id),((char*)user->name),((char*)user->password));
    }
}
char *int_char(int src)
{
    char r,*string=(char*)malloc(100*sizeof(char));
    int n=src,j=0;
    while(n!=0)
    {
        r=n%10;
        string[j++]=(r+48);
        n/=10;
    }
    string[j]='\0';
    strrev(string);
    return string;
}
int char_to_int(char*num)
{

    int length=strlen(num);
    int var=1;
    int i,c=0,temp;
    for(i=0; i<length; i++)
    {
        if(i==0 && num[i]==45 )
        {
            var=-1;
        }
        else
        {
            temp=(num[i]-48);
            c=c*10+temp;
        }
    }
    c=c*var;
    return c;
}
#endif

