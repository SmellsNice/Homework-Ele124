#include <stdio.h>
#include <stdlib.h>

void Hunerler(float ItemPrice, float *donationTotal, float *profitTotal);

int main() {
  float randomNumber, donationTotal = 0.0, profitTotal = 0.0;
  FILE *donationBook = fopen("donations.txt", "w");
  
  for(int i = 0; i<50; i++) {
    randomNumber = (rand() % 2000) / 100.0; // Get a float between 0.0 and 20.0. Mind the 100.0 otherwise the output would be integer thus truncated.
    printf("Item is %.2f\n", randomNumber);
    fprintf(donationBook, "Item is %.2f\n", randomNumber);

    Hunerler(randomNumber, &donationTotal, &profitTotal);
  }

  printf("Donation is %.2f\nProfit is %.2f", donationTotal, profitTotal);
  fprintf(donationBook, "Donation is %.2f\nProfit is %.2f", donationTotal, profitTotal);

  fclose(donationBook);
  return 0;
}

void Hunerler(float ItemPrice, float *donationTotal, float *profitTotal) {
  int ProfitPart = (int)ItemPrice; // Truncate ItemPrice to find the profit.
  
  *donationTotal += ItemPrice - ProfitPart; // Find the leftover donation.
  *profitTotal += ProfitPart;
}
