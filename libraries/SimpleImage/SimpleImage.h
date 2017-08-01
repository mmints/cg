/** @file SimpleImage.h
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
#ifndef SIMPLEIMAGE_H_
#define SIMPLEIMAGE_H_

#include <stdexcept>
#include <cstdlib>

// #define S_NO_OPENGL     // #define to deactivate all OpenGL/GLEW/GLFW code

#if !defined(S_NO_OPENGL)
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "WindowManager.h"
#endif // !defined(S_NO_OPENGL)

//! @class SimpleImage
class SimpleImage
{
protected:
  int m_width;    ///< Width of the image
  int m_height;   ///< Height of the image

public:
  //! \brief Constructor: default
  //! Creates empty image. normally not used.
  SimpleImage()
  {
    m_width = m_height = 0;
  };

  //! \brief Destructor
  //! Frees all allocated memory
  virtual ~SimpleImage() { };

  /// \brief Returns the width of the image
  int width() const
  {
    return m_width;
  }

  /// \brief Returns the height of the image
  int height() const
  {
    return m_height;
  }

#if !defined(S_NO_OPENGL)
  friend void WindowManager::displayWindow(unsigned int id);

protected:
  // ---------------- OpenGL based onscreen display ----------------

  //! \brief Initializes the GLFW window to render to
  /*!
   Creates an OpenGL context window using GLFW3 (http://www.glfw.org/).
   Sets the windows position an registers the callbacks for all input data (mouse, window, keyboard)
   */
  void init_display(std::string wintitle);

  //! \brief Returns a singleton instance
  /*!
   Singleton instance needed to register C-style-API callbacks of GLFW input handling
   */
  static SimpleImage &getInstance()
  {
    static SimpleImage instance;
    return instance;
  }

  //! \brief Returns the GLFWwindow of this image
  GLFWwindow *getWindow(void);

  //! \brief Resets the zoom-factor and the position of the image
  void reset();

protected:
  //! \brief Render-loop for displaying the pixel data of the image
  void display_function();

  GLFWwindow *window; //! GLFW window variable
  int m_id;     //! ID of the image referenced from WindowManager

  //! ---------------- GLFW C-Style-API callbacks implementation ----------------
  /*!
    GLFW only supports a C-styled callback system. Using the singleton pattern to
    register callbacks (all methods without '_implemented' in name) to this class by using static methods.
    The static methods call the class-methods (all methods with '_implemented' in name), implemented
    in the SimpleGreyImage.cpp-file.
  */
  //! Handle GLFW window resize event
  static void resize_function(GLFWwindow *window, int width, int height)
  {
    getInstance().resize_function_implemented(window, width, height);
  }
  void resize_function_implemented(GLFWwindow *window, int width, int height);

  //! Handle GLFW mouse event
  static void mouse_button_function(GLFWwindow *window, int button, int state, int action)
  {
    getInstance().mouse_function_implemented(window, button, state, action);
  }
  void mouse_function_implemented(GLFWwindow *window, int button, int state, int action);

  //! Handle GLFW mouse scroll events
  static void mouse_scroll_function(GLFWwindow *window, double xoffset, double yoffset)
  {
    getInstance().mouse_scroll_function_implemented(window, xoffset, yoffset);
  }
  void mouse_scroll_function_implemented(GLFWwindow *window, double xoffset, double yoffset);

  //! Handles GLFW cursor move events
  void mouse_cursor_function_implemented(GLFWwindow *window, double x, double y);
  static void mouse_cursor_function(GLFWwindow *window, double x, double y)
  {
    getInstance().mouse_cursor_function_implemented(window, x, y);
  }

  //! Handles GLFW keyboard events
  void keyboard_function_implemented(GLFWwindow *window, int key, int action);
  static void keyboard_function(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    getInstance().keyboard_function_implemented(window, key, action);
  }

  //! Handles GLFW window position events
  void window_pos_function_implemented(GLFWwindow *window, int x, int y);
  static void window_pos_function(GLFWwindow *window, int x, int y)
  {
    getInstance().window_pos_function_implemented(window, x, y);
  }
#endif // !defined(S_NO_OPENGL)

};

#endif /* SIMPLEIMAGE_H_ */
