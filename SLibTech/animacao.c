#ifndef _WIN32
#define _DEFAULT_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
    #define DORMIR(ms) Sleep(ms)
    #include <windows.h>
#else
    #define CLEAR "clear"
    #define DORMIR(ms) usleep((ms) * 1000)
    #include <unistd.h>
#endif

#define RESET_CURSOR "\033[H"

void animacaoFolhear() {
    char *frames[] = {
        "      _______________________ \n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |__________|____________|\n",

        "      _______________________ \n"
        "     |          |         /  |\n"
        "     |          |        /   |\n"
        "     |          |       /    |\n"
        "     |          |      /     |\n"
        "     |__________|_____/______|\n",

        "      _______________________ \n"
        "     |          |       /    |\n"
        "     |          |      /     |\n"
        "     |          |     /      |\n"
        "     |          |    /       |\n"
        "     |__________|___/________|\n",

        "      _______________________ \n"
        "     |          |     /      |\n"
        "     |          |    /       |\n"
        "     |          |   /        |\n"
        "     |          |  /         |\n"
        "     |__________|_/__________|\n",

        "      _______________________ \n"
        "     |          | |          |\n"
        "     |          | |          |\n"
        "     |          | |          |\n"
        "     |          | |          |\n"
        "     |__________|_|__________|\n",

        "      ________________________\n"
        "     |        \\ |            |\n"
        "     |         \\|            |\n"
        "     |          \\            |\n"
        "     |           \\           |\n"
        "     |___________\\___________|\n",

        "      _______________________ \n"
        "     |       \\  |            |\n"
        "     |        \\ |            |\n"
        "     |         \\|            |\n"
        "     |          \\            |\n"
        "     |_________\\|____________|\n",

        "      _______________________ \n"
        "     |     \\    |            |\n"
        "     |      \\   |            |\n"
        "     |       \\  |            |\n"
        "     |        \\ |            |\n"
        "     |_________\\|____________|\n",

        "      _______________________ \n"
        "     |   \\      |            |\n"
        "     |    \\     |            |\n"
        "     |     \\    |            |\n"
        "     |      \\   |            |\n"
        "     |_______\\__|____________|\n",

        "      _______________________ \n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |          |            |\n"
        "     |__________|____________|\n"
    };

    int totalFrames = 10;
    int velocidade = 100;

    time_t inicio = time(NULL);
    int frame = 0;

    system(CLEAR);

    while (difftime(time(NULL), inicio) < 5.0) {
        printf("%s", RESET_CURSOR);
        printf("\n\n\n\n\n");
        printf("%s", frames[frame]);
        fflush(stdout);
        DORMIR(velocidade);

        frame++;
        if (frame >= totalFrames) frame = 0;
    }

    system(CLEAR);
}
