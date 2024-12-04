#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>

using namespace std;

// Define the Player structure
struct Player {
    char registrationNumber[50];
    char firstName[50];
    char lastName[50];
    char dateOfBirth[20];
    char teams[2][50]; // Player can select a maximum of 2 teams
    int runsScored;
};

// Define the Team structure
struct Team {
    char name[50];
};

// Function prototypes
void Header();
void displayMenu();
void addNewPlayer(vector<Player>& players, const vector<Team>& teams);
void displayPlayers(const vector<Player>& players);
void searchPlayer(const vector<Player>& players);
bool login(string& username);
void savePlayersToFile(const vector<Player>& players);
void loadPlayersFromFile(vector<Player>& players);
void pause();
void manageTeams(vector<Team>& teams);
void displayTeams(const vector<Team>& teams);
void addNewTeam(vector<Team>& teams);
void viewTeamDetails(const vector<Team>& teams, const vector<Player>& players);
void clearPreviousLine();

// Main function
int main() {
    vector<Player> players;
    vector<Team> teams;
    string loggedInUser;
    bool loggedIn = false;

    // Load existing players and teams from files
    loadPlayersFromFile(players);

    while (true) {
        if (!loggedIn) {
            system("cls");
            Header();
            cout << "\n\n-1- Login\n-2- Exit\n\n";
            int choice;
            cout << "Enter your Choice: ";
            cin >> choice;
            if (choice == 1) {
                if (login(loggedInUser)) {
                    loggedIn = true;
                }
            } else if (choice == 2) {
                break;
            } else {
                cout << "Invalid choice!\n";
            }
        } else {
            displayMenu();
            int choice;
            cout << "Enter your Choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    manageTeams(teams);
                    break;

                case 2:
                    viewTeamDetails(teams, players);
                    break;

                case 3:
                    displayPlayers(players);
                    break;

                case 4:
                    addNewPlayer(players, teams);
                    savePlayersToFile(players);
                    break;

                case 5:
                    searchPlayer(players);
                    break;                
                
                case 6:
                    loggedIn = false;
                    cout << "\nLogout";
                    sleep(1);
                    clearPreviousLine();
                    cout << "\nLogout..";
                    sleep(1);
                    clearPreviousLine();
                    cout << "\nLogout...";
                    sleep(1);
                    clearPreviousLine();
                    cout << "Logged out successfully.\n";
                    break;
                case 7:
                    return 0;
                default:
                    cout << "Invalid choice!\n";
                    sleep(2);
            }
        }
    }

    return 0;
}

// Function to display the main menu
void displayMenu() {
    system("cls");
    Header();
    cout << "             ****=========       DASHBOARD         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    cout << "-1- Manage Teams\n"
         << "-2- View Team Details\n"
         << "-3- Display Players Information\n"
         << "-4- Add New Player\n"
         << "-5- Search Players\n"         
         << "-6- Logout\n"
         << "-7- Exit\n\n";
}

// Function to add a new player
void addNewPlayer(vector<Player>& players, const vector<Team>& teams) {
    system("cls");
    Header();
    cout << "          ****=========       PLAYER ADDITION LOG         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    Player newPlayer;

    cout << "Enter Registration Number: ";
    cin >> newPlayer.registrationNumber;
    cout << "Enter First Name: ";
    cin >> newPlayer.firstName;
    cout << "Enter Last Name: ";
    cin >> newPlayer.lastName;
    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    cin >> newPlayer.dateOfBirth;
    cout << "Enter Runs Scored: ";
    cin >> newPlayer.runsScored;

    cout << "\nAvailable Teams:\n";
    for (size_t i = 0; i < teams.size(); ++i) {
        cout <<"-"<< i + 1 << "- " << teams[i].name << "\n";
    }

    cout << "Enter the number of the first team: ";
    int teamIndex1;
    cin >> teamIndex1;
    if (teamIndex1 > 0 && teamIndex1 <= teams.size()) {
        strcpy(newPlayer.teams[0], teams[teamIndex1 - 1].name);
    } else {
        cout << "Invalid team selection!\n";
        sleep(3);
        return;
    }

    cout << "Enter the number of the second team (or 0 to skip): ";
    int teamIndex2;
    cin >> teamIndex2;
    if (teamIndex2 > 0 && teamIndex2 <= teams.size()) {
        strcpy(newPlayer.teams[1], teams[teamIndex2 - 1].name);
    } else if (teamIndex2 == 0) {
        strcpy(newPlayer.teams[1], "");
    } else {
        cout << "Invalid team selection!\n";
        return;
    }

    players.push_back(newPlayer);
    cout << "\nPlayer added successfully!\n";
    sleep(3);
}

// Function to display all players
void displayPlayers(const vector<Player>& players) {
    system("cls");
    Header();
    cout << "         ****=========       PLAYERS' INFORMATION         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    for (size_t i = 0; i < players.size(); ++i) {
        cout << "Registration Number: " << players[i].registrationNumber << "\n"
             << "Name: " << players[i].firstName << " " << players[i].lastName << "\n"
             << "Date of Birth: " << players[i].dateOfBirth << "\n"
             << "Teams: " << players[i].teams[0];
        if (strlen(players[i].teams[1]) > 0) {
            cout << ", " << players[i].teams[1];
        }
        cout << "\nRuns Scored: " << players[i].runsScored << "\n\n";
    }
    pause(); // Pause to keep the information on screen
}

