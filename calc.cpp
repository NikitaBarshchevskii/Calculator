#include <iostream>
#include <string>
#include "Stack.hpp"
#include "StackArray.hpp"
#include <vector>

void printStack(StackArray<std::string> &stack)
{
  std::cout << "STACK:" << '\n';
  for (int i = 1; i <= stack.getCapacity(); i++)
  {
    std::string temp = stack.at(i);
    std::cout << temp << '\n';
  }
  std::cout << "STACK END\n\n";
}

int evaluatePostfix(std::vector <std::string> postfix, size_t stackSize = 100)
{
  std::cout << "\nEvaluate postfix:\n";
  int oper_1 = 0;
  int oper_2 = 0;
  StackArray<std::string> tempStack(stackSize);

  for (std::string elem : postfix)
  {
    if (elem == "+")
    {
      oper_2 = stoi(tempStack.pop());
      oper_1 = stoi(tempStack.pop());
      tempStack.push(std::to_string(oper_1 + oper_2));
    }
    else if (elem == "-")
    {
      oper_2 = stoi(tempStack.pop());
      oper_1 = stoi(tempStack.pop());
      tempStack.push(std::to_string(oper_1 - oper_2));
    }
    else if (elem == "*")
    {
      oper_2 = stoi(tempStack.pop());
      oper_1 = stoi(tempStack.pop());
      tempStack.push(std::to_string(oper_1 * oper_2));
    }
    else if (elem == "/")
    {
      oper_2 = stoi(tempStack.pop());
      oper_1 = stoi(tempStack.pop());
      tempStack.push(std::to_string(oper_1 / oper_2));
    }
    else
    {
      tempStack.push(elem);
    }
    printStack(tempStack);
  }
  return stoi(tempStack.pop());
}

bool getPostfixFromInfix(std::string infix, std::vector <std::string> postfix, size_t stackSize = 100)
{
  std::cout << "Get postfix from infix:\n";
  std::string temp;
  StackArray<std::string> tempStack(stackSize);

  for (int i = 0; i < infix.length(); i++)
  {
    switch (infix.at(i))
    {
    case '(':
      tempStack.push("(");
      break;

    case '+':
      if (!tempStack.isEmpty())
      {
        temp = tempStack.pop();
        while (temp == "+" || temp == "-" || temp == "/" || temp == "*")
        {
          postfix.push_back(temp);
          if (tempStack.isEmpty())
          {
            break;
          }
          temp = tempStack.pop();
        }
      }
      tempStack.push("+");
      break;

    case '-':
      if (!tempStack.isEmpty())
      {
        temp = tempStack.pop();
        while (temp == "+" || temp == "-" || temp == "/" || temp == "*")
        {
          postfix.push_back(temp);
          if (tempStack.isEmpty())
          {
            break;
          }
          temp = tempStack.pop();
        }
      }
      tempStack.push("-");
      break;

    case '*':
      if (!tempStack.isEmpty())
      {
        temp = tempStack.pop();
        while (temp == "*" || temp == "/")
        {
          postfix.push_back(temp);
          if (tempStack.isEmpty())
          {
            break;
          }
          temp = tempStack.pop();
        }
      }
      tempStack.push("*");
      break;

    case '/':
      if (!tempStack.isEmpty())
      {
        temp = tempStack.pop();
        while (temp == "*" || temp == "/")
        {
          postfix.push_back(temp);
          if (tempStack.isEmpty())
          {
            break;
          }
          temp = tempStack.pop();
        }
      }
      tempStack.push("/");
      break;

    case ')':
      temp = tempStack.pop();
      while (temp != "(")
      {
        postfix.push_back(temp);
        if (tempStack.isEmpty())
        {
          break;
        }
        temp = tempStack.pop();
      }
      break;

    default: // Вся магия тут (магия 333 + 444 = 777)
      if (infix.at(i) == ' ')
      {
        break;
      }
      else
      {
        int count = 0;
        while (infix.at(i + count) != ' ')
        {
          count++;
          if (i + count >= infix.length())
          {
            break;
          }
        }
        postfix.push_back(infix.substr(i, count));
        i += count - 1;
        break;
      }
    }
    printStack(tempStack);
  }
 
  while (!tempStack.isEmpty())
  {
    postfix.push_back(tempStack.pop());
  }

  for (std::string elem : postfix)
  {
    std::cout << elem << "\n";
  }

  std::cout << "\nANSWER: " << evaluatePostfix(postfix);
  return tempStack.isEmpty();
}

int main()
{
  try
  {
    std::vector <std::string> postfix;
    std::string inputTemp;
    std::getline(std::cin, inputTemp);
    
    getPostfixFromInfix(inputTemp, postfix);

  }
  catch (const StackOverflow& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const StackUnderflow& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const WrongStackSize& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
