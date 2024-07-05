
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
   //if statement not working
   while(correct){
      printf("What field needs to be update? ");
      scanf("%s", answer);
      printf("%s\n", answer);
      if(strcmp(answer,"domain")==0){
         printf("What do you wish to update %s to: ", answer);
         scanf("%s", update);
         //current.domain = update;
         printf("--%s--\n", current.domain);
         correct = !correct;
      }
      else if (strcmp(answer,"url")==0){
         printf("What do you wish to update %s to: ", answer);
         scanf("%s", update);
         correct = true;
      }
      else if (strcmp(answer,"username")==0){
         printf("What do you wish to update %s to: ", answer);
         scanf("%s", update);
         correct = true;
      }
      else if (strcmp(answer,"password")==0){
         printf("What do you wish to update %s to: ", answer);
         scanf("%s", update);
         correct = true;
      }
      }
   return 0;
   }

int main() {
   
   FILE *fptr;
   if( create(fptr, "Yamazon") == -1)
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
