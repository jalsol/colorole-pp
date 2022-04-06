#include <dpp/dpp.h>

#include "constants.h"

int main() {
    dpp::cluster bot(kBotToken);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_interaction_create([](const dpp::interaction_create_t& event) {
         if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(dpp::slashcommand("ping", "Ping pong time", bot.me.id), kGuildId);
        }
    });

    bot.start(false);
}