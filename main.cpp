#include <iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
#include<math.h>
#include <unordered_map>


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;


class Solution{
private:
    vector<long long> timestamps;    // all the timestamps
    vector<string> symbol;           // all the symbol
    vector<int> quality;             // all the quality
    vector<int> prices;              // all the prices
public:
    void print(){
        for(int i = 0; i < quality.size(); i++) cout << quality[i] << endl;
    }
    Solution(){
        ifstream inFile("input.csv", ios::in);
        string lineStr;
        vector<vector<string>> strArray;
        while (getline(inFile, lineStr)) {
            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;
            int i = 0;
            while (getline(ss, str, ',')) {
                //  use i % 4 to decide which item of four is.
                string temp = str;
                if (i % 4 == 0) {
                    long long llNum = strtoll(temp.c_str(), NULL, 10);
                    timestamps.push_back(llNum);
                } else if (i % 4 == 1) {
                    symbol.push_back(temp);
                } else if (i % 4 == 2) {
                    int j = stoi(temp);
                    quality.push_back(j);
                } else {
                    int j = stoi(temp);
                    prices.push_back(j);
                }
                i++;
            }
        }
    }
    void process() {
        map<string, vector<int>> mymap;
        mymap.clear();
        unsigned int num = timestamps.size();
        // use a sorted map.
        for (int i = 0; i < num; i++) {
            if (!mymap.count(symbol[i])) {
                vector<int> temp;
                mymap[symbol[i]] = temp;
            }
            mymap[symbol[i]].push_back(i);
        }

        ofstream outFile;
        outFile.open("output.csv", ios::out);
        for (auto [key, val]: mymap) {
            string symbol = key;
            long long MaxTimeGap = 0;
            int Volume = 0, WeightedAveragePrice = 0, MaxPrice = 0, sum = 0;
            for (int i = 0; i < val.size(); i++) {
                Volume += quality[val[i]];
                MaxPrice = max(prices[val[i]], MaxPrice);
                sum += quality[val[i]] * prices[val[i]];
                if (i > 0) {
                    MaxTimeGap = max(MaxTimeGap, (timestamps[val[i]] - timestamps[val[i - 1]]));
                }
            }
            WeightedAveragePrice = sum / Volume;
            // output file
            outFile << symbol << "," << MaxTimeGap << "," << Volume << "," <<
                    WeightedAveragePrice << "," << MaxPrice << endl;
        }
        outFile.close();
    }
};

// main function£¬the input file is 'input.csv'£¬and the output is 'output.csv'
// The total amount of the time for solving this problem is 110 minutes.

int main(int argc, char **argv){
    Solution* s = new Solution();
    s->process();
    // s->print();
    s->process();
    return 0;

}
