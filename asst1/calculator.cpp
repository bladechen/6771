/// @file:   calculator.cpp
/// @brief:  a simple stack based calculator
/// @author: bladechen
///
/// 2017-08-15

#include <algorithm>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

class Digit
{
    // maybe we should put private data declaration in the end of the Digit class.
    // but put here to be more outstanding.
private:
    int inum = 0;
    double dnum = 0.0;
    bool is_int = true;

public:
    Digit(int i):inum{i}, is_int{true}
    {

    }

    Digit(double d): dnum{d}, is_int{false}
    {

    }

    // Digit(){}
    //
    // Digit(const Digit& right): inum{right.inum}, dnum{right.dnum}, is_int{right.is_int}
    // {
    //
    // }

    // the caller expect an integer, if the stack top is a double, simply Exception.
    int get_int() const
    {
        if (! is_int )
        {
            throw std::invalid_argument("get_int, but it is double\n");
        }
        return inum;
    }

    // sqrt(int) should return int.
    // sqrt(double) return double.
    Digit sqrt() const
    {
        if (is_int)
        {
            if (inum < 0)
            {
                throw std::invalid_argument("sqrt negative number\n");
            }
            return Digit{static_cast<int>(::sqrt(static_cast<double>(inum)))};
        }
        else
        {
            if (dnum < 0)
            {
                throw std::invalid_argument("sqrt negative number\n");
            }
            return Digit{::sqrt(dnum)};
        }
    }

    friend Digit operator + (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit{a.inum + b.inum};
        else if ( a.is_int == false && b.is_int ) return Digit{a.dnum + b.inum};
        else if (a.is_int && b.is_int == false) return Digit{a.inum + b.dnum};
        else return Digit{a.dnum + b.dnum};
    }

    friend Digit operator * (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit{a.inum * b.inum};
        else if (a.is_int == false && b.is_int ) return Digit{a.dnum * b.inum};
        else if (a.is_int && b.is_int == false) return Digit{a.inum * b.dnum};
        else return Digit{a.dnum * b.dnum};
    }

    friend Digit operator / (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit{a.inum / b.inum};
        else if ( a.is_int == false && b.is_int ) return Digit{a.dnum / b.inum};
        else if (a.is_int && b.is_int == false) return Digit{a.inum / b.dnum};
        else return Digit{a.dnum / b.dnum};
    }

    friend Digit operator - (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit{a.inum - b.inum};
        else if ( a.is_int == false && b.is_int ) return Digit{a.dnum - b.inum};
        else if (a.is_int && b.is_int == false) return Digit{a.inum - b.dnum};
        else return Digit{a.dnum - b.dnum};
    }

    friend std::ostream& operator << (std::ostream& out, const Digit& a)
    {
        if (a.is_int) out << a.inum;
        else out << a.dnum;
        return out;
    }
};

bool is_int(const std::string& s)
{
    for (const auto& i : s)
    {
        // XXX no negative input, i!='-' is only for my own test purpose.
        if (isdigit(i) == false && i != '-')
        {
            return false;
        }
    }
    return true;
}

bool is_double(const std::string& s)
{
    for (const auto& i : s)
    {
        if (isdigit(i) == false && i != '.' && i != '-')
        {
            return false;
        }
    }
    return true;
}

Digit get_next_digit(std::stack<Digit>& st)
{
    if (st.size() < 1)
    {
        throw std::invalid_argument("no elem pop from stack, invalid input!");
    }
    Digit a = st.top();
    st.pop();
    return a;
}

void do_calc(const std::string& next_symbol, std::stack<Digit>& st)
{
    if (is_int(next_symbol))
    {
        st.push(Digit{std::stoi(next_symbol)});
    }
    else if (is_double(next_symbol))
    {
        st.push(Digit{std::stod(next_symbol)});
    }
    else if (next_symbol == "pop")
    {
        st.pop();
    }
    else if (next_symbol == "add")
    {
        if (st.size() < 2)
            throw std::invalid_argument("no enough number to add, invalid input!");

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a + b;
        std::cout << a << " + " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "sub")
    {
        if (st.size() < 2)
            throw std::invalid_argument("no enough number to sub, invalid input!");

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a - b;
        std::cout << a << " - " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "div")
    {

        if (st.size() < 2)
            throw std::invalid_argument("no enough number to div, invalid input!");

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a / b;
        std::cout << a << " / " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "mult")
    {
        if (st.size() < 2)
            throw std::invalid_argument("no enough number to mult, invalid input!");

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a * b;
        std::cout << a << " * " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "sqrt")
    {
        if (st.size() < 1)
            throw std::invalid_argument("no enough number to sqrt, invalid input!");

        Digit a = get_next_digit(st);
        Digit b = a.sqrt();
        std::cout << "sqrt " << a << " = " << b << std::endl;
        st.push(b);
    }
    else if (next_symbol == "reverse")
    {
        if (st.size() < 1)
             throw std::invalid_argument("no enough number to reverse, invalid input!");

        Digit tmp = get_next_digit(st);

        // reverse should first get a integer from the stack top, then try to reverse the number of digit in the stack
        int reverse_number = tmp.get_int();
        if (static_cast<int>(st.size()) < reverse_number)
            throw std::invalid_argument("no enough number to reverse, invalid input!");

        std::vector<Digit> tmp_vec;
        while (reverse_number --)
        {
            tmp_vec.push_back(get_next_digit(st));
        }
        for (auto i : tmp_vec)
        {
            st.push(i);
        }
    }
    else
    {
        throw std::invalid_argument("strange symbol, invalid input!");
    }
}

void calc(const std::vector<std::string> & input, std::stack<Digit>& st)
{
    // should use vector index to handle nested repeat easily.
    // not be banned in the asst spec. so i use it.
    for (size_t i = 0; i < input.size(); ++ i)
    {
        const std::string& cur_symbol = input[i];
        if (cur_symbol == "repeat")
        {
            Digit tmp = get_next_digit(st);
            int repeat_count = tmp.get_int();
            // find next related endrepeat
            int tmp_count = 1; // count for repeat/endrepeat
            int next_idx = -1; // the next related endrepeat
            std::vector<std::string> nest_repeat_symbol;
            for (size_t j = i + 1; j < input.size(); ++ j)
            {
                if (input[j] == "repeat")
                {
                    tmp_count ++;
                }
                else if (input[j] == "endrepeat")
                {
                    tmp_count --;
                    if (tmp_count == 0)
                    {
                        next_idx = static_cast<int>(j);
                        break;
                    }
                }
                nest_repeat_symbol.push_back(input[j]);
            }
            if (next_idx == -1)
            {
                throw std::invalid_argument("repeat error?, invalid input!");
            }
            while (repeat_count --)
            {
                calc(nest_repeat_symbol, st);
            }
            i = next_idx; // index to the related endrepeat
        }
        else
        {
            do_calc(cur_symbol, st);
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "argv count error" << std::endl;
        return -1;
    }
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

    std::stack<Digit> st;
    calc(input, st);
    return 0;
}
