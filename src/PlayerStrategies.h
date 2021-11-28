class Player;

class PlayerStrategy{
public:
    virtual void issueOrder() = 0;
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;
private:
    Player* p;
};

class NeutralPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    virtual vector<Territory *> toAttack();
    virtual vector<Territory *> toDefend();
};

class CheaterPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    virtual vector<Territory *> toAttack();
    virtual vector<Territory *> toDefend();
};

class HumanPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    virtual vector<Territory *> toAttack();
    virtual vector<Territory *> toDefend();
};

class AggressivePlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    virtual vector<Territory *> toAttack();
    virtual vector<Territory *> toDefend();
};

class BenevolentPlayerStrategy: public PlayerStrategy{
public:
    void issueOrder();
    virtual vector<Territory *> toAttack();
    virtual vector<Territory *> toDefend();
};