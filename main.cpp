#include "user.hpp"
#include "transaction.hpp"

int main()
{
    vector<User> vartotojai;
    vector<Transaction> transactionPool;
    vector<Transaction> transactionList;

    VartotojuGeneravimas(vartotojai);
    TransakcijuGeneravimas(vartotojai, transactionPool);

    /* for (int i = 0; i<transactionPool.size(); i++)
    {
        cout<<transactionPool[i].getId()<<" "<<transactionPool[i].getSiuntejoPk()<<" "<<transactionPool[i].getGavejoPk()<<" "<<transactionPool[i].getVal()<<" "<<i<<endl;
    } */

    TransakcijuParinkimas(transactionPool, transactionList, 128); //3 kintamasis nurodo kiek transakciju bus bloke
    string merkle = MerkleGeneravimas(transactionList);

    /* for (int i = 0; i<100; i++)
    {
        cout<<transactionList[i].getId()<<endl;
    } */

    
}