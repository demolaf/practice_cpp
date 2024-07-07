// CppPrj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

enum PlayerPosition
{
    forward,
    midfielder,
    defender,
    goalkeeper
};

/* Searchable
* Abstract class used to define how to make an object
*/
class Searchable
{
public:
    virtual std::vector<std::string> terms() = 0;
    virtual std::string title() = 0;
};

class Player : public Searchable
{
public:
    Player(std::string name, std::string club, int overallRating, PlayerPosition playerPosition)
        : id{ generateId() }, name{ name }, club{ club }, 
        playerPosition{ playerPosition }, overallRating{ overallRating }
    {

    }

    std::vector<std::string> terms() override
    {
        return { std::to_string(id), name, club };
    }

    std::string title() override
    {
        return name;
    }

    int getId() const
    {
        return id;
    }

    static Player getPlayerById(int id, const std::vector<Player>& players) 
    {
        for (const auto& player : players) {
            if (player.id == id) {
                return player;
            }
        }
        throw std::runtime_error("Player not found");
    }

    static std::vector<Player> players()
    {
        return {
            Player{"Cristiano Ronaldo", "Al Nassr", 86, PlayerPosition::forward},
            Player{"Lionel Messi", "Inter Miami", 88, PlayerPosition::forward},
            Player{"Kylian Mbappe", "Real Madrid", 94, PlayerPosition::forward},
            Player{"Erling Haaland", "Manchester City", 91, PlayerPosition::forward},
            Player{"Neymar Jr", "Al Hilal", 87, PlayerPosition::forward},
            Player{"Vinicius Jr", "Real Madrid", 90, PlayerPosition::forward},
            Player{"Mohammed Salah", "Liverpool", 89, PlayerPosition::forward},
            Player{"Bukayo Saka", "Arsenal", 87, PlayerPosition::forward},
            Player{"Bernardo Silva", "Manchester City", 89, PlayerPosition::midfielder},
            Player{"Martin Odegaard", "Arsenal", 88, PlayerPosition::midfielder},
            Player{"Jamal Musiala", "Bayern", 87, PlayerPosition::midfielder},
            Player{"Declan Rice", "Arsenal", 86, PlayerPosition::midfielder},
            Player{"Rodri Cascante", "Manchester City", 89, PlayerPosition::midfielder},
            Player{"Kevin De Bruyne", "Manchester City", 92, PlayerPosition::midfielder},
            Player{"Luka Modric", "Real Madrid", 88, PlayerPosition::midfielder},
            Player{"Jeremie Frimpong", "Bayer Leverkusen", 85, PlayerPosition::defender},
            Player{"William Saliba", "Arsenal", 87, PlayerPosition::defender},
            Player{"Virgil Van Dijk", "Liverpool", 90, PlayerPosition::defender},
            Player{"Matthijs De Ligt", "Bayern", 86, PlayerPosition::defender},
            Player{"Thibaut Courtois", "Real Madrid", 91, PlayerPosition::goalkeeper},
            Player{"Jan Oblak", "Athletico Madrid", 87, PlayerPosition::goalkeeper},
            Player{"Allison Becker", "Liverpool", 89, PlayerPosition::goalkeeper},
            Player{"Ederson Moraes", "Manchester City", 88, PlayerPosition::goalkeeper},
        };
    }

    int generateId() const {
        return 100 + std::rand() % 900;
    }

    static void printPlayers(const std::vector<Player> players)
    {
        for (const auto& player : players) {
            std::cout << "\nId: " << player.id << " Name: " << player.name << std::endl;
        }
    }

    std::string name;
    std::string club;
    PlayerPosition playerPosition;
    int overallRating;

private:
    int id;
};

class Team : public Searchable 
{
public:
    Team(std::string name, std::vector<Player> players) 
        : name{ name }, players { players }
    {

    }

    std::vector<std::string> terms() override
    {
        return { name };
    }

    std::string title() override
    {
        return name;
    }

    std::vector<Player> getPlayers() const
    {
        return players;
    }

    void updatePlayers(const std::vector<Player> updatedPlayers)
    {
        this->players = updatedPlayers;
    }
    
    static void printTeamDetails(const std::vector<Team> teams) 
    {
        for (const auto& team : teams) {
            std::cout << "\nName: " << team.name << std::endl;
            for (const auto& player : team.players) {
                std::cout << "\nId: " << player.getId() << " Name: \n" << player.name << std::endl;
            }
        }
    }

    const std::string name;
private:
    std::vector<Player> players;
};

// Play match instructions
// 1.How many teams?
// 2.Select players (or search through players) for each team
// 3.Start the match
// 4.Wait for the result
// 5.Review match result
class App 
{
public:
    App() 
        : playerPool{
        Player::players()
    }
    {
        Player::printPlayers(playerPool);
    }

    void run() 
    {
        selectTeams();
        selectPlayers();
    }

private:
    void selectTeams() 
    {
        std::cout << "\nNumber of teams (e.g. 2, 4, 8, 16):" << std::endl;
        std::cin >> noOfTeams;

        std::cout << "\nPlayers per team:" << std::endl;
        std::cin >> playersPerTeam;

        for (int i = 0; i < noOfTeams; i++)
        {
            std::string name;
            std::cout << "\nType team " << i << " name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);
            Team team = Team{ name, {} };
            teams.push_back(team);
        }   
    }

    void selectPlayers() 
    {
        // Loop through all the created teams and ask for players from the user
        for (auto &team: teams)
        {
            std::vector<int> selectedPlayerIds{};
            std::vector<Player> selectedPlayers{};

            std::cout << "\nSelect " << playersPerTeam << " players for team " << team.name << " by id:" << std::endl;
            
            // Display to the user all players in the player pool
            // std::cout << "\nAll players: \n" << std::endl;
            // Player::printPlayers(playerPool);

            // Loop through the max players per team and ask for a player
            for (int i = 0; i < playersPerTeam; ++i)
            {
                // Prompt to search for a player
                std::cout << "Do you want to search or select by inserting the id (y/n):" << std::endl;

                // Search for player
                char searchForPlayer;
                std::cin >> searchForPlayer;

                int selectedPlayerId;

                if (searchForPlayer == 'y')
                {
                    selectedPlayerId = searchPlayers();
                }
                else 
                {
                    // Select by id
                    std::cout << "Enter player id:" << std::endl;
                    std::cin >> selectedPlayerId;
                }

                selectedPlayerIds.push_back(selectedPlayerId);
            }

            // Loop through selected player ids and get the actual player object from the id
            for (auto& playerId: selectedPlayerIds) {
                selectedPlayers.push_back(Player::getPlayerById(playerId, playerPool));
            }

            team.updatePlayers(selectedPlayers);

            Team::printTeamDetails(teams);
        }
    }

    int searchPlayers()
    {
        std::string query;
        std::cout << "Enter player name or club:" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, query);

        int playerFoundId = 0;

        for (auto& player : playerPool)
        {
            for (auto& term : player.terms())
            {
                if (query == term)
                {
                    playerFoundId = player.getId();
                    std::cout << "Players found:" << player.name << "\n" << std::endl;
                }
            }
        }

        if (playerFoundId == 0) {
            std::cout << "Player not found" << std::endl;
        }

        return playerFoundId;
    }

    std::vector<Team> teams;
    int noOfTeams;
    int playersPerTeam;
private:
    std::vector<Player> playerPool;
};

int main()
{
    App app = App();
    app.run();
}
