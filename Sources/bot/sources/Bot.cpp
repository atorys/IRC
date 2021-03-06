#include "Bot.hpp"
#include <list>

static void Error(std::string msg){
    std::cout << "Error: " << msg << "\n";
    exit(1);
}

const int buffSize = 10;
static std::string Jokes[][20] = {
    {"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀ ",
"⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀ ",
"⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀ ",
"⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀ ",
"⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀ ",
"⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀ ",
"⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀ ",
"⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀ ",
"⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀  ",
"⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀ ",
"⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"},
{"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⣀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣠⡄⣶⡖⣿⣟⠀⢸⣿⣾⣿⢹⡟⢻⡷⣾⠿⣿⣴⣶⣄⡄",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⣿⡟⢹⣷⢽⠷⠹⠗⠂⠀⢃⣉⣈⣀⣙⣋⣁⠙⠒⠋⠼⠛⡿⠁",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢰⡿⢿⡆⠀⠘⠓⠀⣁⣠⣤⣶⣦⡘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⡄⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⡾⣿⡉⠻⠞⢃⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣦⡙⢿⣿⣿⣿⠇⠰⣦⠘⣿⣿⣿⠇⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣤⣤⣤⠙⣃⣴⡾⣫⣭⡻⣿⣿⣿⡿⣟⣛⢿⣿⣿⣿⣆⠻⣿⣿⣇⣈⣁⣼⣿⣿⡟⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣿⡿⢋⣠⣾⣿⣿⡇⡏⠈⢻⣜⣛⣫⡾⠋⢹⡏⣿⣿⣿⣿⣧⡘⣿⣿⣿⣿⢏⣾⡟⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣌⠻⣿⣿⣿⣿⡿⢋⣴⣿⣿⣿⡿⣫⡵⠇⠀⠀⠉⠉⠉⠀⠀⢸⡇⣿⣿⣿⣿⣿⣷⡘⣿⣿⣷⣿⡟⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣷⣌⠻⣿⠟⣰⣿⣿⣿⣿⡟⣼⠃⢠⡄⠀⠀⠀⠀⠀⠀⠀⠘⣷⢻⣿⣿⣿⣿⣿⣷⠘⣿⣿⠟⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠷⢠⠸⣿⣿⣿⣿⣿⢸⠇⠀⣈⠀⠀⠐⠽⠃⠀⠀⠀⠀⠸⡇⣿⣿⣿⣿⣿⣿⣧⠹⠋⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⢿⣧⠹⣿⣿⣿⣿⢿⠀⠈⠿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⡿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠒⠢⠍⠊⢿⣧⢻⣿⣿⣿⡼⣇⠀⠓⠒⠐⠂⠀⠀⠀⠀⠀⠀⣸⢇⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⣿⣿⠿⠶⠦⠄⠀⢻⣧⠹⣿⣿⣷⡝⣦⡀⠀⠀⠀⠀⠀⠀⠀⢀⣴⢫⣾⢟⣽⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣭⣤⣀⣀⠀⠀⠀⠀⠀⠹⣷⡙⣿⣿⣿⣮⣝⡷⢦⣤⣤⣤⡴⢾⣫⡵⢟⣵⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⣼⣿⡿⠿⢿⣿⣿⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠘⢿⣎⠻⣿⣿⣿⣿⣿⣶⣶⣶⣿⠿⣫⣴⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠸⠋⠀⢀⣴⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠹⣷⣝⢿⣿⣿⣿⣿⣿⣿⣷⠿⠛⣡⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⠋⠀⠀⠀⢀⣀⣠⣤⣤⠀⠀⠀⢸⡆⠈⠻⣷⣝⠿⣿⠷⠟⣋⣥⣶⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⢀⣾⣿⣿⣿⣿⡏⢀⣠⣴⣾⣿⣿⣿⣿⣿⠀⠀⠀⣼⡇⠀⢠⠀⠉⣡⠀⣶⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢀⣼⣿⡇⢠⠸⠀⠀⢹⣇⢹⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢸⣿⣿⣴⣿⣿⡟⠀⡞⠀⠀⠀⠀⢻⣦⠻⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"},
{"░░░░░░░░░▄░░░░░░░░░░░░░░▄░░░░",
"░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌░░░",
"░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐░░░",
"░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐░░░",
"░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐░░░",
"░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌░░░",
"░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌░░",
"░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐░░",
"░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌░",
"░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌░",
"▐▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐░",
"▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌",
"▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐░",
"░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌░",
"░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐░░",
"░░▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌░░",
"░░░░▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀░░░",
"░░░░░░▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀░░░░░",
"░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▀▀░░░░░░░░"},
{"⬜⬜⬜⬜⬜⬜🐸🐸🐸🐸🐸🐸⬜🐸🐸⬜⬜⬜⬜",
"⬜⬜⬜⬜⬜🐸✅✅✅✅✅✅🐸✅✅🐸⬜⬜⬜", 
"⬜⬜⬜⬜🐸✅✅🐸🐸🐸🐸🐸🐸✅🐸🐸🐸⬜⬜", 
"⬜⬜⬜🐸✅✅🐸✅✅✅✅✅✅🐸✅✅✅🐸⬜", 
"⬜⬜⬜🐸✅✅✅🐸🐸🐸🐸🐸🐸✅🐸🐸🐸🐸🐸", 
"⬜⬜🐸✅✅✅🐸🐸⬜⬛⬛⬜🐸🐸⬜⬛⬛⬜🐸",
"⬜🐸🐸✅✅✅🐸⬜⬛⬛⬛⬜🐸⬜⬛⬛⬛⬜🐸",
"🐸✅🐸✅✅✅✅🐸🐸🐸🐸🐸✅🐸🐸🐸🐸🐸⬜", 
"🐸✅🐸✅✅✅✅✅🐸🐸🐸✅✅✅🐸🐸🐸⬜⬜",
"🐸✅✅✅✅✅✅✅✅✅✅🐸✅🐸✅✅✅🐸⬜", 
"✅✅✅✅✅✅✅✅✅🐸🐸✅✅✅🐸🐸✅🐸⬜",
"✅✅✅✅✅✅✅✅✅🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥", 
"✅✅✅✅✅✅✅🟥🟥🧰🧰🧰🧰🧰🧰🧰🧰🟥⬜", 
"🐸✅✅✅✅✅🟥🧰🧰🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥", 
"🐸✅✅✅✅🐸🟥🟥🟥🟥✅✅✅✅✅✅✅🐸⬜", 
"⬜🐸✅✅✅✅🐸🐸✅✅✅✅✅✅✅✅🐸⬜⬜", 
"⬜⬜🐸✅✅✅✅✅✅✅✅✅✅✅✅🐸⬜⬜⬜", 
"⬜⬜⬜🐸🐸✅✅✅✅✅✅✅✅🐸🐸⬜⬜⬜⬜",
"⬜⬜⬜⬜⬜🐸🐸🐸🐸🐸🐸🐸🐸⬜⬜⬜⬜⬜⬜"}
     ,{"⠐⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠂",
             "⠄⠄⣰⣾⣿⣿⣿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣆⠄⠄",
             "⠄⠄⣿⣿⣿⡿⠋⠄⡀⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠋⣉⣉⣉⡉⠙⠻⣿⣿⠄⠄",
             "⠄⠄⣿⣿⣿⣇⠔⠈⣿⣿⣿⣿⣿⡿⠛⢉⣤⣶⣾⣿⣿⣿⣿⣿⣿⣦⡀⠹⠄⠄",
             "⠄⠄⣿⣿⠃⠄⢠⣾⣿⣿⣿⠟⢁⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠄⠄",
             "⠄⠄⣿⣿⣿⣿⣿⣿⣿⠟⢁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠄⠄",
             "⠄⠄⣿⣿⣿⣿⣿⡟⠁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄",
             "⠄⠄⣿⣿⣿⣿⠋⢠⣾⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄",
             "⠄⠄⣿⣿⡿⠁⣰⣿⣿⣿⣿⣿⣿⣿⣿⠗⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⡟⠄⠄",
             "⠄⠄⣿⡿⠁⣼⣿⣿⣿⣿⣿⣿⡿⠋⠄⠄⠄⣠⣄⢰⣿⣿⣿⣿⣿⣿⣿⠃⠄⠄",
             "⠄⠄⡿⠁⣼⣿⣿⣿⣿⣿⣿⣿⡇⠄⢀⡴⠚⢿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢠⠄⠄",
             "⠄⠄⠃⢰⣿⣿⣿⣿⣿⣿⡿⣿⣿⠴⠋⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⡟⢀⣾⠄⠄",
             "⠄⠄⢀⣿⣿⣿⣿⣿⣿⣿⠃⠈⠁⠄⠄⢀⣴⣿⣿⣿⣿⣿⣿⣿⡟⢀⣾⣿⠄⠄",
             "⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⢶⣿⣿⣿⣿⣿⣿⣿⣿⠏⢀⣾⣿⣿⠄⠄",
             "⠄⠄⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⠋⣠⣿⣿⣿⣿⠄⠄",
             "⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣼⣿⣿⣿⣿⣿⠄⠄",
             "⠄⠄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣴⣿⣿⣿⣿⣿⣿⣿⠄⠄",
             "⠄⠄⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⢁⣴⣿⣿⣿⣿⠗⠄⠄⣿⣿⠄⠄",
             "⠄⠄⣆⠈⠻⢿⣿⣿⣿⣿⣿⣿⠿⠛⣉⣤⣾⣿⣿⣿⣿⣿⣇⠠⠺⣷⣿⣿⠄⠄",
             "⠄⠄⣿⣿⣦⣄⣈⣉⣉⣉⣡⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⠉⠁⣀⣼⣿⣿⣿⠄⠄"
     },
     {
         "⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⣠⣤⣶⣶",
         "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⢰⣿⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣾⣿⣿⣿⣿",
         "⣿⣿⣿⣿⣿⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿",
         "⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿",
         "⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿",
         "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿"
     }
};

