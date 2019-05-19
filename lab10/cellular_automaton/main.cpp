#include <iostream>
#include <bitset>
#include <string>

using namespace std;

const int ArraySize = 20;
const int NumGenerations = 10;
const string Initial = "0011101101010101001000";

/*
000 -> 0
001 -> 0
010 -> 0
011 -> 1
100 -> 0
101 -> 1
110 -> 1
111 -> 0
*/

int main() {
   bitset<ArraySize + 2> array(Initial);
   for(int j = 0; j < NumGenerations; ++j) {
       bitset<ArraySize + 2> tmpArray(array);
       for(int i = ArraySize; i >= 1 ; --i) {
           cout << (tmpArray[i] ? "#" : "_");
           int val = (int)tmpArray[i-1] << 2 | (int)tmpArray[i] << 1 | (int)tmpArray[i+1];
           array[i] = (val == 3 || val == 5 || val == 6);
       } cout << endl;
   }
}
