#include <iostream>
using namespace std;

class Toy {
    public:
        Toy() {
            cout << "Toy created using a constructor WITHOUT paramters" << endl;
        }

        Toy(string name): 
        name(name){   //use initialization list rather than a constructor with assignments
            // this->name = name;   // this method is less efficient
            cout << "Toy created using a constructor WITH paramters" << endl;
        }

        Toy(const Toy &toy) {
            this->name = toy.name;
            cout << "Toy created using a COPY constructor" << endl;
        }

        Toy& operator = (const Toy &toy) {
            if (this == &toy) {             // Item 11 base class
                cout << "Assignment to self stopped for the base class... Be more careful next time :)\n" << endl;
                return *this;
            }
            this->name = toy.name;
            // cout << "Toy created using COPY ASSIGNMENT OPERATOR with RETURN" << endl;
            return *this;                  // Item 10 base class: assignment operator returns a reference to *this
        }

        virtual void welcomeMessage() {
            cout << "Hi, I am *" << this->name << "*! Welcome to our fairytale land :)\n"  << endl;
        }

        void changeName(string newName) {
            this->name = newName;
        }

        void printName() {
            cout << "My name is " << this->name << endl;
        }

        virtual ~Toy() {
            cout << "Base Destructor: Toy is broken :( You can buy another one" << endl;
        }

    private:
        // string name;
        string name = "Fluffy";  // name should be initialized before use (here or in the default constructor);
};


class MinAgeToy : public Toy {
    public:
        MinAgeToy() {
            cout << "Mininum age required toy created using a constructor WITHOUT paramters" << endl;
        }

        // MinAgeToy (const MinAgeToy &toy) = delete;      //disallow the use of COPY constructor

        MinAgeToy& operator = (const MinAgeToy &toy) {
            if (this == &toy) {             // Item 11 derived class
                cout << "Assignment to self stopped for the derived class... Be more careful next time :)\n" << endl;
                return *this;
            }

            Toy::operator = (toy);          // Item 12: if this line is commented then the value for the "name" member will always have the default value, even though the value was changed
            this->minAge = toy.minAge;
            // cout << "Toy created using COPY ASSIGNMENT OPERATOR with RETURN" << endl;
            return *this;                  // Item 10 derived class: assignment operator returns a reference to *this
        }

        void welcomeMessage() {
            cout << "This toy requires a minimum age of " << this->minAge << "\n" << endl;
        }

        void changeRequiredAge (int newAge) {
            this->minAge = newAge;
        }

        ~MinAgeToy() {
            cout << "Derived Destructor: Toy is broken :( Ask your parents to buy another one" << endl;
        }

    private:
        int minAge = 13;
        MinAgeToy (const MinAgeToy &toy);   // declared here so diassolow the use of compiler generated function
};

int main() {

    // simple toys created using constructor WITHOUT parameters / WITH paramters / COPY constructor / COPY ASSIGNMENT OPERATOR

    Toy myToy;                  // constructor WITHOUT parameters (here name it's not initialized before use)
    myToy.welcomeMessage();

    Toy myToy2("Barbie");       // constructor WITH parameters
    myToy2.welcomeMessage();

    Toy myToy3(myToy);          // COPY constructor
    myToy3.changeName("Bobby");
    myToy3.welcomeMessage();

    myToy3 = myToy2;            // COPY ASSIGNMENT OPERATOR with RETURN
    myToy3.welcomeMessage();
    myToy3 = myToy3;            // SELF ASSIGNMENT


    // minimum age required toys created using constructor WITHOUT parameters / COPY ASSIGNMENT OPERATOR

    MinAgeToy maToy;                // constructor WITHOUT parameters
    maToy.welcomeMessage();

    // MinAgeToy maToy2 = maToy;    // COPY constructor is inaccessible (private)

    MinAgeToy maToy3;               // constructor WITHOUT parameters
    maToy3.changeRequiredAge(3);    
    maToy3.welcomeMessage();
    maToy3 = maToy;                 // COPY ASSIGNMENT OPERATOR
    maToy3.welcomeMessage();
    maToy3 = maToy3;                // SELF ASSIGNMENT

    cout << "\nItem 12:" << endl;
    MinAgeToy thunder;
    MinAgeToy whiskey;
    whiskey.changeName("Bobby");
    thunder = whiskey;
    thunder.printName();
    whiskey.printName();
    cout << endl;
}