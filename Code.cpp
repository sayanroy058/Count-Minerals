#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Function to count unique deposits and mineral occurrences in a map
void countDeposits(const std::vector<std::string>& map, int mapNumber, int lineNumber) {
    int rows = map.size();
    int cols = map[0].length();
    std::vector<std::vector<bool> > visited(rows, std::vector<bool>(cols, false));
    std::map<char, int> mineralOccurrences;

    int depositCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] != '.' && !visited[i][j]) {
                char mineral = map[i][j];
                depositCount++;

                // Depth-first search to find all connected minerals in the deposit
                std::vector<std::pair<int, int> > stack;
                stack.push_back(std::make_pair(i, j));
                while (!stack.empty()) {
                    int x = stack.back().first;
                    int y = stack.back().second;
                    stack.pop_back();

                    if (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y] && map[x][y] == mineral) {
                        visited[x][y] = true;
                        mineralOccurrences[mineral]++;
                        stack.push_back(std::make_pair(x - 1, y));  // Check north
                        stack.push_back(std::make_pair(x + 1, y));  // Check south
                        stack.push_back(std::make_pair(x, y - 1));  // Check west
                        stack.push_back(std::make_pair(x, y + 1));  // Check east
                    }
                }
            }
        }
    }

    // Print the results
    if (depositCount == 0) {
        std::cout << mapNumber << "(" << lineNumber << "): no deposits ";
    } else {
        std::cout << mapNumber << "(" << lineNumber << "): deposits=" << depositCount << " ";
    }

    std::map<char, int>::const_iterator it;
    for (it = mineralOccurrences.begin(); it != mineralOccurrences.end(); ++it) {
        const char mineral = it->first;
        const int count = it->second;
        std::cout << mineral << "s=" << count << " ";
    }
    std::cout << std::endl;
}

int main() {
    int mapNumber = 1,  lineNumber = 1;

    // Open the input file
    std::ifstream inputFile("hw3in.txt");
    if (!inputFile) {
        std::cerr << "Error while opening the file" << std::endl;
        return 1;
    }

    // Read each map from the input file and count the deposits and mineral occurrences
    while (true) {
        int numLines;
        if (!(inputFile >> numLines)) {
            // Break the loop if the input operation fails or there are no more lines in the file
            break;
        }
        inputFile.ignore();  // Ignore the newline character after reading the number of lines
				
        if (numLines == 0) {
            // If there are no lines in the map, print a message and continue to the next iteration of the loop
            std::cout << mapNumber << "(" << lineNumber << "): no deposits " << std::endl;
            lineNumber++;  
            mapNumber++;
            continue;
        }

        // Read the lines of the map and count the deposits and mineral occurrences
        std::vector<std::string> currentMap;
        std::string line;
        for (int i = 0; i < numLines; i++) {
            std::getline(inputFile, line);
            currentMap.push_back(line);
        }

        countDeposits(currentMap, mapNumber, lineNumber);
        lineNumber = lineNumber + numLines + 1;

        mapNumber++;
	}

    // Close the input file
    inputFile.close();

    return 0;
}
