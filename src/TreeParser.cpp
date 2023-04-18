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


TreeParser::~TreeParser() {
  this->clear();
}

void TreeParser::clear() {
  this->clear(this->root);
  this->root = nullptr;
}

void TreeParser::clear(Node* p) {
  if (p) {
    clear(p->left);
    clear(p->right);
    delete p;
  }
  expression = "";
  position = 0;
  while (!mathStack.empty()) {
    mathStack.pop();
  }
}

void TreeParser::processExpression(string& expression) {
  if (expression != "") {
    this->clear();
    this->expression = expression;
    position = 0;

    this->root = new Node;

    processExpression(root);
  }
}

void TreeParser::processExpression(Node* p) {
  while (position < expression.length()) {
    if (expression.at(position) == '(') {
      p->left = new Node;
      // p->left->data = expression.at(position); Don't put data in yet, right?
      position++;
      processExpression(p->left);
    }
    else if (isDigit(expression.at(position)) || expression.at(position) == '.') {
      string tempString = expression.substr(position, 1);
      position++;
      while (isDigit(expression.at(position)) || expression.at(position) == '.') {
        tempString += expression.at(position);
        position++;
      }
      p->data = tempString;
      return;
    }
    else if (isOperator(expression.at(position))) {
      p->data = expression.at(position);
      p->right = new Node;
      position++;
      processExpression(p->right);
    }
    else if (expression.at(position) == ')') {
      position++;
      return;
    }
    else if (expression.at(position) == ' ') {
      position++;
    }
  }
}

// Public computeAnswer
double TreeParser::computeAnswer() {
  computeAnswer(root);
  return this->mathStack.top();
}

// Private computeAnswer
void TreeParser::computeAnswer(Node* ptr) {
  if (ptr) {
    computeAnswer(ptr->left);
    computeAnswer(ptr->right);

    if (isDigit(ptr->data.at(0))) {
      this->mathStack.push(std::stod(ptr->data));
    }
    else if (isOperator(ptr->data.at(0))) {
      double second = mathStack.top();
      mathStack.pop();
      double first = mathStack.top();
      mathStack.pop();
      double result;

      if (ptr->data == "+") {
        result = first + second;
      }
      else if (ptr->data == "-") {
        result = first - second;
      }
      else if (ptr->data == "*") {
        result = first * second;
      }
      else if (ptr->data == "/") {
        result = first / second;
      }
      else if (ptr->data == "^") {
        result = pow(first, second);
      }
      mathStack.push(result);
    }
  }
}


bool TreeParser::isDigit(char c) const {
  return (c >= '0' && c <= '9');
}

bool TreeParser::isOperator(char c) const {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Public inOrder
void TreeParser::inOrderTraversal() const {
  inOrderTraversal(root);
}

// Private inOrder
void TreeParser::inOrderTraversal(Node* p) const {
  if (p) {
    inOrderTraversal(p->left);
    cout << p->data << " ";
    inOrderTraversal(p->right);
  }
}

// Public postOrder
void TreeParser::postOrderTraversal() const {
  postOrderTraversal(root);
}

// Private postOrder
void TreeParser::postOrderTraversal(Node* p) const {
  if (p) {
    postOrderTraversal(p->left);
    postOrderTraversal(p->right);
    cout << p->data << " ";
  }
}

void TreeParser::displayParseTree() const {
  cout << "The expression seen using in-order traversal: ";
  this->inOrderTraversal();
  cout << endl;
  cout << "The expression seen using post-order traversal: ";
  this->postOrderTraversal();
  cout << endl;
}
