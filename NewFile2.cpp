#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Passenger {
    char name[30];
};

struct User {
    char username[20];
    char password[20];
};

static int p = 0;

class Bus {
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][30];

public:
    void allotment(User users[], int numUsers);
    void install();
    void showBuses();
    void showSeats(const char busNumber[]);
    // ... (other class methods)
};

// Initialization of array of objects of class Bus
Bus bus[10];

void Bus::allotment(User users[], int numUsers) {
    char username[20], password[20];

    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    int userIndex;
    bool validUser = false;

    // Check user authentication
    for (userIndex = 0; userIndex < numUsers; ++userIndex) {
        if (strcmp(users[userIndex].username, username) == 0 && strcmp(users[userIndex].password, password) == 0) {
            validUser = true;
            break;
        }
    }

    if (!validUser) {
        cout << "Invalid username or password.\n";
        return;
    }

    int seat;
    char number[5];

    cout << "Bus no: ";
    cin >> number;

    int n;
    for (n = 0; n <= p; n++) {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }

    while (n <= p) {
        cout << "\nSeat Number: ";
        cin >> seat;

        if (seat > 32) {
            cout << "\nThere are only 32 seats available in this bus.";
        } else {
            if (strcmp(bus[n].seat[seat / 4][(seat % 4) - 1], "Empty") == 0) {
                cout << "Enter passenger's name: ";
                cin >> bus[n].seat[seat / 4][(seat % 4) - 1];

                // Store passenger information
                Passenger passenger;
                cout << "Enter passenger's name: ";
                cin.ignore(); // Clear the buffer
                cin.getline(passenger.name, sizeof(passenger.name));

                // You can now use or store the passenger information
                cout << "Seat reserved successfully!\n";
            } else {
                cout << "The seat is already occupied.\n";
            }
        }
        break; // Exit loop after one iteration
    }
}

void Bus::install() {
    cout << "Enter bus number: ";
    cin >> bus[p].busn;

    cout << "Enter driver's name: ";
    cin >> bus[p].driver;

    cout << "Enter arrival time: ";
    cin >> bus[p].arrival;

    cout << "Enter departure time: ";
    cin >> bus[p].depart;

    cout << "Enter from location: ";
    cin >> bus[p].from;

    cout << "Enter to location: ";
    cin >> bus[p].to;

    // Initialize seats as "Empty"
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 4; ++col) {
            strcpy(bus[p].seat[row][col], "Empty");
        }
    }

    p++;
}

void Bus::showBuses() {
    cout << "Available Buses:\n";
    for (int i = 0; i < p; ++i) {
        cout << "Bus No: " << bus[i].busn << "\tDriver: " << bus[i].driver << "\n";
    }
}

void Bus::showSeats(const char busNumber[]) {
    int n;
    for (n = 0; n < p; ++n) {
        if (strcmp(bus[n].busn, busNumber) == 0)
            break;
    }

    if (n >= p) {
        cout << "Bus not found.\n";
        return;
    }

    cout << "Bus No: " << bus[n].busn << "\n";
    cout << "Seats:\n";
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 4; ++col) {
            cout << "Seat " << (row * 4 + col + 1) << ": " << bus[n].seat[row][col] << "\n";
        }
    }
}

int main() {
    const int numUsers = 2;
    User users[numUsers] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };

    int choice;
    do {
        cout << "\n\n";
        cout << "\t\t***SIMPLE BUS RESERVATION SYSTEM***";
        cout << "\n\n";

        cout << "\t\t\t1. Install Bus\n\t\t\t"
             << "2. Reserve Seat\n\t\t\t"
             << "3. Show Available Buses\n\t\t\t"
             << "4. Show Seats of a Bus\n\t\t\t"
             << "5. Exit";

        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bus[p].install();
                break;
            case 2:
                bus[p].allotment(users, numUsers);
                break;
            case 3:
                bus[p].showBuses();
                break;
            case 4:
                {
                    char busNumber[5];
                    cout << "Enter bus number: ";
                    cin >> busNumber;
                    bus[p].showSeats(busNumber);
                }
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
