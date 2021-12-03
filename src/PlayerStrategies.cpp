#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include <algorithm>
#include "Orders.h"
#include "GameEngine.h"

extern void dprint(string message, section option);

// ********************************** //
//      PlayerStrategy functions:     //
// ********************************** //
PlayerStrategy::PlayerStrategy()
{
    this->player = new Player();
}

PlayerStrategy::PlayerStrategy(Player *p)
{
    this->player = p;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &ps)
{
    this->player = new Player(*ps.player);
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &ps)
{
    if (this == &ps)
        return *this;

    player = new Player(*ps.player);
    return *this;
}

Player *PlayerStrategy::getPlayer()
{
    return player;
}

void PlayerStrategy::setPlayer(Player *p)
{
    this->player = p;
}

void PlayerStrategy::issueOrder(Order *o)
{
    player->getOrderList()->add(o);
}

// ********************************************* //
//        NormalPlayerStrategy functions:       //
// ********************************************* //

NormalPlayerStrategy::NormalPlayerStrategy(Player *p) : PlayerStrategy(p) {}

void NormalPlayerStrategy::issueOrder()
{
    Player *issuingPlayer = this->getPlayer();
    // Second condition added due to cheating player who eliminated player durig issueOrdersPhase
    if (issuingPlayer->isDoneIssuing() or issuingPlayer->getTerritories().empty())
    {
        if (issuingPlayer->getTerritories().empty())
        {
            dprint("\tPlayer " + issuingPlayer->getName() + " has been eliminated (not yet audited) by a cheater. isDone flag set to 1", section::issueOrderFromPlayer);
            issuingPlayer->setDoneIssuing(true);
        }
        return void();
    }

    // (1) Deploy: until reinforc pool == 0
    if (issuingPlayer->getReinforcementPool() > 0)
    {
        // cout << "Debug playerIssueOrder. Num of reinforcement pool: " << issuingPlayer->getReinforcementPool() << endl;
        // Check if there is no more territory in priority queue -> rebuild it until pool is empty
        if (issuingPlayer->getPriorityDefending().empty())
        {
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        Territory *territoryTarget = issuingPlayer->getPriorityDefending().top();

        // Create Deploy -> decrease reinforcement
        Deploy *deploy = new Deploy(1, issuingPlayer, territoryTarget);
        issuingPlayer->setReinforcementPool(issuingPlayer->getReinforcementPool() - 1);

        // cout << "Issueing: " << deploy->getDetails() << endl;
        issuingPlayer->issueOrder(deploy);
        issuingPlayer->popPriorityDefend();
    }
    else // when no more reinforcementPool
    {
        // (3) Advance
        if (issuingPlayer->isDoneDeploying() == false)
        {
            // This block should be entered only ONCE, before the first Advance order
            issuingPlayer->setDoneDeploying(true);
            issuingPlayer->getPriorityDefending() = priority_queue<Territory *, vector<Territory *>, compareArmySize>(); // clear queue
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        if (issuingPlayer->isDoneDeploying() and (issuingPlayer->getPriorityDefending().size() > 0 && issuingPlayer->getPriorityAttacking().size() > 0))
        {
            // Need to handle the case when the size of priorityAttack =/= size of priorityDefence => rebuild one or both queues depending on the strategy
            Player *currentPlayer = issuingPlayer;
            Territory *territorySource = currentPlayer->getPriorityDefending().top();
            Territory *territoryTarget = currentPlayer->getPriorityAttacking().top(); // problem is empties before priorityDefending
            Advance *advance = new Advance((territorySource->getNumberOfArmies() / 2), currentPlayer, territorySource, territoryTarget);
            // cout << "Issueing! " << advance->getDetails() << endl;
            currentPlayer->issueOrder(advance);
            currentPlayer->popPriorityAttack();
            currentPlayer->popPriorityDefend();
        }
        // check if no more advance order can be created -> set isDone flag to true
        if (issuingPlayer->getPriorityDefending().size() == 0 || issuingPlayer->getPriorityAttacking().size() == 0)
        {
            issuingPlayer->toggleDoneIssuing();
            // cout << "Finished issueing Deploy and Advance. isDone flag is set to " << to_string(issuingPlayer->isDoneIssuing()) << endl;
        }
    }
}
vector<Territory *> NormalPlayerStrategy::toAttack()
{
    vector<Territory *> attackableTerritories = vector<Territory *>();

    // Get the players territories
    for (Territory *territory : getPlayer()->getTerritories())
    {
        // add them to the attackable Territories if they have an army on them
        if (territory->getNumberOfArmies() > 0)
            attackableTerritories.push_back(territory);
    }

    vector<Territory *> neighbourTerritories = vector<Territory *>();
    for (Territory *territory : attackableTerritories)
    {

        // cout << "the neighbours of " << territory->getName() << " are as follows:\n";
        for (Territory *neighbour : territory->getNeighbors())
        {
            // cout << neighbour->getName() << ", owned by " << neighbour->getOwner()->getName() <<"\n";

            // If we haven't already seen the territory, add it to the list.
            if (!count(neighbourTerritories.begin(), neighbourTerritories.end(), neighbour))

                // ALLOW ADVANCE ON OWN TERRITORY AND OPPONENT TERRITORY
                neighbourTerritories.push_back(neighbour);
        }
    }

    return neighbourTerritories;
}
vector<Territory *> NormalPlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
}
string NormalPlayerStrategy::strategyName()
{
    return "Normal strategy";
}

// ********************************************* //
//        CheaterPlayerStrategy functions:       //
// ********************************************* //

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p){};

