#pragma once
#include "saki.h"

using namespace std;

Staff_S::Staff_S(mutex* lok): lock(lok){
    reseed();
    tousaki_loc = "../resources/tousaki.txt";
    unseki_loc = "../resources/unseki.txt";
    
    fstream tou(tousaki_loc);
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    fstream uns(tousaki_loc);
    if(!uns.is_open()){
        cerr << "opening unseki file failed!" << endl;
    }
    uns.close();
}

Staff_S::Staff_S(mutex* lok, string tloc="../resources/tousaki.txt", string uloc="../resources/unseki.txt"): lock(lok), tousaki_loc(tloc), unseki_loc(uloc){
    reseed();
    fstream tou(tousaki_loc);
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    fstream uns(tousaki_loc);
    if(!uns.is_open()){
        cerr << "opening unseki file failed!" << endl;
    }
    uns.close();
}

Staff_S::~Staff_S(){}

void Staff_S::reseed(){
    seed = rand();
}

pair<bool, string> Staff_S::add_tousaki(dpp::snowflake id){
    bool ret = tousaki(id.str());
    pair<bool, string> dis(ret, NULL);
    if(ret){
        dis.second = TOUSAKI_BENE;
        return dis;
    }
    else{
        dis.second = TOUSAKI_MALE;
        return dis;
    }
}
pair<bool, string> Staff_S::add_unseki(dpp::snowflake id){
    bool ret = tousaki(id.str());
    pair<bool, string> dis(ret, NULL);
    if(!ret){
        dis.second = UNSEKI_4;
        return dis;
    }
    else{
        lock->lock();
        switch(seed % 4){
        case 0:
            dis.second = UNSEKI_0;
            break;
        case 1:
            dis.second = UNSEKI_1;
            break;
        case 2:
            dis.second = UNSEKI_2;
            break;
        default:
            dis.second = UNSEKI_3;
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
void Staff_S::clear_unseki(){
    lock->lock();
    ofstream uns(unseki_loc, ios::trunc);
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
bool Staff_S::unseki(string id){
    lock->lock();
    ifstream uns(unseki_loc);
    if(!uns.is_open()){
        cerr << "opening unseki file failed!" << endl;
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

    ofstream out(tousaki_loc, ios::app);
    out << id << endl;
    out.close();

    lock->unlock();
    return true;
}