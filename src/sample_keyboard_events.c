#include "../include/gub.h"
#include "../include/utils/keyboard.h"

void pressKey0() { puts("KEY 0 PRESSED"); }
void pressKey1() { puts("KEY 1 PRESSED"); }
void pressKey2() { puts("KEY 2 PRESSED"); }
void pressKey3() { puts("KEY 3 PRESSED"); }
void pressKey4() { puts("KEY 4 PRESSED"); }
void pressKey5() { puts("KEY 5 PRESSED"); }
void pressKey6() { puts("KEY 6 PRESSED"); }
void pressKey7() { puts("KEY 7 PRESSED"); }
void pressKey8() { puts("KEY 8 PRESSED"); }
void pressKey9() { puts("KEY 9 PRESSED"); }

void pressKeya() { puts("KEY a PRESSED"); }
void pressKeyb() { puts("KEY b PRESSED"); }
void pressKeyc() { puts("KEY c PRESSED"); }
void pressKeyd() { puts("KEY d PRESSED"); }
void pressKeye() { puts("KEY e PRESSED"); }
void pressKeyf() { puts("KEY f PRESSED"); }
void pressKeyg() { puts("KEY g PRESSED"); }
void pressKeyh() { puts("KEY h PRESSED"); }
void pressKeyi() { puts("KEY i PRESSED"); }
void pressKeyj() { puts("KEY j PRESSED"); }
void pressKeyk() { puts("KEY k PRESSED"); }
void pressKeyl() { puts("KEY l PRESSED"); }
void pressKeym() { puts("KEY m PRESSED"); }
void pressKeyn() { puts("KEY n PRESSED"); }
void pressKeyo() { puts("KEY o PRESSED"); }
void pressKeyp() { puts("KEY p PRESSED"); }
void pressKeyq() { puts("KEY q PRESSED"); }
void pressKeyr() { puts("KEY r PRESSED"); }
void pressKeys() { puts("KEY s PRESSED"); }
void pressKeyt() { puts("KEY t PRESSED"); }
void pressKeyu() { puts("KEY u PRESSED"); }
void pressKeyv() { puts("KEY v PRESSED"); }
void pressKeyw() { puts("KEY w PRESSED"); }
void pressKeyx() { puts("KEY x PRESSED"); }
void pressKeyy() { puts("KEY y PRESSED"); }
void pressKeyz() { puts("KEY z PRESSED"); }

int gameLoop(void *args)
{
    addKeyPressEventListener(GUB_KEY_0, pressKey0);
    addKeyPressEventListener(GUB_KEY_1, pressKey1);
    addKeyPressEventListener(GUB_KEY_2, pressKey2);
    addKeyPressEventListener(GUB_KEY_3, pressKey3);
    addKeyPressEventListener(GUB_KEY_4, pressKey4);
    addKeyPressEventListener(GUB_KEY_5, pressKey5);
    addKeyPressEventListener(GUB_KEY_6, pressKey6);
    addKeyPressEventListener(GUB_KEY_7, pressKey7);
    addKeyPressEventListener(GUB_KEY_8, pressKey8);
    addKeyPressEventListener(GUB_KEY_9, pressKey9);

    addKeyPressEventListener(GUB_KEY_a, pressKeya);
    addKeyPressEventListener(GUB_KEY_b, pressKeyb);
    addKeyPressEventListener(GUB_KEY_c, pressKeyc);
    addKeyPressEventListener(GUB_KEY_d, pressKeyd);
    addKeyPressEventListener(GUB_KEY_e, pressKeye);
    addKeyPressEventListener(GUB_KEY_f, pressKeyf);
    addKeyPressEventListener(GUB_KEY_g, pressKeyg);
    addKeyPressEventListener(GUB_KEY_h, pressKeyh);
    addKeyPressEventListener(GUB_KEY_i, pressKeyi);
    addKeyPressEventListener(GUB_KEY_j, pressKeyj);
    addKeyPressEventListener(GUB_KEY_k, pressKeyk);
    addKeyPressEventListener(GUB_KEY_l, pressKeyl);
    addKeyPressEventListener(GUB_KEY_m, pressKeym);
    addKeyPressEventListener(GUB_KEY_n, pressKeyn);
    addKeyPressEventListener(GUB_KEY_o, pressKeyo);
    addKeyPressEventListener(GUB_KEY_p, pressKeyp);
    addKeyPressEventListener(GUB_KEY_q, pressKeyq);
    addKeyPressEventListener(GUB_KEY_r, pressKeyr);
    addKeyPressEventListener(GUB_KEY_s, pressKeys);
    addKeyPressEventListener(GUB_KEY_t, pressKeyt);
    addKeyPressEventListener(GUB_KEY_u, pressKeyu);
    addKeyPressEventListener(GUB_KEY_v, pressKeyv);
    addKeyPressEventListener(GUB_KEY_w, pressKeyw);
    addKeyPressEventListener(GUB_KEY_x, pressKeyx);
    addKeyPressEventListener(GUB_KEY_y, pressKeyy);
    addKeyPressEventListener(GUB_KEY_z, pressKeyz);

    do
    {
        clearScreen();
        drawScreen();
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(512, 512, "SAMPLE KEYBOARD EVENTS")