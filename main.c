
#include "stdio.h"
#include <string.h>
#include <stdbool.h>

//This is the basic struct that all CRUD operations will use and the file will contain
#define lpass 25
#define lusername 25
#define lurl 2048
#define ldomain 150
struct loginfo{
   char url[lurl];//yes I googled how long a url can be and that is the limit
   char domain[ldomain];
   char username[lusername];
   char password[lpass];
};

//This subroutine will create a file for use in the database
   //The file will contian a struct consisting of the domain name, the url, the username, the password
   //the date created and the date last updated
   //The fptr will be moved to the correct address as well
int create(FILE *fptr, char domain[]){

   //The domain name will be used as the file name
   //In order to initalize the file, the domain name plus the file type, .txt, will be inputted into fname
   char fname[150];
   strcpy(fname, domain);
   strcat(fname, ".txt");

   //fname will then be used to open the file
   fptr = fopen (domain, "w");

   //check to see if the file has been correctly opened, if not abort
   if(fptr==NULL)
   {
      printf("Unable to open file.\n\n\n\n");
      return -1;
   }

   /*Need to figure out how to get url, username, and password. Also may need a function to autogenerate password*/
   //Adding the information to the struct
   struct loginfo current = {"_blank", "_blank", "_blank", "_blank"};
   printf("url:\t\t%s\ndomain:\t\t%s\nusername:\t%s\npassword:\t%s\n", current.url, current.domain, current.username, current.password);
   fprintf(fptr, "url:\t\t%s\ndomain:\t\t%s\nusername:\t%s\npassword:\t%s\n", current.url, current.domain, current.username, current.password);
   return 0;
}


//This function is supposed to recieve a part of a struct that is a string and update the member
bool MemberUpdate(FILE *ptr, char answer[1028], char *current){
   char update[1028];
   printf("What do you wish to update %s to: ", answer);
   scanf("%s", update);
   //current.domain = update;
   printf("--%s--\n", current);
   return false;
}

//This function should ask what needs to be updated and then requests what the new update should be
int Update(FILE *fptr){
   //file is not opening
   if(fptr==NULL)
   {
      printf("Unable to open file.\n\n\n\n");
      return -1;
   }
   struct loginfo current;
   bool correct = true;
   char answer[20];
   char update[lurl];
   char *sptr;
   //This loop will ask the user for the field that they want to be updated and then ask for the update
   while(correct){
      printf("What field needs to be update? ");
      scanf("%s", answer);
      printf("%s\n", answer);
      if(strcmp(answer,"domain")==0){
         sptr = &current.domain;
         MemberUpdate(fptr, answer, sptr);
      }
      else if (strcmp(answer,"url")==0){
         sptr = &current.url;
         MemberUpdate(fptr, answer, sptr);
      }
      else if (strcmp(answer,"username")==0){
         sptr = &current.username;
         MemberUpdate(fptr, answer, sptr);
      }
      else if (strcmp(answer,"password")==0){
         sptr = &current.password;
         MemberUpdate(fptr, answer, sptr);
      }
      printf("Do you want to update any other field? Please enter Y for yes or N for no.\n");
      scanf("%s", answer);
      printf("%s", answer);
      //the program will ask the user if there are any other fields to be updated
      fflush(stdin);
      //Y is resulting to default else if
      do{
         printf("Do you want to update any other field? Please enter Yes for yes or No for no.\n");
         scanf("%s", answer);
         printf("%s", answer);
         printf("%s", answer);
      }while(answer!="No"&&answer!="Yes");//If statment not working
      if(answer=="No")
         correct=!correct;
      }
   return 0;
   }

int main() {
   
   FILE *fptr;
   if( create(fptr, "Test") == -1)
      printf("Something horrible happened\n");
   fptr = fopen("Yamazon.txt", "w");
   if( Update(fptr) == -1)
      printf("Something horrible happened\n");
   fclose(fptr);
   //Lop going to infinite
  /* fptr = fopen("Yamazon.txt", "r");
   while(fptr!="\0"){
      printf("%c", fptr);
      fptr++;

   }
   fclose(fptr);*/

   return 0;
}
