#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

void getConnection(string city, map<string, map<string, int>> &roadmap, set<string> &connectedComponent);

int main(int argc, char **argv ) {
    string city;
    string destination;
    int distance;
    int maxDistance = 0;
    map<string, map<string, int>> roadmap;

    //read in file
    string lineStart;
    ifstream inputFile("input1.txt");
    inputFile >> lineStart;

    //Construct data structure:
    // separate values into city, destination, and distance
    //Create map<string(city):map<string(dest):int(distance)>
    //Creates map with data from file
    // Sum distances for a max value
    while (lineStart != "END"){
        city = lineStart;
        inputFile >> destination;
        inputFile >> distance;
        inputFile >> lineStart;

        roadmap[city][destination] = distance;
        roadmap[destination][city] = distance;
        maxDistance += distance;
    }

    //Create a structure to track connected locations
    vector<set<string>> connections(1);

    for (pair<string, map<string, int>> c : roadmap) {
        bool connected = false;
        for(set<string> Component : connections){
            if(Component.count(c.first) > 1) {
                connected = true;
                break;
            }
        }

        if(!connected){
            set<string> connectedComponent;
            getConnection(c.first, roadmap, connectedComponent);

            if(connections.size() == 1){
                connections.at(0) = connectedComponent;
            } else {
                connections.push_back(connectedComponent);
            }
        }
    }

    for(set<string> component : connections){
        cout << endl << "Connection:" << endl;
        for(string location : component){
            cout << location << endl;
        }
    }

    for (pair<string, map <string, int>> c : roadmap){
        cout << c.first << endl;

        for (pair<string, int> d : c.second){
            cout << "\t" << d.first << ": " << d.second << endl;
        }
    }

    //Search data structure:
    //Set found condition to false
    //Create queue of pair<int cost, string destination>
    //Create distance variable
    string startingCity = "Bremen";
    string destinationCity = "Frankfurt";
    int travelDistance = 0;
    bool found = false;
    priority_queue<pair<int, string>> searchQueue;
    searchQueue.push(pair<int, string> (travelDistance, startingCity)); //Start at city

    while (!found) {
        //expand next node in queue
        pair<int, string> node = searchQueue.top();
        searchQueue.pop();
        node.first = node.first * -1;
        cout << endl << node.first;

        if(node.first >= maxDistance) {
            break;
        }

        for(pair<string, int> c : roadmap.at(node.second)) {
            //Check if any nodes are destination
            if (c.first == destinationCity) {
                found = true;
                travelDistance = node.first + c.second;
                break;
            } else {    //Add to queue in priority order
                searchQueue.push(pair<int, string> (((node.first + c.second) * -1), c.first));
            }
        }
    }

    cout << endl << "Minimum travel distance: " << travelDistance << endl;

    return 0;
}

void getConnection(string city, map<string, map<string, int>> &roadmap, set<string> &connectedComponent){
    if(connectedComponent.count(city) > 0) {
        return;
    }

    connectedComponent.insert(city);

    for(pair<string, int> c : roadmap.at(city)) {
        getConnection(c.first, roadmap, connectedComponent);
    }
}