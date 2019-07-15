/**
 * Fractals assignment for CS106B in Stanford Summer Session 2019
 * Two programs for drawing recursive graphics: Sierpinski triangles and Flood fill
 * Author: Kevin Li
 */
#include "fractals.h"
using namespace std;

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order);
void drawSierpinskiTriangleHelper(GWindow& window, double x, double y, double size, int order, int color, int baseColor);
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
    int oldColor = window.getColorInt();
    // Color schemes:
    // 1. level color: decimal(8900331) sky blue
    //    base color: decimal(8308816) or #7EC850 (lawn grass green)
    // 2. create mountains with green forest
    //    level color: decimal(11842740) or #b4b4b4 (a shade of gray)
    //    base color: decimal(8308816) or #7EC850 (lawn grass green)
    drawSierpinskiTriangleHelper(window, x, y, size, order, 8900331, 8308816);
    window.setColor(oldColor);
}

/**
 * @brief Helper function for drawing Sierpinski Triangle recursively with colors for different level
 * @param window the grpahic window
 * @param x x coordinate to draw the triangle
 * @param y y coordinate to draw the triangle
 * @param size the size of the triangle or the length of its sides
 * @param order the order of the triangle, function will draw 3 ^ order number of triangles.
 *        0 order will draw nothing. Negative orders will throw an error.
 * @param levelColor the starting level color which will gradually gets darker as level increases
 * @param baseColor the base color that fills the three downward pointing triangles when order == 1
 */
void drawSierpinskiTriangleHelper(GWindow& window, double x, double y, double size, int order, int levelColor, int baseColor) {
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
        window.setColor(baseColor);
        window.fillPolygon({x, y, x + size, y, x + size, y, x + size / 2, y + height, x + size / 2, y + height, x , y});
    } else {
        int step = levelColor / order;
        double height = sqrt(3) / 2 * size;
        window.setColor(levelColor);
        window.fillPolygon({x + size / 2, y, x + size / 4, y + height / 2, x + 3 * size / 4, y + height / 2});
        drawSierpinskiTriangleHelper(window, x, y, size / 2, order - 1, levelColor - step, baseColor);
        drawSierpinskiTriangleHelper(window, x + size / 2, y, size / 2, order - 1, levelColor - step, baseColor);
        drawSierpinskiTriangleHelper(window, x + size / 4, y + height / 2, size / 2, order - 1, levelColor - step, baseColor);
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
