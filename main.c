
#include "stdio.h"
#include <ctype.h>
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
   printf("Please enter the username: ");
   scanf("%s", current.username);
   printf("\nPlease enter the password: ");
   scanf("%s", current.password);
   printf("\n");
   printf("{url:\t\t%s}\ndomain:\t\t%s\nusername:\t%s\npassword:\t%s\n", current.url, current.domain, current.username, current.password);
   fprintf(fptr, "url:\t\t%s\ndomain:\t\t%s\nusername:\t%s\npassword:\t%s\n", current.url, current.domain, current.username, current.password);
   return 0;
}


//This function is supposed to recieve a part of a struct that is a string and update the member
bool MemberUpdate(FILE *ptr, char update[1028], char member[]){
   printf("What do you wish to update %s to: ", update);
   scanf("%s", member);//use str copy
   printf("--%s--\n", member);
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
   //This loop will ask the user for the field that they want to be updated and then ask for the update
   while(correct){
      printf("What field needs to be update? ");
      scanf("%s", answer);
      printf("%s\n", answer);
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
      do{
         printf("Do you want to update any other field? Please enter Yes for yes or No for no.\n");
         scanf("%s", answer);
      }while(strcmp(answer, "No")==1&&strcmp(answer, "Yes")==1);//Use string compare
      for(int i=0; answer[i]!='\0'; i++){
         answer[i]=tolower(answer[i]);
         printf("%c", answer[i]);
      }
      if(strcmp(answer, "no")==0)
         correct=!correct;
      }
   return 0;
   }

int delete(char FileName){
   if(remove("Hello.txt") != 0)
      printf("Did not delete file.");
   return 0;
}

int main() {
   
   FILE *fptr;
   if( create(fptr, "Test") == -1)
      printf("Something horrible happened\n");
   fptr = fopen("Yamazon.txt", "w");
   if( Update(fptr) == -1)
      printf("Something horrible happened\n");
   delete("Hello.txt");
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
