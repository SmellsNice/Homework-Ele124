#include <stdio.h>
#include <stdlib.h>

int main( void )
{
//variable declarations
float aRandomNumber ;
for( int i=0; i<50; i++ )
{ //Generates a random number between 0 and 20
aRandomNumber = rand()%21;
printf("Rand modulo 21 gives gives %.2f \n", aRandomNumber);
aRandomNumber = aRandomNumber /100;
printf("We divide by 100 to get %.2f \n \n", aRandomNumber);
}
system("pause");
} /* end function main */
