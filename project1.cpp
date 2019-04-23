/*
 * Title: project1.cpp
 * Abstract: This program creates a virtual Vendning Machine in which the user
             or admin can interact with.
 * Author: Rocco Estrada
 * ID: 2219
 * Date: 03/01/19
*/ 
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class VendingMachine
{
public:
    VendingMachine();
    VendingMachine(int newNumber, string newName);
    void setNumber(int newNumber){number = newNumber;}
    void setName(string newName){name = newName;}
    string display();
    void displayMenu();
    void refill(int water, int coffee, int chip, int choc);
    void status();
    void selectItem();
    void reset();
    bool payment();
    void displayReceipt();
    double total();
    void deselect();
    void completeTransaction();
    
private:
    int number; //ID Number
    string name; 
    int numWater;
    int numCoffee;
    int numChip;
    int numChoc;
    int soldWater;
    int soldCoffee;
    int soldChip;
    int soldChoc;
    int saleWater;
    int saleCoffee;
    int saleChip;
    int saleChoc;
    double subtotal;
    double earnings;
    bool selectWater;
    bool selectCoffee;
    bool selectChip;
    bool selectChoc;
    static const double priceWater = 1.5;
    static const double priceCoffee = 2.0;
    static const double priceChip = 1.0;
    static const double priceChoc = 2.5;
    
};

int main()
{
    cout << "===== Welcome to CSUMB Vending Machine =====\n";

    VendingMachine machine1;
    cout << machine1.display();  // Display the ID and name of machine1.

    VendingMachine machine2 (200, "Library"); 
    cout << machine2.display();

    cout << "\n===== Updated machine1 Info =====\n";
    machine1.setNumber(100);
    machine1.setName("BIT117");
    cout << machine1.display(); 

    cout << "\n===== machine1 Status (1) =====\n";
    machine1.status();  // status() function displays current status of the machine.

    machine1.refill(5, 7, 3, 10); // A machine’s admin can refill the items.

    cout << "\n===== machine1 Status (2) =====\n";
    machine1.status();

    cout << endl;
    machine1.displayMenu();

    cout << endl;
    machine1.selectItem();   // A user can select item(s).

    cout << "\n===== machine1 Payment (1) =====\n";
    if(machine1.payment() == true)   // Pay with a debit card or cash.
    {
        cout << "\n===== Receipt (1) =====\n";
        machine1.displayReceipt();
    }
    else 
    {
        // Note that if a user entered incorrect payment information,
        // all selections should be deselected.
        cout << "Invalid payment. All selections are cancelled.\n";
    }

    cout << "\n===== machine1 Status (3) =====\n";
    machine1.status();

    cout << endl;
    machine1.selectItem();

    cout << endl;
    machine1.deselect( );  // A user can de-select items.

    cout << endl;
    machine1.selectItem();

    cout << "\n===== machine1 Payment (2) =====\n";
    if(machine1.payment())
    {
        cout << "\n===== Receipt (2) =====\n";
        machine1.displayReceipt();
    }

    cout << "\n===== machine1 Status (4) =====\n";
    machine1.status();

    machine1.reset();  // An admin resets the machine to the initial 
                       // status, except the ID and name of the machine.
    cout << "\n===== machine1 Status (5) =====\n";
    machine1.status();

    cout << "\n===== Thank you! =====\n";

    return 0;
}

VendingMachine::VendingMachine()
{
    setNumber(0);
    setName("UNKNOWN");
    numWater = 0;
    numCoffee = 0;
    numChip = 0;
    numChoc = 0;
    
    saleWater = 0;
    saleCoffee = 0;
    saleChip = 0;
    saleChoc = 0;
    
    soldWater = 0;
    soldCoffee = 0;
    soldChip = 0;
    soldChoc = 0;
    
    selectWater = false;
    selectCoffee = false;
    selecetChip = false;
    selectChoc = false;
}

