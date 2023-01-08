#include "finalProject.h"

//constructors for custom exception classes, passes paramter to the parent class constructor
invalid_reference::invalid_reference(const string &message): invalid_argument(message) {}
inventory_Underflow::inventory_Underflow(const string &message): logic_error(message) {}
inventory_Overflow::inventory_Overflow(const string& message) : logic_error(message) {}

//Inventory constuctor, sets revenue to 0
Inventory::Inventory(int length)
    :revenue(0)
{
        //initialize variable
        this->length = length;
        //create an array on heap and set all pointers to nullptr
        inventory = new StockItem* [length];
        for (int i = 0; i < length; i++)
            inventory[i] = nullptr;
}

//return revenue data
double Inventory::getRevenue()
{ return revenue; }

//modify revenue data
void Inventory::addRevenue(double profit)
{
    revenue += profit;
    cout << "\nSell complete!\n";
}

//delete one or all stocks
void Inventory::deleteStock(int index)
{
    //if "delete all"
    if (index == -1)
    {
    //delete array, and return
    delete[] inventory;
    return;
    }

    //delete indivudal item, and set its pointer to nullptr
    delete inventory[index];
    inventory[index] = nullptr;
    cout << "\nStock deleted.\n";

}//end method

//create new stock
void Inventory::createStock(int type) throw (invalid_reference, inventory_Overflow)
{
    //input data
    string ref = stringReader("Enter stock reference number (4 characters): ", 4, 4);
    //obtain the next avaliable index
    //exception may be thrown here if inventory is full
    int index = spaceFinder(ref);

    //create a superclass pointer to carry information
    StockItem* ptr = nullptr;

    //input data
    double price = numReader("Enter stock price (between $0 and $1000): ", 1000);
    double quantity = numReader("Enter stock quantity (between 0 and 100): ", 100);

    //enter switch and request relevant data input
    switch (type)
    {
    case 1:
    {
        string fit;
        cout << "1. Loose\n";
        cout << "2. Regular\n";
        cout << "3. Skinny\n";
        int i = numReader("Choose a fit type number: ", 3, 1);

        switch (i)
        {
        case 1:
            fit = "Loose";
        case 2:
            fit = "Regular";
        case 3:
            fit = "Skinny";
        }
        double length = numReader("Enter length (26-34 inches): ", 34, 26);
        double waist = numReader("Enter waist size (34 - 64 inches): ", 64, 34);
        //create new object, store its address
        ptr = new Jeans(ref, "Jeans", price, quantity, length, waist, fit);
        break;
    }
    case 2:
    {
        double length = numReader("Enter length (26-34 inches): ", 34, 26);
        double waist = numReader("Enter waist size (34 - 64 inches): ", 64, 34);
        //create new object, store its address
        ptr = new Pants(ref, "Pants", price, quantity, length, waist);
        break;
    }
    case 3:
    {
        double chest = numReader("Enter chest size (41 - 50 inches): ", 50, 41);
        double sleeve = numReader("Enter sleeve size (25 - 30 inches): ", 30, 25);
        string colour = stringReader("Enter hoodie colour: ", 15);
        //create new object, store its address
        ptr = new Hoodie(ref, "Hoodie", price, quantity, chest, sleeve, colour);
        break;
    }
    case 4:
    {
        string colour = stringReader("Enter t-shirt colour: ", 15);
        string size;
        cout << "1. Small\n";
        cout << "2. Medium\n";
        cout << "3. Large\n";
        int i = numReader("Choose a fit type number: ", 3, 1);
        switch (i)
        {
        case 1:
            size = "Small";
        case 2:
            size = "Medium";
        case 3:
            size = "Large";
        }
        ptr = new TShirts(ref, "Tshirt", price, quantity, colour, size);
        break;
    }
    }//end switch
    cout << "\nStock creation is successful!\n";

    //store the newly created in the previously obtained index
    inventory[index] = ptr;
}//end function

//sell stock method
void Inventory::sellStock(int index, int amount) throw(invalid_reference, inventory_Underflow)
{
    addRevenue(inventory[index]->sell(amount));
}

//display info for all stocks
void Inventory::stockReport()
{
    bool empty = true;
    //check if empty
    for (int i = 0; i < length; i++)
    {
        if (inventory[i] != nullptr)
        {
            empty = false;
            break;
        }
    }//end for loop

    //if not empty
    if (!empty)
    {
        //print the headers for each category, loop through inventory
        //use dynamic cast to determine if the object is of the correct type
        cout << "\nPANTS/JEANS\n";
        for (int i = 0; i < length; i++)
        {
            if (dynamic_cast <Pants*> (inventory[i]))
            {
            //call the function (polymorphism used here)
              inventory[i]->displayInfo();
              cout << endl;
            }
        }
        //same process
        cout << "\nHoodies\n";
        for (int i = 0; i < length; i++)
        {
            if (dynamic_cast <Hoodie*> (inventory[i]))
            {
              inventory[i]->displayInfo();
              cout << endl;
            }
        }

        cout << "\nTShirts\n";
        for (int i = 0; i < length; i++)
        {
            if (dynamic_cast <TShirts*> (inventory[i]))
            {
              inventory[i]->displayInfo();
              cout << endl;
            }
        }

    }//end if block

    //error message
    else
        cout << "\nInventory is empty!\n";
}//end function

