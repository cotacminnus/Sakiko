#include "saki.h"
#include <thread>
#include <ctime>

using namespace std;

bool clean_init = false;
ifstream setup_loc;
map<string, string> globl_str;
dpp::snowflake ID;
mutex local_file;

//定时器，每天当地时间0点清空历史
void saki_recycle(string tloc="../resources/tousaki.txt", string uloc="../resources/unsei.txt", int gmt=0){
    if(gmt > 12 || gmt < -12){
        gmt = 0;
    }
    time_t cur = time(nullptr);
    tm cur_tm = *gmtime(&cur);
    int sec_til;
    cout << "Current UTC time:" << cur_tm.tm_hour << ":" << cur_tm.tm_min << ":" << cur_tm.tm_sec << endl;

    while(true){
        cur = time(nullptr);
        cur_tm = *gmtime(&cur);
        sec_til = 86400 - cur_tm.tm_hour * 3600 - cur_tm.tm_min * 60 - cur_tm.tm_sec - (gmt * 3600);
        if(sec_til < 0){
            sec_til += 86400;
        }
        cout << sec_til << " seconds until file clear" << endl;
        this_thread::sleep_for(chrono::seconds(sec_til));
        ofstream kill(tloc, ios::trunc);
        kill.close();
        kill.open(uloc, ios::trunc);
        kill.close();
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    int opt;
    const char* optstr = "cs:";
    while((opt = getopt(argc, argv, optstr)) != -1){
        switch (opt){
            case 'c':   //启动时清空历史
                clean_init = true;
            case 's':   //配置文件路径
                setup_loc.open(optarg);
                break;
            default:
                break;
        }
    }

    if(!setup_loc.is_open()){
        cerr << "Cannot open setup file!" << endl;
        return 1;
    }
    else{
        string tmp;     //配置存在字典中
        while(!setup_loc.eof()){
            setup_loc >> tmp;
            if(tmp == "#token"){
                setup_loc >> tmp;
                globl_str["TOKEN"] = tmp;
                cout << "Token: " << tmp << endl;
            }
            else if(tmp == "#tousaki_loc"){
                setup_loc >> tmp;
                globl_str["TOUSAKI_LOC"] = tmp;
                cout << "Tousaki location: " << tmp << endl;
            }
            else if(tmp == "#unsei_loc"){
                setup_loc >> tmp;
                globl_str["UNSEI_LOC"] = tmp;
                cout << "Unsei location: " << tmp << endl;
            }
            else if(tmp == "#gmt"){
                setup_loc >> tmp;
                globl_str["GMT"] = tmp;
                cout << "GMT: " << tmp << endl;
            }
        }
    }

    pid_t pid = getpid();
    cout << "PID: " << pid << endl;

    //计时，每天当地时间0点清空历史
    thread timer(saki_recycle, globl_str["TOUSAKI_LOC"], globl_str["UNSEI_LOC"], stoi(globl_str["GMT"]));
    timer.detach();     //你免费了
    
    Staff_S Saki(&local_file, globl_str["TOUSAKI_LOC"], globl_str["UNSEI_LOC"]);
    if(clean_init){     //启动时清空历史
        Saki.clear_tousaki();
        Saki.clear_unsei();
    }
    
    dpp::cluster bot(globl_str["TOKEN"], dpp::i_default_intents | dpp::i_message_content);

    //获取dcid
    bot.current_user_get([&bot](const dpp::confirmation_callback_t& cb){
        if(cb.is_error()){
            cerr << cb.get_error().message << endl;
        }
        else{
            dpp::user temp = get<dpp::user_identified>(cb.value);
            cout << "Discord ID: " << temp.id << endl;
            ID = temp.id;
        }
    });

    bot.on_log(dpp::utility::cout_logger());

    //客服S
	bot.on_ready([&bot](const dpp::ready_t& event) {
        /* We don't need the run_once here as we're not registering commands! */
 
        /* Set the bot presence as online and "Playing..."! */
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "客服S为您服务"));
    });

    bot.on_message_create([&bot, &Saki](const dpp::message_create_t& event) {
        if(event.msg.mentions.size() != 0){     //スタッフ仕事
            for(auto i : event.msg.mentions){
                if(i.first.id == ID){
                    sleep(2);
                    if(event.msg.content.find("今日运势") != string::npos || event.msg.content.find("今日運勢") != string::npos){
                        pair<bool, string> res = Saki.add_unsei(event.msg.author.id);
                        event.reply(res.second);
                    }
                    else if(event.msg.content.find("投祥") != string::npos){
                        pair<bool, string> res = Saki.add_tousaki(event.msg.author.id);
                        event.reply(res.second);
                    }
                    else{
                        event.reply("您好，客服S为您服务。");
                    }
                    break;
                }
            }
        }
        //名 场 面
        else if (event.msg.content.find("我什么都会做") != string::npos || event.msg.content.find("我什麼都會做") != string::npos) {
            sleep(2);
            event.reply(SAKI_SOYO_10, true);
        }
        //名 场 面
        //超级加倍
        else if (event.msg.content.find("さきちゃん") != string::npos) {
            sleep(2);
            event.reply(SAKI_SOYO_0, true);
            sleep(2);
            event.send(SAKI_SOYO_123);
            sleep(2);
            event.send(SAKI_SOYO_45678);
            sleep(2);
            event.send(SAKI_SOYO_9ab);
            sleep(2);
            event.send(SAKI_SOYO_cdef);
            sleep(2);
            event.reply(SAKI_SOYO_10, true);
        }
        //春日影，启动！
        else if(event.msg.content.find("春日影") != string::npos){
            sleep(2);
            dpp::message msg(event.msg.channel_id, "");
            msg.add_file("saki_naki.png", dpp::utility::read_file("../resources/sakichan.png"));
            event.reply(msg);
        }
    });

    //客服小祥，启动！
    bot.start(dpp::st_wait);
    
    return 0;
}