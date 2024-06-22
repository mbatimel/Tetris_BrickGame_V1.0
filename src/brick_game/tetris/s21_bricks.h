#ifndef S21_BRICKS_H
#define S21_BRICKS_H
#define FIGURE_INIT() \
  {                   \
    I.fig[1][0] = 1;  \
    I.fig[1][1] = 1;  \
    I.fig[1][2] = 1;  \
    I.fig[1][3] = 1;  \
                      \
    O.fig[1][2] = 1;  \
    O.fig[2][2] = 1;  \
    O.fig[2][1] = 1;  \
    O.fig[1][1] = 1;  \
                      \
    J.fig[1][0] = 1;  \
    J.fig[2][0] = 1;  \
    J.fig[2][1] = 1;  \
    J.fig[2][2] = 1;  \
                      \
    L.fig[1][1] = 1;  \
    L.fig[2][1] = 1;  \
    L.fig[2][2] = 1;  \
    L.fig[3][2] = 1;  \
                      \
    S.fig[1][1] = 1;  \
    S.fig[2][1] = 1;  \
    S.fig[2][2] = 1;  \
    S.fig[3][2] = 1;  \
                      \
    Z.fig[1][2] = 1;  \
    Z.fig[2][1] = 1;  \
    Z.fig[2][2] = 1;  \
    Z.fig[3][1] = 1;  \
                      \
    T.fig[1][2] = 1;  \
    T.fig[2][0] = 1;  \
    T.fig[2][1] = 1;  \
    T.fig[2][2] = 1;  \
  }

struct Figure {
  int fig[4][4];
};

typedef struct Figure figure;

extern figure I;
extern figure O;
extern figure J;
extern figure L;
extern figure S;
extern figure Z;
extern figure T;

#endif  // enf of S21_BRICKS_H