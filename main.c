//retrieve is not reading from file properly

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
   scanf("%25s", current.username);
   printf("\nPlease enter the password: ");
   scanf("%25s", current.password);
   printf("\n");
   printf("url:\t\t%s\ndomain:\t\t%s\nusername:\t%s\npassword:\t%s\n", current.url, current.domain, current.username, current.password);
   fprintf(fptr, "url:\t\t{%s}\ndomain:\t\t{%s}\nusername:\t{%s}\npassword:\t{%s}\n", current.url, current.domain, current.username, current.password);
   fclose(fptr);
   return 0;
}


//This function is supposed to recieve a part of a struct that is a string and update the member
bool MemberUpdate(FILE *ptr, char update[1028], char member[]){
   printf("What do you wish to update %s to: ", update);
   scanf("%10s", member);//use str copy
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
      do{
         printf("Do you want to update any other field? Please enter Yes for yes or No for no.\n");
         scanf("%2s", answer);
      }while(strcmp(answer, "No")==1&&strcmp(answer, "Yes")==1);//Use string compare
      for(int i=0; answer[i]!='\0'; i++){
         answer[i]=tolower(answer[i]);
      }
      if(strcmp(answer, "no")==0)
         correct=!correct;
      }
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

int retrieve(char name[150], char *password[lpass], char *username[lusername], char *url[lurl], char *domain[ldomain]){
   FILE *fptr;
   char retrieve[2048];
   //char FileName = concat(domain, ".txt");
   fptr = fopen(name, "r");
   if(fptr==NULL){
      printf("Unable to open file\n");
      return 0;
   }
   printf("in retrieve\n\n");
      fscanf(fptr, "%2048s", retrieve);
      printf("%s\t", retrieve);
      fscanf(fptr, "%2048s", retrieve);
      printf("%s\n", retrieve);
      strcpy(url, retrieve);

      fscanf(fptr, "%2048s", retrieve);
      printf("%s\t", retrieve);
      fscanf(fptr, "%2048s", retrieve);
      printf("%s\n", retrieve);
      strcpy(domain, retrieve);

      fscanf(fptr, "%2048s", retrieve);
      printf("%s\t", retrieve);
      fscanf(fptr, "%2048s", retrieve);
      printf("%s\n", retrieve);
      strcpy(username, retrieve);

      fscanf(fptr, "%2048s", retrieve);
      printf("%s\t", retrieve);
      fscanf(fptr, "%2048s", retrieve);
      printf("%s\n", retrieve);
      strcpy(password, retrieve);

   return 0;
}

int main() {
   
   FILE *fptr;
   fptr = fopen("Test", "w");
   if( create(fptr, "Test") == -1)
      printf("Something horrible happened\n");
     /*   
   if( Update(fptr) == -1)
      //printf("Something horrible happened\n");
   delete();*/
   struct loginfo current;
   retrieve("Test", &current.password, &current.username, &current.url, &current.domain);
   printf("username: %s\npassword: %s\nurl: %s\ndomain: %s\n", current.username, current.password, current.url, current.domain);

   fclose(fptr);

   return 0;
}
