#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

void do_something() {
    std::cout << "Doing something...\n";
}

void do_something(int a) {
    std::cout << "Doing something with int " << a << "...\n";
}

void do_something(int a, double b) {
    std::cout << "Doing something with int " << a << " and double " << b << "...\n";
}

template<typename... Args>
int test1(Args... args)
{
    std::string cmd;
    if constexpr (sizeof...(args) >= 1 && std::is_same_v<std::string, std::tuple_element_t<0, std::tuple<Args...>>>)
    {
        cmd = std::get<0>(std::make_tuple(args...));
    }
    if constexpr (sizeof...(args) == 1) {
        do_something();
    }
    else if constexpr (sizeof...(args) == 2 && std::is_same_v<int, std::tuple_element_t<1, std::tuple<Args...>>>) {
        int int_a = std::get<1>(std::make_tuple(args...));
        do_something(int_a);
    }
    else if constexpr (sizeof...(args) == 3) {
        if constexpr (std::is_same_v<int, std::tuple_element_t<1, std::tuple<Args...>>> && std::is_same_v<double, std::tuple_element_t<2, std::tuple<Args...>>>) {
            int int_a = std::get<1>(std::make_tuple(args...));
            double double_b = std::get<2>(std::make_tuple(args...));
            do_something(int_a, double_b);
        }
    }
    return 0;
}

int main()
{
    test1("test", 1);  // Calls test1(std::string, int)
    test1("test", 1, 2);  // Calls test1(std::string, int, int)
    test1("test", 1, 2.0);  // Calls test1(std::string, int, double)
    test1("test");  // Calls test1(std::string)
    return 0;
}


