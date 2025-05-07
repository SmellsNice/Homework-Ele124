#include <math.h>
#include <stdio.h>

int main() {
  int popularity, size, homeValue;

  printf("Enter popularity: ");
  scanf("%d", &popularity); /* Inputting popularity */

  printf("\nEnter size: ");
  scanf("%d", &size); /* Inputting size */

  homeValue = (int)((pow(popularity, 3) + pow(size, 2)) * 10000); /* Calculating homeValue */

  printf("\nHome value is: %d", homeValue); /* Outputting homeValue */

  return 0;
}

