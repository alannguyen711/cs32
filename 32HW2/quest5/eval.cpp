#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool syntacticallyValid(string oginfix)
{
    if (oginfix.size() == 0) return false;
    
    for (int i = 0; i < oginfix.size(); i++) // if not a digit or valid operator
    {
        bool validOperator = (oginfix[i] == '!' || oginfix[i] == '|' || oginfix[i] == '&' || oginfix[i] == '(' || oginfix[i] == ')');
        if (isspace(oginfix[i]))
            continue;
        else if (!isdigit(oginfix[i]) && !validOperator)
            return false;
    }
    string infix = "";
    for (int i = 0; i < oginfix.size(); i++) // get rid of spaces
    {
        if (!isspace(oginfix[i]))
            infix += oginfix[i];
    }
    
    if (infix[0] == '|' || infix[0] == '&' || infix[0] == ')')
        return false;
    
    if (infix[infix.size()-1] == '!' || infix[infix.size()-1] == '|' || infix[infix.size()-1] == '&' || infix[infix.size()-1] == '(')
        return false;
    
    for (int i = 0; i < infix.size()-1; i++)
    {
        if (isdigit(infix[i]) && isdigit(infix[i+1])) // no numbers next to each other
            return false;
        if (isdigit(infix[i]) && infix[i+1] == '(') // no ( after numbers
        return false;
    }
    
    for (int i = 0; i < infix.size()-1; i++)
    {
        if (infix[i] == '(') // only number or ! allowed after
        {
            if (!(isdigit(infix[i+1]) || infix[i+1] == '!' || infix[i+1] == '('))
                return false;
        }
    }
    
    for (int i = 1; i < infix.size(); i++)
    {
        if (infix[i] == ')') // only numbers allowed before
        {
            if (!(isdigit(infix[i-1]) || infix[i-1] == ')'))
                return false;
        }
    }
    
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '!') // only numbers or ( can follow
        {
            if (!(isdigit(infix[i+1]) || infix[i+1] == '('))
                return false;
        }
    }
    
    int openCount = 0; int closedCount = 0; // number of ( and ) must be equal
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '(')
            openCount++;
        if (infix[i] == ')')
            closedCount++;
    }
    if (openCount != closedCount)
        return false;
    
    return true;
}

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    if (!syntacticallyValid(infix))
        return 1;
    
    // infix to postfix conversion
    postfix = ""; // Initialize postfix to empty
    stack<char> operators; // Initialize the operator stack to empty
    for (int i = 0; i < infix.size(); i++) // For each character ch in the infix string
    {
        switch (infix[i]) // Switch (ch)
        {
            case '0':// case operand
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix += infix[i];// append ch to end of postfix
                break;
            case '(':
                operators.push('('); // push ch onto the operator stack
                break;
            case ')':
                  // pop stack until matching '('
                while (operators.top() != '(')// While stack top is not '('
                {
                    postfix += operators.top(); // append the stack top to postfix
                    operators.pop(); // pop the stack
                }
                operators.pop(); // pop the stack  // remove the '('
                break;
            case '!':
            case '|':
            case '&':
                    
                while ((!operators.empty()) && (operators.top() != '(')) // While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                {
                    if (infix[i] == '&')
                    {
                        if (operators.top() == '&' || operators.top() == '!')
                        {
                            postfix += operators.top(); // append the stack top to postfix
                            operators.pop(); // pop the stack
                        }
                        else
                            break;
                    }
                    else if (infix[i] == '|')
                    {
                        postfix += operators.top(); // append the stack top to postfix
                        operators.pop(); // pop the stack
                    }
                    else if (operators.top() == '!')
                    {
                        postfix += operators.top(); // append the stack top to postfix
                        operators.pop(); // pop the stack
                    }
                    if (infix[i] == '!')
                        break;
                    
                    
                }
                operators.push(infix[i]); // push ch onto the stack
                break;
        }
    }
    while (!operators.empty()) // While the stack is not empty
    {
        postfix += operators.top(); // append the stack top to postfix
        operators.pop(); // pop the stack
    }
    
    // EVALUATE POSTFIX
    stack<bool> operands; // Initialize the operand stack to empty
    for (int i = 0; i < postfix.size(); i++)// For each character ch in the postfix string
    {
        if (isdigit(postfix[i])) // if ch is an operand
        {
            int value = postfix[i] - '0'; // push the value that ch represents onto the operand stack
            operands.push(values[value]);
        }
        else // ch is a binary operator
        {
            if (postfix[i] == '|' || postfix[i] == '&')
            {
                bool operand2 = operands.top(); // set operand2 to the top of the operand stack
                operands.pop(); // pop the stack
                bool operand1 = operands.top(); // set operand1 to the top of the operand stack
                operands.pop(); // pop the stack
                if (postfix[i] == '|')
                {
                    bool resulting = (operand2 || operand1);
                    operands.push(resulting);
                }
                if (postfix[i] == '&')
                {
                    bool resulting = (operand2 && operand1);
                    operands.push(resulting);
                }
            }
            if (postfix[i] == '!')
            {
                if (operands.top())
                {
                    operands.pop();
                    operands.push(false);
                }
                if (!operands.top())
                {
                    operands.pop();
                    operands.push(true);
                }
            }
        }
            
    }
    // When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
    if (operands.top())
        result = true;
    if (!operands.top())
        result = false;
    
    return 0;
}

int main()
{}
