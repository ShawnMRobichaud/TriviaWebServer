
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // For std::swap
#include <unordered_set>
#include "Players.cpp"

using namespace std;

class TriviaQuestion {
private:
    string question;
    vector<string> answers;
    string originalCorrectAnswer;  // Store the original correct answer
    int correctAnswerIndex;  // Track the index of the correct answer after shuffling
    unordered_set<int> usedRandomValues;

public:
    // Constructor
    TriviaQuestion(string q, string a1, string a2, string a3, string a4, int correctIndex) {
        question = q;
        answers.push_back(a1);
        answers.push_back(a2);
        answers.push_back(a3);
        answers.push_back(a4);
        correctAnswerIndex = correctIndex;
        originalCorrectAnswer = answers[correctIndex];  // Save the correct answer
    }

    // Method to generate a random value (ensuring no duplicates) between 0 and 199
    int generateRandomValue(Players& player) {
        int playerID = player.getID();  // Get the player’s ID from the Players object
        srand(time(0) + playerID);      // Seed RNG with player ID
        int randomValue;
    
        // Ensure that the random value is unique for this player
        do {
            randomValue = rand() % 200;  // Random number between 0 and 199
        } while (usedRandomValues.find(randomValue) != usedRandomValues.end());
    
        usedRandomValues.insert(randomValue);  // Mark value as used
        return randomValue;
    }
    

    // Simpler method to shuffle the answers randomly
    void shuffleAnswers() {
        // Use std::rand() to shuffle answers (simple version)
        for (int i = 0; i < answers.size(); i++) {
            // Random index between i and the end of the vector
            int randomIndex = i + rand() % (answers.size() - i);
            swap(answers[i], answers[randomIndex]);  // Swap the elements
        }

        // After shuffling, find the new index of the correct answer
        for (int i = 0; i < answers.size(); i++) {
            if (answers[i] == originalCorrectAnswer) {
                correctAnswerIndex = i;  // Update the correctAnswerIndex after shuffle
                break;
            }
        }
    }

    // Method to print the trivia question, answers, and player info
        void printQuestion(Players& player) {
            cout << "Player Name: " << player.getName() << endl;
            cout << "Player ID: " << player.getID() << endl;
            cout << player.getName() << " is answering the question:" << endl;
        
            cout << "Question: " << question << endl;
        
            cout << "Answers:" << endl;
            for (int i = 0; i < 4; i++) {
                cout << i + 1 << ". " << answers[i] << endl;
            }
            //remove the comment below to test
            cout << "Correct answer is: " << answers[correctAnswerIndex] << endl;
        
            int randomValue = generateRandomValue(player);
            cout << "Generated random value for Player " << player.getName() << ": " << randomValue << endl;
        }
        
    };

int main() {
    Players player1;
    player1.setName("bigatake");
    player1.generateID();

    Players player2;
    player2.setName("quicklearner");
    player2.generateID();

    Players player3;
    player3.setName("gameguru");
    player3.generateID();

    TriviaQuestion tq1("What is the capital of France?", 
                       "London", "Berlin", "Paris", "Rome", 2);  // Correct answer is "Paris" at index 2

    TriviaQuestion tq2("What is the capital of England?", 
                       "London", "Berlin", "Paris", "Rome", 0);
    
    TriviaQuestion tq3("What is the capital of Italy?", 
                       "London", "Berlin", "Paris", "Rome", 3);  
    // Create a list of players and trivia questions and loop through them

    vector<TriviaQuestion> tqs = {tq1, tq2, tq3};
    vector<Players> players = {player1, player2, player3};

    for (auto& player : players) {
        for(auto& tq : tqs) {
        tq.shuffleAnswers();  // Shuffle the answers for each player
        tq.printQuestion(player);  // Print the question and answers for this player
        cout << endl;
        }
    }

    return 0;
}
