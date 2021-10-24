#include "user.hpp"
#include "hash.hpp"
#include "transaction.hpp"
#include "blockchain.hpp"
#include "laikas.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void VartotojuGeneravimas(vector<User>& vartotojai)
{
    int n = 1000; //kiek vartotoju bus
    vartotojai.reserve(n);

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(100, 1000000);

    for (int i = 0; i < n; i++)
    {
        User u;

        u.setVardas("Vardas" + to_string(i));
        u.setVal(distribution(generator));
        u.setPk(DuomenuHashinimas(u.getVardas() + to_string(u.getVal()) + to_string(distribution(generator)))); //laikinas private key generavimo sprendimas

        vartotojai.push_back(u);
    }
}

void TransakcijuGeneravimas(vector<User> vartotojai, vector<Transaction>& transactionPool)
{
    int n = 10000;
    transactionPool.reserve(n);

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(0, 1000 - 1);

    int u1; //user 1 (siuntejas)
    int u2; //user 2 (gavejas)

    while (transactionPool.size() != transactionPool.capacity())
    {
        Transaction t;

        u1 = distribution(generator);
        u2 = distribution(generator);

        if (u1 != u2)
        {
            uniform_real_distribution<float> distributionF(1, (vartotojai[u1].getVal() / 5)); //kol kas vartotojai atsakingi ir neisleidzia daugiau nei penktadalio valiutos :)

            t.setVal(distributionF(generator));
            t.setSiuntejoPk(vartotojai[u1].getPk());
            t.setGavejoPk(vartotojai[u2].getPk());

            t.setId(DuomenuHashinimas(to_string(t.getVal()) + t.getSiuntejoPk() + t.getGavejoPk()));

            transactionPool.push_back(t);
        }
    }
}

void TransakcijuParinkimas(vector<Transaction>& transactionPool, vector<Transaction>& transactionList, int n, vector<User> vartotojai)
{
    random_device device;
    mt19937 generator(device());


    vector<User>::iterator itUser;
    string pk;

    for (int i = 0; i < n; i++) // n nurodo kiek transakciju bus paimta
    {
        if (transactionPool.size() == transactionList.size()) break;
        uniform_int_distribution<int> distribution(0, transactionPool.size() - 1);
        int sk = distribution(generator);

        pk = transactionPool[sk].getGavejoPk();
        itUser = find_if(vartotojai.begin(), vartotojai.end(), [&pk](const User& u) { return u.getPk() == pk; });
        auto index = distance(vartotojai.begin(), itUser);

        if (vartotojai[index].getVal() < transactionPool[sk].getVal() || transactionPool[sk].getId() != DuomenuHashinimas(to_string(transactionPool[sk].getVal()) + transactionPool[sk].getSiuntejoPk() + transactionPool[sk].getGavejoPk()))
        {
            transactionPool.erase(transactionPool.begin() + sk);
            --i;
        }
        else transactionList.push_back(transactionPool[sk]);

    }
}

string MerkleGeneravimas(vector<Transaction> transactionList)
{
    vector<string> merkle;
    vector<string> merkle1; //kopija

    // pirma patikrinam ar is viso daugiau nei 1 transactionas yra
    if (transactionList.size() == 0) return DuomenuHashinimas("");
    if (transactionList.size() == 1) return DuomenuHashinimas(transactionList[0].getId());

    for (int i = 0; i < transactionList.size(); i++)
    {
        merkle.push_back(transactionList[i].getId());
    }

    merkle1 = merkle;


    while (merkle1.size() > 1)
    {
        merkle.clear();

        if (merkle1.size() % 2 != 0) merkle1.push_back(merkle1.back());

        for (int i = 0; i < merkle1.size(); i = i + 2) merkle.push_back(DuomenuHashinimas(merkle1[i] + merkle1[i + 1]));

        merkle1 = merkle;
    }

    return merkle1[0];
}

