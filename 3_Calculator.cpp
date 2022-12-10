#include <string>
#include <iostream>
#include <stack>
using std::cin, std::cout, std::endl;

void doOperation (char op, std::stack<int>& rpn_num)
{
    int x {0}, y {0};
    y = rpn_num.top();
    rpn_num.pop();
    x = rpn_num.top();
    rpn_num.pop();
    
    if (op == '+')
    {
        rpn_num.push (x + y);
    }
    else if (op == '-')
    {
        rpn_num.push (x - y);
    }
    else if (op == '*')
    {
        rpn_num.push (x * y);
    }
    else if (op == '/')
    {
        rpn_num.push (int(x / y));
    }
}

int main()
{
    std::string input {};
    std::getline(cin, input, '\n');

    std::stack<char> rpn_buf;
    std::string rpn {};
        
    for (char i : input)
    {
        if (i >= '0' and i <= '9')
        {
            rpn += i;
        }
        else if (i == '(')
        {
            if (isdigit (rpn.back()))
            {
                cout << "error: early \'(\'" << endl;
                return -1;
            }            
            rpn_buf.push (i);
        }
        else if (i == '*' or i == '/')
        {
            if (isdigit (rpn.back()))
            {
                rpn += '|';
            }
            
            while (rpn_buf.size() and (rpn_buf.top() == '*' or rpn_buf.top() == '/'))
            {
                rpn += rpn_buf.top();
                rpn_buf.pop();
            }

            rpn_buf.push (i);
        }
        else if (i == '+' or i == '-')
        {   
            if (isdigit (rpn.back()))
            {
                rpn += '|';
            }
            
            while (rpn_buf.size() and (rpn_buf.top() == '*' or rpn_buf.top() == '/' or rpn_buf.top() == '+' or rpn_buf.top() == '-'))
            {
                rpn += rpn_buf.top();
                rpn_buf.pop();
            }

            rpn_buf.push (i);
        }
        else if (i == ')')
        {
            bool pmatch = false;
            while (rpn_buf.size())
            {
                if (rpn_buf.top() == '(')
                {
                    pmatch = true;
                    rpn_buf.pop();
                    break;
                }
                rpn += rpn_buf.top();
                rpn_buf.pop();
            }
            if (!pmatch)
            {
                cout << "error: no matching \'(\'" << endl;
                return -1;
            }
        }
    }

    for (auto i = rpn_buf.size(); i > 0; i--)
    {
        if (rpn_buf.top() == '(')
        {
            cout << "error: no matching \')\'" << endl;
            return -1;
        }
        rpn += rpn_buf.top();
        rpn_buf.pop();
    }
    //rpn is ready here

    cout << "rpn: ";
    for (char i : rpn)
    {
        cout << i;
    }
    cout << endl;

    std::stack<int> rpn_num;
    std::string num {};
    for (char i : rpn)
    {
        if (isdigit (i))
        {
            num += i;
            continue;
        }
        else if (i == '|')
        {
            rpn_num.push (std::stoi (num));
            num.erase();
        }
        else if (i == '+' or i == '-' or i == '*' or i == '/')
        {
            if (!num.empty())
            {
                rpn_num.push (std::stoi (num));
                num.erase();
            }
            doOperation (i, rpn_num);
        }
    }

    cout << "result: " << rpn_num.top() << endl;
    cout << endl; 
}