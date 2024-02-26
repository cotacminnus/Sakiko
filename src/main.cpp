#include "saki.h"

using namespace std;

string BOT_TOKEN;

int main(int argc, char* argv[]) {
    int opt;
    const char* optstr = "t:";  // t:(token)
    while((opt = getopt(argc, argv, optstr)) != -1){
        switch (opt){
            case 't':
                BOT_TOKEN = optarg;
                break;
            default:
                break;
        }
    }

    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    //客服S
	bot.on_ready([&bot](const dpp::ready_t& event) {
        /* We don't need the run_once here as we're not registering commands! */
 
        /* Set the bot presence as online and "Playing..."! */
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "客服S为您服务"));
    });

    //名 场 面
    bot.on_message_create([&bot](const dpp::message_create_t& event) {

        if (event.msg.content.find("我什么都会做") != std::string::npos) {
            sleep(1);
            event.reply(SAKI_SOYO_10, true);
        }
    });

    bot.start(dpp::st_wait);
    
    return 0;
}