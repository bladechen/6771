#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<std::string> string_split(const std::string& s, const std::string& delim)
{
    std::vector<std::string> result;
    if (delim.empty())
    {
        result.push_back(s);
        return result;
    }
    std::string::const_iterator substart = s.begin(), subend;
    while (true)
    {
        subend = std::search(substart, s.end(), delim.begin(), delim.end());
        std::string temp(substart, subend);
        if ( !temp.empty())
        {
            result.push_back(temp);
        }
        if (subend == s.end())
        {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}

struct Digit
{
    int inum;
    double dnum;
    bool is_int;
    Digit(int i)
    {
        inum = i;
        is_int = 1;
    }
    Digit(double d)
    {
        dnum = d;
        is_int = 0;
    }
    Digit()
    {
        inum = 0;
        is_int = 0;
    }
    Digit(const Digit& right)
    {
        this->is_int = right.is_int;
        this->inum = right.inum;
        this->dnum = right.dnum;
    }
    friend Digit operator + (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit(a.inum + b.inum);
        else if ( a.is_int == false && b.is_int ) return Digit(a.dnum + b.inum);
        else if (a.is_int && b.is_int == false) return Digit(a.inum + b.dnum);
        else return Digit(a.dnum + b.dnum);
    }
};

bool is_int(const std::string& s)
{
    for (size_t i = 0; i < s.size(); i ++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_double(const std::string& s)
{
    for (size_t i = 0; i < s.size(); i ++)
    {
        if (isdigit(s[i]) ==  false || s[i] != '.')
        {
            return false;
        }
    }
    return true;
}

Digit get_next_digit(std::stack<Digit>& st)
{
    Digit a = st.top();
    st.pop();
    return a;
}

bool do_calc(const std::string& next_symbol, std::stack<Digit>& st)
{
    if (is_int(next_symbol))
    {
        st.push(Digit(std::stoi(next_symbol)));
    }
    else if (is_double(next_symbol))
    {
        st.push(Digit(std::stod(next_symbol)));
    }
    else if (next_symbol == "pop")
    {
        st.pop();
    }
    else if (next_symbol == "add")
    {
        if (st.size() < 2) return false;

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        st.push(a + b);
    }
    else if (next_symbol == "sub")
    {

    }
    else if (next_symbol == "div")
    {

    }
    else if (next_symbol == "mult")
    {

    }
    else if (next_symbol == "sqrt")
    {

    }
    // else if (next_symbol == "revsese")
    // {
    //
    // }
    else
    {
        return false;
    }
    return true;
}


void calc(const std::vector<std::string> & input)
{
    std::stack<Digit> st;
    // bool repeated = 0;

    bool repeated = false;
    std::vector<std::string> repeat_tokens;
    repeat_tokens.clear();
    for (size_t i = 0; i < input.size(); ++ i)
    {
        std::string cur_symbol = input[i];
        if (repeated == true)
        {
            if (cur_symbol == "endrepeat")
            {
                repeated = false;
                // TODO calculate
            }
            else
            {
                repeat_tokens.push_back(cur_symbol);
            }
        }
        else
        {
            if (cur_symbol == "repeat")
            {
                repeated = true;
                repeat_tokens.clear();
            }
            // else if (cur_symbol == "")
            // {
            //
            //
            // }

        }
    }
    return;
}

int main(int argc, char* argv[])
{

	// setup the print out format for the precision required.
	std::cout.setf(std::ios::fixed,std::ios::floatfield);
	std::cout.precision(3);

	// open the file for reading
	std::ifstream in;
	in.open(argv[1]);

	// string to be read into
	std::string s;

    // std::stack<std::string>;
    std::vector<std::string> input;

	// read the file while we have input.
	while (in >> s)
    {
        input.push_back(s);
	}
	in.close();
    Digit a(1.4);
    Digit b(20);
    Digit c = a + b;
    std:: cout <<c.dnum << std::endl;
    std::cout << c.is_int << std::endl;
    // calc(input);

    return 0;
}
