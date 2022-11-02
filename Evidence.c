#include "defs.h"

// Function: addEvidence
// Makes a copy of the given evidence directly into its correct position in the given notebook collection
void addEvidence(NotebookType* arr, EvidenceType* ev) {

  printf("trying to add id: %d\n", ev->id);

  if((arr->size) >= arr->capacity){
    growNotebook(arr);
  }
 
  int i = 0;
  // less than might need to be greater than. May need to switch around comparisons in compareEvidence() too
  while(compareEvidence(&arr->elements[i], ev) < 0 && i++ < MAX_STR-1) {
    printf("compareEvidence shit: %d\n", compareEvidence(&arr->elements[i], ev));
  }
  printf("i is fuckin %d\n", i);
  i--; // look into this, may be an off-by-one error

  EvidenceType *tempEvidence = malloc(sizeof(EvidenceType));

  copyEvidence(tempEvidence, &arr->elements[i]);
  arr->elements[i] = *ev;

  
  for(int j = i+1; j < arr->size; j++){
    printf("adding to evidence: %d\n", arr->elements[j].id);
    copyEvidence(&arr->elements[j], tempEvidence);
    copyEvidence(tempEvidence, &arr->elements[j+1]);

  }
  
  //copyEvidence(&arr->elements[arr->size - 1], tempEvidence);

  printf("before arr %d, ", arr->size);
  arr->size += 1;
  printf("After arr %d \n", arr->size);

  return;
}

int delEvidence(NotebookType *arr, int id) {

  char isFound = 0;
  int i = 0;

  while(i++ < arr->size && !isFound){
    if(arr->elements[i].id){
      isFound = 1;
      i = arr->size;  // Sets ending condition of for-loop to end
    }
  }

  if(!isFound){
    return C_NOK;
  }

  for(int j = i; j < arr->size-1; j++){
    copyEvidence(&arr->elements[j], &arr->elements[j+1]);
  }

  arr->size -= 1;
  
  // You need to remove the last element, I just don't know what to.
  // copyEvidence(arr->size - 1, );

  return C_OK;
}

void copyEvidence(EvidenceType *newEv, EvidenceType *oldEv) {
  char newRoom[MAX_STR];
  char newDevice[MAX_STR];

  strcpy(newRoom, oldEv->room);
  strcpy(newDevice, oldEv->device);
  //for(int i = 0; i < MAX_STR; i++){
  //  newRoom[i] = oldEv->room[i];
  //  newDevice[i] = oldEv->device[i];
  //}

  initEvidence(oldEv->id, newRoom, newDevice, oldEv->value, oldEv->timestamp, newEv);
  return;
}

void growNotebook(NotebookType *arr) {
  
  // Create a temporary notebook to store the old data in
  NotebookType *tempNotebook = malloc(sizeof(NotebookType));


  initNotebook(tempNotebook, arr->capacity * 2);
  printf("Capacity: %d\n", tempNotebook->capacity);

  // Deep copy everything in arr into tempNotebook
  for(int i = 0; i < arr->size; i++) {
    copyEvidence(&tempNotebook->elements[i], &arr->elements[i]);
  }

  // Deallocate the elements of arr
  free(arr->elements);

  arr->elements = tempNotebook->elements;
  arr->capacity *= 2;

  free(tempNotebook);
  return;
}

// returns positive integer if ev1 is "larger", negative if ev1 is "smaller", and 0 if equal
int compareEvidence(EvidenceType *ev1, EvidenceType *ev2){
  // Descending by room name
  // Ascending by timestamp 
  //
  if(strcmp(ev1->room, ev2->room) > 0){
    return 1;
  } else if(strcmp(ev1->room, ev2->room) < 0){
    return -1;
  }

  if(ev1->timestamp < ev2->timestamp){
    return 2;
  } else if(ev1->timestamp > ev2->timestamp){
    return -2;
  }

  // If equal
  return 0;

}

void printNotebook(NotebookType *arr) {
  // EMF at most 1 number after decimal
  // EMF above 4.0 should have (HIGH) written beside it
  // Any THERMAL device data should have at most 2 numbers after decimal
  // THERMAL reading below 0.0 should have (COLD) written beside it
  // Any SOUND device data has at most 1 number after decimal
  // SOUND reading below 35.0 should have (WHISPER) beside it
  // SOUND reading above 70.0 should have (SCREAM) beside it
  // Time is in "seconds since starting the hunt"
  // Time is printed ad hours, minutes, and second, separated by a colon, with 2 digits each
  int   id;
  char  room[MAX_STR];
  char  device[MAX_STR];
  float value;
  int   timestamp;

  for(int i = 0; i < arr->size; i++){
    printf("id: %d \n", arr->elements[i].id);
    printf("room: %s \n", arr->elements[i].room);
    printf("device: %s \n", arr->elements[i].device);
    printf("value: %.1f \n", arr->elements[i].value);
    printf("time: %d:%d:%d \n", 
        arr->elements[i].timestamp/3600, 
        (arr->elements[i].timestamp % 3600) / 60,
        arr->elements[i].timestamp % 60);
  }
  return;
}

void cleanupNotebook(NotebookType *arr) {

  printf("DEALLOCATE THE SHIT BROOOO");
  return;
}