VendingMachine::VendingMachine(int newNumber, string newName)
{
    setNumber(newNumber);
    setName(newName);
    numWater = 0;
    numCoffee = 0;
    numChip = 0;
    numChoc = 0;
    
    saleWater = 0;
    saleCoffee = 0;
    saleChip = 0;
    saleChoc = 0;
    
    soldWater = 0;
    soldCoffee = 0;
    soldChip = 0;
    soldChoc = 0;
    
    selectWater = false;
    selectCoffee = false;
    selecetChip = false;
    selectChoc = false;
}

string VendingMachine::display()
{
    string num;
    stringstream ss;
    ss << number;
    num = ss.str();
    return "Number: " + num + ", Name: " + name + '\n';
}

void VendingMachine::displayMenu()
{
    cout << "===== Vending Machine Menu =====" << "\n  Water............$1.50"
                                               <<"\n  Regular Coffee...$2.00"
                                               << "\n  Sun Chip.........$1.00"
                                               << "\n  Chocolate Bar....$2.50"
                                               << endl;
}

void VendingMachine::refill(int water, int coffee, int chip, int choc)
{
    numWater = water;
    numCoffee = coffee;
    numChip = chip;
    numChoc = choc;
}

void VendingMachine::status()
{
    cout << display() << endl;

    cout << "Sold: Water: " << soldWater << "/ Regular Coffee: " 
         << soldCoffee << "/ Sun Chip: " << soldChip << "/ Chocolate Bar: "
         << soldChoc << endl;

    cout << "Remaining: Water: " << numWater << "/ Regular Coffee: " 
         << numCoffee << "/ Sun Chip: " << numChip << "/ Chocolate Bar: "
         << numChoc << endl;
    cout << "Total Earnings: $" << fixed <<  setprecision (2) << earnings << endl;
}

void VendingMachine::selectItem()
{
    int selection, quantity;
    int *ptrStock, *ptrSale, *ptrSold;
    double cost;
    string item;
    char cont = 'Y';
    bool tooLarge = false;
    bool *ptrSelect;
    
    while(cont != 'N')
    {   
        cost = 0.0;
        quantity = 0;
        cout << "Select Item: ";
        cin >> selection;
        if(selection == 1)
        {
            item = "Water";
            ptrStock = &numWater;
            ptrSale = &saleWater;
            ptrSold = &soldWater;
            ptrSelect = &selectWater;
            cost = priceWater;
        }
        if(selection == 2)
        {
            item = "Regular Coffee";
            ptrStock = &numCoffee;
            ptrSale = &saleCoffee;
            ptrSold = &soldCoffee;
            ptrSelect = &selectCoffee;
            cost = priceCoffee;
        }
        if(selection == 3)
        {
            item = "Sun Chip";
            ptrStock = &numChip;
            ptrSale = &saleChip;
            ptrSold = &soldChip;
            ptrSelect = &selectChip;
            cost = priceChip;
        }
        if(selection == 4)
        {
            item = "Chocolate Bar";
            ptrStock = &numChoc;
            ptrSale = &saleChoc;
            ptrSold = &soldChoc;
            ptrSelect = &selectChoc;
            cost = priceChoc;
        }
        else if(selection < 1 || selection > 4)
        {
            cerr << "Invalid selection!" << endl;
            selection = -1;
        }
        if(selection != -1)
        {
            cout << "How many do you want to buy? ";
            cin >> quantity;
            if(quantity <= *ptrStock)
            {
                cout << "You selected " << item << '(' << quantity << ')' << endl;
            }
            else
            {
                cout << "You selected " << item << '(' << quantity << ')'
                     << " - Sorry. We don't have enough " << item << '.' << endl;
                tooLarge = true;
            }
        }
        if(!tooLarge)
        {
            cost *= quantity;
            subtotal += cost;
            *ptrStock -= quantity;
            *ptrSale = quantity;
            *ptrSold += quantity;
            *ptrSelect = true;
        }
        cout << "Continue? (Y/N) ";
        cin >> cont;
        cout << endl;
    }
}

