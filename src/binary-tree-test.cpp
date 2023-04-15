#include <iostream>
#include <string>
#include "TreeParser.h"

using std::cout;
using std::endl;
using std::string;

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(int testNum, int& correct, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(int testNum, int& correct, double whatItShouldBe, double whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

bool checkTest(int testNum, int& correct, double whatItShouldBe, double whatItIs, double fudge) {

  if ((whatItShouldBe <= whatItIs && whatItShouldBe > whatItIs - fudge) || (whatItShouldBe >= whatItIs && whatItShouldBe < whatItIs + fudge)) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been close to " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

int test_SimpleExpressions(){

  cout << "--------test_SimpleExpressions Tests--------" << endl;

  int testNum  = 1;
  int correct = 0;
  TreeParser tp;

  string expression = "(4+7)";
  tp.processExpression(expression);
  tp.displayParseTree();
  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 11, answer); // 1

  cout << "The result is: " << tp.computeAnswer() << endl;
  expression = "(7-4)";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 3, answer); // 2

  expression = "(9*5)";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 45, answer); // 3

  expression = "(4^3)";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 64, answer); // 4

  return (testNum - 1 >= correct && correct > 0);
}


int test_TwoOrMoreOperators() {

  cout << "--------test_TwoOrMoreOperators Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;

  string expression = "((2-5)-5)";
  tp.processExpression(expression);
  tp.displayParseTree();
  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, -8, answer); // 1

  cout << "The result is: " << tp.computeAnswer() << endl;
  expression = "(5 * (6/2))";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 15, answer); // 2

  expression = "((6 / 3) + (8 * 2))";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 18, answer); // 3

  return (testNum - 1 >= correct && correct > 0);
}

int test_MultiDigitNumbers() {

  cout << "--------test_MultiDigitNumbers Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;

  string expression = "(543+321)";
  tp.processExpression(expression);
  tp.displayParseTree();
  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 864, answer); // 1

  cout << "The result is: " << tp.computeAnswer() << endl;
  expression = "(7.5-3.25)";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 4.25, answer); // 2

  return (testNum - 1 >= correct && correct > 0);
}

int test_BigExpressions() {


  cout << "--------test_BigExpressions Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;

  string expression = "(5 + (34 - (7 * (32 / (16 * 0.5)))))";
  tp.processExpression(expression);
  tp.displayParseTree();
  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 11, answer); // 1

  cout << "The result is: " << tp.computeAnswer() << endl;
  expression = "((5*(3+2))+(7*(4+6)))";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 95, answer); // 2

  expression = "(((2+3)*4)+(7+(8/2)))";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 31, answer); // 3

  expression = "(((((3+12)-7)*120)/(2+3))^3)";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 7077888, answer); // 4


  expression = "(((((9 + (2 * (110 - (30 / 2)))) * 8) + 1000) / 2) + (((3 ^ 4) + 1) / 2))";
  tp.processExpression(expression);
  tp.displayParseTree();
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 1337, answer); // 5
  return (testNum - 1 >= correct && correct > 0);

}

int main(int argc, char** argv) {


  int test = 0;
  int count = 0;

  if (argc > 1) {
    test = std::stoi(argv[1]);
  }
  switch (test) {
  case 0:
    if (test_SimpleExpressions()) count++;
    if (test_TwoOrMoreOperators()) count++;
    if (test_MultiDigitNumbers()) count++;
    if (test_BigExpressions()) count++;

    cout << "----------------" << endl;
    cout << "Passed " << count << " out of 4 group tests" << endl;
    cout << "--End of tests--" << endl;
    return count != 3;
  case 1:
    return !test_SimpleExpressions();
  case 2:
    return !test_TwoOrMoreOperators();
  case 3:
    return !test_MultiDigitNumbers();
  case 4:
    return !test_BigExpressions();
  }

  return 0;
}
