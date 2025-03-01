/*
Name: Allison Kameda, 2001941679, CS 202-1004, WORKSHEET 8
Description: Follows Worksheet 8 instructions, identifies palindromes
Input: String
Output: Will report whether the string was a palindrome or not
ChatGPT: https://chatgpt.com/share/67c2a173-8f44-8012-ae03-88526c38b3e0 
https://chatgpt.com/canvas/shared/67c2a408dad481919a25cd017b002871
*/

#include <iostream>
#include <string>
using namespace std;

/*
Purpose:
This function checks whether the characters at the given indices
leftLetter and rightLetter in the string str are the same, ignoring case
differences.

Parameters:
str (string): The input string.

leftLetter (int): Index of the left character to compare.

rightLetter (int): Index of the right character to compare.

Returns:
true if the characters match (ignoring case).

false otherwise.
*/
bool isPalindrome(string str, int leftLetter, int rightLetter)
{
    //Compare chars after turned to lowercase
    return (tolower(str[leftLetter]) == tolower(str[rightLetter]));
}

/*
Purpose:
This function determines whether the given string is a palindrome using a recursive approach.

Parameters:
str (string): The input string.

Returns:
true if the string is a palindrome.

false if the string is not a palindrome.
*/
bool testString(string str){
    int length = str.length();
    int start = 0;
    int end = length-1;

    /* Checks if the first and last characters of the string match using isPalindrome(). */
    if (!isPalindrome(str, start, end) == false){
        /* If they don’t match, the function immediately returns false */
        return false;
    }

    /*If they match and the string’s length is more than 1, the function recursively
    calls itself with a smaller substring (excluding the first and last characters).
    If the function reaches a single-character string, it returns true (indicating a palindrome).*/
    if (length > 1) {
        return testString(str.substr(1, length - 2));
    }

    //Is a palindrome (this willl only happen if str.length is 1)
    return true;

}

int main(){
    string x = "";
    /*Prompt the user to enter a string.*/
    cout << "Enter a string: ";
    getline(cin, x);

    /*Print outcome of testString()*/
    if (testString(x) == false){
        cout << x << " is not a Palindrome" << endl;
    } else {
        cout << x << " is a Palindrome" << endl;
    }
}
