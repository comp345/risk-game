
void testOrdersLink();

// implementation 

// OrderList is a DoubleList DA with indexes and nodes 
class OrderList 
{
    // Contains nodes of Orders -> pointers
    Order *init;
    
    public:
        OrderList();
        void remove(Order o); 
        void move(Order o, int i);
};

// Abstract class (with virtual functions?)
class Order
{
    public:
        virtual bool validate();
        virtual bool execute();
};

class Deploy : Order 
{
    
};
class Advance : Order 
{

};
class Bomb : Order 
{

};
class Blockade : Order 
{

};
class AirLift : Order 
{

};
class Negotiate : Order 
{

};
