#include<iostream>
#include<vector>
using namespace std;

class Observer {
    public:
        virtual void update(string content) const = 0;
};

class Subject {
    protected:
        vector<Observer*> observer_list;
    public:
        virtual void addObserver(Observer *observer) = 0;
        virtual void removeObserver(Observer *observer_to_remove) = 0;
        virtual void notifyObserver(string sale_offer) = 0;
};

class SuperMarket: public Subject {
    private:
        string name;
    public:
        SuperMarket(string name): name(name) {};
        void addObserver(Observer *observer) {
            observer_list.emplace_back(observer);
        }
        void removeObserver(Observer *observer_to_remove) {
            for(auto iterator = observer_list.begin(); iterator != observer_list.end(); ++iterator) {
                if(*iterator == observer_to_remove) {
                    iterator = observer_list.erase(iterator);
                    break;
                }
            }
        }
        void notifyObserver(string sale_offer) {
            for(auto observer: observer_list) {
                observer->update(sale_offer);
            }
        }
};

class Customer: public Observer {
    private:
        string name;
        Subject *s;
    public:
        Customer(string name): name(name) {}
        void update(string content) const {
            cout<<"Hello "<<name<<" we have a special offer for you"<<endl;
            cout<<content<<endl<<endl;
        }
        void subscribeToSubject(Subject *subject) {
            s = subject;
            s->addObserver(this);
        }
        void unsubscribeToSubject(Subject *subject) {
            s->removeObserver(this);
            s = NULL;
        }
};

int main() {
    SuperMarket *sm = new SuperMarket("Dummy Shop");
    Customer *c1 = new Customer("dummy customer 1");
    Customer *c2 = new Customer("dummy customer 2");
    Customer *c3 = new Customer("dummy customer 3");
    Customer *c4 = new Customer("dummy customer 4");
    c1->subscribeToSubject(sm);
    c2->subscribeToSubject(sm);
    c3->subscribeToSubject(sm);
    c4->subscribeToSubject(sm);
    sm->notifyObserver("Hello World");
    c2->unsubscribeToSubject(sm);
    c4->unsubscribeToSubject(sm);
    sm->notifyObserver("Hello World 2");
    return 0;
}