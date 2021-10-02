#include "user.hpp"
#include "Hashas/hash.hpp"

void VartotojuGeneravimas(vector<User> &vartotojai)
{
    for(int i = 0; i<1000; i++)
    {
        srand(time(NULL));

        User u;

        u.setVardas("Vardas"+to_string(i));
        u.setPk(DuomenuHashinimas(u.getVardas())); //laikinas private key generavimo sprendimas
        u.setVal(rand()%999900+100);

        vartotojai.push_back(u);
    }
}