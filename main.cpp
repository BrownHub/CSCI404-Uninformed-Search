#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

void getConnection(string city, map<string, map<string, int>> &roadmap, set<string> &connectedComponent);

int main(int argc, char **argv ) {
    //Initialize variables for creating map
    string city;
    string destination;
    int distance;
    map<string, map<string, int>> roadmap;

    //read in file
    string lineStart;
    ifstream inputFile(argv[1]);
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
    }

    //Create a structure to track connected locations
    vector<set<string>> connections(1);

    //track connected locations
    for (pair<string, map<string, int>> c : roadmap) {
        bool connected = false;
        for(set<string> Component : connections){
            if(Component.count(c.first) > 0) {
                connected = true;
                break;
            }
        }

        if(!connected){
            set<string> connectedComponent;
            getConnection(c.first, roadmap, connectedComponent);

            connections.push_back(connectedComponent);
        }
    }
    connections.erase(connections.begin());

    //Create variables to search map
    string startingCity = argv[2];
    string destinationCity = argv[3];
    int travelDistance = 0;
    vector<string> travelPath;
    bool connected = false;
    bool found = false;
    bool sameCity = false;
    priority_queue<pair<int, pair<string, vector<string>>>> searchQueue;
    pair<int, pair<string, vector<string>>> startingNode;
    startingNode.first = travelDistance;
    startingNode.second.first = startingCity;
    startingNode.second.second.push_back(startingCity);
    searchQueue.push(startingNode); //Start at city

    //Search map
    for (set<string> component : connections) {
        if(component.count(startingCity) > 0 && component.count(destinationCity) > 0){
            connected = true;
            break;
        }
    }

    if(connected) {
        while (!found) {
            //expand next node in queue
            pair<int, pair<string, vector<string>>> node = searchQueue.top();
            searchQueue.pop();
            node.first = node.first * -1;

            if(node.second.first == destinationCity) {
                sameCity = true;
                break;
            }

            for (pair<string, int> c : roadmap.at(node.second.first)) {
                //Check if any nodes are destination
                if (c.first == destinationCity) {
                    found = true;
                    travelDistance = node.first + c.second;
                    vector<string> path = node.second.second;
                    path.push_back(c.first);
                    travelPath = path;
                    break;
                } else {    //Add to queue in priority order
                    vector<string> path = node.second.second;
                    path.push_back(c.first);
                    pair<int, pair<string, vector<string>>> newNode;
                    newNode.first = (node.first + c.second) * -1;
                    newNode.second.first = c.first;
                    newNode.second.second = path;
                    searchQueue.push(newNode);
                }
            }
        }
    }

    //Print results to terminal
    if(sameCity) {
        cout << "distance: " << travelDistance << " km" << endl;
        cout << "route:" << endl;
        cout << destinationCity << " to " << destinationCity << ", " << travelDistance << " km" << endl;
    } else if(!found) {
        cout << "distance: infinity" << endl;
        cout << "route:\nnone" << endl;
    } else {
        cout << "distance: " << travelDistance << " km" << endl;
        cout << "route:" << endl;

        for (int i = 0; i < travelPath.size() - 1; i++ ) {
            cout << travelPath.at(i) << " to " << travelPath.at(i + 1) << ", ";
            cout << roadmap.at(travelPath.at(i)).at(travelPath.at(i + 1)) << " km" << endl;
        }
    }

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