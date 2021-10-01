#include <vector>
#include <string>

void testOrdersLink();


// Abstract class (with virtual functions?)
class Order
{
    private:
        // to delete
        std::string name;
    public:
        Order();
        Order(std::string name);
        std::string getName() { return name; }
        void setName(std::string orderName) { name = orderName; }
        // To implement
        //virtual bool validate();
        //virtual bool execute();
};

class Deploy : public Order 
{
    public:
        Deploy();
        Deploy(std::string name);
};
class Advance : public Order 
{
    public:
        Advance();
        Advance(std::string name);
};
class Bomb : public Order 
{
    public:
        Bomb();
        Bomb(std::string name);
};
class Blockade : public Order 
{
    public:
        Blockade();
        Blockade(std::string name);
};
class AirLift : public Order 
{
    public:
        AirLift();
        AirLift(std::string name);
};
class Negotiate : public Order 
{   
    public:
        Negotiate();
        Negotiate(std::string name);

};


// OrderList is a DoubleList DA with indexes and nodes 
class OrderList 
{   
    public:
        OrderList();
        // adds an order at the end of the orderlist
        void add(Order o); 
        void remove(int i);
        // initPosition and newPosition are positions (0 to size - 1). Throws out_of_range exception.
        void move(int initPosition, int newPosition);
        void printList();
    private:
        std::vector<Order> *list;

        
};

// Test function (to delete)
void testOrdersDriver();