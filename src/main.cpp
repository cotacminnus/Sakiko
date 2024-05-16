#include "include.h"
#include "saki.h"

using namespace std;
using json = nlohmann::json;

bool clean_init = false;

dpp::snowflake ID;
mutex local_file;

//定时器，每天当地时间0点清空历史
void saki_recycle(string loc, int gmt=0){
    if(gmt > 12 || gmt < -12){
        gmt = 0;
        cerr << "Illegal time zone, resetting to 0..." << endl;
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
        ofstream kill(loc + "tousaki.txt", ios::trunc); //清空
        kill.close();
        kill.open(loc + "unsei.txt", ios::trunc);
        kill.close();
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    int opt;
    const char* optstr = "c";
    while((opt = getopt(argc, argv, optstr)) != -1){
        switch (opt){
            case 'c':   //启动时清空历史
                clean_init = true;
            default:
                break;
        }
    }

    ifstream setup_loc("../config/config.json");
    json config;

    if(!setup_loc.is_open()){
        cerr << "Cannot open setup file!" << endl;
        return 1;
    }
    else{
        setup_loc >> config;    //配置json
    }

    pid_t pid = getpid();
    cout << "PID: " << pid << endl;

    //计时，每天当地时间0点清空历史
    thread timer(saki_recycle, config["local_dir"], config["gmt"]);
    timer.detach();     //你免费了
    
    Staff_S Saki(&local_file, config["local_dir"]);
    if(clean_init){     //启动时清空历史
        Saki.clear_tousaki();
        Saki.clear_unsei();
    }
    
    dpp::cluster bot(config["token"], dpp::i_default_intents | dpp::i_message_content);

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
        if(event.msg.author.id != ID){  //不要左右互搏
            if(event.msg.mentions.size() != 0){     //スタッフ仕事
                for(auto i : event.msg.mentions){
                    if(i.first.id == ID){
                        sleep(2);
                        //白祥跟定返场
                        if(event.msg.content.find("贵安") != string::npos || event.msg.content.find("貴安") != string::npos){
                            event.reply("贵安。");
                        }
                        else if(event.msg.content.find("今日运势") != string::npos || event.msg.content.find("今日運勢") != string::npos){
                            pair<bool, string> res = Saki.add_unsei(event.msg.author.id);
                            dpp::message msg(event.msg.channel_id, "");
                            msg.add_file(res.second, dpp::utility::read_file("../resources/" + res.second));
                            event.reply(msg);
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
            else if (event.msg.content.find("小祥，你终于来了") != string::npos) {
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
            //白祥跟定返场
            else if(event.msg.content.find("贵安") != string::npos || event.msg.content.find("貴安") != string::npos){
                sleep(2);
                event.reply("贵安。");
            }
            //春日影，启动！
            else if(event.msg.content.find("春日影") != string::npos){
                sleep(2);
                dpp::message msg(event.msg.channel_id, "");
                msg.add_file("saki_naki.png", dpp::utility::read_file("../resources/saki_naki.png"));
                event.reply(msg);
            }
            //お　幸　せ　に
            else if(event.msg.content.find("祝你幸福") != string::npos || event.msg.content.find("祝妳幸福") != string::npos){
                sleep(2);
                event.reply("祝你幸福。");
            }
            else if(event.msg.content.find("お幸せに") != string::npos || event.msg.content.find("おしあわせに") != string::npos || event.msg.content.find("オシアワセニ") != string::npos){
                sleep(2);
                event.reply("お幸せに。");
            }
        }
    });

    //客服小祥，启动！
    bot.start(dpp::st_wait);
    
    return 0;
}