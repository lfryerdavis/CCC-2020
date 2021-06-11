//
//  main.cpp
//  CCC-S3
//
//  Created by Leyland Fryer-Davis on 2020-02-18.
//  Copyright © 2020 Leyland Fryer-Davis. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>
#include <map>

using namespace std;

typedef vector<int> ivec;
typedef vector<pair<size_t, size_t> > pvec;
typedef set<string> sset;

string needle;
string haystack;
ivec needleReduced;
ivec currReduced;
pvec hashLocations;
sset uniques;

ostream &operator<<(ostream &stream, ivec &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        stream << obj[i] << " ";
    }
    return stream;
}

ostream &operator<<(ostream &stream, sset &obj)
{
    for (auto it=obj.begin(); it != obj.end(); ++it)
        stream << *it << " ";

    return stream;
}

bool comparison(const pair<size_t, size_t> &a, const pair<size_t, size_t> &b){
    return a.first < b.first;
}

void restartReduce(size_t start)
{
    size_t end = start + needle.size();
    for (auto i = 'a'; i <= 'z'; i++)
    {
        currReduced[i - 'a'] = 0;
    }
    
    for (size_t i = start; i < end; i++)
    {
        char value = haystack[i];
        size_t index = value - 'a';
        currReduced[index]++;
    }
}

void initReduced()
{
    for (auto i = 'a'; i <= 'z'; i++)
    {
        needleReduced.push_back(0);
        currReduced.push_back(0);
    }
    
    for (size_t i = 0; i < needle.size(); i++)
    {
        char value = needle[i];
        size_t index = value - 'a';
        needleReduced[index]++;
    }
    restartReduce(0);

//    cout << "needleReduced = " << needleReduced << endl;
//    cout << "currReduced = " << currReduced << endl;
}

bool isMatch()
{
    for (size_t i = 0; i < needleReduced.size(); i++)
    {
        if (needleReduced[i] != currReduced[i]) return false;
    }
    
    return true;
}

int main()
{
    getline(cin, needle);
    getline(cin, haystack);
//    needle = "abc"; haystack = "bcabcbabacbcbbcabac";
//    needle = "abc"; haystack = "bcabcba";
//    needle = "abc"; haystack = "abcabc";
//    needle = "abcd"; haystack = "abcdcbacbdbcadcbadbcadbc";
//    needle = "abcdefghijklmnopqrstuvwxyz"; haystack = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
//    needle = "abcdefghijklmnopqrstuvwxyz"; haystack = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba";
//    needle = "abcdefghijklmnopqrstuvwxyz"; haystack = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba";
//
//    cout << "needle = " << needle << " length = " << needle.size() << endl;
//    cout << "haystack = " << haystack << " length = " << haystack.size() << endl;

    if (needle.size() > haystack.size())
    {
        cout << "0" << endl;
        return 0;
    }

    initReduced();

    if (needle.size() == haystack.size())
    {
        if (isMatch())
            cout << "1" << endl;
        else
            cout << "0" << endl;
        return 0;
    }

    if (isMatch())
    {
        size_t hashStr = hash<string>{}(haystack.substr(0, needle.size()));
        pair<size_t, size_t> hashLoc = make_pair(hashStr, 0);
        hashLocations.push_back(hashLoc);
    }
    size_t num = haystack.size() - needle.size() + 1;

    for (size_t start = 1; start < num; start++)
    {
        // end goes one past the last position of the string
        size_t end = start + needle.size();
        currReduced[haystack[start - 1] - 'a']--;
        currReduced[haystack[end - 1] - 'a']++;
//        cout << " start = " << start << " end = " << end << " reduceCurr = " << currReduced << endl;
        if (isMatch())
        {
//            cout << " match: ";
            string permutationCandidate = haystack.substr(start, needle.size());
//            cout << "permutationCandidate = " << permutationCandidate << endl;
            // get hash of this string
            size_t hashStr = hash<string>{}(permutationCandidate);
            pair<size_t, size_t> hashLoc = make_pair(hashStr, start);
            hashLocations.push_back(hashLoc);
        }
    }

    // find number of unique permutations
    if (hashLocations.size() == 0)
    {
        cout << "0" << endl;
        return 0;
    }
    
    sort(hashLocations.begin(), hashLocations.end(), comparison);
    size_t count = 1;
    bool addingToSet = false;
    size_t prevCount = 0;
    for (size_t i = 1; i < hashLocations.size(); i++)
    {
        if (hashLocations[i].first != hashLocations[i-1].first)
        {
            count++;
            addingToSet = false;
            prevCount = 0;
        }
        else
        {
            if (!addingToSet)
            {
                uniques.clear();
                count -=1;
                string firstStr = haystack.substr(hashLocations[i-1].second, needle.size());
                string secondStr = haystack.substr(hashLocations[i].second, needle.size());
                uniques.insert(firstStr);
                uniques.insert(secondStr);
                prevCount = uniques.size();
                count += prevCount;
                addingToSet = true;
            }
            else
            {
                string firstStr = haystack.substr(hashLocations[i].second, needle.size());
                uniques.insert(firstStr);
                size_t newCount = uniques.size();
                size_t diff = newCount - prevCount;
                count += diff;
                prevCount = newCount;
            }
        }
    }
    cout << count << endl;

    return 0;
}
