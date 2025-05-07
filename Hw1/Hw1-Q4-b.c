#include <math.h>
#include <stdio.h>

void computeHomeValue(void);

int main() {
  computeHomeValue(); /* Calling computeHomeValue function */

  return 0;
}

void computeHomeValue(void) {
  int popularity, size, homeValue;

  printf("Enter popularity: ");
  scanf("%d", &popularity); /* Inputting popularity */

  printf("\nEnter size: ");
  scanf("%d", &size); /* Inputting size */

  homeValue = (int)((pow(popularity, 3) + pow(size, 2)) * 10000); /* Calculating homeValue */

  printf("\nHome value is: %d", homeValue); /* Outputting homeValue */
}

