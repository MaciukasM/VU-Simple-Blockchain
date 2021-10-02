#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class User {
  private:
    string vardas;
    string pk;
    double val;
  public:
    User () {}

    void setVardas(string vardas) { this->vardas = vardas; }
    string getVardas() const { return vardas; }

    void setPk(string pk) { this->pk = pk; }
    string getPk() const { return pk; }

    void setVal(double valiuta) { this->val = valiuta; }
    double getVal() const { return val; }
};

void VartotojuGeneravimas(vector<User> &vartotojai);

#endif