//players class
#include <iostream>
#include <string>
#include <cstdint> //used for uint8_t
#include <array> 
#include <cstdlib>
#include <ctime>


using namespace std;

class Players {
private:
    string name; //store player name
    array<uint8_t, 6> mac_address; //store a 6 byte mac
    string team; //store team name
    int score; //track score
    int ID; //unique player ID

public:
    //constructor with default values
    Players() : name(""), mac_address{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, team(""), score(0), ID(0) {}

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

    //get function to return mac address
    array<uint8_t, 6> getMac() const {
        //esp_read_mac()?
        //might need seperate setmac func
        return mac_address;
    };
    
    //get function to return team name
    string getTeam() const {
        return team;
    };

    //get function to return overall score
    int getScore() const {
        return score;
    };

    //get function for ID
    int getID() const {
        return ID;
    };

    //function to generate a player ID
    //not too random, but should mac xor should help
    void generateID() {
        ID = (rand() % 90000) + 10000;
        //hash the id with the mac address
        for (int i = 0; i < mac_address.size(); ++i) {
            ID ^= mac_address[i]; // XOR each byte
        }
    };
};

//main func to test class
/*int main() {

    srand(static_cast<unsigned int>(time(0)));

    Players player1;
    player1.setName("bigatake");
    player1.setTeam("Team 1");
    player1.setScore(100);
    player1.generateID();

    cout << "Player Name: " << player1.getName() << endl;
    cout << "Player Team: " << player1.getTeam() << endl;
    cout << "Player Score: " << player1.getScore() << endl;
    cout << "Player ID: " << player1.getID() << endl;

    return 0;
}
*/