// add your imports here
#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>

using std::bitset, std::string, std::cin, std::endl, std::cout, std::getline, std::istringstream;
using std::vector;

int main(){

  //unsigned ints are 32 bits
  unsigned int currentNumber = 1;
  unsigned int seed = 1;
  unsigned int tempNumber = 0;
  int numbersGenerated = 5;
  unsigned upperRange = 0, lowerRange = 0;

//  cout << "Please enter a seed: ";
//  cin >> seed;
//  cout << endl;
//  currentNumber = 0; //initially
//
//  cout << "Please enter a upperRange:";
//  cin >> upperRange;
//
//  cout << "Please enter a lowerRange:";
//  cin >> lowerRange;
//
//  cout << "Please enter the numbers you want to generate:";
//  cin >> numbersGenerated;

  cout << "INPUT: Seed, Numbers generated, lower range, upper range:" << endl;

  vector<int> inputVec;
  string input;
  unsigned int tempInt;
  getline(std::cin, input); // Read a line of input

  string app;
  int counter = 0;

  for(int i = 0; i < input.size(); i++){ //loop through string
    if(input[i] == ' '){ //if we have a space, start adding numbers
      tempInt = stoi(app, 0, 10); //string to int (string, start, base)
      inputVec.push_back(tempInt); //add to vector of unsigned ints
      app.clear(); //clear string for later use
      continue;
    }
    app += input[i];
  }

  //we miss last number in string, so if anything is left inside app, then we add it to our vec
  if (!app.empty()) {
    tempInt = stoi(app, 0, 10);
    inputVec.push_back(tempInt);
  }

  //set prompts
  seed = inputVec[0];
  numbersGenerated = inputVec[1];
  lowerRange = inputVec[2];
  upperRange = inputVec[3];

  cout << "seed: " << inputVec[0] << endl;
  cout << "numbers generated: " << inputVec[1] << endl;
  cout << "lower range: " << inputVec[2] << endl;
  cout << "upper range: " << inputVec[3] << endl;

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
    cout << "clamped value between: " << inputVec[2] << " and " << inputVec[3] << endl;
    cout << "Value before clamping: " << currentNumber << endl;
    currentNumber = lowerRange + (currentNumber % (upperRange - lowerRange + 1));

    //print out binary and int generated from RNG
    cout << endl << "Random number generated as int: " << currentNumber << endl;
  }
}