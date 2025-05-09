#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_signal(int signal[], int size);
void clean_signal(int signal[], int size);

int find_max(int signal[], int size);
int find_min(int signal[], int size);
float find_average(int signal[], int size);

int main() {
  int signal[100], size = sizeof(signal) / sizeof(signal[0]);	// We define the signal array and it's size, and while we don't really need to calculate the size it would be more convenient to do so if we were to change the array size in the future (not that I'll ever touch this script again)

  srand(time(NULL));	// We seed the random number generation, which I totally forgot to do for the last homework submission.

  generate_signal(signal, size);

  printf("Original signal:\n");
  for(int i = 0; i < size; i++) {
    printf("%d ", signal[i]);
  }

  clean_signal(signal, size);

  printf("\n\nCleaned signal:\n");
  for(int i = 0; i < size; i++) {
    printf("%d ", signal[i]);
  }

  printf("\n\nMax: %d, Min: %d, Average: %.2f", find_max(signal, size), find_min(signal, size), find_average(signal, size));

  return 0;
}

void generate_signal(int signal[], int size) {
  for(int i = 0; i < size; i++) {
    signal[i] = rand() % 100 + 1;
  }

  int c = 0;

  while(c < 10) {	// Ensures that we have 10 unique arrays with -1 values since simply generating the array numbers with rand can lead to overlaps.
    int b = rand() % size;

    if(signal[b] != -1) {	// Checks to make sure that signal[b] hasn't already been replaced with -1.
      signal[b] = -1;
      c++;
    }
  }
}

void clean_signal(int signal[], int size) {
  int left, right;	// "left" and "right" are for storing the nearest valid neighbours (as in not -1).

  for(int i = 0; i < size; i++) {
    if(signal[i] == -1) {
      if(i == 0) {
        int d = 1;

        while (i + d < size && signal[i + d] == -1) {	// We make sure that our array does not surpass size, not really necessary since it has to find a valid neighbour before that anyway.
          d++;
        }

        right = signal[i + d];

        signal[i] = right;	// Could also divide this value by 2, if we go by the logic that all values out of bounds are equal to 0 but it doesn't really matter.
      }

      else if(i == size - 1) {
        int c = 1;

        while (i - c >= 0 && signal[i - c] == -1) {	// Same as above, just decreasing.
          c++;
        }

        left = signal[i - c];

        signal[i] = left;
      }

      else {
        int d = 1, c = 1;

        while (i + d < size && signal[i + d] == -1) {	// The nice thing is, since we have already ensured the edge cases are valid, we know for sure that we will find a valid "left" and "right" value even if its 10 -1's in a row.
          d++;
        }

        while (i - c >= 0 && signal[i - c] == -1) {
          c++;
        }

        right = signal[i + d];
        left = signal[i - c];

        signal[i] = (left + right) / 2;	// We find the average of the two closest valid neightbours. Do note that the value is truncated since our array is defined as an integer(s?).
      }
    }
  }
}

int find_max(int signal[], int size) {
  int max = signal[0];

  for(int i = 1; i < size; i++) {
    if(signal[i] > max) {	// We just rinse all the arrays to find the biggest value.
      max = signal[i];
    }
  }

  return max;
}

int find_min(int signal[], int size) {
  int min = signal[0];

  for(int i = 1; i < size; i++) {
    if(signal[i] < min) {	// The opposite of what we do above.
      min = signal[i];
    }
  }

  return min;
}

float find_average(int signal[], int size) {
  float total = 0;

  for(int i = 0; i < size; i++) {
    total += signal[i];
  }

  return total / size;	// We find and return the average value using the total and size, I dunno why I even wrote this comment since it's pretty clear.
}

