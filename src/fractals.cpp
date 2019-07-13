#include "fractals.h"
using namespace std;

/**
 * @brief Draw a Sierpinski Triangle at (x, y) with a side length and at a specific order
 * @param window the graphic window
 * @param x x coordinate to draw the triangle
 * @param y y coordinate to draw the triangle
 * @param size the size of the triangle or the length of its sides
 * @param order the order of the triangle, function will draw 3 ^ order number of triangles.
 *        0 order will draw nothing. Negative orders will throw an error.
 */
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
