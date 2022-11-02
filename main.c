#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{
  NotebookType *evidenceNotebook;
  evidenceNotebook = malloc(sizeof(NotebookType));

  initNotebook(evidenceNotebook, MAX_CAP);
  
  int input = 0;
  int * choice = &input;
  int inputId;
  char inputRoomName[MAX_STR];
  int inputEvidenceType;
  char inputEvidenceTypeString[MAX_STR];

  float inputValue;

  int inputHours;
  int inputMinutes;
  int inputSeconds;

  loadEvidenceData(evidenceNotebook);

  do{
    printMenu(choice);

    switch(*choice){
      case 1:
        int counter = 0;
        printf("Enter the ID of evidence to add: \n >");
        scanf(" %d", &inputId);
        printf("Enter the value of the evidence to add: \n >");
        scanf(" %f", &inputValue);
        printf("Enter the room name of evidence to add: \n > ");
        fgets(inputRoomName, MAX_STR, stdin);
        while(getchar() != '\n' && ++counter);
        inputRoomName[counter] = '\0';

        printf("Enter the evidence type of evidence to add: \n > ");
        scanf(" %d", &inputEvidenceType);
        switch(inputEvidenceType){
          case 1: 
            strcpy(inputEvidenceTypeString, "EMF");
            break;
          case 2:
            strcpy(inputEvidenceTypeString, "THERMAL");
            break;
          case 3:
            strcpy(inputEvidenceTypeString, "SOUND");
            break;
          default:
            printf("Please enter a valid number between 1 and 3 (inclusive)");
        }


        printf("Enter timestamp (HH MM SS): \n >");
        scanf(" %d %d %d", &inputHours, &inputMinutes, &inputSeconds);
        inputSeconds += inputMinutes * 60 + inputHours * 60 * 60;

        EvidenceType *inputEvidence;
        initEvidence(inputId, inputRoomName, inputEvidenceTypeString, inputValue, inputSeconds, inputEvidence);

        addEvidence(evidenceNotebook, inputEvidence);

      case 2:
        printf("Enter ID of evidence to delete: \n > ");
        scanf(" %d", &inputId);
        delEvidence(evidenceNotebook, inputId);
        break;
      case 3:
        printNotebook(evidenceNotebook);
        break;
      case 0:
        break;
      default:
        printf("Please enter a valid input\n");
        break;
    }
  }while(1);

  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

