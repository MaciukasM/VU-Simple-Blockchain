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
    public:
        Block() {}
        Block(string pHash, string mHash, int nonce) 
        { 
            this->pHash = pHash; 
            this->mHash = mHash;
            this->nonce = nonce;
            timestamp = time(0);
        }

        ~Block () {}

        string getPrevHash() const { return pHash; }
        string getHash() const { return bHash; }
        string getMerkleHash() const { return mHash; }
        int getNonce() const { return nonce; }
        int getTimestamp() const { return timestamp; }
};

#endif