//
//  main.cpp
//  CCC-S1
//
//  Created by Leyland Fryer-Davis on 2020-02-12.
//  Copyright © 2020 Leyland Fryer-Davis. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool comparison(const pair<int,int> &a,const pair<int,int> &b){
    return a.first < b.first;
}

int main()
{
    int num;
    cin >> num;

    vector<pair<int, int> > positions;
    
    for (int i=0; i < num; i++)
    {
        int T, X;
        cin >> T;
        cin >> X;
        pair<int, int> position;
        position.first = T;
        position.second = X;
        positions.push_back(position);
    }
    
    sort(positions.begin(), positions.end(), comparison);

    double max_speed = 0;
    for (int i = 0; i < num - 1; i++)
    {
        int del_time = positions[i].first - positions[i+1].first;
        int del_x = positions[i].second - positions[i+1].second;
        double speed = (double)(del_x)/ (double) del_time;
        if (speed < 0) speed = -speed;
        
        if (speed > max_speed)
            max_speed = speed;
    }
    
    cout << max_speed << endl;
    
    return 0;
}
