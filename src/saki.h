#pragma once
#ifndef SAKI_H
#define SAKI_H

#include <dpp/dpp.h>
#include <algorithm>
#include <iostream>
#include <mutex>

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

#define SAKI_SOYO_123 "想演奏是你们的自由，你们就请便吧\n到现在都还执着于过去，真难看\n你也差不多该忘记了吧"
#define SAKI_SOYO_45678 "那么那个乐团算什么\n你讲的话和做的事全都互相矛盾\nCRYCHIC已经毁了\n绝对不可能再复活了\n我已经亲手将它结束了"
#define SAKI_SOYO_9ab "没有人那样拜托你\n这是最后的警告\n今后不要再和我扯上关系了"
#define SAKI_SOYO_cdef "你是抱着多大的觉悟说出这种话的\n你只不过是一个学生，有办法背负其他人的人生吗\n「什么都愿意做」就是这么沉重的话\n做不来的事就别轻易说出口"

#define UNSEI_0 "不祥"
#define UNSEI_1 "小祥"
#define UNSEI_2 "中祥"
#define UNSEI_3 "大祥"
#define UNSEI_4 "亲，今天已经抽过签了呢。"

#define TOUSAKI_BENE "投祥成功！"
#define TOUSAKI_MALE "亲，今天已经投过祥了呢。祝你幸福。"

class Staff_S{
    private:
    //随机种子
    int seed;
    //工作日志
    std::string tousaki_loc;
    std::string unsei_loc;

    std::mutex* lock;

    bool tousaki(std::string id);
    bool unsei(std::string id);

    public:
    Staff_S(std::mutex* lok);
    Staff_S(std::mutex* lok, std::string tdir, std::string udir);
    ~Staff_S();
    void reseed();
    std::pair<bool, std::string> add_tousaki(const dpp::snowflake& id);
    std::pair<bool, std::string> add_unsei(const dpp::snowflake& id);

    void clear_tousaki();
    void clear_unsei();
};

#endif