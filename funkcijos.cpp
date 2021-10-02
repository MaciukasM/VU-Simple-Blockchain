#include "user.hpp"
#include "Hashas/hash.hpp"

void VartotojuGeneravimas(vector<User> &vartotojai)
{
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(100,1000000);

    for(int i = 0; i<1000; i++)
    {
        User u;

        u.setVardas("Vardas"+to_string(i));
        u.setVal(distribution(generator));
        u.setPk(DuomenuHashinimas(u.getVardas()+to_string(u.getVal()))); //laikinas private key generavimo sprendimas

        vartotojai.push_back(u);
    }
}