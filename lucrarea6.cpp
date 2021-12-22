#include <iostream>
#include <memory>
using namespace std;

class Toy {
    public:
        Toy() {
            cout << "Toy created using a constructor WITHOUT paramters\n" << endl;
        }

        Toy(string name, int price): 
        name(name), price(price){
            cout << "Toy created using a constructor WITH paramters" << endl;
        }

        Toy(const Toy &toy) {
            this->name = toy.name;
            this->price = toy.price;
            this->isLocked = toy.isLocked;
            cout << "Toy created using a COPY constructor" << endl;
        }

        Toy& operator = (const Toy &toy) {
            if (this == &toy) { 
                cout << "Assignment to self stopped for the base class... Be more careful next time :)\n" << endl;
                return *this;
            }
            this->name = toy.name;
            this->price = toy.price;
            this->isLocked = toy.isLocked;
            cout << "Toy created using COPY ASSIGNMENT OPERATOR with RETURN" << endl;
            return *this;
        }

        virtual void welcomeMessage() {
            cout << "Hi, I am *" << this->name << "*! Welcome to our fairytale land :)"  << endl;
        }

        void changeName(string newName) {
            this->name = newName;
        }

        void printPrice() {
            cout << "The price for this toy is: " << price << endl;
        }

        bool printIsLocked() {
            cout << "Is the price locked? " << isLocked << endl;
            return this->isLocked;
        }

        virtual ~Toy() {
            cout << "Destructor:    Toy is broken :( You can buy another one" << endl;
        }

        void askForPriceChange(int newPrice) {
            if (this->isLocked) {
                cout << "The price for this toy is LOCKED, you cannot change it" << endl;
            } else {
                cout << "The price for this toy is UNLOCKED, you can change it" << endl;
                this->price = newPrice;
            }
        }

        void setLocked(bool isLocked) {
            this->isLocked = isLocked;
        }

    private:
        string name = "Fluffy";
        int price = 109;
        bool isLocked = false;
};

Toy* createToyInstance() {
    return (new Toy);
}

void lock(Toy &toy) {
    cout << "Locking price for this toy..." << endl;
    toy.setLocked(true);
}

void unlock(Toy &toy) {
    cout << "Unlocking price for this toy..." << endl;
    toy.setLocked(false);
}

class Uncopyable
{
  protected:
    Uncopyable() {}
    virtual ~Uncopyable() {}
  private:
    Uncopyable(const Uncopyable &);
    Uncopyable & operator=(const Uncopyable&);
};

class LockToy: private Uncopyable {
    public: 
        LockToy(Toy &toy):
        lockPtr(toy) {
            lock(lockPtr);                              // acaparare resursa (in momentul crearii obiectului)
        }

        ~LockToy() {
            unlock(lockPtr);                            // eliberare resursa (in momentul distrugerii obiectului)
        }
    private: 
        Toy &lockPtr;
};

int main() {
    cout << "----   UNIQUE  ----" << endl;
    unique_ptr<Toy> uniqueToy(createToyInstance());
    uniqueToy->welcomeMessage();
    // unique_ptr<Toy> uniqueToy2(uniqueToy);           // nu se poate copia pentru ca e unique_ptr
    unique_ptr<Toy> uniqueToy2 = move(uniqueToy);       // nu e copiere, e transfer de ownership
    // uniqueToy->welcomeMessage();                     // nu merge deoarece s-a facut deja transferul de ownership
    uniqueToy2->welcomeMessage();
    uniqueToy2->changeName("Boby");
    uniqueToy2->welcomeMessage();

    cout << "\n----   SHARED  ----" << endl;
    shared_ptr<Toy> sharedToy(createToyInstance());
    sharedToy->welcomeMessage();
    cout << "Count: " << sharedToy.use_count() << endl;
    shared_ptr<Toy> sharedToy2(sharedToy);
    cout << "Count: " << sharedToy.use_count() << endl;
    sharedToy2->welcomeMessage();

    sharedToy->changeName("Boby");
    sharedToy2->welcomeMessage();

    sharedToy2 = move(sharedToy);                       // nu e copiere, e tot transfer de ownership
    cout << "Count: " << sharedToy.use_count() << endl;
    cout << "Count: " << sharedToy2.use_count() << endl;

    cout<< "\n----    Things for item 14    ----" << endl;
    Toy toy("Pufi", 59);
    LockToy *lockedToy = new LockToy(toy);
    toy.askForPriceChange(79);
    toy.printPrice();
    delete lockedToy;
    toy.askForPriceChange(79);
    toy.printPrice();
}