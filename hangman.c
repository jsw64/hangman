#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define MaxWords 2048
#define MaxWordLength 64

int main()
{
  //randomly generate seed based on time
  srand(time(NULL));
  char guessWords[MaxWords][MaxWordLength];
  int WordsReadIn = 0;

  //prompt user for filename
  char fileName[40];
  printf("Enter file name with .txt: ");
  fgets(fileName, 40, stdin);
  fileName[strcspn(fileName, "\n")] = 0;


  FILE *pToFile = fopen(fileName, "r");
  if(pToFile == NULL)
  {
    printf("Failed to Open file\n");
    return 0;
  }

//read in words from text file
  char input[64];
  while(fgets(input, 63, pToFile))
  {
    sscanf(input, "%s", guessWords[WordsReadIn]);

    WordsReadIn++;
  }
  printf("Total Words Read In:%d\n", WordsReadIn);
  fclose(pToFile);

  int playGame = 1;

  while(playGame == 1)
  {

    int randomIndex = rand() % WordsReadIn;
    int numLives = 5;
    int numCorrect = 0;
    int oldCorrect = 0;
    int lengthOfWord = strlen(guessWords[randomIndex]);


    int letterGuessed[8] = {0,0,0,0,0,0,0,0};
    int quit = 0;
    int loopIndex = 0;
    char guess[16];
    char letterEntered;


    while(numCorrect < lengthOfWord)
    {
      printf("\nNew turn... \nHangman Word:");
      for(loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
      {
        if(letterGuessed[loopIndex] == 1)
        {
          printf("%c", guessWords[randomIndex][loopIndex]);
        }
        else
        {
          printf("-");
        }
      }
      printf("\n");

      printf("Number correct so far:%d\n", numCorrect);
      printf("Enter a guess letter('quit' to exit):");
      fgets(guess, 16, stdin);
      if( strncmp(guess, "quit", 4) == 0)
      {
        quit = 1;
        break;
      }
      letterEntered = guess[0];
      printf("letterEntered:%c\n", letterEntered);

      oldCorrect = numCorrect;

      for(loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
      {
        if(letterGuessed[loopIndex] == 1)
        {
          continue;
        }
        if(letterEntered == guessWords[randomIndex][loopIndex])
        {
          letterGuessed[loopIndex] = 1;
          numCorrect++;

        }

      }

      if(oldCorrect == numCorrect)
      {
        numLives--;
        printf("Sorry, wrong guess\n");
        if(numLives == 0)
        {
          break;
        }
      }
      else
      {
        printf("Correct guess\n");
      }
    }

    if(quit == 1)
    {
      printf("The user has quit\n");
      playGame = 0;
    }
    else if(numLives == 0)
    {
      printf("\nSorry you lose, the word was: %s\n", guessWords[randomIndex]);

    }
    else
    {
      printf("\nYOU WIN!\n");
      printf("The word was: %s\n", guessWords[randomIndex]);
    }

}
  return 0;
}
