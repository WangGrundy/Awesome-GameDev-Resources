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

  for(int i = 0; i < numbersGenerated; i++){
    //  xorshift the value by 13 bits to the left;
    seed ^= seed << 13;

    //  xorshift the value by 17 bits to the right;
    seed ^= seed >> 17;

    //  xorshift the value by 5 bits to the left;
    seed ^= seed << 5;

    //clamp final value
    currentNumber = lowerRange + (seed % (upperRange - lowerRange + 1));

    //print out binary and int generated from RNG
    cout << currentNumber << endl;
  }
}