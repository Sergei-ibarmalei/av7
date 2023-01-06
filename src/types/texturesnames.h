#ifndef TEXTURESNAMES_H
#define TEXTURESNAMES_H

namespace tn
{
    enum {MainMenu, MainMenuBright, Scores, ScoresBanner,
              Pause, PressEsc, LiveMult, allGameFonts};
    enum {hero, alien_one, blue_laser, red_laser, star, all_pics};

    enum {
        new_game, rules, exit, new_game_bright, rules_bright, exit_bright,
        pause, pressEscape,
        zeroScore, oneScore, twoScore, threeScore, fourScore, fiveScore,
        sixScore, sevenScore, eightScore, nineScore,
        zeroScoreB, oneScoreB, twoScoreB, threeScoreB, fourScoreB,
        fiveScoreB, sixScoreB, sevenScoreB, eightScoreB, nineScoreB,
        x1, x2, x3, allStringTextures,
        };

    const char* names[allStringTextures] = 
    {
        "NEW GAME", "RULES", "EXIT",
        "NEW GAME", "RULES", "EXIT",
        "PAUSE", "Press Esc to continue, Q to exit",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "x 1", "x 2", "x 3"
    };

    const char* names_pics[all_pics]
    {
        "Hero_1.png", "alien_one.png",
        "laserBlue01.png", "laserRed01.png",
        "one_star.png",
    };
}

#endif