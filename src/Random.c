#include <stdio.h>
#include "Random.h"

int random(int size) {
  int randomNumber = 0;
  randomNumber = rand()%size;
  return randomNumber;
}