bool BlockMining(Block& b, double n)
{
    int nonce;

    string bHash;

    string difficulty = "2-0"; //cia galim pakeisti difficulty - pirmas char'as nurodo kiek 0 turi buti is pradziu hash'e

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(1, 100000000);

    if (n == 0)
    {
        while (true)
        {
            nonce = distribution(generator);

            //Block b(pHash, merkle, nonce, difficulty);

            bHash = DuomenuHashinimas(b.getPrevHash() + b.getMerkleHash() + to_string(b.getTimestamp()) + to_string(nonce) + b.getVersion() + difficulty);

            if (bHash.find_first_not_of("0") > (difficulty[0] - 48 - 1))
            {
                b.setHash(bHash);
                b.setNonce(nonce);
                b.setDifficulty(difficulty);
                return true;
            }
        }
    }
    else
    {
        LaikoMatavimas l;
        l.reset();

        while (l.elapsed() < n)
        {
            nonce = distribution(generator);

            bHash = DuomenuHashinimas(b.getPrevHash() + b.getMerkleHash() + to_string(b.getTimestamp()) + to_string(nonce) + b.getVersion() + difficulty);

            if (bHash.find_first_not_of("0") > (difficulty[0] - 48 - 1))
            {
                b.setHash(bHash);
                b.setNonce(nonce);
                b.setDifficulty(difficulty);
                return true;
            }
        }
        return false;
    }

}

void TransakcijuIvykdymas(vector<Transaction> transactionList, vector<Transaction>& transactionPool, vector<User>& vartotojai)
{
    vector<User>::iterator itUser;
    vector<Transaction>::iterator itTransaction;
    string pk;

    //cout<<"a:"<<transactionList.size()<<endl;
    //cout<<"pool:"<<transactionPool.size()<<endl;

    for (int i = 0; i < transactionList.size(); i++)
    {
        pk = transactionList[i].getGavejoPk();
        itUser = find_if(vartotojai.begin(), vartotojai.end(), [&pk](const User& u) { return u.getPk() == pk; });
        auto index = distance(vartotojai.begin(), itUser);
        vartotojai[index].setVal(vartotojai[index].getVal() + transactionList[i].getVal());

        pk = transactionList[i].getSiuntejoPk();
        itUser = find_if(vartotojai.begin(), vartotojai.end(), [&pk](const User& u) { return u.getPk() == pk; });
        index = distance(vartotojai.begin(), itUser);
        vartotojai[index].setVal(vartotojai[index].getVal() - transactionList[i].getVal());


        pk = transactionList[i].getId();
        itTransaction = find_if(transactionPool.begin(), transactionPool.end(), [&pk](const Transaction& t) { return t.getId() == pk; });
        transactionPool.erase(itTransaction);
        //cout<<pk<<" "<<index<<" "<<vartotojai[index].getPk()<<endl;
    }
    transactionList.clear();
}

