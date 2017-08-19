#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc main.c -o a
*/

int main()
{
   char str[80] = "Idle|WPos:0.0000,0.0000,0.0000|Bf:15,128|FS:0.0,0|WCO:0.0000,0.0000,0.0000";
   const char s[2] = "|";
   char *token;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      printf( "%s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}
