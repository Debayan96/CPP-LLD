#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

class Singleton {
    private:
        static Singleton *instance;
        static mutex m;
        string name;
    protected:
        Singleton(string class_name): name(class_name) {}

    public:
        Singleton (Singleton &other) = delete;
        void operator=(const Singleton &) = delete;

        static Singleton *getSingletonClass(string value);

        string getValue() {
            return name;
        }
};

Singleton* Singleton::instance{nullptr};
mutex Singleton::m;

Singleton* Singleton::getSingletonClass(string value) {
    lock_guard<mutex> lock(m);
    if(instance == nullptr) {
        instance = new Singleton(value);
    }
    return instance;
}

void threadOne() {
    this_thread::sleep_for(chrono::seconds(1));
    Singleton* singleton = Singleton::getSingletonClass("Thread_1");
    cout<<"Value is: "<<singleton->getValue()<<endl;
}

void threadTwo() {
    this_thread::sleep_for(chrono::seconds(1));
    Singleton* singleton = Singleton::getSingletonClass("Thread_2");
    cout<<"Value is: "<<singleton->getValue()<<endl;
}

void testSingleton() {
    thread t1(threadOne);
    thread t2(threadTwo);

    t1.join();
    t2.join();
}

int main() {
    testSingleton();
    return 0;
}