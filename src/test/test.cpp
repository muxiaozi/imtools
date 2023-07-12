#include <any>
#include <iostream>

class Demo {
public:
    Demo() {
        std::cout << "Demo()" << std::endl;
    }
    ~Demo() {
        std::cout << "~Demo()" << std::endl;
    }
    Demo(const Demo &other) {
        std::cout << "Demo(const Demo &other)" << std::endl;
    }
    Demo(Demo &&other) {
        std::cout << "Demo(Demo &&other)" << std::endl;
    }
    Demo &operator=(const Demo &other) {
        std::cout << "Demo &operator=(const Demo &other)" << std::endl;
        return *this;
    }

    void print() {
        std::cout << "Demo" << std::endl;
    }
};

void foo(std::any any) {
    std::cout << "Name: " << any.type().name() << std::endl;
}

int main(int argc, char const *argv[]) {
    Demo demo;
    std::any any;
    any = 100;

    foo(any);

    try {
        std::any_cast<long>(any);
    } catch (std::bad_any_cast &e) {
        std::cout << e.what() << ": from " << any.type().name() << std::endl;
    }

    std::any a = 1;
    int *i = std::any_cast<int>(&a);
    std::cout << *i << "\n";

    return 0;
}