//pagrindine funkcija
void Blockchain(bool mineriai)
{
    vector<User> vartotojai;
    vector<Transaction> transactionPool;
    vector<Transaction> transactionList;
    BlockchainClass bc;
    bool RastasHashas = false;

    double reward = 5; //pavyzdiniam atvejui

    string pHash = " ";

    LaikoMatavimas l;
    double laikas = 0;

    VartotojuGeneravimas(vartotojai);
    TransakcijuGeneravimas(vartotojai, transactionPool);

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(0, 999);

    /* for (int i = 0; i<transactionPool.size(); i++)
    {
        cout<<transactionPool[i].getId()<<" "<<transactionPool[i].getSiuntejoPk()<<" "<<transactionPool[i].getGavejoPk()<<" "<<transactionPool[i].getVal()<<" "<<i<<endl;
    } */

    //Block b;
    string merkle;

    bool ArIsminino = false; //safety check'as

    while (transactionPool.size() > 0)
    {
        Block b;

        if (pHash == " ") pHash = "00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048";

        if (!mineriai)
        {
            TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai); //3 kintamasis nurodo kiek transakciju bus bloke

            /* for (int i = 0; i<100; i++)
            {
                cout<<transactionList[i].getId()<<endl;
            } */

            merkle = MerkleGeneravimas(transactionList);

            Block b0(pHash, merkle);
            //b.setPrevHash(pHash);
            //b.setMerkleHash(merkle);
            b = b0;

            l.reset();
            BlockMining(b);
        }
        else
        {
            ArIsminino = false;
            cout << "\nPradedamas mininimas...\n" << endl;

            while (!ArIsminino)
            {
                TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai);
                merkle = MerkleGeneravimas(transactionList);
                BlockInfo a1;
                a1.setMerkle(merkle);
                a1.setTransactionList(transactionList);
                a1.setMineris(distribution(generator));
                Block b1(pHash, a1.getMerkle());

                TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai);
                merkle = MerkleGeneravimas(transactionList);
                BlockInfo a2;
                a2.setMerkle(merkle);
                a2.setTransactionList(transactionList);
                a2.setMineris(distribution(generator));
                Block b2(pHash, a2.getMerkle());

                TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai);
                merkle = MerkleGeneravimas(transactionList);
                BlockInfo a3;
                a3.setMerkle(merkle);
                a3.setTransactionList(transactionList);
                a3.setMineris(distribution(generator));
                Block b3(pHash, a3.getMerkle());

                TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai);
                merkle = MerkleGeneravimas(transactionList);
                BlockInfo a4;
                a4.setMerkle(merkle);
                a4.setTransactionList(transactionList);
                a4.setMineris(distribution(generator));
                Block b4(pHash, a4.getMerkle());

                TransakcijuParinkimas(transactionPool, transactionList, 128, vartotojai);
                merkle = MerkleGeneravimas(transactionList);
                BlockInfo a5;
                a5.setMerkle(merkle);
                a5.setTransactionList(transactionList);
                a5.setMineris(distribution(generator));
                Block b5(pHash, a5.getMerkle());

                l.reset();
                #pragma omp parallel sections
                {
                    {if (BlockMining(b1, 6) && !ArIsminino)
                    {
                        b = b1;
                        cout << "Isminino 1 mineris!\n" << endl;
                        ArIsminino = true;
                        transactionList = a1.getTransactionList();
                        vartotojai[a1.getMineris()].setVal(vartotojai[a1.getMineris()].getVal() + reward);
                    }}
                    #pragma omp section
                    {if (BlockMining(b2, 6) && !ArIsminino)
                    {
                        b = b2;
                        cout << "Isminino 2 mineris!\n" << endl;
                        ArIsminino = true;
                        transactionList = a2.getTransactionList();
                        vartotojai[a2.getMineris()].setVal(vartotojai[a2.getMineris()].getVal() + reward);
                    }}
                    #pragma omp section
                    {if (BlockMining(b3, 6) && !ArIsminino)
                    {
                        b = b3;
                        cout << "Isminino 3 mineris!\n" << endl;
                        ArIsminino = true;
                        transactionList = a3.getTransactionList();
                        vartotojai[a3.getMineris()].setVal(vartotojai[a3.getMineris()].getVal() + reward);
                    }}
                    #pragma omp section
                    {if (BlockMining(b4, 6) && !ArIsminino)
                    {
                        b = b4;
                        cout << "Isminino 4 mineris!\n" << endl;
                        ArIsminino = true;
                        transactionList = a4.getTransactionList();
                        vartotojai[a4.getMineris()].setVal(vartotojai[a4.getMineris()].getVal() + reward);
                    }}
                    #pragma omp section
                    {if (BlockMining(b5, 6) && !ArIsminino)
                    {
                        b = b5;
                        cout << "Isminino 5 mineris!\n" << endl;
                        ArIsminino = true;
                        transactionList = a5.getTransactionList();
                        vartotojai[a5.getMineris()].setVal(vartotojai[a5.getMineris()].getVal() + reward);
                    }}
                    
                }
                
            }
        }

        time_t t = b.getTimestamp();
        std::tm* now = std::localtime(&t);

        cout << "Bloko mininimas baigtas.\n" << endl;
        cout << "Mininimas uztruko: " << l.elapsed() << " s." << endl;
        laikas += l.elapsed();
        cout << "Difficulty: " << b.getDifficulty() << endl;
        cout << "Hashas: " << b.getHash() << endl;
        cout << "Timestamp: " << b.getTimestamp() << " (" << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << ")" << endl;
        cout << "Nonce: " << b.getNonce() << endl;
        cout << "Merkle: " << b.getMerkleHash() << endl;
        cout << "\n------------------------------------------------------" << endl;

        pHash = b.getHash();

        //cout<<"dydis: "<<transactionPool.size()<<endl;
        TransakcijuIvykdymas(transactionList, transactionPool, vartotojai);
        //cout<<"dar liko: "<<transactionPool.size()<<endl;

        transactionList.clear();
        bc.PridekBloka(b);
    }
    cout << "Visas laikas: " << laikas << endl;

}