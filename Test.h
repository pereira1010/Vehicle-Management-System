

#ifndef TEST_H
#define TEST_H
#include <string>
using namespace std;


// Constants for the menu options
  #define PRIVATE 1
  #define NODE_BASIC 2
  #define LL_BASIC 3
  #define NODE_COMP_OPERATORS 4
  #define RUN_ALL 5
  #define DONE 0

  const int max_test_menu_option = 5;  // Maximum number of menu options

// Function prototypes
  int getTestMenuChoice();
  void promptUnitTest();

  void testPrivate();
  void testNodeBasic();
  void testLinkedListBasic();
  void testNodeCompOperators();


#endif // TEST_H