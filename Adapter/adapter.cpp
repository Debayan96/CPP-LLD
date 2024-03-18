#include<iostream>

using namespace std;

class Duck {
    private:
        string name;
    public:
        Duck(string duck_name): name(duck_name) {}
        void fly() {
            cout<<"Duck is flying"<<endl;
        }
        void quack() {
            cout<<"Quack quack"<<endl;
        }
};

class Turkey {
    private:
        string name;
        int wing_flap_count;
    public:
        Turkey(string turkey_name): name(turkey_name), wing_flap_count(0) {}
        void flap_wings() {
            if(wing_flap_count != 5)
                cout<<name<<" is flapping wings"<<endl;
            else
                cout<<name<<" is fyling"<<endl;
            wing_flap_count = (wing_flap_count + 1) % 6;
        }
        void gobble() {
            cout<<name<<" is gobbling"<<endl;
        }
};

class TurkeyAdapter {
    private:
        Turkey *turkey__;
    public:
        TurkeyAdapter(Turkey *turkey): turkey__(turkey) {}
        void fly() {
            for(int i = 0; i < 5; i++) {
                turkey__->flap_wings();
            }
        }
        void quack() {
            turkey__->gobble();
        }
};

int main() {
    Duck duck("duffy");
    duck.quack();
    duck.fly();
    cout<<endl;
    Turkey turkey("Gobbles"); // name suggested by ChatGPT
    turkey.gobble();
    turkey.flap_wings();
    cout<<endl;
    TurkeyAdapter turkey_adapter(&turkey);
    turkey_adapter.quack();
    turkey_adapter.fly();
    cout<<endl;
    return 0;
}