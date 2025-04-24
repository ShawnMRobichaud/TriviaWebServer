#include <array>
#include <string>
#include <sstream>
#include <cstdint>

using namespace std;

class Scores {
private:
    static const int maxTeams = 8;
    static const int maxScore = 25;
    array<int, maxTeams> teamScores{};
    bool gameOverFlag = false;
    int winningTeamID = -1;

public:
    void initTeam(int teamID) {
        if (teamID >= 0 && teamID < maxTeams) {
            teamScores[teamID] = 0;
        }
    }

    void addPoints(int teamID, int points) {
        if (teamID >= 0 && teamID < maxTeams && !gameOverFlag) {
            teamScores[teamID] += points;

            if (teamScores[teamID] >= maxScore) {
                teamScores[teamID] = maxScore;
                winningTeamID = teamID;
                gameOverFlag = true;
            }
        }
    }

    // Parse cookie string to update team scores
    void loadFromCookie(const string& cookieStr) {
        istringstream ss(cookieStr);
        string token;

        while (getline(ss, token, ';')) {
            size_t equalPos = token.find('=');
            if (equalPos != string::npos) {
                string key = token.substr(0, equalPos);
                string value = token.substr(equalPos + 1);

                // Trim spaces if needed
                key.erase(0, key.find_first_not_of(" "));
                value.erase(0, value.find_first_not_of(" "));

                // Expecting keys like team0, team1, ...
                if (key.rfind("team", 0) == 0) {
                    int id = stoi(key.substr(4));
                    int score = stoi(value);

                    if (id >= 0 && id < maxTeams) {
                        teamScores[id] = score;

                        // Optional: Recheck win condition
                        if (score >= maxScore && !gameOverFlag) {
                            teamScores[id] = maxScore;
                            winningTeamID = id;
                            gameOverFlag = true;
                        }
                    }
                }
            }
        }
    }

    // Generate HTTP cookie string for all scores
    string generateCookieString() const {
        ostringstream cookie;
        for (int i = 0; i < maxTeams; ++i) {
            cookie << "team" << i << "=" << teamScores[i];
            if (i < maxTeams - 1) cookie << "; ";
        }
        return cookie.str();
    }

    // Export scores as array for ESP32 logic
    array<int, maxTeams> getAllScores(bool checkTeamScore) const {
        return checkTeamScore ? teamScores : array<int, maxTeams>{};
    }

    int getScore(int teamID) const {
        return (teamID >= 0 && teamID < maxTeams) ? teamScores[teamID] : -1;
    }

    bool isGameOver() const {
        return gameOverFlag;
    }

    int getWinningTeamID() const {
        return winningTeamID;
    }

    void resetGame() {
        for (int& score : teamScores) {
            score = 0;
        }
        gameOverFlag = false;
        winningTeamID = -1;
    }
};