void VendingMachine::reset()
{
    numWater = 0;
    numCoffee = 0;
    numChip = 0;
    numChoc = 0;
    soldWater = 0;
    soldCoffee = 0;
    soldChip = 0;
    soldChoc = 0;
}

bool VendingMachine::payment()
{
    int payment, pin;
    char dollarSign;
    double cash;
    
    cout << "Payment Option - Debit(1) / Cash(2): ";
    cin >> payment;
    if(payment == 1)
    {
        cout << "Enter PIN: ";
        cin >> pin;
        if(pin == 7777)
        {
            cout << "Valid" << endl;
            return true;
        }
        else
        {
            cerr << "Invalid" << endl;
            deselect();
            return false;
        }
    }
    if(payment == 2)
    {
        cout << "Enter Money Amount: ";
        cin >> dollarSign >> cash;
        cout << "Change: $" << fixed << setprecision (2) 
             << cash - total() << endl;
        return true;
    }
    else
    {
        deselect();
        return false;
    }
    cout << endl;
}

double VendingMachine::total()
{
    double total;
    total = subtotal * (0.1);
    total += subtotal;
    return total;
}

void VendingMachine::displayReceipt()
{
    double tax = subtotal * (0.1);
    
    if(saleWater > 0)
    {
        cout << "Water: $1.50 x " << saleWater <<" = $" << fixed 
             << setprecision (2) << priceWater * saleWater << endl;
    }
    if(saleCoffee > 0)
    {
        cout << "Regular Coffeee: $2.00 x " << saleCoffee <<" = $" << fixed 
             << setprecision (2) << priceCoffee * saleCoffee << endl;
    }
    if(saleChip > 0)
    {
        cout << "Sun Chip: $1.00 x " << saleChip <<" = $" << fixed 
             << setprecision (2) << priceChip * saleChip << endl;
    }
    if(saleChoc > 0)
    {
        cout << "Chocolate Bar: $2.50 x " << saleChoc <<" = $" << fixed 
             << setprecision (2) << priceChoc * saleChoc << endl;
    }
    cout << "Subtotal: $" << fixed << setprecision (2) << subtotal << endl;
    cout << "Tax (10.0%): $" << fixed << setprecision (2) << tax << endl;
    cout << "Total: $" << fixed << setprecision (2) << total() << endl;

    earnings += total();
    completeTransaction();    
}

void VendingMachine::deselect()
{
    cout << "You de-selected" << endl;
    if(selectWater)
    {
        cout << "    Water " << '(' << saleWater << ')' << endl;
        numWater += saleWater;
        soldWater -= saleWater;
        subtotal -= saleWater * priceWater;
        saleWater = 0;
    }
    if(selectCoffee)
    {
        cout << "    Regular Coffee " << '(' << saleCoffee << ')' << endl;
        numCoffee += saleCoffee;
        soldCoffee -= saleCoffee;
        subtotal -= saleCoffee * priceCoffee;
        saleCoffee = 0;
    }
    if(selecetChip)
    {
        cout << "    Sun Chip " << '(' << saleChip << ')' << endl;
        numChip += saleChip;
        soldChip -= saleChip;
        subtotal -= saleChip * priceChip;
        saleChip = 0;
    }
    if(selectChoc)
    {
        cout << "    Chocolate Bar " << '(' << saleChoc << ')' << endl;
        numChoc += saleChoc;
        soldChoc -= saleChoc;
        subtotal -= saleChoc * priceChoc;
        saleChoc = 0;
    }
    
}
//resets transaction variables back to 0 for next transaction
void VendingMachine::completeTransaction()
{
    saleWater = 0;
    saleCoffee = 0;
    saleChip = 0;
    saleChoc = 0;
    subtotal = 0;
}
