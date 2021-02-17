#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <queue>

using namespace std;

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
    //Initializes map with data from file
    // Add distances for a max value
    while (lineStart != "END"){
        city = lineStart;
        inputFile >> destination;
        inputFile >> distance;
        inputFile >> lineStart;

        roadmap[city][destination] = distance;
        maxDistance += distance;
    }

    //Completes map with two-way information
    for (pair<string, map <string, int>> c1 : roadmap){
        for (pair<string, map <string, int>> c2 : roadmap){
            if(c2.second.count(c1.first) > 0){
                roadmap[c1.first][c2.first] = c2.second.at(c1.first);
            }
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
        node.first = node.first * -1;
        searchQueue.pop();

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