Bot::Bot(std::string hostname, std::string port, std::string pass):
        _name("bot"), _hostname(hostname), _port(port), _pass(pass) {

    if (1024 > std::atoi(_port.c_str()) || std::atoi(_port.c_str()) > 65535)
        Error("wrong port number. Please enter the correct port number in range [1024, 65535]");
    hostent *host = NULL;
    host = gethostbyname(hostname.c_str());
    if (host == NULL)
        Error("incorrect hostname");
    std::vector<std::string> splittedaddres = ut::split(hostname, ".");
    sockaddr_in address = {std::atoi(splittedaddres[0].c_str()),
                    std::atoi(splittedaddres[1].c_str()),
                    std::atoi(splittedaddres[2].c_str()),
                    {std::atoi(splittedaddres[3].c_str())}, {}};
    address.sin_family = AF_INET;
    address.sin_port = htons(std::atoi(_port.c_str()));
    if (inet_aton(host->h_name, &address.sin_addr) == 0)
        Error("Incorrect ip address has been passed");
    if ((_BotSocket = socket(address.sin_family, SOCK_STREAM, 0)) == -1){
        Error("Socket troubles");
    }
    if (connect(_BotSocket, (sockaddr*)&address, sizeof(address)) == -1){
        std::cout << errno << " ";
        Error("cannot connect to server");
    }
    _is_auth_confirmed = false;
}

