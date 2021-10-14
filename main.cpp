#include "user.hpp"
#include "transaction.hpp"
#include "blockchain.hpp"

int main()
{
    vector<User> vartotojai;
    vector<Transaction> transactionPool;
    vector<Transaction> transactionList;
    vector<Block> blockchain;

    VartotojuGeneravimas(vartotojai);
    TransakcijuGeneravimas(vartotojai, transactionPool);

    /* for (int i = 0; i<transactionPool.size(); i++)
    {
        cout<<transactionPool[i].getId()<<" "<<transactionPool[i].getSiuntejoPk()<<" "<<transactionPool[i].getGavejoPk()<<" "<<transactionPool[i].getVal()<<" "<<i<<endl;
    } */

    TransakcijuParinkimas(transactionPool, transactionList, 128); //3 kintamasis nurodo kiek transakciju bus bloke

    /* for (int i = 0; i<100; i++)
    {
        cout<<transactionList[i].getId()<<endl;
    } */

    string merkle = MerkleGeneravimas(transactionList);

    Block b("00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048", merkle);

    BlockMining(b);

    cout<<"Mininimas baigtas.\n"<<endl;
    cout<<"Hashas: "<<b.getHash()<<endl;
    cout<<"Timestamp: "<<b.getTimestamp()<<endl;
    cout<<"Nonce: "<<b.getNonce()<<endl;
    cout<<"Merkle:"<<b.getMerkleHash()<<endl;

    //cout<<"dydis: "<<transactionPool.size()<<endl;
    TransakcijuIvykdymas(transactionList, transactionPool, vartotojai);
    //cout<<"dydis: "<<transactionPool.size()<<endl;
    
    blockchain.push_back(b);
}