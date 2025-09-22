#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Veh
 {
    string id;
    string intersection;
};

class TrafficSys 
{
private:
    map<string, queue<Veh>> intersections;  // Vehicles at intersections
    map<string, vector<string>> roads;      // Road connections between intersections
    map<string, string> signals;            // Traffic signals at intersections

public:
    // Add Intersection
    void addInt() 
	{
    system("cls");
    cout << "---- Add Intersection ----\n";
    string name;
    cout << "Enter Intersection Name: ";
    getline(cin, name);

    if (roads.count(name)) 
	{
        cout << "Intersection already exists.\n";
    } else {
        roads[name] = {};
        cout << "Intersection added successfully.\n";
    }
}


    // Add Vehicle to Intersection
  void addVeh() 
  {
    system("cls");
    cout << "---- Add Vehicle ----\n";
    string intersection, id;
    cout << "Enter Intersection: ";
    getline(cin, intersection);

    if (roads.count(intersection)) 
	{
    	
        cout << "Enter Vehicle ID: ";
        getline(cin, id);
        intersections[intersection].push({id, intersection});
        cout << "Vehicle '" << id << "' added to '" << intersection << "'.\n";
    } else 
	{
        cout << "Intersection does not exist.\n";
    }
}


    // Clear Vehicles at Intersection
    void clearVeh() 
	{
    system("cls");
    cout << "---- Clear Vehicles ----\n";
    string intersection;
    cout << "Enter Intersection: ";
    getline(cin, intersection);

    if (roads.count(intersection)) 
	{
        while (!intersections[intersection].empty())
		 {
            intersections[intersection].pop();
        }
        cout << "Cleared all vehicles from '" << intersection << "'.\n";
    } else 
	{
        cout << "Intersection does not exist.\n";
    }
}

    // Display Vehicles at Intersection
  void showVeh()
   {
    system("cls");
    cout << "---- Show Vehicles ----\n";
    string intersection;
    cout << "Enter Intersection: ";
    getline(cin, intersection);

    // Check if the intersection exists
    if (!roads.count(intersection))
	 {
        cout << "Intersection does not exist.\n";
        return;
    }

    // Check if there are vehicles at the intersection
    if (intersections[intersection].empty()) 
	{
        cout << "No vehicles at '" << intersection << "'.\n";
        return;
    }

    // If both checks pass, show the vehicles at the intersection
    cout << "Vehicles at '" << intersection << "':\n";
    int count = 1;
    for (queue<Veh> tempQueue = intersections[intersection]; !tempQueue.empty(); tempQueue.pop()) 
	{
        cout << count++ << ". " << tempQueue.front().id << "\n";
    }
}



   void addConn() 
   {
    system("cls");
    cout << "---- Add Connection ----\n";
    
    string int1, int2;
    cout << "Enter first intersection: ";
    getline(cin, int1);

    cout << "Enter second intersection: ";
    getline(cin, int2);

    if (int1.empty() || int2.empty()) 
	{
        cout << "Error: Intersection names cannot be empty.\n";
        return;
    }

    if (int1 == int2) 
	{
        cout << "Error: Cannot connect an intersection to itself.\n";
        return;
    }

    if (roads.find(int1) == roads.end() || roads.find(int2) == roads.end()) 
	{
        cout << "Error: One or both intersections do not exist.\n";
        return;
    }

 
    if (find(roads[int1].begin(), roads[int1].end(), int2) != roads[int1].end()) 
	{
        cout << "Error: The connection already exists between '" << int1 << "' and '" << int2 << "'.\n";
        return;
    }

    roads[int1].push_back(int2);
    roads[int2].push_back(int1);

    cout << "Connection successfully added between '" << int1 << "' and '" << int2 << "'.\n";
}

  void showInts() 
  {
    system("cls");
    cout << "---- Show Intersections ----\n";
    if (roads.empty()) 
	{
        cout << "No intersections available.\n";
        return;
    }
    for (auto& intersection : roads) 
	{
        cout << "- " << intersection.first << "\n";
    }
}


    // Display Road Network
void showNetwork() 
{
    system("cls");
    cout << "---- Show Network ----\n";
    if (roads.empty()) 
	{
        cout << "No connections available.\n";
        return;
    }

    for (auto& intersection : roads)
	 {
        cout << intersection.first << " is connected to: ";
        if (intersection.second.empty()) 
		{
            cout << "No connections";
        } else 
		{
            for (int i = 0; i < intersection.second.size(); ++i) 
			{
                cout << intersection.second[i];
                if (i + 1 < intersection.second.size()) 
				{
                    cout << ", ";
                }
            }
        }
        cout << "\n";
    }
}



   void clearNetwork() 
   {
    system("cls");
    cout << "---- Clear Network ----\n";
    
    // Iterate through each intersection and clear its connections
    for (auto& intersection : roads) 
	{
        intersection.second.clear();  // Clears the connections of the intersection
    }

    cout << "All connections cleared. Intersections remain intact.\n";
}

