# ccipher

# Megan Jen
05/12/2022

This is a file which can encrypt and decrypt text from a file using the C language. It is interpreted as a bash command which users can use in the terminal program, especially in Ubuntu. 

The file has a main function to set up the encryption or decryption of the desired text and run the attributes of the command, an encryption function to encrypt the text to Ceasar Cipher, and a decryption function to decrypt it.
It first starts with an importation of the following packages; stdio.h, stdlib.h, string.h, fcntl.h, unistd.h,and ctype.h. Like so:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
```
After the importation, I started on the encryption function. 
It is used when the user enters -s with the command, which they should always do when using it.
I have decided to first convert each character to ascii numbers, then place them into functions containing the user’s desired shift.
Each character of the text is translated through the line (ascii+shift-65)%26+65 for the uppercase letters, and (ascii+shift-97)%26+97 for the lowercase letters.

```c
char *encryption(char *text,int strLength, int shift) {

    int ascii;
    char *encrypted = malloc(strLength+1);
    char temp;
    for (int i=0;i<strLength;i++)
    {
        if (isalpha(text[i])==0)
           {
           //only shift letter, ignore all other chars
           //here means the char is not a letter
           encrypted[i]=text[i];
           continue;
           }
        ascii=text[i];
        if (isupper(text[i]))
            {
            	temp=(ascii+shift-65)%26+65;
           	encrypted[i] = temp;
            }
        else
            {
            	temp=(ascii+shift-97)%26+97;
            	encrypted[i] = temp;
            }
    }
    encrypted[strLength]='\0';
    text[strLength-1]='\0';
//    printf("plain text is  %s\n",text);
//    printf("cipher text is  %s\n",encrypted);
    return encrypted;

}
```

For the decryption function, the user enters -r while they use the ccipher command. Therefore, this function is executed, and the user’s text is decrypted. 
The same method is used for this function, but to decrypt each character, I subtracted 26 from the shift for both of the temp lines and put the result in the original shifts’ places.

```c
char *decryption(char *text,int strLength, int shift) {

    int ascii;
    char *decrypted = malloc(strLength+1);
    char temp;
    for (int i=0;i<strLength;i++)
    {
        if (isalpha(text[i])==0)
           {
           //only shift letter, ignore all other chars
           //here means the char is not a letter
           decrypted[i]=text[i];
           continue;
           }
        ascii=text[i];
        if (isupper(text[i]))
            {
            temp=(ascii+26-shift-65)%26+65;
//            temp=(ascii-shift-65)%26+65;
            decrypted[i] = temp;
            }
        else
            {
            temp=(ascii+26-shift-97)%26+97;
//            temp=(ascii-shift-97)%26+97;
            decrypted[i] = temp;
            }
    }
    decrypted[strLength]='\0';
    text[strLength-1]='\0';
//    printf("cipher text is  %s\n",text);
//    printf("plain text is  %s\n",decrypted);
    return decrypted;

}
```

I lastly wrote the main function, which has two arguments, an integer variable called argc and an array variable called argv. We also see some variables initialized to zero, since they would be playing major roles in the code. 
Here are the variables which are initialized at the start of the function:

```c
int main (int argc, char *argv[])
{
	const int SIZE=1024;
	int lineNum = 0,shiftFlag = 0,reverseFlag = 0,args = argc,num = 1,eolFlag=0,numRead=0,j=0,fd;
	char buf[SIZE];
	char enc[SIZE];
	char dec[SIZE];
	char c;
  int shiftNum;
}
```

The main function also checks if there are no arguments. If it is true, then the output just prints out what the user should enter for the command to have their text actually translate.

```c
	if(argc==1)
	{
		printf("Usage: %s -s NUM -r -n file.txt\n",argv[0]);
		exit(0);
	}
```

Like stated above, the command is intended to have -s added to it when used, since that would be stating how many shifts for the caesar cipher translation.
The main function would then parse the arguments for switches. Like so:

```c
	while(args--)
	{
		if(argv[args][0]=='-')
		{
			int switchLen=(int)strlen(argv[args]);
			while(switchLen--)
			{
				if(argv[args][switchLen]=='n')lineNum=1;
				if(argv[args][switchLen]=='s')shiftFlag=1;
				if(argv[args][switchLen]=='r')reverseFlag=1;
			}
		}
	}

