#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void Print (const vector<int>& vec) {
    for (int i =0; i < vec.size(); ++i) {
        cout << vec[i] << '  ';
    }
}

int main () {
    vector <int> vec {5,1,6,3473,134};
    map <string, int> {{"first"s,1}, {"second"s, 2}};
    Print (vec);
    return 0;
}