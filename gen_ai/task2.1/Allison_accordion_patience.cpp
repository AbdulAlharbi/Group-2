/*
Name: Allison Kameda, 2001941679, CS 302-1001, ASSIGNMENT 1
Description: Program to play accordian patience and print results
Input: Use command line to open a file of 52 cards
Output: Hopefully the final stacks after playing will be printed
ChatGPT: https://chatgpt.com/share/67c2aca3-978c-8012-88a5-1bc4016c8a48
https://chatgpt.com/canvas/shared/67c2acd21bb08191981748a5d27f0b76
*/

/*Sadly this file does not function without the associated header files*/
#include "LL.h"
#include "LL.cpp"
#include "myStack.h"
#include "myStack.cpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Linked list to store stacks of cards
    LL<myStack<string>> accordion;
    string card;

    // Read 52 cards from input and initialize stacks
    for (int i = 0; i < 52; i++) {
        cin >> card;
        myStack<string> newStack;
        newStack.push(card);
        accordion.tailInsert(newStack);
    }

    /* PLAY ACCORDION PATIENCE */
    auto current = accordion.begin();
    
    while (current != accordion.end()) {
        auto leftThree = current;
        bool hasThreeLeft = true;
        
        // Move iterator three positions back
        for (int i = 0; i < 3; i++) {
            if (leftThree == accordion.begin()) {
                hasThreeLeft = false;
                break;
            }
            --leftThree;
        }

        if (hasThreeLeft) {
            // Check match for card 3 positions left
            if ((*current).peek()[0] == (*leftThree).peek()[0] || 
                (*current).peek()[1] == (*leftThree).peek()[1]) {
                (*leftThree).push((*current).pop());
                if ((*current).isEmpty()) {
                    accordion.removeAtPosition(current);
                }
                current = leftThree;
                continue;
            }
        }

        // Check match for immediate left card
        auto leftOne = current;
        if (leftOne != accordion.begin()) {
            --leftOne;
            if ((*current).peek()[0] == (*leftOne).peek()[0] || 
                (*current).peek()[1] == (*leftOne).peek()[1]) {
                (*leftOne).push((*current).pop());
                if ((*current).isEmpty()) {
                    accordion.removeAtPosition(current);
                }
                current = leftOne;
                continue;
            }
        }

        // Move to next card if no match is found
        ++current;
    }

    /* PRINT RESULTS */
    int stackCount = 0;
    for (auto it = accordion.begin(); it != accordion.end(); ++it) {
        stackCount++;
    }

    cout << stackCount << " Stacks: ";
    for (auto it = accordion.begin(); it != accordion.end(); ++it) {
        cout << (*it).peek() << ":" << (*it).getSize() << " ";
    }
    cout << endl;
    
    return 0;
}
