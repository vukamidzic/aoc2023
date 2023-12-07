#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

typedef enum CombType {
    FIVEKIND,
    FOURKIND,
    FULLHOUSE,
    THREEKIND,
    TWOPAIR,
    ONEPAIR,
    HIGHCARD
} CombType;

typedef std::pair<std::vector<int>, std::pair<CombType, int>> Card;

int getCardValue(char c) {
    switch (c) {
        case 'A' : {
            return 14;
        }
        case 'K' : {
            return 13;
        }
        case 'Q' : {
            return 12;
        }
        case 'J' : {
            return 11;
        }
        case 'T' : {
            return 10;
        }
        default : {
            return c - '0';
        }
    }
}

bool cmpCards(std::vector<int> c1, std::vector<int> c2) {
    int i = 0;
    while (c1[i] == c2[i] && i < (int)c1.size()) i++;

    return c1[i] > c2[i];
}

CombType getCombType(std::string comb) {
    std::map<char, int> mp;

    for (char c : comb) mp[c]++;
    CombType result;

    switch (mp.size()) {
        case 1 : {
            result = FIVEKIND;
            break;
        }
        case 2 : {
            std::vector<int> values;
            std::transform(mp.begin(), mp.end(), std::back_inserter(values), [](auto &kv) {return kv.second;});
            switch (values[0] == 4 || values[1] == 4) {
                case true : {
                    result = FOURKIND;
                    break;
                }
                case false : {
                    result = FULLHOUSE;
                    break;
                }
            }
            break; 
        }
        case 3 : {
            std::vector<int> values;
            std::transform(mp.begin(), mp.end(), std::back_inserter(values), [](auto &kv) {return kv.second;});
            switch (values[0] == 3 || values[1] == 3 || values[2] == 3) {
                case true : {
                    result = THREEKIND;
                    break;
                }
                case false : {
                    result = TWOPAIR;
                    break;
                }
            } 
            break;
        }
        case 4 : {
            result = ONEPAIR;
            break;
        }
        case 5 : {
            result = HIGHCARD;
            break;
        }
    }

    return result;
}

Card splitStr(std::string line) {
    int n = line.length();
    int pos = line.find(' ');
    std::string cards = line.substr(0, pos);
    Card result = {{}, {getCombType(cards), std::stoi(line.substr(pos+1, n-pos+1))}};

    for (char c : cards) {
        result.first.push_back(getCardValue(c));
    }

    return result;
}

int part1(std::string file_path) {
    std::ifstream input(file_path);
    std::string line;
    std::vector<Card> card_sets;

    while (std::getline(input, line)) {
        Card info = splitStr(line);
        card_sets.push_back(info);
    }

    std::sort(card_sets.begin(), card_sets.end(), [](auto& a, auto& b) {
        if (a.second.first == b.second.first)
            return cmpCards(b.first, a.first);
        else 
            return a.second.first >= b.second.first;
    });

    int rank = 1, sum = 0;
    for (Card cards : card_sets) {
        sum += rank * cards.second.second;
        rank++;
    }

    return sum;
}

int main(void) {
    std::cout << part1("input.txt") << std::endl;

    return 0;
}