#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
          int start = 0;
          int end = s.length()-1;

          //if we've gone through entire word, it's a palindrome
          if (start == end) {
              return true;
          }
          //if starting and ending letters don't match, it's not a palindrome, returnn false
          else if (s.at(start) != s.at(end)) {
              return false;
          }
          //else we cut first and last letters out of the string, then pass it to this function again.
          else {
              s = s.substr(1, s.size()-2);
              return palindrome_recursive(s);
          }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