```

The command was to have three of them, which are -n if the user wants to add line numbers to the output, -s for entering the number of shifts, and -r if the user wants to reverse the encryption. 
I also put in the lineNum, shiftFlag, and reverseFlag in front of the lines to get them ready.

The main function then detects if there is a -s in the start of the calling of the command when the user enters it. If there isn't, an error is thrown. Like so:

```c
if (shiftFlag!=1)
   {
      printf("Missing -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
      exit(0);
   }
```

The user should also enter a number after they enter -s, since that would be the shift of the translation to Caesar Cipher. If there isn't a number after -s, then an error is thrown. Like so:

```c
for (int i=1;i<argc;i++)
{
    if (argv[i][0]=='-')
       if (argv[i][1]=='s')
         {
            if (i==argc-1)
               {
               printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
               exit(0);
               }
               //some code we will talk about later
         }
}
```

And after that part of the for loop is an iteration of the string with a for loop. The argv[] at the start of the code was the entire input the user had desired to translate along with the command, with a variable called tempI being the placement of each character in the input.
The program would then make sure the character after the -s is a digit.
Like so:

```c  
for (int i=1;i<argc;i++) {
//previous code
            i++;
            int tempI=i;
            if (tempI < argc)
               {
               for (int j=0;j<strlen(argv[tempI]);j++)
               {
               if (isdigit(argv[tempI][j])==0)
                  {
                  //this char is not a digit, 0 through 9, then argv[tempI], the argument
                  //after -s is not a number
                  //throw error
                  printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
                  exit(0);
                  }
               }
               //some code we will talk about later 
            }
}               
```
If the user actually enters a number after -s for the shift, the number becomes the shift for the translation, therefore it is declared to the shiftNum variable. Like so:

```c
//some code before this
printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
exit(0);
}
shiftNum=atoi(argv[tempI]);
//and then the next section
```

And again, it returns an error if the user does not enter a number after -s.

```c
  shiftNum=atoi(argv[tempI]);
}
else
{
   printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
   exit(0);
}
```
The entire for loop now looks like this:

```c
for (int i=1;i<argc;i++)
{
    if (argv[i][0]=='-')
       if (argv[i][1]=='s')
         {
            if (i==argc-1)
               {
               printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
               exit(0);
               }
          //reach -s here, to see if next argument is a number, if not, throw error
            i++;
            int tempI=i;
            if (tempI < argc)
               {
//isdigit is per char, needs to make sure every char in a string is a digit
// this is to iterate a string argv[tempI] with a for loop
               for (int j=0;j<strlen(argv[tempI]);j++)
               {
               if (isdigit(argv[tempI][j])==0)
                  {
                  //this char is not a digit, 0 through 9, then argv[tempI], the argument
                  //after -s is not a number
                  //throw error
                  printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
                  exit(0);
                  }
               }
               //if after iterate the string, all chars are digits, then argv[tempI] is a number
               shiftNum=atoi(argv[tempI]);
               }
            else
               {
               printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
               exit(0);
               }
          }
}
```

The program will then determine if the last element is a file name, since it will be the file whose contents the command will translate. If the user does not have a file name for the last element, it throws an error. Like so:

```c
if (isalpha(argv[argc-1][0])==0)
{
//first char is not a letter, throw error
   printf("first char of file name needs to be letter, usage: %s -s NUM -r -n file.txt\n",argv[0]);
   exit(0);
}
```

And if the user does have a file name as the last element, the code will first open the file:

```c
	fd = open( argv[argc-1], O_RDONLY );
	if ( fd == -1 )
	{
        	perror( argv[argc-1] );
        	exit(1);
	}
```

Then it will read the file:

```c
	while((numRead=read(fd,buf,SIZE))>0)
	{
  //reading the file.
  }
```

And while reading the file, the program will parse the buffer, translating the text in the user's test file to caesar cipher.

In the following piece of code, the -n feature is also used for the first time, numbering each line in the output if the input text file has only one line. And If the user enters -r, then the command would reverse the encryption of the text file, so that would mean decrypting the translated message. If the user enters -r before deciding to encrypt a message, it would decrypt it using c=dec[i].

```c
	for(j=0;j<numRead;j++)
	  {
		c=buf[j];
		if(lineNum&&(eolFlag||num==1))
		{
			printf("     %d  ",num++);
			eolFlag=0;
		}
                if (reverseFlag==1)
                {

                     char *p=decryption(buf,numRead, shiftNum);
                     strcpy(dec,p);
                }
                else
                {
		      char *p=encryption(buf,numRead, shiftNum);
		      strcpy(enc,p);
                }
                //some code we will be talking about later
  }
```  
Below that code is the lineNum feature, which numbers the start of all the lines in the output, and while doing so inside the for loop going through the text file, decrypts the text using c=dec[i] if the user decides to enter -r when using the ccipher command. Like so:

```c
               if (lineNum==1)
                   {
                   if (reverseFlag==1)
                        {
                        for (int i=0;i<numRead;i++)
                          {
                          c=dec[i];
                          printf("%c",c);
                          if (c=='\n')
                             {
                             eolFlag=1;
                             }
                          if (eolFlag && i<numRead-1)
                             {
                             printf("     %d ",num++);
                             eolFlag=0;
                              }
                          }
//                        printf("%s\n",dec);
                        }
```

The else statement shows the user deciding not to reverse the encryption, so it could straight-up encrypt the user’s text using c=enc[i] like normal. Like so:

```c
   else
          {
           for (int i=0;i<numRead;i++)
            {
               c=enc[i];
               printf("%c",c);
               if (c=='\n')
                     {
                         eolFlag=1;
                      }
                if (eolFlag && i<numRead-1)
                      {
                          printf("     %d  ",num++);
                          eolFlag=0;
                       }
               }
         }
}
```

This block of code executes when the user decides to not enter -n when using the ccipher command, therefore not numbering the output lines when printing them in bash.

```c
                else
                   {
                    if (reverseFlag==1)
                        {
                        printf("%s\n",dec);
                        }
                    else
                       {
                        printf("%s\n",enc);
                        }
                    }
	        close(fd);
                return 0;
		}
	}
