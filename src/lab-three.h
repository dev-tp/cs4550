#ifndef CS4550_LAB_THREE_H_
#define CS4550_LAB_THREE_H_

struct Point {
  int x, y;
};

Point corners[2] = {
  {.x =  0, .y =  0},
  {.x = 10, .y = 10}
};

double left;
double right;
double bottom;
double top;

void Display();
void GetKey(unsigned char, int, int);
void GetSpecialKey(int, int, int);
void Setup();
void UpdateWindowDimensions();

#endif  // CS4550_LAB_THREE_H_
