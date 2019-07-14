/**
 * Fractals assignment for CS106B in Stanford Summer Session 2019
 * Two programs for drawing recursive graphics: Sierpinski triangles and Flood fill
 * Author: Kevin Li
 */
#include "fractals.h"
using namespace std;

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order);
int floodFill(GWindow& window, int x, int y, int color);
int floodFillHelper(GWindow& window, int x, int y, int currentColor, int targetColor, int pixelsChangedColor);

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

/**
 * @brief Fill an area of the same color with a specified color
 * @param window the graphic window
 * @param x the x coordinate to start filling color
 * @param y the y coordinate to start filling color
 * @param color the new color to fill in
 * @return
 */
int floodFill(GWindow& window, int x, int y, int color) {
    if (!window.inCanvasBounds(x, y)) {
        throw "x, y coordinates outside bounds! Should be from (0, 0) to (" +
            integerToString(window.getCanvasWidth() - 1) + ", " +
            integerToString(window.getCanvasHeight() - 1) + ").";
    }
    int currentColor = window.getPixel(x, y);
    if (currentColor == color) {
        return 0;
    }
    return floodFillHelper(window, x, y, currentColor, color, 0);
}

/**
 * @brief Helper function which does the recursion to do flood fill
 * @param window the graphic window
 * @param x the x coordinate to start filling color
 * @param y the y coordinate to start filling color
 * @param currentColor the current color of the selected pixel
 * @param targetColor the target color user chose
 * @param pixelsChangedColor the number of pixels that changed color
 * @return
 */
int floodFillHelper(GWindow& window, int x, int y, int currentColor, int targetColor, int pixelsChangedColor) {
    window.setPixel(x, y, targetColor);
    int totalPixelsChangedColor = pixelsChangedColor;
    if (window.inCanvasBounds(x - 1, y) && window.getPixel(x - 1, y) == currentColor) {
        totalPixelsChangedColor += floodFillHelper(window, x - 1, y, currentColor, targetColor, 1);
    }
    if (window.inCanvasBounds(x + 1, y) && window.getPixel(x + 1, y) == currentColor) {
        totalPixelsChangedColor += floodFillHelper(window, x + 1, y, currentColor, targetColor, 1);
    }
    if (window.inCanvasBounds(x, y - 1) && window.getPixel(x, y - 1) == currentColor) {
        totalPixelsChangedColor += floodFillHelper(window, x, y - 1, currentColor, targetColor, 1);
    }
    if (window.inCanvasBounds(x, y + 1) && window.getPixel(x, y + 1) == currentColor) {
        totalPixelsChangedColor += floodFillHelper(window, x, y + 1, currentColor, targetColor, 1);
    }
    return totalPixelsChangedColor;
}
