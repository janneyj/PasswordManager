
#include <stdio.h>
#include <string.h>

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
}

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
   return 0;
}

int main() {
   
   FILE *fptr;
   if( create(fptr, "Yamazon") == -1)
      printf("Something horrible happened\n");

   return 0;
}
