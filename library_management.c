/*
    librarysize to store the actual number of books and records placed to track the
    position where the next book variable has to be stored
    membersize serves the same purpose as above but for the users list
    b_id starts with 1 and b_id++ is executed whenever a new book/order is added to avoid duplicates
    heldby = 0 means library has the book
    heldby !=0 some user of that number as user_id has the book
    reservedby = userid user with that id has reserved it
    reservedby = -1 no one has reserved it
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void search(int);
void search_author(int);
void search_title(int);
void search_id(int);
void reserve_book(int);
void welcome();
void return_book(int);
void get_book(int);

struct book{
    /*A book has an uniqueid, book_name, author, issue_no, id of the person holding it,
     id of the person who has requested it and its due date to be returned back*/
    int bookid;
    char bookname[50];
    char bookauthor[50];
    int issue;
    int heldby;
    int requestedby;
    int duedate;
};
struct user{
    /*A user has an id, username, passowrd, cart of 5 books maximum
    , notifcations of 5 notifs max*/
    int id;
    char username[25];
    char password[25];
    int cartsize;
    int notifsize;
    char notifs[10][100];
    struct book cart_book[5];
};
struct book library[1000];
int new_arriv[10];
struct user members[1000];
int librarysize=0;
int removesizel=0;//no. of empty spaces in library[]
int membersize=0;
int removesizem=0;//no. of empty spaces in members[]
int b_id=1;
int issued=0;//To count the no. of books issued out

