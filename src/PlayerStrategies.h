#pragma once
#include <vector>
using std::vector;

#include <string>
using std::string;

class Player;
class Territory;
class Order;

class PlayerStrategy
{
public:
    PlayerStrategy();
    PlayerStrategy(Player *p);
    PlayerStrategy(const PlayerStrategy &p);
    ~PlayerStrategy();

    PlayerStrategy &operator=(const PlayerStrategy &ps);

    virtual void issueOrder() = 0;
    virtual void issueOrder(Order *o);
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;

    // testing function
    virtual string strategyName() = 0;

    void setPlayer(Player *p);
    Player *getPlayer();

private:
    Player *player;
};

class CheaterPlayerStrategy: public PlayerStrategy{
public:
    CheaterPlayerStrategy(Player* p);
    ~CheaterPlayerStrategy();

    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string strategyName();

};

class NormalPlayerStrategy: public PlayerStrategy{
public:
    NormalPlayerStrategy(Player* p);
    ~NormalPlayerStrategy();

    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string strategyName();

};

// class HumanPlayerStrategy: public PlayerStrategy{

// };

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    AggressivePlayerStrategy(Player* p);
    ~AggressivePlayerStrategy();

    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();

    string strategyName();
};

class BenevolentPlayerStrategy: public PlayerStrategy{
public:
    BenevolentPlayerStrategy(Player* p);
    ~BenevolentPlayerStrategy();

    void issueOrder();
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

    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();

    string strategyName();

    void toggleHasBeenAttacked();

    bool getHasBeenAttacked();

private:
    bool hasBeenAttacked;
};