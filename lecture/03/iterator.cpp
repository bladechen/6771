#include <algorithm>
#include <forward_list>
#include <list>
#include <queue>
#include <typeinfo>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

void output()
{
    auto names = std::vector<std::string>{};

   using namespace std::literals;
   for (auto n = ""s; std::cin >> n; )
       names.emplace_back(n);


   // std::ostream_iterator <std::vector<std::string>::value_type > out_it(std::cout, "\n");
   std::copy(names.cbegin(),
             names.cend(),
             std::ostream_iterator<std::string>{std::cout, "\n"});
   std::cout << sizeof(std::vector<int>::value_type) << std::endl;



}
void bid_it()
{

    auto ages = std::list<int>{std::istream_iterator<int>{std::cin}, std::istream_iterator<int>{}};
    ages.sort();
    for (auto i = ages.cbegin(); i != ages.cend(); ++i)
    {
        std::cout << "A person of " << *i << " years can";
        if (*i < 15)
            std::cout << "not";
        std::cout << " watch an MA15+ movie alone.\n";
    }
}
void forward_it()
{

    auto ages = std::forward_list<int> {std::istream_iterator<int>{std::cin}, std::istream_iterator<int>{}};
    // auto ages = std::forward_list<int>{std::istream_iterator<int>{std::cin},
    //     std::istream_iterator<int>{}};
    std::cout << "begin" << "\n";
    auto size = 0;
    for (auto i = ages.cbegin(); i != ages.cend(); ++i)
        ++size;
    // for (auto i = (--ages.end()); i != ages.begin(); --i)
    //      std::cout << *i << std::endl;
    std::cout << size << '\n';
}
void vec_it()
{

    auto ages = std::vector<int>{0, 1, 2, 3, 4, 5};
    {
        for (auto i = ages.begin(); i != ages.end();)
        {
            ages.erase(i++);
            // i = ages.erase(i);
            // std::cout  << * i << std::endl;
        }

        std::cout  << ages.size() << std::endl;

    }
    return;
}
int main()
{

    vector<char> chars;
    for(char c = 'a'; c < 'g'; ++c) {
        chars.push_back(c);
        chars.push_back('a');
    }
    copy(chars.begin(), chars.end(), ostream_iterator<char>(cout, " "));
    cout << endl;
    vector<char>::iterator new_end = remove(chars.begin(), chars.end(), 'a');
    // chars.erase(new_end, chars.end());
    copy(chars.begin(), chars.end(), ostream_iterator<char>(cout, " "));
    cout << endl;
    deque<double> dq1{1.2, 1.9, 3.0};
    deque<double> dq2{9, 1};

    std::copy(dq1.cbegin(), dq1.cend(), std::front_inserter(dq2));

    std::copy(dq2.cbegin(), dq2.cend(), std::ostream_iterator<decltype(dq2)::value_type>(std::cout, "\n"));
    std::cout << "--------\n";
    list<int> lst;
    list<int>::value_type bbb{1};
    std::cout << bbb << std::endl;
    lst.assign(dq1.begin(), dq1.end());
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ++ it)
    {
        std::cout << *it << std::endl;

    }
    for (auto i: lst)
    {
        std::cout << i << std::endl;
    }
    map<int, int> m;
    m[1]=2;
    m[19]=2;
    for (auto i :m )
    {
        std::cout << i.first << i.second << std::endl;

    }
    vec_it();
    bid_it();
    forward_it();

   auto names = std::vector<std::string>{};
   {
       auto begin = std::istream_iterator<decltype(names)::value_type>{std::cin};
       auto end = std::istream_iterator<decltype(names)::value_type>{};
       auto inserter = std::back_insert_iterator<decltype(names)>{names};
       std::copy(begin, end, inserter);

       std::cout << typeid(begin).name() << std::endl;
   }

   std::sort(names.begin(), names.end());
   std::copy(names.cbegin(),
             names.cend(),
             std::ostream_iterator<decltype(names)::value_type>{std::cout, "\n"});
   std::map<std::string, int> a;
   std::cout << typeid(decltype(a)::key_type).name() << std::endl;

   // decltype(i)::value_type b;

}

// ostream_iterator example
// #include <iostream>     // std::cout
// #include <iterator>     // std::ostream_iterator
// #include <vector>       // std::vector
// #include <algorithm>    // std::copy
//
// int main () {
//   std::vector<int> myvector;
//   for (int i=1; i<10; ++i) myvector.push_back(i*10);
//
//   std::ostream_iterator<int> out_it (std::cout,", ");
//   std::copy ( myvector.begin(), myvector.end(), out_it );
//   return 0;
// }
