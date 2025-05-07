#include <math.h>
#include <stdio.h>

int computeHomeValue(int popularity, int size);

int main() {
  int popularity, size, homeValue;

  printf("Enter popularity: ");
  scanf("%d", &popularity); /* Inputting popularity */

  printf("\nEnter size: ");
  scanf("%d", &size); /* Inputting size */

  homeValue = computeHomeValue(popularity, size); /* Calling the computeHomeValue function */

  printf("\nHome value is: %d", homeValue); /* Outputting homeValue */

  return 0;
}

int computeHomeValue(int popularity, int size) {
  return (int)((pow(popularity, 3) + pow(size, 2)) * 10000); /* Calculating popularity */
}

