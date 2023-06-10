#include <iostream>

template <typename T>
class Stack {
private:
    T* stackArray;  // pointer to stack array
    int maxSize;
    int topIndex;   // index of stack's top element

public:
    Stack(int size) : maxSize(size), topIndex(-1) {
        stackArray = new (std::nothrow) T[maxSize];     //no throw an exception on failure, instead return a null pointer
        if (stackArray == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~Stack() {
        delete[] stackArray;
    }

    int size() const {
        return topIndex + 1;
    }

    bool empty() const {
        return (topIndex == -1);
    }

    void push(const T& element) {
        if (size() == maxSize) {
            throw std::overflow_error("Stack is full.");
        }

        stackArray[++topIndex] = element;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty.");
        }

        return stackArray[topIndex--];
    }

    T top() const {
        if (empty()) {
            throw std::logic_error("Stack is empty.");
        }

        return stackArray[topIndex];
    }
};

int main() {
    try {
        Stack<int> stack1(3);
        stack1.push(1);
        stack1.push(5);
        stack1.push(10);

        std::cout << "Stack size = " << stack1.size() << "\n";
        std::cout << "Top element = " << stack1.top() << "\n";

        while (!stack1.empty()) {
            std::cout << "Popped element: " << stack1.pop() << "\n";
        }
    }
    catch (const std::bad_alloc&) {
        std::cerr << "Memory allocation failed: Unable to create the stack." << "\n";
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Stack overflow. " << e.what() << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Stack underflow. " << e.what() << "\n";
    }
    catch (const std::logic_error& e) {
        std::cerr << "Logic error. " << e.what() << "\n";
    }

    return 0;
}