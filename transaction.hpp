#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>

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

        void setSiuntejoPk(string siuntejoPk) { this->siuntejoPk = siuntejoPk; }
        string getSiuntejoPk() const { return siuntejoPk; }

        void setGavejoPk(string gavejoPk) { this->gavejoPk = gavejoPk; }
        string getGavejoPk() const { return gavejoPk; }

        void setVal(double valiuta) { this->val = valiuta; }
        double getVal() const { return val; }
};

#endif