void CheaterPlayerStrategy::issueOrder()
{
    /** CORRECT ALGORITHM : return vector of enemy territories to attack
     * - No orders created
     * - "execute" conquest of all toAttack territories in issueOrder
     * - cheater's territories don't have armies on them
     * - cheated does not touch reinforcement pool -> not good condition to end issueorder
     */
    Player *issuingPlayer = this->getPlayer();
    // Second condition necessary to skip players who were eliminated by cheaters
    if (issuingPlayer->isDoneIssuing() or issuingPlayer->getTerritories().empty())
    {
        if (issuingPlayer->getTerritories().empty())
        {
            dprint("\tPlayer " + issuingPlayer->getName() + " has been eliminated (not yet audited) by a cheater. isDone flag set to 1", section::issueOrderFromPlayer);
            issuingPlayer->setDoneIssuing(true);
        }
        dprint("\tCheater " + issuingPlayer->getName() + " hit the isDoneIssuing check, and will now return void back to GameEngine::issueOrdersPhase", section::issueOrderFromPlayer);
        return void();
    }
    dprint("\tCheater " + issuingPlayer->getName() + " has entered issueOrder", section::issueOrderFromPlayer);

    // is this necessary, since there is a check for isDoneIssuing in GameEngine::issueOrdersPhase ?
    if (issuingPlayer->isDoneIssuing())
    {
        return void();
    }
    // conquer neighbors until all are ours
    while (!issuingPlayer->getPriorityAttacking().empty())
    {
        // Change ownership of territory:
        Territory *conquest = issuingPlayer->popPriorityAttack();
        dprint("\t... cheater " + issuingPlayer->getName() + " is conquering " + conquest->getName(), section::issueOrderFromPlayer);
        issuingPlayer->addTerritory(conquest);
        // remove territory from opponent
        int count = 0;
        vector<Territory *> &enemyTerr = conquest->getOwner()->getTerritories();
        for (vector<Territory *>::iterator it = enemyTerr.begin(); it != enemyTerr.end(); ++it)
        {
            if (*it == conquest)
            {
                break;
            }
            ++count;
        }
        enemyTerr.erase(enemyTerr.begin() + count);
        conquest->setOwner(issuingPlayer); // set new owner of territory
    }

    // check if getPriorityAttacking is empty -> every opponent neighbor territory is conquered
    if (issuingPlayer->getPriorityAttacking().size() == 0)
    {
        issuingPlayer->toggleDoneIssuing();
        dprint("Cheater " + issuingPlayer->getName() + "'s isDone flag is set to " + to_string(issuingPlayer->isDoneIssuing()) + "\n", section::issueOrderFromPlayer);
    }
}

vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    /** CORRECT ALGORITHM : return vector of enemy territories to attack
     * - No orders created
     * - "execute" conquest of all toAttack territories in issueOrder
     * - cheater's territories don't have armies on them
     */
    vector<Territory *> attackableTerritories = vector<Territory *>();

    // Get the players territories
    for (Territory *territory : getPlayer()->getTerritories())
    {
        // since cheater has no armies on territories, remove below condition
        // if (territory->getNumberOfArmies() > 0)
        {
            attackableTerritories.push_back(territory);
        }
    }

    vector<Territory *> neighbourTerritories = vector<Territory *>();
    for (Territory *territory : attackableTerritories)
    {

        // cout << "the neighbours of " << territory->getName() << " are as follows:\n";
        for (Territory *neighbour : territory->getNeighbors())
        {
            // cout << neighbour->getName() << ", owned by " << neighbour->getOwner()->getName() <<"\n";

            // If we haven't already seen the territory, add it to the list.
            if (!count(neighbourTerritories.begin(), neighbourTerritories.end(), neighbour))

                // If it already belongs to us then we dont have to attack it.
                if (neighbour->getOwner() != getPlayer())
                    neighbourTerritories.push_back(neighbour);
        }
    }

    return neighbourTerritories;
};

vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string CheaterPlayerStrategy::strategyName()
{
    return "Cheater strategy";
}

// ************************************************ //
//      AggressivePlayerStrategy functions:         //
// ************************************************ //

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p){};


// same strat as normal player, except that toAttack uses a comparator to prioritize strongest territories
void AggressivePlayerStrategy::issueOrder()
{
    Player *issuingPlayer = this->getPlayer();
    // Second condition added due to cheating player who eliminated player durig issueOrdersPhase
    if (issuingPlayer->isDoneIssuing() or issuingPlayer->getTerritories().empty())
    {
        if (issuingPlayer->getTerritories().empty())
        {
            dprint("\tPlayer " + issuingPlayer->getName() + " has been eliminated (not yet audited) by a cheater. isDone flag set to 1", section::issueOrderFromPlayer);
            issuingPlayer->setDoneIssuing(true);
        }
        return void();
    }

    // (1) Deploy: until reinforc pool == 0
    if (issuingPlayer->getReinforcementPool() > 0)
    {
        // cout << "Debug playerIssueOrder. Num of reinforcement pool: " << issuingPlayer->getReinforcementPool() << endl;
        // Check if there is no more territory in priority queue -> rebuild it until pool is empty
        if (issuingPlayer->getPriorityDefending().empty())
        {
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        Territory *territoryTarget = issuingPlayer->getPriorityDefending().top();

        // Create Deploy -> decrease reinforcement
        Deploy *deploy = new Deploy(1, issuingPlayer, territoryTarget);
        issuingPlayer->setReinforcementPool(issuingPlayer->getReinforcementPool() - 1);

        // cout << "Issueing: " << deploy->getDetails() << endl;
        issuingPlayer->issueOrder(deploy);
        issuingPlayer->popPriorityDefend();
    }
    else // when no more reinforcementPool
    {
        // (3) Advance
        if (issuingPlayer->isDoneDeploying() == false)
        {
            // This block should be entered only ONCE, before the first Advance order
            issuingPlayer->setDoneDeploying(true);
            issuingPlayer->getPriorityDefending() = priority_queue<Territory *, vector<Territory *>, compareArmySize>(); // clear queue
            for (Territory *toDefend : issuingPlayer->toDefend())
            {
                issuingPlayer->addToPriorityDefend(toDefend);
            }
        }

        if (issuingPlayer->isDoneDeploying() and (issuingPlayer->getPriorityDefending().size() > 0 && issuingPlayer->getPriorityAttacking().size() > 0))
        {
            // Need to handle the case when the size of priorityAttack =/= size of priorityDefence => rebuild one or both queues depending on the strategy
            Player *currentPlayer = issuingPlayer;
            Territory *territorySource = currentPlayer->getPriorityDefending().top();
            Territory *territoryTarget = currentPlayer->getPriorityAttacking().top(); // problem is empties before priorityDefending
            Advance *advance = new Advance((territorySource->getNumberOfArmies() / 2), currentPlayer, territorySource, territoryTarget);
            // cout << "Issueing! " << advance->getDetails() << endl;
            currentPlayer->issueOrder(advance);
            currentPlayer->popPriorityAttack();
            currentPlayer->popPriorityDefend();
        }
        // check if no more advance order can be created -> set isDone flag to true
        if (issuingPlayer->getPriorityDefending().size() == 0 || issuingPlayer->getPriorityAttacking().size() == 0)
        {
            issuingPlayer->toggleDoneIssuing();
            // cout << "Finished issueing Deploy and Advance. isDone flag is set to " << to_string(issuingPlayer->isDoneIssuing()) << endl;
        }
    }
}
// Same toAttack implementation as normal player, except we deploy and advance on strongest territory (different comparator used)
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    vector<Territory *> attackableTerritories = vector<Territory *>();

    // Get the players territories
    for (Territory *territory : getPlayer()->getTerritories())
    {
        // add them to the attackable Territories if they have an army on them
        if (territory->getNumberOfArmies() > 0)
            attackableTerritories.push_back(territory);
    }

    vector<Territory *> neighbourTerritories = vector<Territory *>();
    for (Territory *territory : attackableTerritories)
    {

        // cout << "the neighbours of " << territory->getName() << " are as follows:\n";
        for (Territory *neighbour : territory->getNeighbors())
        {
            // cout << neighbour->getName() << ", owned by " << neighbour->getOwner()->getName() <<"\n";

            // If we haven't already seen the territory, add it to the list.
            if (!count(neighbourTerritories.begin(), neighbourTerritories.end(), neighbour))

                // ALLOW ADVANCE ON OWN TERRITORY AND OPPONENT TERRITORY
                neighbourTerritories.push_back(neighbour);
        }
    }

    return neighbourTerritories;
};

vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    return getPlayer()->getTerritories();
};

string AggressivePlayerStrategy::strategyName()
{
    return "Aggressive strategy";
}

// // ************************************************ //
// //        BenevolentPlayerStrategy functions:       //
// // ************************************************ //

// BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p){};

// BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
// {
// }

// void BenevolentPlayerStrategy::issueOrder(Order *o)
// {
//     getPlayer()->getOrderList()->add(o);
// }

// vector<Territory *> BenevolentPlayerStrategy::toAttack()
// {
//     //Since a benevolent player never advances to an enemy territory,
//     //All this advance orders will target his own territories.
//     return getPlayer()->getTerritories();
// };

// vector<Territory *> BenevolentPlayerStrategy::toDefend()
// {
//     return getPlayer()->getTerritories();
// };

// string BenevolentPlayerStrategy::strategyName()
// {
//     return "Benevolent strategy";
// }

// // ********************************************* //
// //        NeutralPlayerStrategy functions:       //
// // ********************************************* //

// NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p){hasBeenAttacked = false;};

// NeutralPlayerStrategy::~NeutralPlayerStrategy()
// {
// }

// void NeutralPlayerStrategy::issueOrder(Order *o)
// {
//     if(hasBeenAttacked == true)
//         getPlayer()->setPlayerStrategy(new AggressivePlayerStrategy(getPlayer()));

//     // Doesnt issue any order?
//     // getPlayer()->getOrderList()->add(o);
// }

// vector<Territory *> NeutralPlayerStrategy::toAttack()
// {
//     //Doesnt issue any orders, do we need to return an attacking list?
//     return getPlayer()->getTerritories();
// };

// vector<Territory *> NeutralPlayerStrategy::toDefend()
// {
//     return getPlayer()->getTerritories();
// };

// string NeutralPlayerStrategy::strategyName()
// {
//     return "Neutral strategy";
// }

// void NeutralPlayerStrategy::toggleHasBeenAttacked(){
//     if(hasBeenAttacked)
//         hasBeenAttacked = false;
//     else
//         hasBeenAttacked = true;
// }