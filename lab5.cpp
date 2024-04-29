#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <hash_set>
#include <fstream>
using namespace std;
class Bank {
    string name;
    double summ;
    string type;
    double bet;
public:
    Bank(string name, double summ, string type, double bet) : name(name), summ(summ), type(type), bet(bet) {}
    friend ostream& operator<<(ostream& os, const Bank& dt) {
        os << "Name: " << dt.name << ", Sum: " << dt.summ << ", Type: " << dt.type << ", Bet: " << dt.bet;
        return os;
    }
    bool operator<(const Bank& o) const {
        return summ < o.summ;
    }
    bool operator==(const Bank& o) const {
        return name == o.name && summ == o.summ && type == o.type && bet == o.bet;
    }
    struct MyHash {
        size_t operator()(const Bank& b) const noexcept {
            hash <string> hasher;
            size_t hn = hasher(b.name);
            size_t hs = hasher(to_string(b.summ));
            size_t ht = hasher(b.type);
            size_t hb = hasher(to_string(b.bet));
            return hn ^ hs ^ ht ^ hb;
        }
    };
    Bank& operator=(const Bank& o) {
        if (this != &o) {
            name = o.name;
            summ = o.summ;
            type = o.type;
            bet = o.bet;
        }
        return *this;
    }
};
int main()
{
    vector <Bank> bank;
    set <Bank> set_bank;
    unordered_set<Bank, Bank::MyHash> unordered_set_bank;
    ifstream infile("input.txt");
    string name, type;
    double summ, bet;
    while (infile >> name >> summ >> type >> bet) {
        Bank b(name, summ, type, bet);
        bank.emplace_back(name, summ, type, bet);
        set_bank.insert(b);
        unordered_set_bank.insert(b);
    }
    sort(bank.begin(), bank.end());
    for (const auto& bank : bank) {
        cout << bank << endl;
    }
    deque <Bank> c_bank;
    copy(bank.begin(), bank.end(), back_inserter(c_bank));
    ofstream outfile("output.txt");
    for (const auto& bank : bank) {
        outfile << bank << endl;
    };
    for (const auto& bank : c_bank) {
        outfile << bank << endl;
    };
    for (const auto& bank : set_bank) {
        outfile << bank << endl;
    };
    for (const auto& bank : unordered_set_bank) {
        outfile << bank << endl;
    }
}
