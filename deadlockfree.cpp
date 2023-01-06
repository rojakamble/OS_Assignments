// deadlock free program

#include <iostream>
using namespace std;

//calculate minimum number of resources needed
int min_resource(int process, int need) {
   int calculate = 0;
   calculate = process * (need - 1) + 1;
   return calculate;
}
int main() {
   int process = 5, need = 3;
   cout << "minimum required resources are : " << min_resource(process, need);
   return 0;
}