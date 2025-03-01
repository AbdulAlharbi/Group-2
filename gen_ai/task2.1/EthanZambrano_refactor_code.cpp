/*
* Name: Ethan Zambrano, CS 302, Assignment 3
* Input: User input of 2 valid large numbers 
* Output: Prompt/display user to enter 2 valid numbers,
*         then the result of the two added will follow.
*/
#include <iostream>
#include <vector>
#include <thread>
#include <cctype>

using namespace std;

vector<short> num1, num2, resultSum, carryOver; // global vectors (variables)
int num1Size;

void parallelLongAddition(int leftMostIndex, int rightMostIndex);

bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    string inputNum1, inputNum2;
    vector<thread> threadPool;

    // Prompt user for two valid numbers
    do {
        cout << "\nEnter the first number: ";
        cin >> inputNum1;
    } while (!isValidNumber(inputNum1));
    cout << endl;

    do {
        cout << "Enter the second number: ";
        cin >> inputNum2;
    } while (!isValidNumber(inputNum2));
    cout << endl;

    // Convert input strings to digit vectors
    for (char c : inputNum1) num1.push_back(c - '0');
    for (char c : inputNum2) num2.push_back(c - '0');
    num1Size = num1.size();

    // Ensure num2 is the same size as num1
    while (num2.size() < num1Size) num2.insert(num2.begin(), 0);

    // Determine the maximum power-of-2 thread count
    int maxThreads = thread::hardware_concurrency();
    while (maxThreads & (maxThreads - 1)) { // Reduce to nearest power of 2
        maxThreads--;
    }

    // Resize result and carry vectors
    resultSum.resize(num1Size);
    carryOver.resize(num1Size);

    // Calculate digits per thread
    int digitsPerThread = num1Size / maxThreads;
    int leftMostIndex = 0;

    for (int i = 0; i < maxThreads; ++i) {
        int rightMostIndex = leftMostIndex + digitsPerThread - 1;
        if (i == maxThreads - 1) rightMostIndex = num1Size - 1; // last thread takes remaining digits
        threadPool.emplace_back(parallelLongAddition, leftMostIndex, rightMostIndex);
        leftMostIndex = rightMostIndex + 1;
    }

    // Join threads
    for (auto& t : threadPool) t.join();

    // Handle carry overs
    for (int i = num1Size - 1; i >= 0; --i) {
        if (i == 0 && carryOver[i] == 1) {
            resultSum.insert(resultSum.begin(), 1);
        } else if (carryOver[i] == 1) {
            resultSum[i - 1] += carryOver[i];
            if (resultSum[i - 1] >= 10) {
                carryOver[i - 1] = 1;
                resultSum[i - 1] -= 10;
            }
        }
    }

    // Display result
    cout << "Result = ";
    for (short digit : resultSum) cout << digit;
    cout << endl;
    return 0;
}

/*
* FUNCTION_IDENTIFIER: parallelLongAddition()
* parameters: int leftMostIndex, int rightMostIndex
* return value: none
*/
void parallelLongAddition(int leftMostIndex, int rightMostIndex) {
    for (int i = rightMostIndex; i >= leftMostIndex; --i) {
        int sum = num1[i] + num2[i];
        if (sum >= 10) {
            // carry over is a one
            resultSum[i] = sum - 10;
            carryOver[i] = 1;
        } else {
            // carry over is a zero
            resultSum[i] = sum;
            carryOver[i] = 0;
        }
    }
}
