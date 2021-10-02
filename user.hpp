#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

class User {
  private:
    string vardas;
    string pk;
    int val;
  public:
    User () {}

    void setVardas(string vardas) { this->vardas = vardas; }
    string getVardas() const { return vardas; }

    void setPk(string pk) { this->pk = pk; }
    string getPk() const { return pk; }

    void setVal(int valiuta) { this->val = valiuta; }
    int getVal() const { return val; }
};

void VartotojuGeneravimas(vector<User> &vartotojai);

#endif