#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Player {
    string name;
    bool isWerewolf;
    bool isAlive;
};

void initializePlayers(vector<Player>& players, int numPlayers) {
    cout << "\nInitializing players..." << endl;
    for (int i = 0; i < numPlayers; i++) {
        Player player;
        cout << "Enter player " << i + 1 << " name: ";
        cin >> player.name;
        player.isWerewolf = false;
        player.isAlive = true;
        players.push_back(player);
    }
}

void assignRoles(vector<Player>& players) {
    srand(time(0));
    int numWerewolves = 1; // จำนวนหมาป่า
    int assigned = 0;

    while (assigned < numWerewolves) {
        int randomIndex = rand() % players.size();
        if (!players[randomIndex].isWerewolf) {
            players[randomIndex].isWerewolf = true;
            assigned++;
        }
    }
    cout << "Roles assigned!\n";
}

void displayAlivePlayers(const vector<Player>& players) {
    cout << "\nAlive Players: " << endl;
    for (const auto& player : players) {
        if (player.isAlive) {
            cout << player.name << endl;
        }
    }
}

Player* findPlayerByName(vector<Player>& players, const string& name) {
    for (auto& player : players) {
        if (player.name == name && player.isAlive) {
            return &player;
        }
    }
    return nullptr;
}

bool werewolfAction(vector<Player>& players) {
    string target;
    cout << "\nWerewolf, choose a player to eliminate: ";
    cin >> target;

    Player* targetPlayer = findPlayerByName(players, target);
    if (targetPlayer) {
        targetPlayer->isAlive = false;
        cout << target << " has been eliminated by the Werewolf!\n";
        return true;
    } else {
        cout << "Invalid target. Try again." << endl;
        return false;
    }
}

bool villagersVote(vector<Player>& players) {
    string target;
    cout << "\nVillagers, vote to eliminate a player: ";
    cin >> target;

    Player* targetPlayer = findPlayerByName(players, target);
    if (targetPlayer) {
        targetPlayer->isAlive = false;
        cout << target << " has been eliminated by the villagers!\n";
        return true;
    } else {
        cout << "Invalid target. Try again." << endl;
        return false;
    }
}

bool checkWinCondition(const vector<Player>& players) {
    int werewolfCount = 0;
    int villagerCount = 0;

    for (const auto& player : players) {
        if (player.isAlive) {
            if (player.isWerewolf) werewolfCount++;
            else villagerCount++;
        }
    }

    if (werewolfCount == 0) {
        cout << "\nVillagers win!" << endl;
        return true;
    }
    if (werewolfCount >= villagerCount) {
        cout << "\nWerewolf wins!" << endl;
        return true;
    }
    return false;
}

int main() {
    int numPlayers;

    cout << "Welcome to Werewolf Game!" << endl;
    cout << "Enter number of players (minimum 3): ";
    cin >> numPlayers;

    if (numPlayers < 3) {
        cout << "Need at least 3 players to play." << endl;
        return 0;
    }

    vector<Player> players;
    initializePlayers(players, numPlayers);
    assignRoles(players);

    bool gameEnded = false;

    while (!gameEnded) {
        displayAlivePlayers(players);
        
        // Werewolf's turn
        while (!werewolfAction(players));

        gameEnded = checkWinCondition(players);
        if (gameEnded) break;

        // Villagers' vote
        displayAlivePlayers(players);
        while (!villagersVote(players));

        gameEnded = checkWinCondition(players);
    }

    return 0;
}
