#include <iostream>
#include "OrderedArray.h"
#include "UnorderedArray.h"

using namespace std;

int main() {
    cout << "Output of ordered array:" << endl;
    OrderedArray<int> orderedArray(10);
    orderedArray.push(3);
    orderedArray.push(2);
    orderedArray.push(1);
    orderedArray.push(5);
    orderedArray.push(4);
    for (int i = 0; i < orderedArray.GetSize(); i++)
        cout << orderedArray[i] << endl;

    cout << "\nOutput of unordered array:" << endl;
    UnorderedArray<int> unorderedArray(5);
    unorderedArray.push(3);
    unorderedArray.push(2);
    unorderedArray.push(1);
    unorderedArray.push(5);
    unorderedArray.push(4);
    for (int i = 0; i < unorderedArray.GetSize(); i++)
        cout << unorderedArray[i] << endl;
    return 0;
}
