/** @file SimpleImage.cpp
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Base class for Simple image classes (for GLFW 'window manager').
 *
 *  @author     Detlev Droege
 *
 *  @created    October 2014
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */

#include "SimpleImage.h"
#include <sstream>

#if !defined(S_NO_OPENGL)

//! ================== Defines & static variables ==================
#define   SCREEN_X   1024
#define   SCREEN_Y   768

#define   MAXZOOM    5.0
#define   MINZOOM    0.5
#define   ZOOMRES    100.0

static GLfloat  zoom = 1.0,
                zoom_window = 1.0,
                zoom_view = 1.0;

static int offset = 10;
static int  window_x_pos = 100,
            window_y_pos = 100;

static double movX = 0,
              movY = 0,
              xClicked = 0,
              yClicked = 0,
              xOffset = 0,
              xOld = 0,
              yOld = 0,
              yOffset = 0,
              x = 0,
              y = 0;

void SimpleImage::reset()
{
  zoom = 1.0f;
  movX = 0.0f;
  movY = 0.0f;
}

void SimpleImage::display_function()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  //glBindTexture(GL_TEXTURE_2D, texName); // was done in show()

  glLoadIdentity();
  glTranslatef((GLfloat)movX, (GLfloat)movY, 0.0);
  glScalef(zoom, -zoom, 1.0); // zoom and flip y-coordinates (image processing coordinate system)

  /*
   -1,1                  1,1
   ________________________
   |                      |
   |                      |
   |                      |
   |                      |
   |______________________|
  -1,-1                  1,-1
  */

  glBegin(GL_TRIANGLES);
  // Triangle One
  //glColor3f(1.0, 0.0, 0.0);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.0, -1.0);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(1.0,  1.0);
  glTexCoord2f(0.0, 1.0);
  glVertex2f(-1.0,  1.0);
  // Triangle Two
  //glColor3f(0.0, 1.0, 0.0);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(-1.0, -1.0);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(1.0,  1.0);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(1.0, -1.0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void SimpleImage::init_display(std::string wintitle)
{
  //! Print current image info
  std::cout << "Image id: " << m_id << " @size (" << m_width << ", " << m_height << ")" << std::endl;

  //! Create the window
  window = glfwCreateWindow(m_width, m_height, wintitle.c_str(), 0, 0);
  if (window) {
    glfwSetWindowPos(window, window_x_pos + offset, window_y_pos + offset);
    glfwMakeContextCurrent(window);

    // Register callbacks
    glfwSetWindowSizeCallback(window, &SimpleImage::resize_function);
    glfwSetMouseButtonCallback(window, &SimpleImage::mouse_button_function);
    glfwSetScrollCallback(window, &SimpleImage::mouse_scroll_function);
    glfwSetCursorPosCallback(window, &SimpleImage::mouse_cursor_function);
    glfwSetKeyCallback(window, &SimpleImage::keyboard_function);
    glfwSetWindowPosCallback(window, &SimpleImage::window_pos_function);
  }
  else {
    std::ostringstream err_msg;
    err_msg << "ERROR: window creation failed for image id = " << m_id;

    throw std::runtime_error(err_msg.str());
  }

  glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
  glShadeModel(GL_FLAT);  // Enables flat Shading
  glEnable(GL_DEPTH_TEST);
}

GLFWwindow *SimpleImage::getWindow(void)
{
  return window;
}

//! ---------------- Callbacks implementation ----------------
void SimpleImage::resize_function_implemented(GLFWwindow *window, int newWidth, int newHeight)
{
  glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

  m_width = newWidth;
  m_height = newHeight;
}

void SimpleImage::keyboard_function_implemented(GLFWwindow *window, int key, int action)
{
  switch (key) {
    case 27:
      exit(1);
      break;
    case 'c':
    case 'C':
      glfwSetWindowShouldClose(window, true);
      break;
    case 'q':
    case 'Q':
      exit(0);
      break;
    case 'r':
    case 'R':
      zoom_view = 1.0;
      movX = 0;
      movY = 0;
      break;
    default:
      return;
  }
  zoom = zoom_window;
}

void SimpleImage::mouse_function_implemented(GLFWwindow *window, int button, int state, int action)
{
  //! Buttons
  if (button == GLFW_MOUSE_BUTTON_1 && state == GLFW_PRESS) {
    //! Get window size - dirty hack because of C-Style-API of GLFW callbacks
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    double cursor_x, cursor_y;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    xOld = movX;
    yOld = movY;

    xClicked = cursor_x;
    yClicked = cursor_y;
  }
}


void SimpleImage::mouse_cursor_function_implemented(GLFWwindow *window, double xNew, double yNew)
{
  //! Get window size - dirty hack because of C-Style-API of GLFW callbacks
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  x = xNew;
  y = yNew;

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
    xOffset = xClicked - x;
    yOffset = yClicked - y;

    movX = xOld - xOffset / width;
    movY = yOld + yOffset / height;
  }
}

void SimpleImage::mouse_scroll_function_implemented(GLFWwindow *window, double xoffset, double yoffset)
{
  if (yoffset < 0.0) {
    zoom_view /= 1.05f;
  }
  else if (yoffset > 0.0) {
    zoom_view *= 1.05f;
  }
  if (zoom_view > MAXZOOM) zoom_view = MAXZOOM;
  if (zoom_view < MINZOOM) zoom_view = MINZOOM;
  zoom = zoom_view * zoom_window;
}

void SimpleImage::window_pos_function_implemented(GLFWwindow *window, int x, int y)
{
  glfwGetWindowPos(window, &window_x_pos, &window_y_pos);
}

#endif // !defined(S_NO_OPENGL)
