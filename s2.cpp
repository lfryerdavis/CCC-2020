//
//  main.cpp
//  CCC-S2
//
//  Created by Leyland Fryer-Davis on 2020-02-12.
//  Copyright © 2020 Leyland Fryer-Davis. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> ivec;
typedef vector<bool> bvec;
typedef vector<ivec> imatrix;
typedef vector<bvec> bmatrix;

ostream &operator<<(ostream &stream, ivec &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        stream << obj[i] << " ";
    }
    return stream;
}

ostream &operator<<(ostream &stream, imatrix &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        stream << i << " [ " << obj[i] << "]" << endl;
    }
    return stream;
}

ostream &operator<<(ostream &stream, bvec &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        if (obj[i])
            stream << "T ";
        else
            stream << "F ";

    }
    return stream;
}

ivec values;
bvec visited;
imatrix locationsByValue;
const int maxValue = 1000000;
//const int maxValue = 15;

int M, N;

bool findSolution(int currLoc)
{
    if (currLoc == 0) // made it to the entrance! success!
        return true;
    if (visited[currLoc]) // already been here. can't visit again
        return false;
    
    visited[currLoc] = true;
    int row = currLoc / N + 1;
    int col = currLoc % N + 1;
    int newVal = row*col;
    
//    cout << "currLoc = " << currLoc << " row = " << row << " col = " << col << " newVal = " << newVal << endl;

    // find candidates
    ivec candidates = locationsByValue[newVal];
    for (int i = 0; i < candidates.size(); i++)
    {
        if (findSolution(candidates[i]))
            return true;
    }
    
    return false;
}

int main()
{
    cin >> M;
    cin >> N;
    
    int maxSize = M*N;
    for (int i = 0; i <= maxValue; i++)
    {
        ivec row;
        locationsByValue.push_back(row);
    }
    
    for (int i = 0; i < maxSize; i++)
    {
        int value;
        cin >> value;
        values.push_back(value);
        visited.push_back(false);
        locationsByValue[value].push_back(i);
    }

//    cout << visited << endl;
//    cout << values << endl;
//    cout << locationsByValue << endl;
//
    // start at end and get candidates then recurse.
    if (findSolution(M*N-1))
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    return 0;
}


