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
int create(char domain[]){

   FILE *fptr = fopen (domain, "w");

   //check to see if the file has been correctly opened, if not abort
   if(fptr==NULL)
   {
      printf("Unable to open file.\n\n\n\n");
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
   return 0;
}



//This function should ask what needs to be updated and then requests what the new update should be
int Update(char domain[]){
   //file is not opening
   FILE *fptr = fopen(domain, "w");
   if(fptr==NULL)
   {
      printf("Unable to open file.\n\n\n\n");
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
   return 0;
   }
//This subroutine will ask the user what file they want delete and will either delete the file or display an error message
int delete(void){
   char FileName[100];
   printf("What file do you want to delete? ");
   scanf("%150s", FileName);
   if(remove(FileName) != 0)
      printf("Did not delete file.");
   return 0;
}

int retrieve(char name[150], struct loginfo* info){
   FILE *fptr;
   char retrieve[2048];
   fptr = fopen(name, "r");
   if(fptr==NULL){
      printf("Unable to open file\n");
      return -1;
   }

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->url);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->domain);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->username);

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%2048s", info->password);

   fclose(fptr);

   return 0;
}

int main() {
   
   /*FILE *fptr;
   fptr = fopen("Test", "w");*/
   char option = true;
   char user_input[2];
   do {
      printf("Please input C for create, U for Update and D for delete.\n");
      scanf("%1s", user_input);
      if (strcmp(user_input, "C") == 0){
         if( create("Test") == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "U")==0){
         if( Update("Test") == -1)
            printf("Something horrible happened\n");
      }
      else
         option = false;
   }
   while (option == true);
   
   struct loginfo current;
   retrieve("Test", &current);
   printf("username: %s\npassword: %s\nurl: %s\ndomain: %s\n", current.username, current.password, current.url, current.domain);

   return 0;
}
