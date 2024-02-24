#pragma once
#include <dpp/dpp.h>

#define SAKI_SOYO_0 "真是会虚情假意呢"
#define SAKI_SOYO_1 "想演奏是你们的自由，你们就请便吧"
#define SAKI_SOYO_2 "到现在都还执着于过去，真难看"
#define SAKI_SOYO_3 "你也差不多该忘记了吧"
#define SAKI_SOYO_4 "那么那个乐团算什么"
#define SAKI_SOYO_5 "你讲的话和做的事全都互相矛盾"
#define SAKI_SOYO_6 "CRYCHIC已经毁了"
#define SAKI_SOYO_7 "绝对不可能再复活了"
#define SAKI_SOYO_8 "我已经亲手将它结束了"
#define SAKI_SOYO_9 "没有人那样拜托你"
#define SAKI_SOYO_a "这是最后的警告"
#define SAKI_SOYO_b "今后不要再和我扯上关系了"
#define SAKI_SOYO_c "你是抱着多大的觉悟说出这种话的"
#define SAKI_SOYO_d "你只不过是一个学生，有办法背负其他人的人生吗"
#define SAKI_SOYO_e "「什么都愿意做」就是这么沉重的话"
#define SAKI_SOYO_f "做不来的事就别轻易说出口"
#define SAKI_SOYO_10 "你这个人，满脑子都只想到自己呢"

class Bot{
    private:

    const std::string handle;
    const std::string token;
    dpp::cluster* bot;

    public:

    Bot();
    Bot(std::string _handle, std::string _token);
    Bot(Bot& alt);
    Bot(Bot&& alt);
    ~Bot();
};