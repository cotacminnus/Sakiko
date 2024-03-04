#include "include.h"

using namespace std;

Staff_S::Staff_S(mutex* lok): lock(lok){
    reseed();
    tousaki_loc = "../resources/tousaki.txt";
    unsei_loc = "../resources/unsei.txt";

    ifstream tou(tousaki_loc);
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    ifstream uns(unsei_loc);
    if(!uns.is_open()){
        cerr << "opening unsei file failed!" << endl;
    }
    uns.close();
}

Staff_S::Staff_S(mutex* lok, string tloc, string uloc): lock(lok), tousaki_loc(tloc), unsei_loc(uloc){
    reseed();
    ifstream tou(tousaki_loc);
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    ifstream uns(unsei_loc);
    if(!uns.is_open()){
        cerr << "opening unsei file failed!" << endl;
    }
    uns.close();
}

Staff_S::~Staff_S(){}

void Staff_S::reseed(){
    seed = rand();
    cout << "New seed: " << seed << endl;
}

pair<bool, string> Staff_S::add_tousaki(const dpp::snowflake& id){
    bool ret = tousaki(id.str());
    pair<bool, string> dis(ret, "");
    if(ret){
        dis.second = TOUSAKI_BENE;
        return dis;
    }
    else{
        dis.second = TOUSAKI_MALE;
        return dis;
    }
}
pair<bool, string> Staff_S::add_unsei(const dpp::snowflake& id){
    bool ret = unsei(id.str());
    pair<bool, string> dis(ret, "");
    if(!ret){
        dis.second = UNSEI_4;
        return dis;
    }
    else{
        lock->lock();
        switch(seed % 4){
        case 0:
            dis.second = UNSEI_0;
            break;
        case 1:
            dis.second = UNSEI_1;
            break;
        case 2:
            dis.second = UNSEI_2;
            break;
        default:
            dis.second = UNSEI_3;
            break;
        }
        lock->unlock();
        return dis;
    }
}

void Staff_S::clear_tousaki(){
    lock->lock();
    ofstream tou(tousaki_loc, ios::trunc);
    tou.close();
    reseed();
    lock->unlock();
}
void Staff_S::clear_unsei(){
    lock->lock();
    ofstream uns(unsei_loc, ios::trunc);
    uns.close();
    reseed();
    lock->unlock();
}

bool Staff_S::tousaki(string id){
    lock->lock();
    ifstream tou(tousaki_loc);
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
        lock->unlock();
        return false;
    }
    string lin;
    while(getline(tou, lin)){
        if(id == lin){
            tou.close();
            reseed();
            lock->unlock();
            return false;
        }
    }
    tou.close();
    reseed();

    ofstream out(tousaki_loc, ios::app);
    out << id << endl;
    out.close();

    lock->unlock();
    return true;
}
bool Staff_S::unsei(string id){
    lock->lock();
    ifstream uns(unsei_loc);
    if(!uns.is_open()){
        cerr << "opening unsei file failed!" << endl;
        lock->unlock();
        return false;
    }
    string lin;
    while(getline(uns, lin)){
        if(id == lin){
            uns.close();
            reseed();
            lock->unlock();
            return false;
        }
    }
    uns.close();
    reseed();

    ofstream out(unsei_loc, ios::app);
    out << id << endl;
    out.close();

    lock->unlock();
    return true;
}