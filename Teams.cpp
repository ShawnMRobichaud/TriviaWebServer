#include <array>
#include <vector>
#include <string>
#include <cstdint>
// #include "players class"

using namespace std;

class Teams {
private:
    static const int maxPlayersPerTeam = 4;
    static const int maxTeams = 8;
    static const int maxScore = 25;

    vector<Players> teamPlayers[maxTeams];     // Players grouped by team ID
    array<int, maxTeams> teamScores{};         // Score per team
    bool gameOverFlag = false;
    int winningTeamID = -1;

public:
    // Add a player to a team by team ID
    void addPlayer(int teamID, const Players& player) {
        if (teamID >= 0 && teamID < maxTeams && teamPlayers[teamID].size() < maxPlayersPerTeam) {
            teamPlayers[teamID].push_back(player);
        }
    }

    // Remove the last player added to a team
    void removeLastPlayer(int teamID) {
        if (teamID >= 0 && teamID < maxTeams && !teamPlayers[teamID].empty()) {
            teamPlayers[teamID].pop_back();
        }
    }

    // Calculate and update team scores based on all player scores
    void updateTeamScores() {
        for (int teamID = 0; teamID < maxTeams; ++teamID) {
            int total = 0;
            for (const auto& player : teamPlayers[teamID]) {
                total += player.getScore();
            }

            teamScores[teamID] = total;

            if (total >= maxScore && !gameOverFlag) {
                teamScores[teamID] = maxScore;  // Cap score
                winningTeamID = teamID;
                gameOverFlag = true;
            }
        }
    }

    // Return team score by ID
    int getTeamScore(int teamID) const {
        if (teamID >= 0 && teamID < maxTeams) {
            return teamScores[teamID];
        }
        return -1;
    }

    // Return full score array if flag is true
    array<int, maxTeams> getAllScores(bool checkFlag) const {
        if (checkFlag) {
            return teamScores;
        }
        return {}; // Empty/default if not checking
    }

    // Return true if game is over
    bool isGameOver() const {
        return gameOverFlag;
    }

    // Return the winning team ID
    int getWinningTeamID() const {
        return winningTeamID;
    }

    // Reset all teams and scores
    void resetTeams() {
        for (int i = 0; i < maxTeams; ++i) {
            teamPlayers[i].clear();
            teamScores[i] = 0;
        }
        gameOverFlag = false;
        winningTeamID = -1;
    }
};