void search_title(int id){
    char title[50];
    int userid = id;
    int flag =0;
    int r_ch;
    printf("Enter the book title to be searched : \n");
    scanf("%[^\n]%*c", &title);
    for(int i=0;i<(librarysize+removesizel);i++){
        if(strcmpi(title,library[i].bookname) == 0){
            flag++;
            printf("Book ID : %d \n",library[i].bookid);
            printf("Title : %s \n",library[i].bookname);
            printf("Author : %s \n",library[i].bookauthor);
            printf("Issue number : %d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book is unavailable, would you like to place an order for the same \n");
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}
void search_author(int id){
    char author[50];
    int userid = id;
    int flag=0;
    int r_ch;
    printf("Enter the author name to be view all the books written by them : \n");
    scanf(" %[^\n]%*c", &author);
    for(int i=0;i<librarysize+removesizel;i++){
        if(strcmpi(author,library[i].bookauthor) == 0){
            flag++;
            printf("Book ID : %d \n",library[i].bookid);
            printf("Title : %s \n",library[i].bookname);
            printf("Author : %s \n",library[i].bookauthor);
            printf("Issue number : %d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book is unavailable, would you like to place an order for the same \n");
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}

void search_id(int id){
    int userid =id;
    int bkid;
    int flag=0;
    int r_ch;
    printf("Enter the book id to be searched : \n");
    scanf("%d", &bkid);
    for(int i=0;i<librarysize+removesizel;i++){
        if(bkid==library[i].bookid){
            flag++;
            printf("Book ID : %d \n",library[i].bookid);
            printf("Title : %s \n",library[i].bookname);
            printf("Author : %s \n",library[i].bookauthor);
            printf("issue number : %d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book id %d is unavailable, would you like to place an order for the same \n",bkid);
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}
void search(int id){
    int userid = id;
    int ch =0;
    do{
    printf("Enter 1 to search for book by Title\n");
    printf("Enter 2 to search for book by Author\n");
    printf("Enter 3 to search for book by Book ID\n");
    printf("Enter 0 to exit \n");
    scanf("%d",&ch);
        switch(ch){
        case 0: return;
        case 1: search_title(userid);
                break;
        case 2: search_author(userid);     
                break;
        case 3: search_id(userid);
                break;
        default : printf("Wrong Choice!, try again");                
    }
    }while(ch!=0);
    /*Search for a particular title*/
    
    /*Search for a particular book_id*/
    
    /*Search for by title and author*/
    
}
 void checkout(int id){
    /* After searching the user will be asked to enter the id of the book he wants
    to checkout, if the user doesn't have a book of the same title in his cart and
    library has the book, its held by will be set to user_id and due_date will be 
    generated, will be added to his cart at cart[cartsize] and cartsize++, librarysize -- */
    int bkid=0;
    int userid = id;
    int exit=0;
    printf("Please enter the ID of the book, you want to check out : ");
    scanf("%d",&bkid);
    int flag=0;
    int size = librarysize+removesizel;
    int loc =0;
    /*This loop serves the purpose of getting the location of the given book and to change the flag value to 1 if the book is present
    flag remains 0 if the book is not present*/
    for(int i =0;i<size;i++){
        if(library[i].bookid==bkid){
            flag=1;
            loc=i;
            break;
        }
    }  
    /*This loops is used to check if the users' cart has the book already and to prevent duplicates*/
    int flag1=0; 
    for(int i =0;i<members[userid].cartsize;i++){
        if(members[userid].cart_book[i].bookid==library[loc].bookid){
            flag1=1;
        }
    } 
    if(flag==0&&flag1==0){
        printf("Book not present, make sure you enter the correct book ID\n");
        exit=1;
    }
    else if(flag==1&&flag1==0){
        printf("Book present, you have already borrowed %d books and can hold only 5 book at any given time.\n",members[userid].cartsize);
        library[loc].heldby = userid;
        members[userid].cart_book[members[userid].cartsize]=library[loc];   
        members[userid].cartsize++;
        printf("Book successfully issued by you\n");
        issued++;  
    }
    else if(members[userid].cartsize==5){
        printf("You cannot borrow more than 5 books at once, please return a book to borrow this books\n");
    }
    else{
        printf("You seem to have the same book in your cart, please return the book to borrow it again\n");
    }
}

void return_book(int id){
    /*if user has book in his cart only then he can return the book*/
    int r_id;
    printf("Enter the ID of the book to be returned");
    scanf("%d",&r_id);
    for(int i =0;i<members[id].cartsize;i++){
        if (members[id].cart_book[i].bookid==r_id){
            library[r_id].heldby=-1;
            //members[id].cart_book[members[id].cartsize]=NULL;
            members[id].cartsize--;
            printf("Book successfully returned to the library\n");

        }
    }
}

void reserve_book(int id){
    /* A new field will be created in the library with 
    requested_by = user_id,bookname =title[],bookauthor=author[]
    bookid = b_id, b_id++*/
    char t[50];
    char a[50];
    int iss;
    printf("Enter the Title of the book");
    scanf(" %[^\n]%*c", t);
    printf("Enter the Author's name");
    scanf(" %[^\n]%*c", a);
    printf(" Enter the issue number");
    scanf("%d", &iss);
    int size = librarysize+removesizel;
    /* Updating the Library */
    library[size].bookid = b_id;
    b_id++;
    strcpy(library[size].bookname,t);
    strcpy(library[size].bookauthor,a);
    library[size].heldby = -1;
    library[size].issue = iss;
    library[size].requestedby = id;
    printf("The reservation id is %d, it will be the book id once the book is available",library[size].bookid);
    printf("This id will be required to cancel reservations");
}
void delete_reservation(int id){
    /* shift all the books after the book id position to delete the reservation if held_by =-1 */
    int r_id;
    printf("Enter the reservation ID of the reservation that you want to cancel");
    scanf("%d",&r_id);
    int size = librarysize+removesizel;
    int flag=0;
    for(int i =0;i<size;i++){
        if(library[i].bookid==r_id&&library[i].requestedby==id){
            strcpy(library[i].bookname,"");
            strcpy(library[i].bookauthor,"");
            library[i].heldby=-1;
            library[i].requestedby=-1;
            flag=1;
            break;
        }
    if(flag==0){
        printf("No such reservation placed with the library!");
    }    
    else{
        printf("Reservations succesfully cancelled!");
    }
    }
}


void add_user()
{   int j=0;
        for(j=0;j<membersize+removesizem;j++)
        {
            if(members[j].id==0)
                break;
        }
        char name[50];
        printf("Enter the Username");
        scanf(" %[^\n]%*c", name);
        members[j].id= j+1;
        strcpy(members[j].username,name);
        strcpy(members[j].password,toupper(name));
    /*The deafault password is username in upper case, the member is advised to change his/her password after login*/
        members[j].cartsize=0;
        members[j].notifsize=0;
        for(int i =0;i<5;i++)
        {
        strcpy(members[j].cart_book[i].bookauthor,"");
        strcpy(members[j].cart_book[i].bookname,"");
        members[j].cart_book[i].bookid=0;
        members[j].cart_book[i].issue=0;
        members[j].cart_book[i].heldby=-1;
        members[j].cart_book[i].requestedby=0;
        members[j].cart_book[i].bookid=0;
        strcpy(members[j].notifs[i],"");
        }
    membersize++;
    printf("Account Created Successfully\n");
    printf("Userid number alloted : %d",members[j].id);
    printf("The deafault password is username in upper case, the member is advised to change his/her password after login\n");
}
void add_book(){
    /*A librarian only function to add books to the library at librarysize abd librarysize ++
    also adds the book in new arriv[10]*/
    int j=0;
        for(j=0;j<librarysize+removesizel;j++)
        {
            if(library[j].bookid==0)
                break;
        }
        printf("Enter the Book's name : ");
        gets(library[j].bookname);
        printf("Enter the Autor's name : ");
        gets(library[j].bookauthor);
        printf("Enter the Issue number :");
        scanf("%d",library[j].issue);
        library[j].heldby=-1;
        library[j].requestedby=-1;
        librarysize++;
        printf("Book Added to Library Successfully\n");
        printf("Bookid number alloted : %d",library[j].bookid);

    for(int i=9;i>0;i++)    
    {
        new_arriv[i]=new_arriv[i-1];
    }
    new_arriv[0]=library[j].bookid;


}
void delete_user(){
    /*a librarian only function to remove an user by making all the fields of the specific id blank */
    int userid;
    printf("Enter Userid to delete user : ");
    scanf("%d",&userid);
    if((userid<(membersize+removesizem))&&(userid>0))
    {
        for(int i=0;i<membersize+removesizem;i++)
        { 
            if (members[i].id==userid)
            {
                printf("Found User\n");
                printf("Are you sure you want to delete user?\n");
                int yes;
                printf("Enter 1 to delete or press any other key to cancel");
                if(yes==1)
                {
                members[i].id=0;
                strcpy(members[i].username,"");
                strcpy(members[i].password,"");
                members[i].cartsize=0;
                members[i].notifsize=0;
                //user_books[] and notifs[][] also NULL
               }
               else
               {
                printf("User not deleted");
               }
            

            }
            
            
        }
        
     
    
    }

    else
    {
         printf("Invalid Userid\n Try Again");
    }
    
    
}

void delete_book(){
    /*A librarian only function similar to delete_user() but for books*/
    int bkid;
    printf("Enter Bookid to delete book : ");
    scanf("%d",&bkid);
    if((bkid<(librarysize+removesizel))&&(bkid>0))
    {
        for(int i=0;i<librarysize+removesizel;i++)
        {   
            if (library[i].bookid==bkid)
            {
                printf("Found Book\n");
                printf("Are you sure you want to delete book?\n");
                int yes;
                printf("Enter 1 to delete or press any other key to cancel");
                if(yes==1)
                {
                library[i].bookid=0;
                strcpy(library[i].bookname,"");
                strcpy(library[i].bookauthor,"");
                library[i].issue=0;
                library[i].heldby=0;
                library[i].requestedby=0;
                library[i].duedate=0;
                }
                else
                {
                printf("Book not deleted");
                }
            }
            
        }
        
     
    
    }

    else
    {
         printf("Invalid Bookid\n Try Again");
    }
    

}
void password_change(int id){
    /*if login is validated user can reset his/her password*/
    int userid=id;
    char temppass[25];
    printf("Enter you current password : ");
    gets(temppass);
    if(strcmp(members[id-1].password,temppass)==0)
    {
        printf("Enter your new password : ");
        gets(members[id-1].password);
        printf("\nPassword changed successfully");

    }
    else
    {
        printf("\nWrong Password, Try again");
    }
}
void inventory(){
    /*a functions that provides data such as number of books, users etc etc*/
    //add another variable to see the no. of books in library & no. of books issued
    int opt;
    do{
        printf("Enter 1 to see the inventory of Books\n");
        printf("Enter 2 to see the number of active users\n");
        printf("Enter 3 to return to the previous screen\n");
        scanf("%d",&opt);
        if(opt==1)
        {
            printf("Total Number of BOOKS owned by library : %d\n",librarysize);
            printf("Number of Books issued out to members : %d\n ",issued);
            printf("Number of Books present in the library : %d\n ",(librarysize-issued));
        }
        else if(opt==2)
        {
            printf("Number of Active Users : %d",membersize);
        }
        else if(opt==3)
        {
            break;
        }
    }while(opt!=3);
}

void member(){
    /*contains the welcome page for the member login and the required functions*/
}
void librarian(){
    /*a function to display the choice after validating login for a librarian*/
}
void new_books(){
    //shows the 10 latest books added to library
    printf("10 latest books added to the library\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s \t\t\t BY %s \n",i+1,library[new_arriv[i]].bookname,library[new_arriv[i]].bookauthor);
    }
    
}
void welcome(){
    /* The function which creates a screen and provides option to log in. */
    printf("********************************************************************************************\n");
    printf("********************************************************************************************\n");
    printf("                        Welcome to LIBRARY MANAGMENT SYSTEM\n");
    printf("********************************************************************************************\n");
    printf("********************************************************************************************\n");
    new_books();
    int ch;
    do{
        printf("Enter 1 to login as member \n");
        printf("Enter 2 to login as librarian \n");
        printf("Enter 3 to  exit\n");
        scanf("%d",&ch);
        if(ch==1)
             member();
        else if(ch==2)
            librarian();
        else if(ch!=3)
            printf("invalid choice!");
    }while(ch!=3);
    
}
int main(){
    
    welcome();
    return 0;
}
