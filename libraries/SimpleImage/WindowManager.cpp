/** @file WindowManager.cpp
*  Image Processing Lecture, BV1, Uni Koblenz.
*  Simple window manager class to display different SimpleImages.
*
*  @author    Guido Schmidt
*  @created   November 2013
*  @modified   November 2014
*  @modified   January 2016
*  @modified   January 2017
*  @version  2017-01-24
*/
#include "WindowManager.h"
#include "SimpleImage.h"
#include <sstream>

#if !defined(S_NO_OPENGL)

WindowManager &WindowManager::instance(void)
{
  static WindowManager m_instance;
  return m_instance;
}

WindowManager::WindowManager()
{
  m_images_list = std::vector<SimpleImage *>();

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glfwInit();

  //! Print tooltipp
  std::cout << "=== Simple****Image ===\n"
  "--------------------------------------\n"
  "Mouse button 1 pressed = navigate\n"
  "Mouse scroll wheel = zoom\n\n"
  "Keyboard shortcuts:\n"
  " R,r = reset view\n"
  " c,C = close window\n"
  " Q,q = quit\n"
  "--------------------------------------\n";
}

WindowManager::~WindowManager()
{
  if (m_images_list.empty())
    glfwTerminate();
}

void WindowManager::addImageWindow(SimpleImage *image)
{
  m_images_list.push_back(image);
}

SimpleImage *WindowManager::getImageWindow(unsigned int id)
{
  if (id < m_images_list.size())
    return m_images_list.at(id);
  else {
    std::ostringstream err_msg;
    err_msg << "WindowManager: no window " << id << " in [0 .. " << m_images_list.size() - 1 << "]";
    throw std::range_error(err_msg.str().c_str());
  }
}

const int WindowManager::getImageCount()
{
  return m_images_list.size() - 1;
}

void WindowManager::displayWindow(unsigned int id)
{
  m_images_list.at(id)->display_function();
}
#endif // !defined(S_NO_OPENGL)
