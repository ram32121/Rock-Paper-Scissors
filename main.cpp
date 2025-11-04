#include <iostream>
#include <random>
#include <string>
#include <cctype>
#include <iomanip>

class RockPaperScissors {
private:
    int playerScore;
    int computerScore;
    int rounds;
    std::mt19937 rng;
    
    enum Choice { ROCK = 1, PAPER = 2, SCISSORS = 3 };
    
public:
    RockPaperScissors() : playerScore(0), computerScore(0), rounds(0) {
        std::random_device rd;
        rng.seed(rd());
    }
    
    void displayWelcome() {
        std::cout << "================================\n";
        std::cout << "  ROCK, PAPER, SCISSORS GAME\n";
        std::cout << "================================\n";
        std::cout << "Rules:\n";
        std::cout << "- Rock beats Scissors\n";
        std::cout << "- Paper beats Rock\n";
        std::cout << "- Scissors beats Paper\n";
        std::cout << "================================\n\n";
    }
    
    void displayMenu() {
        std::cout << "Choose your move:\n";
        std::cout << "1. Rock\n";
        std::cout << "2. Paper\n";
        std::cout << "3. Scissors\n";
        std::cout << "4. View Scores\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice (1-5): ";
    }
    
    std::string choiceToString(Choice choice) {
        switch(choice) {
            case ROCK: return "Rock";
            case PAPER: return "Paper";
            case SCISSORS: return "Scissors";
            default: return "Invalid";
        }
    }
    
    Choice getPlayerChoice() {
        int choice;
        while(true) {
            std::cin >> choice;
            if(std::cin.fail() || choice < 1 || choice > 5) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! Please enter a number between 1-5: ";
            } else {
                return static_cast<Choice>(choice);
            }
        }
    }
    
    Choice getComputerChoice() {
        std::uniform_int_distribution<int> dist(1, 3);
        return static_cast<Choice>(dist(rng));
    }
    
    int determineWinner(Choice player, Choice computer) {
        if(player == computer) {
            return 0; // Tie
        }
        
        if((player == ROCK && computer == SCISSORS) ||
           (player == PAPER && computer == ROCK) ||
           (player == SCISSORS && computer == PAPER)) {
            return 1; // Player wins
        }
        
        return -1; // Computer wins
    }
    
    void playRound(Choice playerChoice) {
        Choice computerChoice = getComputerChoice();
        rounds++;
        
        std::cout << "\n--- Round " << rounds << " ---\n";
        std::cout << "You chose: " << choiceToString(playerChoice) << "\n";
        std::cout << "Computer chose: " << choiceToString(computerChoice) << "\n";
        
        int result = determineWinner(playerChoice, computerChoice);
        
        if(result == 0) {
            std::cout << "It's a tie!\n";
        } else if(result == 1) {
            std::cout << "You win this round!\n";
            playerScore++;
        } else {
            std::cout << "Computer wins this round!\n";
            computerScore++;
        }
        
        std::cout << "Current Score - You: " << playerScore 
                  << " | Computer: " << computerScore << "\n\n";
    }
    
    void displayScores() {
        std::cout << "\n=== GAME STATISTICS ===\n";
        std::cout << "Rounds played: " << rounds << "\n";
        std::cout << "Your score: " << playerScore << "\n";
        std::cout << "Computer score: " << computerScore << "\n";
        
        if(playerScore > computerScore) {
            std::cout << "You're winning! \n";
        } else if(computerScore > playerScore) {
            std::cout << "Computer is winning! \n";
        } else {
            std::cout << "It's a tie game! \n";
        }
        
        if(rounds > 0) {
            double winRate = (double)playerScore / rounds * 100;
            std::cout << "Your win rate: " << std::fixed << std::setprecision(1) 
                      << winRate << "%\n";
        }
        std::cout << "=======================\n\n";
    }
    
    void displayFinalResults() {
        std::cout << "\n=== FINAL RESULTS ===\n";
        displayScores();
        std::cout << "Thanks for playing!\n";
        std::cout << "=====================\n";
    }
    
    void run() {
        displayWelcome();
        
        while(true) {
            displayMenu();
            int choice = getPlayerChoice();
            
            switch(choice) {
                case 1:
                case 2:
                case 3:
                    playRound(static_cast<Choice>(choice));
                    break;
                case 4:
                    displayScores();
                    break;
                case 5:
                    displayFinalResults();
                    return;
                default:
                    std::cout << "Invalid choice! Please try again.\n\n";
            }
        }
    }
};

int main() {
    RockPaperScissors game;
    game.run();
    return 0;
}