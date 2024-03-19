#include<iostream>
#include<vector>
#include <stdexcept>
using namespace std;

class pizza_not_found : public exception {
    private:
        string message;
    public:
        pizza_not_found(string pizza_name) {
            message = "Pizza '" + pizza_name + "' not found!";
        }
        virtual const char* what() const throw() {
            return message.c_str();
        }
};

class Pizza {
    protected:
        int cost;
        int calories;
        vector<string> ingredients;
    public:
        Pizza(int cost, int calories, const vector<string>& ingredients): cost(cost), calories(calories), ingredients(ingredients) {
            this->ingredients.push_back("Cheese");
        }
        virtual void makePizza() const = 0;
};

class VegPizza: public Pizza {
    public:
        VegPizza(int cost, int calories, const vector<string>& ingredients) : Pizza(cost, calories, ingredients) {
            this->ingredients.push_back("Broccoli");
        }
        void makePizza() const override {
            for(string ingredient: ingredients) {
                cout<<"Add "<<ingredient<<endl;
            }
        }
};

class NonVegPizza: public Pizza {
    public:
        NonVegPizza(int cost, int calories, const vector<string>& ingredients) : Pizza(cost, calories, ingredients) {
            this->ingredients.push_back("Chicken");
        }
        void makePizza() const override {
            for(string ingredient: ingredients) {
                cout<<"Add "<<ingredient<<endl;
            }
        }
};

class PizzaFactory {
    private:
        Pizza* pizza;
        string option;
    public:
        PizzaFactory(string option): option(option) {
            if(option == "Veg") {
                pizza = new VegPizza(250, 500, {"Tomato", "Bell Peppers", "Mushroom"});
            } else if(option == "NonVeg") {
                pizza = new VegPizza(750, 700, {"Sundried tomatoes", "Fancy herbs"});
            } else {
                throw pizza_not_found(option);
            }
        }
        Pizza* getPizza() {
            cout<<":::: Making "<<option<<" pizza ::::"<<endl;
            pizza->makePizza();
            cout<<endl;
            return pizza;
        }
};

int main() {
    PizzaFactory veg_restaurant("Veg");
    Pizza* veg_pizza = veg_restaurant.getPizza();

    PizzaFactory non_veg_restaurant("NonVeg");
    Pizza* non_veg_pizza = non_veg_restaurant.getPizza();

    try {
         PizzaFactory hybrid_restaurant("Hybrid");
    } catch (const pizza_not_found& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}