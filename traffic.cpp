#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

/* ---------------- LINKED LIST : SIGNAL MANAGEMENT ---------------- */
struct Signal {
    int signalId;
    string status;
    Signal* next;
};

Signal* head = NULL;

void addSignal(int id, string status) {
    Signal* newSignal = new Signal{id, status, head};
    head = newSignal;
    cout << "Signal added successfully\n";
}

void displaySignals() {
    Signal* temp = head;
    cout << "\nTraffic Signals:\n";
    while (temp) {
        cout << "Signal ID: " << temp->signalId 
             << " | Status: " << temp->status << endl;
        temp = temp->next;
    }
}

/* ---------------- HASH TABLE : VEHICLE TRACKING ---------------- */
unordered_map<int, string> vehicleMap;

void trackVehicle(int vehicleId, string status) {
    vehicleMap[vehicleId] = status;
}

void showVehicles() {
    cout << "\nVehicle Status:\n";
    for (auto v : vehicleMap) {
        cout << "Vehicle " << v.first << " -> " << v.second << endl;
    }
}

/* ---------------- QUEUE : VEHICLE WAITING ---------------- */
queue<int> vehicleQueue;

void addVehicle(int vehicleId) {
    vehicleQueue.push(vehicleId);
    trackVehicle(vehicleId, "Waiting");
    cout << "Vehicle added to queue\n";
}

/* ---------------- STACK : UNDO SIGNAL CHANGE ---------------- */
stack<int> undoStack;

void allowVehicle() {
    if (vehicleQueue.empty()) {
        cout << "No vehicles waiting\n";
        return;
    }
    int vehicleId = vehicleQueue.front();
    vehicleQueue.pop();
    undoStack.push(vehicleId);
    vehicleMap[vehicleId] = "Passed";
    cout << "Vehicle " << vehicleId << " passed the signal\n";
}

void undoVehiclePass() {
    if (undoStack.empty()) {
        cout << "Nothing to undo\n";
        return;
    }
    int vehicleId = undoStack.top();
    undoStack.pop();
    vehicleMap[vehicleId] = "Waiting";
    cout << "Undo successful for Vehicle " << vehicleId << endl;
}

/* ---------------- TREE : VEHICLE CLASSIFICATION ---------------- */
struct TreeNode {
    string type;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createVehicleTree() {
    TreeNode* root = new TreeNode{"Vehicle", NULL, NULL};
    root->left = new TreeNode{"Light", NULL, NULL};
    root->right = new TreeNode{"Heavy", NULL, NULL};
    root->left->left = new TreeNode{"Bike", NULL, NULL};
    root->left->right = new TreeNode{"Car", NULL, NULL};
    root->right->left = new TreeNode{"Bus", NULL, NULL};
    root->right->right = new TreeNode{"Truck", NULL, NULL};
    return root;
}

void displayTree(TreeNode* root, int space = 0) {
    if (!root) return;
    space += 5;
    displayTree(root->right, space);
    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    cout << root->type << "\n";
    displayTree(root->left, space);
}

/* ---------------- GRAPH : ROAD NETWORK ---------------- */
#define JUNCTIONS 4
int graph[JUNCTIONS][JUNCTIONS] = {
    {0,1,1,0},
    {1,0,1,1},
    {1,1,0,1},
    {0,1,1,0}
};

void showRoadNetwork() {
    cout << "\nRoad Network (Graph):\n";
    for (int i = 0; i < JUNCTIONS; i++) {
        for (int j = 0; j < JUNCTIONS; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

/* ---------------- MAIN MENU ---------------- */
int main() {
    TreeNode* vehicleTree = createVehicleTree();
    int choice;

    do {
        cout << "\n---- Smart Traffic Management System ----\n";
        cout << "1. Add Traffic Signal\n";
        cout << "2. Display Signals\n";
        cout << "3. Add Vehicle\n";
        cout << "4. Allow Vehicle to Pass\n";
        cout << "5. Undo Vehicle Pass\n";
        cout << "6. Show Vehicle Status\n";
        cout << "7. Show Vehicle Classification\n";
        cout << "8. Show Road Network\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int id;
        string status;

        switch (choice) {
            case 1:
                cout << "Enter Signal ID & Status (Red/Green): ";
                cin >> id >> status;
                addSignal(id, status);
                break;

            case 2:
                displaySignals();
                break;

            case 3:
                cout << "Enter Vehicle ID: ";
                cin >> id;
                addVehicle(id);
                break;

            case 4:
                allowVehicle();
                break;

            case 5:
                undoVehiclePass();
                break;

            case 6:
                showVehicles();
                break;

            case 7:
                displayTree(vehicleTree);
                break;

            case 8:
                showRoadNetwork();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
