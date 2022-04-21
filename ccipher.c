#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

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

