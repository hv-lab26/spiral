#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define STEP 0.15f
#define GAP  0.45f
#define DELAY 8000

static void restore(int sig) {
    (void)sig;
    printf("\x1b[2J\x1b[H\x1b[?25h");
    exit(0);
}

int main(void) {
    signal(SIGINT, restore);
    printf("\x1b[?25l");

    for (;;) {
        struct winsize ws;
        int W = 80, H = 24;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col && ws.ws_row) {
            W = ws.ws_col;
            H = ws.ws_row;
        }
        float cx = W / 2.0f, cy = H / 2.0f;
        float rmax = sqrtf(cx * cx / 4 + cy * cy);

        printf("\x1b[2J");
        fflush(stdout);

        for (float th = 0; GAP * th < rmax; th += STEP) {
            float r = GAP * th;
            int x = (int)roundf(cx + 2.0f * r * cosf(th));
            int y = (int)roundf(cy + r * sinf(th));
            if (x < 0 || x >= W || y < 0 || y >= H) continue;

            printf("\x1b[%d;%dH*", y + 1, x + 1);
            fflush(stdout);
            usleep(DELAY);
        }

        sleep(2);
    }
}
