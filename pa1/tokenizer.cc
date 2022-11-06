#include "tokenizer.h"

bool isLetter(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
    return true;
  }
  return false;
}

bool isDigit(char c) {
  if (c >= '0' && c <= '9') {
    return true;
  }
  return false;
}

bool isVarName(std::string str) {
  int len = str.size();
  if (len > 10) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    if (i == 0) { // first char
      if (!isLetter(str[i])) {
        return false;
      }
    }
    else {
      if (!isLetter(str[i]) && !isDigit(str[i])) {
        return false;
      }
    }
    return true;
  }
}

Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  // std::cout << "1";
  // std::stringstream stream(ln);
  // const char delim = ' ';
  // while (std::getline(stream, str, delim)) {
  //   std::cout << str << std::endl;
  //   if (str == " ") continue;
  //   tokens.push_back(getToken());
  // }
  int len = ln.size();
  // int start = 0;
  for (int i = 0; i < len; i++) {
    if (ln[i] == ' ') {
      continue;
    }
    Token t;
    if (ln[i] == ';') {
      t.type = "SEMI";
      t.content = ";";
      tokens.push_back(t);
    }
    else if (ln[i] == '+') {
      t.type = "ADD";
      t.content = "+";
      tokens.push_back(t);
    }
    else if (ln[i] == '-') {
      t.type = "NEG";
      t.content = "-";
      tokens.push_back(t);
    }
    else if (ln[i] == '*') {
      t.type = "MULT";
      t.content = "*";
      tokens.push_back(t);
    }
    else if (ln[i] == '(') {
      t.type = "LPR";
      t.content = "(";
      tokens.push_back(t);
    }
    else if (ln[i] == ')') {
      t.type = "RPR";
      t.content = ")";
      tokens.push_back(t);
    }
    else if (ln[i] == ',') {
      t.type = "COMMA";
      t.content = ",";
      tokens.push_back(t);
    }
    else if (ln[i] == ':') {
      t.type = "COL";
      t.content = ":";
      tokens.push_back(t);
    }
    else if (ln[i] == '0') {
      t.type = "CONST";
      t.content = "0";
      tokens.push_back(t);
    }
    else if (ln[i] == '1') {
      t.type = "CONST";
      t.content = "1";
      tokens.push_back(t);
    }
    else if (isLetter(ln[i])) {
      std::string str;
      str += ln[i];
      i++;
      while (i < len && (isLetter(ln[i]) || isDigit(ln[i]))) {
        str += ln[i];
        i++;
      }
      i--;
      if (str.size() > 10) {
        std::cout << "ERROR: Invalid token." << std::endl;
      }
      else {
        t.type = "VAR_NAME";
        t.content = str;
        tokens.push_back(t);
      }
    }
    else {
      std::cout << "ERROR: Invalid token." << std::endl;
    }
  }
}

bool Tokenizer::advanceToken() {
  // your code starts here
  if (counter + 1 < tokens.size()) {
    return true;
  }
  return false;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  if (counter < tokens.size()) {
    return true;
  }
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  return tokens[counter];
}

void Tokenizer::addCounter() {
  counter++;
}

int Tokenizer::getCounter() {
  return counter;
}
