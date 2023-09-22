// add your imports here
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(){

  //unsigned ints are 32 bits
  unsigned int currentNumber = 1;
  unsigned int seed = 1;
  unsigned int tempNumber = 0;
  int numbersGenerated = 5;
  unsigned upperRange = 0, lowerRange = 0;

  cout << "Please enter a seed: ";
  cin >> seed;
  cout << endl;
  seed = currentNumber;

  for(int i = 0; i < numbersGenerated; i++){
    cout << "---------------------------------------------------------------\n";
    cout << "seed is: " << seed << endl;

    //  xorshift the value by 13 bits to the left;
    tempNumber = seed << 13;
    currentNumber ^= tempNumber;

    //  xorshift the value by 17 bits to the right;
    tempNumber = seed >> 17;
    currentNumber ^= tempNumber;

    //  xorshift the value by 5 bits to the left;
    tempNumber = seed >> 5;
    currentNumber ^= tempNumber;

    //clamp final value
    currentNumber = lowerRange + (currentNumber % (upperRange - lowerRange + 1));

    cout << endl << "Random number generated: " << currentNumber << endl;

    //set seed for next round
    seed = currentNumber;
  }
}