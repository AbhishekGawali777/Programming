#include <iostream>
#include <memory>

class CSingleton {
public:
    static CSingleton& getInstance() {
        static CSingleton instance; // Guaranteed to be destroyed.
                               // Instantiated on first use.
        return instance;
    }
    // Following Rule of Five to prevent copies and moves.
    CSingleton(CSingleton const&) = delete; // Prevent copy-construction
    void operator=(CSingleton const&) = delete; // Prevent assignment
    CSingleton(CSingleton&&) = delete; // Prevent move-construction
    void operator=(CSingleton&&) = delete; // Prevent move-assignment

    // Temporary method for demonstration
    void showMessage() {
        std::cout << "Hello from Singleton!" << std::endl;
    }

private:
    CSingleton() {} // Private constructor
};


int main(int argc, char* argv[]) {
    std::cout << "Singleton Patern Example in C++14" << std::endl;
    
    CSingleton& singleton = CSingleton::getInstance();
    CSingleton& sigleton2 = CSingleton::getInstance();

    singleton.showMessage();
    
    std::cout << "Address of singleton instance 1: " << &singleton << std::endl;
    std::cout << "Address of singleton instance 2: " << &sigleton2 << std::endl;
    
    return 0;
}
