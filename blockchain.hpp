#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <iostream>
#include <ctime>

using namespace std;

class Block
{
    private:
        string pHash; //praeito bloko hashas
        string bHash; //pacio blocko hashas
        string mHash; //merkle tree hashas
        int timestamp;
        int nonce = 0;
        string difficulty;
        string version = "v0.1";
    public:
        Block() {}
        Block(string pHash, string mHash, int nonce, string difficulty) 
        { 
            this->pHash = pHash; 
            this->mHash = mHash;
            
            timestamp = time(0);

            this->nonce = nonce;
            this->difficulty = difficulty;
        }

        ~Block () {}

        string getPrevHash() const { return pHash; }
        string getHash() const { return bHash; }
        string getMerkleHash() const { return mHash; }
        int getNonce() const { return nonce; }
        int getTimestamp() const { return timestamp; }
        string getVersion() const { return version; }
        string getDifficulty() const { return difficulty; }

        string setHash(string bHash) { this->bHash = bHash; }
};

string BlockMining(string merkle, string pHash = "00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048");

#endif