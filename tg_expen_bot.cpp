#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>//namespace std
#include <string>//std::string
#include <fstream>
#include "tg_expen_bot.hpp"

int main() 
{
    std::ifstream in("greeting_user.txt");
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    std::string greeting_text(size, ' ');
    in.seekg(0);
    in.read(&greeting_text[0], size);
    TgUser::Users users;


    //start up the server through c++ wrapper 
    TgBot::Bot bot("5974563516:AAEHwP2WpGqL1MQ-BI7BMx4v2dXtSiNwBEY");

    bot.getEvents().onCommand("start", [&bot, &greeting_text, &users](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, greeting_text);
        users.AddUser(message->chat->id);
    });

    bot.getEvents().onCommand("add", [&bot, &users](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        users.AddExpense(message->chat->id,message->text.c_str());
        // bot.getApi().sendMessage(message->chat->id, greeting_text);

    });

    bot.getEvents().onCommand("getexpenses", [&bot, &users](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        //get the keyword
        std::string queryString = message->text.substr(message->text.find(" ") +1);
        size_t expense = users.GetExpense(message->chat->id, queryString.c_str());
        std::string reply("your expenses in ");
        reply += queryString + " are: " + std::to_string(expense) + "\n";
        bot.getApi().sendMessage(message->chat->id, reply);

    });
    
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}