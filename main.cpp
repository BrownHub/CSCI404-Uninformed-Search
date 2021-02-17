#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, char **argv ) {
    //read in file & construct data structure:
    // separate values into city, destination, and distance
    string city;
    string destination;
    int distance;
    map<string, map<string, int>> roadmap;

    string lineStart;
    ifstream inputFile("input1.txt");
    inputFile >> lineStart;

    while (lineStart != "END"){
        city = lineStart;
        inputFile >> destination;
        inputFile >> distance;
        inputFile >> lineStart;

        roadmap[city][destination] = distance;
    }

    roadmap[city][destination] = distance;

    for (pair<string, map <string, int>> c : roadmap){
        cout << c.first << endl;

        for (pair<string, int> d : c.second){
            cout << "\t" << d.first << ": " << d.second << endl;
        }
    }
    // Create map<string(city):map<string(dest):int(distance)>
    // Add distances for a max value
    // Create connection groups?

    //Search data structure:
    //

    return 0;
}