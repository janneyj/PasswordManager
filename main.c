//retrieve is not reading from file properly

#include "stdio.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define lpass 25
#define lusername 25
#define lurl 2048
#define ldomain 150

//This is the basic struct that all CRUD operations will use and the file will contain
struct loginfo{
   char url[lurl];//yes I googled how long a url can be and that is the limit
   char domain[ldomain];
   char username[lusername];
   char password[lpass];
};


//This function is supposed to recieve a part of a struct that is a string and update the member
bool MemberUpdate(FILE *ptr, char updateName[1028], char member[]){
   printf("Input %s: ", updateName);
   scanf("%1028s", member);//use str copy
   printf("--%s--\n", member);
   return false;
}

int get_name(char *name){
   char user_input[1048];

   printf("Input the url\n");
   scanf("%1048s", user_input);
   int start = 0;
   int end = 0;

   char start_phrase[5] = "www.\0";
   char end_phrase[5][5] = {".com\0", ".gov\0", ".org\0", ".edu\0", ".mil\0"};
   char check[5];
   check[4] = '\0';
   char domain[1048];
   int result = 5;
   
   for(int i =3; user_input[i]; i++){
      for(int n = 0; n < 4; n++){
         check[n] = user_input[i-(3-n)];
      }
      result = strcmp(check,start_phrase);
      if (result==0){
         start = i+1;}
      
      if (((check[3] == 47) && (check[4] == 0)) || ((check[2] == 47) && (check[3] != 47))){
         end = i-4;
      }
   }
   int n = 0;
   for(int i = start; i < end; i++){

      domain[n] = user_input[i];
      n++;
   }
   printf("**%s**\n", domain);

   fflush(stdin);
   return 0;
}

/*
Name: create
Parameters: 
      domain - string: the domain / name of the file to be opened
Return:
      0: if normal
      -1: if there is a problem
Description:
      creates a file consisting of one struct where the file name is the domain name
*/
int create(){
   char domain[2048];
   get_name(&domain[0]);

   FILE *fptr = fopen (domain, "w");

   //check to see if the file has been correctly opened, if not abort
   if(fptr==NULL)
   {
      printf("Create: Unable to open file.\n\n\n\n");
      return -1;
   }

   //Adding the information to the struct
   struct loginfo current = {"_blank", "_blank", "_blank", "_blank"};
   /*printf("Please enter the username: ");
   scanf("%25s", current.username);*/
   MemberUpdate(fptr, "username", current.username);
   MemberUpdate(fptr, "password", current.password);
   MemberUpdate(fptr, "url", current.url);
   fprintf(fptr, "url:\t\t{%s}\ndomain:\t\t{%s}\nusername:\t{%s}\npassword:\t{%s}\n", current.url, current.domain, current.username, current.password);
   fclose(fptr);
   fflush(stdin);
   return 0;
}



//This function should ask what needs to be updated and then requests what the new update should be
//FIXME retrieve and save it. Currently not retrieving or saving just updating a struct
int Update(){
   //file is not opening
   char FileName[2048];
   get_name(&FileName[0]);
   FILE *fptr = fopen(FileName, "w");
   if(fptr==NULL)
   {
      printf("Update: Unable to open file.\n\n\n\n");
      return -1;
   }
   struct loginfo current;
   bool correct = true;
   char answer[20];
   char update[lurl];
   printf("What field needs to be update? ");
   scanf("%10s", answer);
   if(strcmp(answer,"domain")==0){
      MemberUpdate(fptr, answer, current.domain);
   }
   else if (strcmp(answer,"url")==0){
      MemberUpdate(fptr, answer, current.url);
   }
   else if (strcmp(answer,"username")==0){
      MemberUpdate(fptr, answer, current.username);
   }
   else if (strcmp(answer,"password")==0){
      MemberUpdate(fptr, answer, current.password);
   
   }
      
   for(int i=0; answer[i]!='\0'; i++){
      answer[i]=tolower(answer[i]);
   }
   fflush(fptr);//file not being saved correctly

   fclose(fptr);
   fflush(stdin);
   return 0;
   }
/*
Name: delete
Parameters: void
Return: 
   0 - int: if there were no errors
   -1 - int: if there was an error
Description: This will ask the user for the file to be deleted, deletes the file, and confirms if it was deleted
*/   
int delete(void){
   char FileName[2048];
   get_name(&FileName[0]);
   if(remove(FileName) != 0){
      printf("Did not delete file.");
      return -1;
   }
   fflush(stdin);
   return 0;
}

/*
Name: retrieve
Parameters:
      name - char[150]: the name of the file that should be opened
      info - struct loginfo*: a pointer to the struct that the values should be saved to
Return:
      0 - int: if it is normal
      -1 - int: if there is a problem
Description: This will read from the file the parts of the loginfo struct and save it to a struct
*/
int retrieve(char name[150], struct loginfo* info){
   //opening the file and checking to make sure that the file opened correctly
   char FileName[2048];
   get_name(&FileName[0]);
   FILE *fptr;
   char retrieve[2048];
   fptr = fopen(FileName, "r");
   if(fptr==NULL){
      printf("Retrieve: Unable to open file\n");
      return -1;
   }
   //the first part read is the name of the struct that it is a part of so it should be skipped
   //the second part is the actual part that needs to be saved
   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->url);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->domain);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->username);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->password);

   fclose(fptr);
   fflush(stdin);
   return 0;
}

int main() {
   char option = true;
   char user_input[2];
   do {
      printf("Please input C for create, U for Update and D for delete.\n");
      scanf("%1s", user_input);
      if (strcmp(user_input, "C") == 0){
         if( create() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "U")==0){
         if( Update() == -1)
         if( create() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "U")==0){
         if( delete() == -1)
         if( Update() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "D")==0){
         if( delete() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "K")==0){
         char domain[1048];
         get_name(&domain[0]);
      }
      else
         option = false;
   }
   while (option == true);
   printf("Retrieving file\n");
   struct loginfo current;
   retrieve("joy", &current);
   printf("username: %s\npassword: %s\nurl: %s\ndomain: %s\n", current.username, current.password, current.url, current.domain);

   return 0;
}