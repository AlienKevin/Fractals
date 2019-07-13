#include "fractals.h"
using namespace std;

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {
    if (x < 0 || y < 0) {
        throw "x, y coordinates must be greater than or equal to 0!";
    }
    if (size < 0) {
        throw "Size must be greater than or equal to 0!";
    }
    if (order == 0) {
        // do nothing
    } else if (order < 0) {
        throw "Order must be greater than or equal to 0!";
    } else if (order == 1){
        double height = sqrt(3) / 2 * size;
        window.drawLine(x, y, x + size, y);
        window.drawLine(x + size, y, x + size / 2, y + height);
        window.drawLine(x + size / 2, y + height, x , y);
    } else {
        double height = sqrt(3) / 2 * size;
        drawSierpinskiTriangle(window, x, y, size / 2, order - 1);
        drawSierpinskiTriangle(window, x + size / 2, y, size / 2, order - 1);
        drawSierpinskiTriangle(window, x + size / 4, y + height / 2, size / 2, order - 1);
    }
}

int floodFill(GWindow& window, int x, int y, int color) {

    return 0;   // this is only here so it will compile
}
