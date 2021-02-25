#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <complex>
#include <string>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <assert.h>
#include <stdio.h>

using namespace std;

void Yahia74() {
    freopen("f.txt", "r", stdin);
    freopen("6.in", "w", stdout);
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 1e5 + 74, OO = 0x3f3f3f3f;

class Car;

class Street;

class Intersection;

class Car {
public:
    int id;
    vector<string> path;

    Car() {

    }

    Car(int id_, vector<string> path_) {
        id = id_;
        path = path_;
    }

};


class Intersection {
public:
    int id;
    bool signColor;
    vector<string> inComing;

    Intersection() {

    }

    Intersection(int id_, bool signColor_) {
        id = id_;
        signColor = signColor_;
    }
};

class Street {
public:
    Intersection start;
    Intersection end;
    string name;
    int length;
    int priority;

    Street() {

    }

    Street(Intersection start_, Intersection end_, string name_, int length_) {
        start.id = start_.id;
        end.id = end_.id;
        name = name_;
        length = length_;
    }
};


int duration;
int numOfIntersections;
int numOfStreets;
int numOfCars;
int bonusPoints;


vector<Street> streets;
vector<Car> cars;
vector<Intersection> intersections;
map<string, int> mp;


int norm(double val, double max, double min) {
    return (double) (val - min) / (max - min) * 10 + 1;
}


int main() {
    Yahia74();
    cin >> duration >> numOfIntersections >> numOfStreets >> numOfCars >> bonusPoints;
    intersections.resize(numOfIntersections);
    streets.resize(numOfStreets);
    cars.resize(numOfCars);
    for (int i = 0; i < numOfIntersections; i++) {
        intersections[i].id = i;
    }
    for (int i = 0; i < numOfStreets; i++) {
        int st, ed;
        string name;
        int length;
        cin >> st >> ed >> name >> length;
        Street street(intersections[st], intersections[ed], name, length);
        streets[i] = street;
        intersections[ed].inComing.push_back(name);
    }

    for (int i = 0; i < numOfCars; i++) {
        int numOfStreets;
        cin >> numOfStreets;
        vector<string> carPath;
        for (int j = 0; j < numOfStreets; j++) {
            string name;
            cin >> name;
            carPath.push_back(name);
            mp[name]++;
        }
        Car car(i, carPath);
        cars[i] = car;
    }
    for (int i = 0; i < numOfStreets; i++) {
        streets[i].priority = mp[streets[i].name];
    }
//    sort(streets.begin(), streets.end(), [&](Street p1, Street p2) {
//        return p1.priority < p2.priority;
//    });
    int mx = 0, mn = 0;
    for (int i = 0; i < numOfStreets; i++) {
        mx = max(mx, streets[i].priority);
        mn = min(mn, streets[i].priority);
    }
    for (int i = 0; i < numOfStreets; i++) {
        streets[i].priority = norm(streets[i].priority, mx, mn);
        mp[streets[i].name] = streets[i].priority;
    }
    cout << numOfIntersections << endl;
    for (int i = 0; i < numOfIntersections; i++) {
        cout << i << endl;
        cout << intersections[i].inComing.size() << endl;
        for (int j = 0; j < intersections[i].inComing.size(); j++) {
            string inStreet = intersections[i].inComing[j];
            cout << inStreet << ' ' << mp[inStreet] + 1 << endl;
        }
    }
}