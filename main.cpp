#include "user.hpp"
#include "transaction.hpp"
#include "blockchain.hpp"

int main()
{
    int ats = 0;
    do
    {
        cout<<"\n1 - Blockchain'as su 1 miner'iu (v0.1)"<<endl;
        cout<<"2 - Blockchain'as su 5 miner'iais (v0.2)\n"<<endl;
        cout<<"Iveskite savo pasirinkima: ";
        cin>>ats;
        cout<<"\n\n-------------------------------------------\n"<<endl;
    } while (ats != 1 && ats != 2);

    if(ats == 1) Blockchain();
    if(ats == 2) Blockchain();
    
    
}