// Function to search for a player by registration number
void searchPlayer(const vector<Player>& players) {
    system("cls");
    Header();
    cout << "          ****=========       PLAYER SEARCH LOG         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    char regNum[50];
    cout << "Enter Registration Number to search: ";
    cin >> regNum;

    for (size_t i = 0; i < players.size(); ++i) {
        if (strcmp(players[i].registrationNumber, regNum) == 0) {
            system("cls");
            Header();
            cout << "          ****=========       PLAYERS DETAILS         =========****\n";
            cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
            cout << "Registration Number: " << players[i].registrationNumber << "\n"
                 << "Name: " << players[i].firstName << " " << players[i].lastName << "\n"
                 << "Date of Birth: " << players[i].dateOfBirth << "\n"
                 << "Teams: " << players[i].teams[0];
            if (strlen(players[i].teams[1]) > 0) {
                cout << ", " << players[i].teams[1];
            }
            cout << "\nRuns Scored: " << players[i].runsScored << "\n\n";
            pause(); // Pause to keep the information on screen
            return;
        }
    }
    cout << "Player not found!\n";
    pause(); // Pause to keep the information on screen
}

// Function to handle user login
bool login(string& username) {
    system("cls");
    Header();
    string user, pass;
    cout << "            ****=========       LOGIN PORTAL         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    // For simplicity, use hardcoded username and password
    if (user == "admin" && pass == "123") {
        cout << "\nLogin.";
        sleep(1);
        clearPreviousLine();
        cout << "\nLogin..";
        sleep(1);
        clearPreviousLine();
        cout << "\nLogin...";
        sleep(1);
        clearPreviousLine();
        cout << "\nLogin Successfully!\n\n";
        sleep(2);
        username = user;
        return true;
    } else {
        cout << "\nInvalid credentials!\n";
        sleep(3);
        system("cls");
        return false;
    }
}

// Function to save players to a file
void savePlayersToFile(const vector<Player>& players) {
    ofstream outFile("players.txt");
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        outFile << players[i].registrationNumber << "\n"
                << players[i].firstName << "\n"
                << players[i].lastName << "\n"
                << players[i].dateOfBirth << "\n"
                << players[i].teams[0] << "\n"
                << players[i].teams[1] << "\n"
                << players[i].runsScored << "\n";
    }
    outFile.close();
}

// Function to load players from a file
void loadPlayersFromFile(vector<Player>& players) {
    ifstream inFile("players.txt");
    if (!inFile) {
        return;
    }

    players.clear();
    Player player;
    while (inFile.getline(player.registrationNumber, 50)) {
        inFile.getline(player.firstName, 50);
        inFile.getline(player.lastName, 50);
        inFile.getline(player.dateOfBirth, 20);
        inFile.getline(player.teams[0], 50);
        inFile.getline(player.teams[1], 50);
        inFile >> player.runsScored;
        inFile.ignore(); // to clear the newline character left in the buffer
        players.push_back(player);
    }
    inFile.close();
}

// Function to display and manage teams
void manageTeams(vector<Team>& teams) {
    system("cls");
    Header();
    cout << "          ****=========       TEAM MANAGEMENT         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    cout << "-1- Display Teams\n-2- Add New Team\n-3- Return to Main Menu\n\n";
    int choice;
    cout << "Enter your Choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            displayTeams(teams);
            break;
        case 2:
            addNewTeam(teams);
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice!\n";
    }
}

// Function to display all teams
void displayTeams(const vector<Team>& teams) {
    system("cls");
    Header();
    cout << "                ****=========       TEAMS         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    for (size_t i = 0; i < teams.size(); ++i) {
        cout << i + 1 << ". " << teams[i].name << "\n\n";
    }
    pause(); // Pause to keep the information on screen
}

// Function to add a new team
void addNewTeam(vector<Team>& teams) {
    system("cls");
    Header();
    cout << "          ****=========       TEAM ADDITION LOG         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    Team newTeam;
    cout << "Enter Team Name: ";
    cin.ignore(); // Clear the newline character from the buffer
    cin.getline(newTeam.name, 50);
    teams.push_back(newTeam);
    cout << "\nTeam added successfully!\n";
    sleep(3);
}

// Function to view team details along with players
void viewTeamDetails(const vector<Team>& teams, const vector<Player>& players) {
    system("cls");
    Header();
    cout << "          ****=========       VIEW TEAM DETAILS         =========****\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n\n\n";
    for (size_t i = 0; i < teams.size(); ++i) {
        cout << "Team: " << teams[i].name << "\n";
        cout << "Players:\n";
        for (size_t j = 0; j < players.size(); ++j) {
            if (strcmp(players[j].teams[0], teams[i].name) == 0 || strcmp(players[j].teams[1], teams[i].name) == 0) {
                cout << " - " << players[j].firstName << " " << players[j].lastName << "\n";
            }
        }
        cout << "\n";
    }
    pause(); // Pause to keep the information on screen
}

// Function to pause the screen
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to clear the previous line
void clearPreviousLine() {
    cout << "\033[A\033[2K"; // ANSI escape code to move cursor up one line and clear the line
}

//Welcome Message
void Header() {
    cout << "\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n";
    cout << "\n------------------------------------------------------------------------------\n\n";
    cout << "  ****=========       Upcountry Warriors Baseball Club         =========****\n";
    cout << "                            Batticaloa, Sri Lanka                             ";
    cout << "\n------------------------------------------------------------------------------\n\n";
    cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*\n";
}
