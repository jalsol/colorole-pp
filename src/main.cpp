#include "constants.h"
#include "client.h"

int main() {
#ifdef DEVELOPMENT
    std::cout << "[DEBUG] Development mode\n";
#endif // DEVELOPMENT

    ClientClass client(kBotToken, sd::USER_CONTROLED_THREADS);

    client.setIntents(
          sd::Intent::SERVER_MESSAGES
        | sd::Intent::SERVER_MEMBERS
        | sd::Intent::SERVER_PRESENCES
    );

    client.run();
}
