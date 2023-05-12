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

#if 0
#include <iostream>
#include <vector>
#include <any>
#include <typeinfo>

// 定义一个函数模板，使用包展开和折叠将所有参数保存到一个std::vector<std::any>对象中
template<typename... Args>
void print_arguments(Args&&... args) {
    std::vector<std::any> argument_vector{ std::any(args)... };

    std::cout << "Arguments:\n";
    for (auto&& arg : argument_vector) {
        std::cout << "- Type: ";
        if (arg.has_value()) {
            const std::type_info& type = arg.type();
            if (type == typeid(int)) {
                std::cout << "int, "<<std::any_cast<int>(arg);
            } else if (type == typeid(double)) {
                std::cout << "double, "<<std::any_cast<double>(arg);
            } else if (type == typeid(std::string)) {
                std::cout << "std::string, "<<std::any_cast<std::string>(arg);
            } else if (type == typeid(char *))
            {
                 std::cout << "char * ,"<<std::any_cast<char *>(arg);
            } else if (type == typeid(const char *))
            {
                 std::cout << "const char *  ,"<<std::any_cast<const char *>(arg);
            }
            //std::cout << "Value: " << std::any_cast<double>(arg) << std::endl;
        } else {
            std::cout << "undefined" << std::endl;
        }
    }
}


int main() {
    int i = 42;
    double d = 3.1415926;
    std::string s = "Hello, world!";

    // 调用print_arguments函数，传入不同类型和个数的参数
    print_arguments(i, d, s, "test", 1, 2.0);

    return 0;
}

#endif

