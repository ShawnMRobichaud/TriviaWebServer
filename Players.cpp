//players class
#include <iostream>
#include <string>
#include <cstdint> //used for uint
#include <array> 
#include <cstdlib>
#include <random> //for random number generation


using namespace std;

class Players {
private:
    string name; //store player name
    string team; //store team name
    uint16_t score; //track score
    uint16_t ID; //unique player ID

    // static engine & distribution for random number generation
    static mt19937 rng;
    static uniform_int_distribution<uint16_t> dist;

public:
    //constructor with default values
    Players() : name(""), team(""), score(0), ID(0) {}

    //set function for name
    void setName( string playerName) {
        name = playerName;
    };

    //set function for overall score
    void setScore(int points) {
        score = points;
    };

    //set function for team name
    void setTeam(string playerTeam) {
        team = playerTeam;
    };

    //get function to return name
    string getName() const {
        return name;
    };

    //get function to return team name
    string getTeam() const {
        return team;
    };

    //get function to return overall score
    uint16_t getScore() const {
        return score;
    };

    //get function for ID
    uint16_t getID() const {
        return ID;
    };

    void generateID() {
        //random 3 digit ID
        ID = dist(rng);
    }
};

    // static member definitions
    mt19937 Players::rng{ random_device{}() };
    uniform_int_distribution<uint16_t> Players::dist{ 100, 999 };

//main func to test class
/*
int main() {

    Players player1;
    player1.setName("bigatake");
    player1.setTeam("Team 1");
    player1.setScore(6);
    player1.generateID();

    cout << "Player Name: " << player1.getName() << endl;
    cout << "Player Team: " << player1.getTeam() << endl;
    cout << "Player Score: " << player1.getScore() << endl;
    cout << "Player ID: " << player1.getID() << endl;

    return 0;
}
    */