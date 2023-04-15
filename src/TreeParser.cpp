// Copyright 2023, Bradley Peterson, Weber State University, all rights reserved. (4/2023)

#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cstdio>

#include "TreeParser.h"

using std::stack;
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::pow;


TreeParser::TreeParser() {
  this->initialize();
}
TreeParser::~TreeParser() {
  this->deleteTree(this->root);
}

void TreeParser::deleteTree(Node* p) {
  if (p) {
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
  }
}

// Public computeAnswer
double TreeParser::computeAnswer()
{
  computeAnswer(root);
  return this->mathStack.top();
}

// Private computeAnswer
void TreeParser::computeAnswer(Node* ptr)
{
  if (ptr)
  {
    computeAnswer(ptr->left);
    computeAnswer(ptr->right);

    // Do I want this stuff outside the above if statement, or here?
    if (isDigit(ptr->data.at(0)))
    {
      this->mathStack.push(std::stod(ptr->data));
    }
    else if (isOperator(ptr->data.at(0)))
    {
      double second = mathStack.top();
      mathStack.pop();
      double first = mathStack.top();
      mathStack.pop();
      double result;

      if (ptr->data == "+")
      {
        result = first + second;

      }

      else if (ptr->data == "-")
      {
        result = first - second;
      }

      else if (ptr->data == "*")
      {
        result = first * second;
      }

      else if (ptr->data == "/")
      {
        result = first / second;
      }

      else if (ptr->data == "^")
      {
        result = pow(first, second);
      }

      mathStack.push(result);
    }

  }
}

void TreeParser::processExpression(Node* p)
{
  while (position < expression.length())
  {
    if (expression.at(position) == '(')
    {
      p->left = new Node;
      // p->left->data = expression.at(position); Don't put data in yet, right?
      position++;
      processExpression(p->left);
    }

    else if (isDigit(expression.at(position)) || expression.at(position) == '.')
    {
      string tempString = expression.substr(position, 1);
      position++;

      while (isDigit(expression.at(position)) || expression.at(position) == '.')
      {
        tempString += expression.at(position);
        position++;
      }
      p->data = tempString;
      return;
    }

    else if (isOperator(expression.at(position)))
    {
      p->data = expression.at(position);
      p->right = new Node;
      position++;
      processExpression(p->right);
    }

    else if (expression.at(position) == ')')
    {
      position++;
      return;
    }

    else if (expression.at(position) == ' ')
    {
      position++;
      // processExpression(p); "let it go around for the next iteration of the loop"
    }
  }
}

bool TreeParser::isDigit(char c) const
{
  return (isdigit(c)) ? (true) : (false); // || c == '.'
}

bool TreeParser::isOperator(char c) const
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') ? (true) : (false);
}

void TreeParser::processExpression(string& expression)
{
  if (expression != "")
  {
    this->expression = expression;
    position = 0;

    this->root = new Node;

    processExpression(root);
  }
}

// Public inOrder
void TreeParser::inOrderTraversal() const
{
  inOrderTraversal(root);
}

// Private inOrder
void TreeParser::inOrderTraversal(Node* p) const
{
  if (p)
  {
    inOrderTraversal(p->left);
    cout << p->data << " ";
    inOrderTraversal(p->right);
  }
}

// Public postOrder
void TreeParser::postOrderTraversal() const
{
  postOrderTraversal(root);

}

// Private postOrder
void TreeParser::postOrderTraversal(Node* p) const
{
  if (p)
  {
    postOrderTraversal(p->left);
    postOrderTraversal(p->right);
    cout << p->data << " ";
  }
}

void TreeParser::initialize() {
  expression = "";
  position = 0;
  while (!mathStack.empty()) {
    mathStack.pop();
  }
}

double TreeParser::castStrToDouble(const string& s) const {
  return std::stod(s);
}

string TreeParser::castDoubleToStr(const double d)  const {
  return std::to_string(d);
  
}

void TreeParser::displayParseTree() const {
  cout << "The expression seen using in-order traversal: ";
  this->inOrderTraversal();
  cout << endl;
  cout << "The expression seen using post-order traversal: ";
  this->postOrderTraversal();
  cout << endl;
}
//
//
//void TreeParser::initialize() {
//  
//  // TODO: Uncomment when these data members are declared
//  //expression = "";
//  //position = 0;
//  //while (!mathStack.empty()) {
//  //  mathStack.pop();
//  //}
//}
//
//double TreeParser::castStrToDouble(const string& s) {
//  istringstream iss(s);
//  double x;
//  iss >> x;
//  return x;
//}
//
//string TreeParser::castDoubleToStr(const double d) {
//  ostringstream oss;
//  oss << d;
//  return oss.str();
//
//}
//
//
//void TreeParser::displayParseTree() const {
//
//  // TODO, comment out when these methods are implemented
//  //cout << "The expression seen using in-order traversal: ";
//  //inOrderTraversal();
//  //cout << endl;
//  //cout << "The expression seen using post-order traversal: ";
//  //postOrderTraversal();
//  //cout << endl;
//
//}
//
//string TreeParser::computeAnswer() {
//  return "";
//}
//
//void TreeParser::processExpression(const string& expression) {
// 
//}
