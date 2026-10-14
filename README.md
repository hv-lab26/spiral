# spiral

An ASCII spiral animation for the terminal, written in C. It's inspired by the classic Apple IIe spiral demo: a single-arm spiral is drawn dot by dot from the center outward, fills the screen, then clears and starts again.

```
               *           *     *               *     *      *    *     *
   *                *     *     *     *******     *     *
         *     *    *     *    **    **     **     *     *    *     *     *
                          *    *     ** **   **    *     *
   *     *     *    *     *     *     ***    **    *           *    *
                     *     *     *           *     *     *    *
    *     *    *           *      ****   ****     *     *           *
```

## Build and run

```bash
gcc spiral.c -o spiral -lm
./spiral
```

Press `Ctrl+C` to quit. The spiral scales to your terminal window, so make the window bigger or full screen for a larger spiral.

On macOS, if linking fails with `tapi error` / `unknown architecture`, build against an older SDK:

```bash
gcc -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX15.4.sdk spiral.c -o spiral -lm
```

## How it works

Each dot lies on an Archimedean spiral, `r = GAP * θ`. The angle `θ` increases by a fixed `STEP` for each dot, so the dots form a solid line near the center and spread out toward the edges. The x coordinate is doubled because terminal characters are about twice as tall as they are wide. Each dot is placed with an ANSI cursor-move escape code, so dots that are already drawn stay on screen.

## Tweaks

Edit these constants at the top of `spiral.c`:

| Constant | Default | Effect |
|----------|---------|--------|
| `STEP`   | `0.15`  | Angle between dots (radians). Smaller means denser dots. |
| `GAP`    | `0.45`  | Spacing between turns of the spiral. |
| `DELAY`  | `8000`  | Microseconds between dots. Larger means slower drawing. |
