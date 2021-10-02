#include "user.hpp"

int main()
{
    vector<User> vartotojai;
    VartotojuGeneravimas(vartotojai);

    cout<<vartotojai[0].getVardas()<<" "<<vartotojai[0].getPk()<<" "<<vartotojai[0].getVal()<<endl;
}