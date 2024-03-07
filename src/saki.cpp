#include "saki.h"

using namespace std;

Staff_S::Staff_S(mutex* lok): lock(lok){
    reseed();
    local_dir = "../local/";

    fstream tou(local_dir + "tousaki.txt");
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    fstream uns(local_dir + "unsei.txt");
    if(!uns.is_open()){
        cerr << "opening unsei file failed!" << endl;
    }
    uns.close();
}

Staff_S::Staff_S(mutex* lok, string dir): lock(lok), local_dir(dir){
    reseed();
    fstream tou(local_dir + "tousaki.txt");
    if(!tou.is_open()){
        cerr << "opening tousaki file failed!" << endl;
    }
    tou.close();
    fstream uns(local_dir + "unsei.txt");
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

pair<bool, string> Staff_S::add_tousaki(const dpp::snowflake& id){  //记小本本
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
pair<bool, string> Staff_S::add_unsei(const dpp::snowflake& id){    //记小本本
    bool ret = unsei(id.str());
    pair<bool, string> dis(ret, "");
    if(!ret){
        dis.second = UNSEI_U;
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

void Staff_S::clear_tousaki(){  //大赦天下
    lock->lock();
    ofstream tou(local_dir + "tousaki.txt", ios::trunc);
    tou.close();
    reseed();
    lock->unlock();
}
void Staff_S::clear_unsei(){    //大赦天下
    lock->lock();
    ofstream uns(local_dir + "unsei.txt", ios::trunc);
    uns.close();
    reseed();
    lock->unlock();
}

bool Staff_S::tousaki(string id){   //投祥
    lock->lock();
    ifstream tou(local_dir + "tousaki.txt");
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

    ofstream out(local_dir + "tousaki.txt", ios::app);
    out << id << endl;
    out.close();

    lock->unlock();
    return true;
}

bool Staff_S::unsei(string id){     //今日运势
    lock->lock();
    ifstream uns(local_dir + "unsei.txt");
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

    ofstream out(local_dir + "unsei.txt", ios::app);
    out << id << endl;
    out.close();

    lock->unlock();
    return true;
}