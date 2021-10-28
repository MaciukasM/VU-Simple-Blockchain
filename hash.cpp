#include "hash.hpp"

//funkcija paimta is https://github.com/MantasM2001/VU-hash-function/blob/main/funkcijos.cpp

string DuomenuHashinimas(string duomenys)
{
    string hash; // cia saugojamas hashas
    unsigned int temp = 12345; //kintamasis, kuriame laikomas skaicius, kuri vis keisime dauginant is ivairiu skaiciu (is pradziu sudauginsime su simboliu ascii vertemis ir pan.)
    int ascii = 0; //skaicius gautas is 'temp', kuri naudosim grazinti kokia nors ascii reiksme i hasha

    unsigned int sum = 0; //ascii reiksmiu suma (testavimui)
    //int s = 10000;

    for (int i = 0; i < duomenys.length(); i++) //input'as keicia pati skaiciu
    {
        sum += int(duomenys[i]); //(testavimui)
        temp = (temp * (int(duomenys[i]) + 2) * 2) + i + sum;
        temp << 2;
        temp = temp * temp * temp;

        //if(i == 1022 || i == 1023 || i == 1024 || i == 1025 || i == 1062 || i == 1063) cout<<"i: "<<i<<" "<<temp<<" "<<int(duomenys[i])+2<<endl;
    }

    //cout<<"s: "<<s<<endl; //(testavimui)

    string paverstasSkaicius; //vertimui skaiciu i string
    char simbolis; //char'as kuris eis i hasha (gaunamas is 'ascii' reiksmes)

    //hash'o sudarymas
    for (int i = 0; i < 64; i++)
    {
        temp = temp * M_PI;
        paverstasSkaicius = to_string(temp);
        ascii = (paverstasSkaicius[1] * paverstasSkaicius[3] + paverstasSkaicius[4] * paverstasSkaicius.back() + paverstasSkaicius[2] * i + temp / 2) % 16 + 48; //gaunam ascii reiksmes 48-63
        //if(i==0) cout<<"a: "<<temp<<endl; //testavimui
        if (ascii > 57) ascii += 39; //kad gauti raides a-f
        simbolis = ascii;
        hash += simbolis;
    }
    return hash;
}