```

It then closes the file.

```c
	close(fd);
	return 0;
}
```

This is what our main function looks like as a whole.

```c
int main (int argc, char *argv[])
{
	const int SIZE=1024;
	int lineNum = 0,shiftFlag = 0,reverseFlag = 0,args = argc,num = 1,eolFlag=0,numRead=0,j=0,fd;
	char buf[SIZE];
	char enc[SIZE];
	char dec[SIZE];
	char c;
        int shiftNum;
//CHECK FOR NO ARGS
	if(argc==1)
	{
		printf("Usage: %s -s NUM -r -n file.txt\n",argv[0]);
		exit(0);
	}
//PARSE ARGS FOR SWITCHES
	while(args--)
	{
		if(argv[args][0]=='-')
		{
			int switchLen=(int)strlen(argv[args]);
			while(switchLen--)
			{
				if(argv[args][switchLen]=='n')lineNum=1;
				if(argv[args][switchLen]=='s')shiftFlag=1;
				if(argv[args][switchLen]=='r')reverseFlag=1;
			}
		}
	}

//Now detect if there is -s, if not, throw error, -s is required

if (shiftFlag!=1)
   {
      printf("Missing -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
      exit(0);
   }

//Now detect if an integer (shift) after  -s, if not, throw error, -s NUM is required

for (int i=1;i<argc;i++)
{
    if (argv[i][0]=='-')
       if (argv[i][1]=='s')
         {
            if (i==argc-1)
               {
               printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
               exit(0);
               }
          //reach -s here, to see if next argument is a number, if not, throw error
            i++;
            int tempI=i;
            if (tempI < argc)
               {
//isdigit is per char, needs to make sure every char in a string is a digit
// this is to iterate a string argv[tempI] with a for loop
               for (int j=0;j<strlen(argv[tempI]);j++)
               {
               if (isdigit(argv[tempI][j])==0)
                  {
                  //this char is not a digit, 0 through 9, then argv[tempI], the argument
                  //after -s is not a number
                  //throw error
                  printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
                  exit(0);
                  }
               }
               //if after iterate the string, all chars are digits, then argv[tempI] is a number
               shiftNum=atoi(argv[tempI]);
               }
            else
               {
               printf("Missing NUM after -s, usage: %s -s NUM -r -n file.txt\n",argv[0]);
               exit(0);
               }
          }
}
//Now shift number after -s is in variable shiftNum
//printf("shift number is %d\n",shiftNum);

//Now, need to determine if last argument is a file name, which first char must be letter, or throw error

if (isalpha(argv[argc-1][0])==0)
{
//first char is not a letter, throw error
   printf("first char of file name needs to be letter, usage: %s -s NUM -r -n file.txt\n",argv[0]);
   exit(0);
}

//Now command is fine, read file into array buf[SIZE]

//OPEN FILE
	fd = open( argv[argc-1], O_RDONLY );
	if ( fd == -1 )
	{
        	perror( argv[argc-1] );
        	exit(1);
	}
//READ FILE
	while((numRead=read(fd,buf,SIZE))>0)
	{
//PARSE BUFFER
	for(j=0;j<numRead;j++)
	  {
		c=buf[j];
		if(lineNum&&(eolFlag||num==1))
		{
			printf("     %d  ",num++);
			eolFlag=0;
		}
                if (reverseFlag==1)
                {

                     char *p=decryption(buf,numRead, shiftNum);
                     strcpy(dec,p);
                }
                else
                {
		      char *p=encryption(buf,numRead, shiftNum);
		      strcpy(enc,p);
                }
//Now add line number if -n is given
//lineNum was set to 1 when -n was detected above
                if (lineNum==1)
                   {
                   if (reverseFlag==1)
                        {
                        for (int i=0;i<numRead;i++)
                          {
                          c=dec[i];
                          printf("%c",c);
                          if (c=='\n')
                             {
                             eolFlag=1;
                             }
                          if (eolFlag && i<numRead-1)
                             {
                             printf("     %d ",num++);
                             eolFlag=0;
                              }
                          }
//                        printf("%s\n",dec);
                        }
                   else
                       {
                        for (int i=0;i<numRead;i++)
                          {
                          c=enc[i];
                          printf("%c",c);
                          if (c=='\n')
                             {
                             eolFlag=1;
                             }
                          if (eolFlag && i<numRead-1)
                             {
                             printf("     %d  ",num++);
                             eolFlag=0;
                              }
                          }
//                        printf("%s\n",enc);
                        }
                    }
                else
                   {
//print output no line number
                    if (reverseFlag==1)
                        {
                        printf("%s\n",dec);
                        }
                    else
                       {
                        printf("%s\n",enc);
                        }
                    }
	        close(fd);
                return 0;
		}
//	}
	}
//CLOSE FILE
	close(fd);
	return 0;
}
```



