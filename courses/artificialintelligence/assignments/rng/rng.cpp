// add your imports here
#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::cin;
using std::bitset;

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
  currentNumber = seed; //initially

  cout << "Please enter a upperRange:";
  cin >> upperRange;

  cout << "Please enter a lowerRange:";
  cin >> lowerRange;

  cout << "Please enter the numbers you want to generate:";
  cin >> numbersGenerated;

  cout << endl;

  for(int i = 0; i < numbersGenerated; i++){
    cout << "---------------------------------------------------------------\n";
    cout << "seed as int: " << seed << endl;
    cout << "seed as binary " << bitset<32>(seed) << endl;

    //  xorshift the value by 13 bits to the left;
    tempNumber = seed << 13;
    currentNumber ^= tempNumber;

    //  xorshift the value by 17 bits to the right;
    tempNumber = seed >> 17;
    currentNumber ^= tempNumber;

    //  xorshift the value by 5 bits to the left;
    tempNumber = seed >> 5;
    currentNumber ^= tempNumber;

    //set seed for next round
    seed = currentNumber;

    //clamp final value
    cout << "Value before clamping: " << currentNumber << endl;
    currentNumber = lowerRange + (currentNumber % (upperRange - lowerRange + 1));

    //print out binary and int generated from RNG
    cout << endl << "Random number generated as int: " << currentNumber << endl;
  }
}