/** @file WindowManager.h
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
#pragma once

#include <vector>
#include <iostream>

class SimpleImage;

//! @class WindowManager
/*!
  WindowManager obtains a vector of all registered SimpleImage-objects.
*/
class WindowManager
{
public:
  //! \brief Returns an instance
  /*!
    WindowManager class is implemented as singleton
    @return Instance of the window manager
  */
  static WindowManager &instance(void);

  //! \brief Adds a SimpleImage object to the window manager
  /*!
    @param image  a pointer of the SimpleImage that should be added
  */
  void addImageWindow(SimpleImage *image);

  //! \brief Returns an image by its id
  /*!
    @return a pointer to the desired SimpleImage
  */
  SimpleImage *getImageWindow(unsigned int id);

  //! \brief Returns the count of images registered at the window manager
  /*!
    @return The count of images, registered at the window manager
  */
  const int getImageCount();

  //! \brief Displays a SimpleImage using GLFW (http://www.glfw.org)
  /*!
    @param id The id of the SimpleImage that should be renderd
  */
  void displayWindow(unsigned int id);

private:
  //! All images are stored in a list
  std::vector<SimpleImage *> m_images_list;

  //! \brief Constructor: default
  //! This is private because class is implemented as singleton
  WindowManager();

  //! \brief Destructor
  ~WindowManager();
};
