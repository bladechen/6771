#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
#include <vector>

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
    double get_number()
    {
        return this->is_int ?this->inum : this->dnum;
    }
    Digit sqrt()
    {
        if (this->is_int)
        {
            return Digit( (int)::sqrt((double)(this->inum)));
        }
        else
        {
            return Digit( (double)::sqrt(this->dnum));
        }
    }
    friend Digit operator + (const Digit& a, const Digit& b )
    {
        // std::cout << a << " + " << b << " = " << std::endl;
        if (a.is_int && b.is_int) return Digit(a.inum + b.inum);
        else if ( a.is_int == false && b.is_int ) return Digit(a.dnum + b.inum);
        else if (a.is_int && b.is_int == false) return Digit(a.inum + b.dnum);
        else return Digit(a.dnum + b.dnum);
    }

    friend Digit operator * (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit(a.inum * b.inum);
        else if ( a.is_int == false && b.is_int ) return Digit(a.dnum * b.inum);
        else if (a.is_int && b.is_int == false) return Digit(a.inum * b.dnum);
        else return Digit(a.dnum * b.dnum);
    }

    friend Digit operator / (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit(a.inum / b.inum);
        else if ( a.is_int == false && b.is_int ) return Digit(a.dnum / b.inum);
        else if (a.is_int && b.is_int == false) return Digit(a.inum / b.dnum);
        else return Digit(a.dnum / b.dnum);
    }

    friend Digit operator - (const Digit& a, const Digit& b )
    {
        if (a.is_int && b.is_int) return Digit(a.inum - b.inum);
        else if ( a.is_int == false && b.is_int ) return Digit(a.dnum - b.inum);
        else if (a.is_int && b.is_int == false) return Digit(a.inum - b.dnum);
        else return Digit(a.dnum - b.dnum);
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
        if (isdigit(s[i]) ==  false && s[i] != '.')
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
        Digit c = a + b;
        std::cout << a << " + " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "sub")
    {
        if (st.size() < 2) return false;

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a - b;
        std::cout << a << " - " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "div")
    {
        if (st.size() < 2) return false;

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a / b;
        std::cout << a << " / " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "mult")
    {
        if (st.size() < 2) return false;

        Digit a = get_next_digit(st);
        Digit b = get_next_digit(st);
        Digit c = a * b;
        std::cout << a << " * " << b << " = " << c << std::endl;
        st.push(c);
    }
    else if (next_symbol == "sqrt")
    {
        if (st.size() < 1) return false;
        Digit a = get_next_digit(st);
        Digit b = a.sqrt();
        std::cout << "sqrt " << a << " = " << b << std::endl;
        st.push(b);
    }
    else if (next_symbol == "reverse")
    {
        if (st.size() < 1) return false;
        int reverse_number = (int)(get_next_digit(st).get_number());
        if ((int)st.size () < reverse_number) return false;
        std::vector<Digit> tmp;
        while (reverse_number --)
        {
            tmp.push_back(get_next_digit(st));
        }
        for (size_t i = 0; i < tmp.size(); ++ i)
        {
            st.push(tmp[i]);
        }
    }
    else
    {
        return false;
    }
    return true;
}


void calc(const std::vector<std::string> & input)
{
    std::stack<Digit> st;

    bool repeated = false;
    std::vector<std::string> repeat_tokens;
    repeat_tokens.clear();
    int repeat_count = 0;
    // FIXME nested repeat
    for (size_t i = 0; i < input.size(); ++ i)
    {
        std::string cur_symbol = input[i];
        if (repeated == true)
        {
            if (cur_symbol == "endrepeat")
            {
                repeated = false;
                for (int k = 0; k < repeat_count; ++ k)
                {
                    for (size_t j = 0; j < repeat_tokens.size(); ++ j)
                    {
                        do_calc(repeat_tokens[j], st);
                    }
                }
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
                repeat_count = (int)(get_next_digit(st).get_number());
            }
            else
            {
                do_calc(cur_symbol, st);
            }
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
    calc(input);
    return 0;
}