void Bot::run(){
    _replymessage = "PASS " + _pass + "\r\n"\
    "NICK " + _name + "\r\n"\
    "USER bot bot bot :work work \r\n";
    while (true){
        reply();
        getMessage();
        parse();
        execute();
    }     
}

void Bot::reply(){

    if (!_replymessage.empty()){
        send(_BotSocket, _replymessage.c_str(), _replymessage.length(), 0);
        _replymessage.clear();
    }
}

void Bot::getMessage(){
    int Bytes;
    char buff[buffSize];
    bzero(&buff, sizeof(buff));
    if ((Bytes = recv(_BotSocket, &buff, buffSize - 1, 0)) > 0){
        _incomeBuff += buff;
    } else {
        throw("error");
    }
}

std::string Bot::getRequest() {
    std::string::size_type index = _incomeBuff.find("\n") + 1;
    std::string request = _incomeBuff.substr(0, index);
    _incomeBuff.erase(0, index);
    return request;
}

void Bot::parse(){
    _request = getRequest();
    if (_request.find("PRIVMSG") != std::string::npos || _request.find("NOTICE") != std::string::npos){
        _currentType = "PRIVMSG";
    } else if (_request.find(":ircserv 375 BOT :- Message of the day -") != std::string::npos) {
        _is_auth_confirmed = true;
        _currentType = "SKIP";
    } else if (_request.find(":ircserv 451 * :You have not registered") != std::string::npos || _request.find("You may not reregister") != std::string::npos || _incomeBuff.find(":ircserv 464 * :Password incorrect") != std::string::npos){
        _currentType = "AUTH";
    } else 
        _currentType = "SKIP";
}

void Bot::execute(){
    if (_currentType == "PRIVMSG"){
        std::cout << _request;
        _request.erase(0, _request.find(":") + 1);
        std::cout << _request;
        std::string name = _request.substr(0, _request.find(" "));
        std::cout << "[" << name << "]\n";
        unsigned long positionInMsg = _request.find(':');
        if (positionInMsg != _request.npos && positionInMsg != _request.length() - 1){
            _request = _request.substr(positionInMsg + 1);
            if (_request.find("joke") != std::string::npos || _request.find("анекдот") != std::string::npos){
                std::list<std::string> TotalMessage;
                std::srand(std::time(NULL));
                std::string *Joke = Jokes[rand() % 6];
                for (size_t i = 0; i < 20 && !Joke[i].empty(); ++i) {
                    TotalMessage.push_back(" :" + Joke[i] + "\r\n");
                }
                if (!TotalMessage.empty()) {
                    for (std::list<std::string>::iterator i = TotalMessage.begin(); i != TotalMessage.end(); ++i) {
                        _replymessage += "NOTICE " + name + *i;
                    }
                }
            }
        }
    } else if (_currentType == "AUTH"){
        if (_is_auth_confirmed == true){
            return;
        }
        static int tries = 3;
        if (tries < 0){
            std::cout << "error: authentication failed.";
            throw("end");
        }
        std::cout << "You wrote a wrong password, try again.\n";
        std::cin >> _pass;
        std::cout << "You written a new password : " << _pass << ". Let's try it.\n";
        _replymessage = "PASS " + _pass + "\r\n"\
            "NICK " + _name + "\r\n"\
            "USER BOT bot bot :work work \r\n";
        tries--;
    } else if (_currentType == "SKIP"){
        return;
    }
}
