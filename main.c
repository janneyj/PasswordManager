//retrieve is not reading from file properly
//Please Comment Me! Why am is being passive aggressive to myself?
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
bool MemberUpdate(char updateName[1028], char member[]){
   printf("Input %s: ", updateName);
   scanf("%1028s", member);//use str copy
   printf("--%s--\n", member);
   return false;
}

int get_name(char *URL, char* domain){
   int start = 0;
   int end = 0;
   const char start_phrase[3][9] = {"www.\0", "https://\0", "http://\0"};
   const char end_phrase[5][5] = {".com", ".gov", ".org", ".edu", ".mil"};
   
   if(strlen(URL)==0)
   {
      printf("ERROR: null string\nCalled by get_name\n");
   }
   for(int n = 0; n < 3 && start == 0; n++)
   {
      char compare[9];
      int t = strlen(start_phrase[n]);
      for(int i = 0; i < strlen(start_phrase[n]); i++)
      {
         compare[i] = URL[i];
      }
      if(strncmp(compare, start_phrase[n], strlen(start_phrase[n])) == 0)
         start = n+strlen(start_phrase[n]);
   }

   for(int n = 0; n < 5 && end == 0; n++)
   {
      char compare[5];
      int begin = strlen(URL)-strlen(end_phrase[n]);
      for(int i = begin; i <= strlen(URL); i++)
      {
         compare[i-begin] = URL[i];
      }
      if(strcmp(compare, end_phrase[n]) == 0)
      {
         end = begin;
      }
   }
   int n;
   for(int i = start; i < end; i++)
   {
      n=i-start;
      domain[n] = URL[i];

   }
   domain[n+1] = 0;
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
   //Adding the information to the struct
   struct loginfo current = {"_blank\0", "_blank\0", "_blank\0", "_blank\0"};
   
   MemberUpdate("username", current.username);
   MemberUpdate("password", current.password);
   MemberUpdate("url", current.url);
   get_name(&current.url[0], &current.domain[0]);

   char temp[2048];
   strcpy(temp, current.domain);
   
   FILE *fptr = fopen (strcat(temp, ".txt"), "w");

   //check to see if the file has been correctly opened, if not abort
   if(fptr==NULL)
   {
      printf("Create: Unable to open file.\n\n\n\n");
      return -1;
   }

   fprintf(fptr, "url:\t\t{%s}\ndomain:\t\t{%s}\nusername:\t{%s}\npassword:\t{%s}\n",
      current.url, current.domain, current.username, current.password);
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
   get_name(&FileName[0], &FileName[0]);
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
int retrieve(char FileName[], struct loginfo* info){
   //opening the file and checking to make sure that the file opened correctly
   FILE *fptr;
   char retrieve[2048];
   strcat(FileName, ".txt");
   fptr = fopen(FileName, "r");
   if(fptr==NULL){
      printf("Retrieve: Unable to open file\n");
      return -1;
   }
   //the first part read is the name of the struct that it is a part of so it should be skipped
   //the second part is the actual part that needs to be saved
   char ch[1];
   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%1s", ch);
   fscanf(fptr, "%2048s", info->url);
   info->url[strlen(info->url)-1] = 0;

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%1s", ch);
   fscanf(fptr, "%2048s", info->domain);
   info->domain[strlen(info->domain)-1] = 0;

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%1s", ch);
   fscanf(fptr, "%2048s", info->username);
   info->username[strlen(info->username)-1] = 0;

   fscanf(fptr, "%2048s", retrieve);
   fscanf(fptr, "%1s", ch);
   fscanf(fptr, "%2048s", info->password);
   info->password[strlen(info->password)-1] = 0;

   fclose(fptr);
   fflush(stdin);
   return 0;
}

//This function should ask what needs to be updated and then requests what the new update should be
//FIXME retrieve and save it. Currently not retrieving or saving just updating a struct
int Update(struct loginfo* current){
   //file is not opening
   char FileName[2048];
   printf("Input URL: ");
   scanf("%2048s", FileName);
   get_name(&FileName[0], &FileName[0]);
   retrieve(FileName, current);
   if(remove(FileName) != 0)
   {
      printf("ERROR: Update could not remove old file\n");
      return -1;
   }
   FILE *fptr = fopen(FileName, "w");
   if(fptr==NULL)
   {
      printf("Update: Unable to open file.\n\n\n\n");
      return -1;
   }
   bool correct = true;
   char answer[20];
   char update[lurl];
   printf("What field needs to be update? ");
   scanf("%10s", answer);
   if(strcmp(answer,"domain")==0){
      MemberUpdate(answer, current->domain);
   }
   else if (strcmp(answer,"url")==0){
      MemberUpdate(answer, current->url);
   }
   else if (strcmp(answer,"username")==0){
      MemberUpdate(answer, current->username);
   }
   else if (strcmp(answer,"password")==0){
      MemberUpdate(answer, current->password);
   
   }
      
   for(int i=0; answer[i]!='\0'; i++){
      answer[i]=tolower(answer[i]);
   }
   fflush(fptr);//file not being saved correctly
   fprintf(fptr, "url:\t\t{%s}\ndomain:\t\t{%s}\nusername:\t{%s}\npassword:\t{%s}\n",
      current->url, current->domain, current->username, current->password);
   fclose(fptr);
   fflush(stdin);
   return 0;
   }


//This funciton allows the user to access a step by step guide to using the program
void help(){
   printf("Press\n1 - For help with saving a password\n2 - For help with viewing a password, username, or URL\n");
   printf("3 - For help with updating a password, username, or URL\n");
   printf("4 - For deleting a password\n");
   char choice[2];
   scanf("%2s", choice);
   if(strcmp(choice, "1")==0){
      printf("Steps to creating a password\n");
      printf("1. Input C when prompted by the terminal\n");
      printf("2. Copy the URL for the website you want to save the password for\n");
      printf("3. Paste the URL into the terminal when prompted\n");
      printf("4. Input the username that is associated with the username\n");
      printf("5. Input the password you want to save for future use\n");
      printf("6. Re-input the url (Please be patient while we work on this issue. Thank you!)\n");
   }
   else if (strcmp(choice, "2")==0){
      printf("Steps to viewing a password, username, or URL\n");
      printf("1. Input R when prompted by the terminal\n");
      printf("2. Copy the URL for the website you want to save the password for\n");
   }
   else if (strcmp(choice, "3")==0){
      printf("Steps to updating a password, username, or URL\n");
      printf("1. Input U when prompted by the terminal\n");
      printf("2. Copy the URL for the website you want to save the password for\n");
      printf("3. Paste the URL into the terminal when prompted\n");
      printf("4. Type the desired field you want to update (username, password, or URL)\n");
      printf("5. Input the updated field\n");
   }
      else if (strcmp(choice, "4")==0){
      printf("Steps to deleting a password\n");
      printf("1. Input D when prompted by the terminal\n");
      printf("2. Copy the URL for the website you want to save the password for\n");
      printf("3. Paste the URL into the terminal when prompted\n");
   }
   else{
      printf("Wow you really are confused. Please only input a 1, 2, 3, 4 with no spaces, commas, or anything else.\n");
      printf("No literally just type the number and press enter.");
   }
}

void printLogInfo(struct loginfo* info)
{
   printf("URL: %s\nDomain: %s\nUsername: %s\nPassword: %s\n",
      info->url, info->domain, info->username, info->password);
}

int main() {
   char option = true;
   char user_input[2];

   printf("Welcome's to I Can't Remember My Password\n");
   printf("  ***********\n");
   printf(" **  +   +  **\n");
   printf("**           **\n");
   printf(" **   ---   **\n");
   printf("  ***********\n");
   
   struct loginfo current;   
   do {
      printf("Please input C for create, R for retrieve, U for Update, D for delete, and H for Help.\n");
      printf("To end the program press any other key\n");
      scanf("%1s", user_input);
      if (strcmp(user_input, "C") == 0||strcmp(user_input, "c")==0){
         if( create() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "U")==0||strcmp(user_input, "u")==0){
         if( Update(&current) == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "R")==0||strcmp(user_input, "r")==0){
         printf("Input URL: ");
         char temp[lurl];
         scanf("%2048s", temp);
         get_name(&temp[0], &temp[0]);
         if( retrieve(temp, &current) == -1)
            printf("Something horrible happened\n");
         else
            printLogInfo(&current);
      }
      else if (strcmp(user_input, "D")==0||strcmp(user_input, "d")==0){
         if( delete() == -1)
            printf("Something horrible happened\n");
      }
      else if (strcmp(user_input, "H")==0||strcmp(user_input, "h")==0){
         char domain[1048];
         help();
      }
      else
      {
         option = false;
      }
   }while (option == true);

   if(option == true){
      printf("Retrieving file\n");
      retrieve("joy", &current);
      printf("username: %s\npassword: %s\nurl: %s\ndomain: %s\n", current.username, current.password, current.url, current.domain);
   }
   return 0;
}
