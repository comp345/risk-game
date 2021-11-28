class Player;

class PlayerStrategy{
public:
    void issueOrder() = 0;
    vector<Territory *> toAttack() = 0;
    vector<Territory *> toDefend() = 0;
private:
    Player* p;
}

class Neutral: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
}

class Cheater: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
}

class Human: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
}

class Aggressive: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
}

class Benevolent: public PlayerStrategy{
public:
    void issueOrder();
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
}