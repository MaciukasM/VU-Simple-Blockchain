#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include "user.hpp"

using namespace std;

class Transaction
{
    private:
        string id;
        string siuntejoPk;
        string gavejoPk;
        double val;
    public:
        Transaction() {}
        ~Transaction() {}

        void setSiuntejoPk(string siuntejoPk) { this->siuntejoPk = siuntejoPk; }
        string getSiuntejoPk() const { return siuntejoPk; }

        void setGavejoPk(string gavejoPk) { this->gavejoPk = gavejoPk; }
        string getGavejoPk() const { return gavejoPk; }

        void setVal(double valiuta) { this->val = valiuta; }
        double getVal() const { return val; }

        void setId(string id) { this->id = id; }
        string getId() const { return id; }
};

void TransakcijuGeneravimas(vector<User> vartotojai, vector<Transaction> &transactionPool);
void TransakcijuParinkimas(vector<Transaction> transactionPool, vector<Transaction> &transactionList, int n);
string MerkleGeneravimas(vector<Transaction> transactionList);

#endif