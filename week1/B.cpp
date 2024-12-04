#include <iostream>  
#include <vector>
using namespace std;


long long findMax(vector<int> numbers) {
    int arraySize = numbers.size();
    bool currPositive = true;
    long long sum = 0;

    if (numbers[0] < 0) {
        currPositive = false;
    }

    
    for (int i = 0; i < arraySize;) {
        int num = numbers[i];
        int j = i;

        for (; j < arraySize; j++) {
            if (currPositive) {
                if (numbers[j] < 0) {
                    currPositive = false;
                    
                    break;
                }
            } else {
                if (numbers[j] > 0) {
                    currPositive = true;
                    break;
                }
            }
            if (numbers[j] > num) {
                num = numbers[j];
            }
        }
        sum += num;
        i = j;
    }

    return sum;
}

int main() {
    int testCases;
    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        int numberSize;
        cin >> numberSize;
        vector<int> numbers(numberSize);
        for (int j = 0; j < numberSize; j++) {
            cin >> numbers[j];
        }

        cout << findMax(numbers) << endl;
    }

    return 0;
}
