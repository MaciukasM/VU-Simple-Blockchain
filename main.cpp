#include "user.hpp"
#include "transaction.hpp"

int main()
{
    vector<User> vartotojai;
    vector<Transaction> transactionPool;

    VartotojuGeneravimas(vartotojai);
    TransakcijuGeneravimas(vartotojai, transactionPool);

    /* for (int i = 0; i<transactionPool.size(); i++)
    {
        cout<<transactionPool[i].getId()<<" "<<transactionPool[i].getSiuntejoPk()<<" "<<transactionPool[i].getGavejoPk()<<" "<<transactionPool[i].getVal()<<" "<<i<<endl;
    } */

    
}