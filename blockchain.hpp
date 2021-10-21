#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Block
{
    private:
        string pHash; //praeito bloko hashas
        string bHash; //pacio blocko hashas
        string mHash; //merkle tree hashas
        time_t timestamp;
        int nonce = 0;
        string difficulty;
        string version = "v0.1";
    public:
        Block() {}
        Block(string pHash, string mHash) 
        { 
            this->pHash = pHash; 
            this->mHash = mHash;
            
            timestamp = time(0);
        }
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
        time_t getTimestamp() const { return timestamp; }
        string getVersion() const { return version; }
        string getDifficulty() const { return difficulty; }

        void setHash(string bHash) { this->bHash = bHash; }
        void setNonce(int nonce) { this->nonce = nonce; }
        void setDifficulty(string difficulty) { this->difficulty = difficulty; }
        void setPrevHash(string pHash) { this->pHash = pHash; }
        void setMerkleHash(string mHash) { this->mHash = mHash; }
};

class BlockInfo //cia bus saugoma informacija dar neisminintam blokui, kad butu paprasciau padaryti 5 minerius
{
    private:
        vector<Transaction> transactionList;
        string merkle;
    public:
        BlockInfo() {}

        ~BlockInfo() {}

        vector<Transaction> getTransactionList() const { return transactionList;}
        string getMerkle() const { return merkle; }

        void setTransactionList(vector<Transaction> transactionList) { this->transactionList = transactionList; }
        void setMerkle(string merkle) { this->merkle = merkle; }
}; 

void BlockMining(Block &b, bool &RastasHashas);
void Blockchain(bool mineriai = false);

#endif