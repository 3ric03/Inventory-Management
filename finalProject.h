#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

//class/function headers
//variable declarations

using namespace std;

//custom made exception classes, inherited from default exception classes
class invalid_reference :public invalid_argument
{
public:
    explicit invalid_reference(const string &);
};
class inventory_Underflow :public logic_error
{
public:
    explicit inventory_Underflow(const string&);
};
class inventory_Overflow :public logic_error
{
public:
    explicit inventory_Overflow(const string&);
};

//stock item class
class StockItem
{
//private members
private:
    string itemRef, itemName;
    double price;
    int quantity;
//public members
public:
    //constructor
    StockItem(string, string, double, int);
    //methods
    void addQuantity(int);
    string getRef();
    //virtual function
    virtual void displayInfo();
    double sell(int) throw(inventory_Underflow);

};//end StockItem

//Pants class, inherited from StockItem class
class Pants : public StockItem
{
//private members
private:
    double length, waist;
//public members
public:
    //constructor and polymorphism
    Pants(string, string, double, int, double, double);
    void displayInfo();

};//end Pants class

//Jeans class, inherited from Pants class
class Jeans : public Pants
{
//private members
private:
    string fit;
//public members
public:
    //constructor and polymorphism
    Jeans(string, string, double, int, double, double, string);
    void displayInfo();

};//end Jeans class

//Hoodie class, inherited from StockItem class
class Hoodie : public StockItem
{
//private members
private:
    double chest, sleeve;
    string colour;
//public members
public:
    //constructor and polymorphism function
    Hoodie(string, string, double, int, double, double, string);
    void displayInfo();

};//end Hoodie class

//TShirt class, inherited from StockItem class
class TShirts : public StockItem
{
private:
    string colour, shirtSize;
public:
    TShirts(string, string, double, int, string, string);
    void displayInfo();
};// end TShirt class

//Inventory class
class Inventory
{
private:
    int revenue, length;
    //double pointer used to create an array of pointers to StockItem objects
    StockItem** inventory;
public:
    //constructor
    Inventory(int);
    //methods
    double getRevenue();
    void addRevenue(double profit);
    void deleteStock(int);
    void createStock(int)  throw (invalid_reference, inventory_Overflow);
    void sellStock(int, int) throw(invalid_reference, inventory_Underflow);
    void stockReport();
    void addStocks(int, int) throw (invalid_reference);
    int itemSearch(string) throw (invalid_reference);
    int spaceFinder(string) throw (invalid_reference, inventory_Overflow);
    void tester();
};

//function prototypes
double numReader(string, int, int minV = 0);
string stringReader(string, int, int minV = 0);
