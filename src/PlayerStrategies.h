#pragma once
#include<vector>
using std::vector;

#include<string>
using std::string;

class Player;
class Territory;
class Order;

class PlayerStrategy{
public:
    PlayerStrategy();
    PlayerStrategy(Player* p);
    PlayerStrategy(const PlayerStrategy& p);

    PlayerStrategy &operator=(const PlayerStrategy &ps);

    virtual void issueOrder(Order* o) = 0;
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;

    //testing function
    virtual string strategyName() = 0;

    virtual ~PlayerStrategy();

    void setPlayer(Player* p);
    Player* getPlayer();
private:
    Player* p;
};

// class CheaterPlayerStrategy: public PlayerStrategy{

// };

// class HumanPlayerStrategy: public PlayerStrategy{

// };

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    AggressivePlayerStrategy(Player* p);
    ~AggressivePlayerStrategy();

    void issueOrder(Order* o);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();

    string strategyName();
};

class BenevolentPlayerStrategy: public PlayerStrategy{
public:
    BenevolentPlayerStrategy(Player* p);
    ~BenevolentPlayerStrategy();

    void issueOrder(Order* o);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();

    string strategyName();
};

class NeutralPlayerStrategy: public PlayerStrategy{
public:
    NeutralPlayerStrategy(Player* p);
    ~NeutralPlayerStrategy();
    // NeutralPlayerStrategy(const NeutralPlayerStrategy& p);
    // NeutralPlayerStrategy &operator=(const NeutralPlayerStrategy &ps);

    void issueOrder(Order* o);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();

    string strategyName();

    void toggleHasBeenAttacked();

private:
    bool hasBeenAttacked;
};