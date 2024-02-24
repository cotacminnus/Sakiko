#pragma once
#include "saki.h"

using namespace std;
using namespace dpp;

    /*
    const std::string handle;
    const std::string token;
    dpp::cluster* bot;
    */

Bot::Bot() : handle(NULL), token(NULL), bot(nullptr){}  //别用

Bot::Bot(std::string _handle, std::string _token) : handle(_handle), token(_token){
    bot = new cluster(token, dpp::i_default_intents | dpp::i_message_content);
}

Bot::Bot(Bot& alt){}

Bot::Bot(Bot&& alt){}

Bot::~Bot(){
    bot->shutdown();
    delete bot;
}