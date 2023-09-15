#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>  // For numeric_limits
using namespace std;

struct Point {
    double x;
    double y;
};

class ShapeAnalyzer {
private:
    vector<Point> points;

public:
    void readFromFile(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        points.clear();  // Clear existing points when reading from a new file.
        string line;
        while (getline(file, line)) {
            if (line == "PTS") {
                readPoints(file);
            } else if (line == "CON") {
                // You can implement reading connections here if needed.
            }
        }

        file.close();
    }

    void readPoints(ifstream& file) {
        points.clear();
        string line;
        while (getline(file, line) && !line.empty()) {
            istringstream iss(line);
            Point point;
            iss >> point.x >> point.y;
            points.push_back(point);
        }
    }

    double calculateArea() {
        int n = points.size();
        double area = 0.0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (points[i].x * points[j].y - points[j].x * points[i].y);
        }
        area = abs(area) / 2.0;
        return area;
    }

    int findPointToRemove() {
        int n = points.size();
        double maxArea = -numeric_limits<double>::infinity();
        int pointToRemove = -1;

        for (int i = 0; i < n; i++) {
            vector<Point> tempPoints = points;
            tempPoints.erase(tempPoints.begin() + i);
            ShapeAnalyzer tempAnalyzer;
            tempAnalyzer.points = tempPoints;
            double area = tempAnalyzer.calculateArea();

            if (area > maxArea) {
                maxArea = area;
                pointToRemove = i;
            }
        }

        return pointToRemove;
    }

    Point findEquidistantPoint() {
        Point equidistantPoint = {0.0, 0.0};
        int n = points.size();

        for (int i = 0; i < n; i++) {
            equidistantPoint.x += points[i].x;
            equidistantPoint.y += points[i].y;
        }

        equidistantPoint.x /= n;
        equidistantPoint.y /= n;

        return equidistantPoint;
    }
};

int main() {
    ShapeAnalyzer analyzer;
    analyzer.readFromFile("data.txt");

    double largestArea = analyzer.calculateArea();
    cout << "Largest Area: " << largestArea << endl;

    int pointToRemove = analyzer.findPointToRemove();
    cout << "Point to Remove for Largest Area: " << pointToRemove << endl;

    Point equidistantPoint = analyzer.findEquidistantPoint();
    cout << "Equidistant Point: (" << equidistantPoint.x << ", " << equidistantPoint.y << ")" << endl;

    return 0;
}
