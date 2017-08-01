#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace PixelTools {
	void init();
    void put_pixel(int x, int y, float r, float g, float b);
}