        // Manage Traffic Signals
void manageSignals() 
{
    system("cls");
    string intersection, color;

    cout << "Enter intersection name: ";
    getline(cin, intersection);
    if (!roads.count(intersection)) 
	{
        cout << "Intersection doesn't exist.\n";
        cin.get(); // Pause to keep the window open
        return;
    }

    cout << "Enter signal color (green, yellow, red): ";
    getline(cin, color);
    transform(color.begin(), color.end(), color.begin(), ::toupper);

    if (color == "GREEN" || color == "YELLOW" || color == "RED")
	 {
    	
        signals[intersection] = color;
        cout << "Signal at '" << intersection << "' updated to " << color << ".\n";
    } else 
	{
        cout << "Invalid color. Use GREEN, YELLOW, or RED.\n";
    }

    cin.get(); // Pause to keep the window open
}

void showSignals() 
{
	
    system("cls");
    
    if (signals.empty()) 
	{
        cout << "No signal data.\n";
        return;
    }

    for (auto& signal : signals) 
	{
        cout << signal.first << ": " << signal.second << "\n";
    }
}


    // Clear All Data
    void clearInts() {
        system("cls");
        cout << "---- Clear All Intersections ----\n";
        roads.clear();
        intersections.clear();
        signals.clear();
        cout << "All intersections, vehicles, and signals have been cleared.\n";
    }
    // Save Data to File
void saveData(string filename)
 {
    system("cls");
    ofstream file(filename);
    if (!file.is_open()) 
	{
        cout << "Error: Unable to open file for saving data.\n";
        return;
    }

    // Save intersections
    file << "Intersections:\n";
    for (auto& intersection : roads) 
	{
        file << intersection.first << "\n";
    }

    // Save vehicles
    file << "Vehicles:\n";
    for (auto& intersection : intersections) 
	{
        queue<Veh> tempQueue = intersection.second;
        while (!tempQueue.empty()) 
		{
            file << intersection.first << " " << tempQueue.front().id << "\n";
            tempQueue.pop();
        }
    }

    // Save road network connections
    file << "Road Network:\n";
    for (auto& intersection : roads) 
	{
        file << intersection.first;
        for (auto& conn : intersection.second)
		
	    {
            file << " " << conn;
        }
        file << "\n";
    }

    // Save traffic signals
    file << "Traffic Signals:\n";
    for (auto& signal : signals) 
	{
        file << signal.first << " " << signal.second << "\n";
    }

    file.close();
    cout << "Data saved.\n";
}

// Load Data from File
void loadData(string filename) 
{
    system("cls");
    ifstream file(filename);
    if (!file.is_open()) 
	{
        cout << "Error: Unable to open file.\n";
        return;
    }

    string line;
    string currentSection;

    while (getline(file, line)) 
	{
        // Ignore empty lines
        if (line.empty()) continue;

        // Detect section headers
        if (line == "Intersections:" || line == "Vehicles:" || line == "Road Network:" || line == "Traffic Signals:") 
		{
            currentSection = line;
            continue;
        }

        // Process data based on the current section
        if (currentSection == "Intersections:")
		 {
            roads[line] = {}; // Add intersection
        } else if (currentSection == "Vehicles:") 
		{
            stringstream ss(line);
            string intersection, id;
            ss >> intersection >> id;
            intersections[intersection].push({id, intersection});
        } else if (currentSection == "Road Network:") 
		{
            stringstream ss(line);
            string intersection, conn;
            ss >> intersection;
            while (ss >> conn) {
                roads[intersection].push_back(conn);
            }
        } else if (currentSection == "Traffic Signals:") 
		{
            stringstream ss(line);
            string intersection, signal;
            ss >> intersection >> signal;
            signals[intersection] = signal;
        }
    }

    file.close();
    cout << "Data loaded successfully.\n";
}
   
void menu() 
{

    int choice;
    string filename = "traffic_data.txt";
    do {
        system("cls");
        cout << "=========================================================\n";
        cout << "                 Traffic Management System               \n";
        cout << "=========================================================\n";
        cout << "1. Add Intersection\n";
        cout << "2. Add Vehicle\n";
        cout << "3. Clear Vehicles\n";
        cout << "4. Show Vehicles\n";
        cout << "5. Add Connection\n";
        cout << "6. Show All Intersections\n";
        cout << "7. Show Network\n";
        cout << "8. Clear Network\n";
        cout << "9. Manage Traffic Signals\n";
        cout << "10. Show Traffic Signals\n";
        cout << "11. Clear All intersections\n";
        cout << "12. Save Data\n";
        cout << "13. Load Data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice (0-13):\n";
        cout << "=========================================================\n";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addInt(); 
			break;
            case 2: addVeh(); 
			break;
            case 3: clearVeh(); 
			break;
            case 4: showVeh(); 
			break;
            case 5: addConn();
			 break;
            case 6: showInts(); 
			break;
            case 7: showNetwork(); 
			break;
            case 8: clearNetwork(); 
			break;
            case 9: manageSignals(); 
			break;
            case 10: showSignals(); 
			break;
            case 11: clearInts(); 
			break;
            case 12: saveData(filename); 
			break;
            case 13: loadData(filename); 
			break;
            case 0: cout << "Exiting the Traffic Management System. Goodbye!\n";
			 break;
            default: cout << "Invalid choice. Please try again.\n"; 
			break;
        }

        if (choice != 0) 
		{
            cout << "\nPress Enter to return to the menu...";
            cin.get();
        }
    } while (choice != 0);
}
     
};

int main()
 {
    TrafficSys system;
    system.menu();
    return 0;
}
