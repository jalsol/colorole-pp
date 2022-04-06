#include <dpp/dpp.h>
#include <dpp/fmt/format.h>

#include "constants.h"
#include "utils.h"

int main() {
    dpp::cluster bot(kBotToken);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
        const std::string& command = event.command.get_command_name();

        // TODO: complete this
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            // TODO: refactor this

            dpp::slashcommand colorole("colorole", "Choose a color", bot.me.id);
            colorole.add_option(
                dpp::command_option(
                    dpp::co_string,
                    "hex_code",
                    "Color hex code",
                    true
                )
            );

            dpp::slashcommand random("random", "Let the bot choose a *random* color", bot.me.id);

            bot.guild_command_create(colorole, kGuildId);
            bot.guild_command_create(random  , kGuildId);
        }
    });

    bot.start(false);
}