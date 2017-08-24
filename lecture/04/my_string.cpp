
#include <vector>
#include <iostream>
#include <string.h>
class MyString {
    public:
    // private:
        char* _data;
        size_t   _len;
        void _init_data(const char *s) {
            _data = new char[_len+1];
            memcpy(_data, s, _len);
            _data[_len] = '\0';
        }
    public:
        MyString() {
            _data = NULL;
            _len = 0;
            std::cout << "default * construct" <<std::endl;
        }

        MyString(const char* p) {
            _len = strlen (p);
            _init_data(p);
            std::cout << "normal char * construct: " << _data <<std::endl;
        }

        MyString(const MyString& str) {
            _len = str._len;
            _init_data(str._data);
            std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
        }

        MyString& operator=(const MyString& str) {
            if (this != &str) {
                _len = str._len;
                _init_data(str._data);
            }
            std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
            return *this;
        }

        MyString(MyString&& str) {
            std::cout << "Move Constructor is called! source: " << str._data << std::endl;
            _len = str._len;
            _data = str._data;
            str._len = 0;
            str._data = NULL;
        }


        MyString& operator=(MyString&& str) {
            std::cout << "Move Assignment is called! source: " << str._data << std::endl;
            if (this != &str) {
                _len = str._len;
                _data = str._data;
                str._len = 0;
                str._data = NULL;
            }
            return *this;
        }

        virtual ~MyString() {
            if (_data) free(_data);
        }
};

MyString get_string()
{
    MyString a =  MyString("get_string");
    std::cout << &a << std::endl;
    a._len ++;

    return a;

}

int main() {
    // char*p = NULL;
    // std::cout << p << std::endl;
    MyString a;
    a = MyString("Hello");
    std::cout << "=======" << std::endl;
    // std::vector<MyString> vec(2);
    std::vector<MyString> vec;
    // vec.push_back(MyString());
    // vec.push_back(MyString());
    vec.push_back(MyString("World"));
    std::cout << "=======" << std::endl;
    std::cout << vec.capacity() << std::endl;
    vec.push_back(get_string());
    std::cout << vec.size() << std::endl;
    std::cout << "=======" << std::endl;
    MyString b  ;
    b = (get_string());
    std::cout << &b << std::endl;

    std::cout << b._data << std::endl;
    std::cout << b._len << std::endl;
    std::cout << std::flush;
}