//adding more quantity to stocks
void Inventory::addStocks(int index, int quanitity) throw (invalid_reference)
{
    //invoke the method on the relevant object
    inventory[index]->addQuantity(quanitity);
}

//search for the index of an item based on its stock reference
int Inventory::itemSearch (string id) throw (invalid_reference)
{
    for (int i = 0; i < length; i++)
    {
        if (inventory[i] != nullptr)
        {
            //if match, return the index
            if (inventory[i]->getRef() == id)
                return i;
        }
    }
    //if no matches found, throw exception
    throw invalid_reference("Stock reference not found.\n");
}//end function

//find the index of the next empty space in inventory array
int Inventory::spaceFinder(string id ) throw (invalid_reference, inventory_Overflow)
{

    bool duplicate = true;
    //this function is called while creating an object
    //therefore it must check if the new ID is duplicate
    try
    {
        itemSearch(id);
    }
    //if ID isn't duplicate, itemSearch() will throw exception
    catch (invalid_reference& e)
    {
        duplicate = false;
    }

    if (!duplicate)
    {
        //find the earliest empty index, return
        for (int i = 0; i < length; i++)
        {
            if (inventory[i] == nullptr)
                return i;
        }
        //if empty index not found, throw exception
            throw inventory_Overflow("\nCannot add new stock item, inventory is full!\n");
    }
    //if duplicate ID, throw exception
    else
        throw invalid_reference("duplicate stock reference!\n");
}//end function

//StockItem constructor, use initlializer list
StockItem::StockItem(string id, string name, double price, int stock)
    : itemRef(id), itemName(name), price(price), quantity(stock)
{}

//add quantity
void StockItem::addQuantity(int quantity)
{
    this->quantity += quantity;
    cout << "\nQuantity Updated!\n";
}

//return stock reference
string StockItem::getRef() { return itemRef;}

//print stock info (virtual function)
void StockItem::displayInfo()
{
    //cout << "Stock name: " << itemName << endl;
    cout << "   Stock reference code: " << itemRef << endl;
    cout << "   Stock price: $" << price << endl;
    cout << "   Quantities remaining: " << quantity << endl;
}

//sell stocks
double StockItem::sell(int amount) throw (inventory_Underflow)
{
    //is sell amount is larger than remainign quantity, throw exception
    if (quantity < amount)
        throw inventory_Underflow("\nSell failed, insufficient stocks.\n");
    quantity -= amount;
    //return revenue from sales
    return price * amount;

}//end function

//constructor for pants
Pants::Pants(string id, string name, double price, int stock, double l, double w)
    :StockItem(id, name, price, stock), length(l), waist(w)
{}

//display stock info (polymorphism)
void Pants::displayInfo()
{
    StockItem::displayInfo();
    cout << "   Length: " << length << " inches\n";
    cout << "   Waist size: " << waist << " inches\n";
}

//constructor for jeans
Jeans::Jeans(string id, string name, double price, int stock, double l, double w, string fit)
    :Pants(id, name, price, stock, l, w), fit(fit)
{}

//display stock info (polymorphism)
void Jeans::displayInfo()
{
    Pants::displayInfo();
    cout << "   Fit: " << fit << endl;
}

//constructor for hoodie
Hoodie::Hoodie(string id, string name, double price, int stock,
    double c,  double s, string colour)
    :StockItem(id, name, price, stock), chest(c),  sleeve(s), colour(colour)
{}

//display stock info (polymorphism)
void Hoodie::displayInfo()
{
    StockItem::displayInfo();
    cout << "   Chest width: " << chest << " inches\n";;
    cout << "   Sleeve length: " << sleeve << " inches\n";;
    cout << "   Colour: " << colour << endl;
}

//constructor for Tshirt
TShirts::TShirts(string id, string name, double price, int stock, string c, string size)
    :StockItem(id, name, price, stock), colour(c), shirtSize(size)
{}

void TShirts::displayInfo()
{
    StockItem::displayInfo();
    cout << "   Shirt size: " << shirtSize << endl;
    cout << "   Colour: " << colour << endl;
}

//function to input a number value, checks if number is in a specific domain
double numReader(string prompt, int maxV, int minV)
 {
    double x;
    //loop until valid input
    while (true)
    {
        try
        {
            //display prompt
            cout << prompt;
            cin >> x;
            //if out of range, throw exception
            if (x < minV || x > maxV)
                throw (invalid_argument("\nInvalid number input, please try again\n"));
            //if valid, return
            return x;
        }
        //catch error and print message
        catch (invalid_argument& exp)
        {
            cout << exp.what();
        }
    }//end loop
 }//end function

 //same concept as numReader(), but checks for string length
string stringReader(string prompt, int max, int min)
{
    string x;
    while (true)
    {
        try
        {
            cout << prompt;
            cin >> x;
            if (x.length() < min || x.length() > max)
                throw (invalid_argument("\nInvalid string input, please try again\n"));
            return x;
        }
        catch (invalid_argument& exp)
        {
            cout << exp.what();
        }
    }
}

//create three default stock items for debug purposes.
void Inventory::tester()
{
    cout << "\nThree default stock items has been created for demo purposes.\n";
    inventory[0] = new Pants("P001", "Sweat Pants", 75, 1, 30, 40);
    inventory[1] = new Hoodie("H001", "White Hoodie", 100, 2, 42, 28, "white");
    inventory[2] = new TShirts("T001", "Black T-shirt", 50, 3, "black", "Medium");
}
