/**
 * @file SimpleRGBImage.cpp
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#include "SimpleRGBImage.h"

void SimpleRGBImage::init_attributes()
{
  m_width    = 0;
  m_height   = 0;
#if !defined(S_NO_OPENGL)
  WindowManager::instance().addImageWindow(this);
  m_id = WindowManager::instance().getImageCount();
#endif
}

SimpleRGBImage::SimpleRGBImage()
{
  init_attributes();
}

SimpleRGBImage::~SimpleRGBImage()
{
}

SimpleRGBImage::SimpleRGBImage(int wid, int hig)
{
  init_attributes();
  resize(wid, hig);
}

void SimpleRGBImage::resize(int wid, int hig)
{
  assert((wid > 0) && (hig > 0));
  m_width = wid;
  m_height = hig;
  red.resize(wid, hig);
  green.resize(wid, hig);
  blue.resize(wid, hig);
}

SimpleRGBImage::SimpleRGBImage(const SimpleRGBImage &img)
{
  init_attributes();
  resize(img.width(), img.height());
  red   = img.red;
  green = img.green;
  blue  = img.blue;
}

#if __cplusplus >= 201103L // C++11 and later
SimpleRGBImage::SimpleRGBImage(SimpleRGBImage && img)
{
  init_attributes();
  m_height = img.m_height;
  m_width  = img.m_width;
  red   = std::move(img.red);
  green = std::move(img.green);
  blue  = std::move(img.blue);
}
#endif

SimpleRGBImage& SimpleRGBImage::operator=(const SimpleRGBImage & img)
{
  init_attributes();
  resize(img.width(), img.height());
  red   = img.red;
  green = img.green;
  blue  = img.blue;
  return *this;
}

#if __cplusplus >= 201103L // C++11 and later
SimpleRGBImage& SimpleRGBImage::operator=(SimpleRGBImage && img)
{
  if (this == &img) // copying me to myself ...
    return *this;
  m_height = img.m_height;
  m_width  = img.m_width;
  red   = std::move(img.red);
  green = std::move(img.green);
  blue  = std::move(img.blue);
  return *this;
}
#endif

SimpleRGBImage::SimpleRGBImage(const std::string &filename)
{
  init_attributes();

  if (filename == "")
    throw std::runtime_error("Unable to load image from file: Empty filename");
  std::ifstream in(filename.c_str(), std::ios::binary);
  if (!in.good())
    throw std::runtime_error("Unable to open file " + filename);

  // check for file type
  std::string filetype;
  in >> filetype;
  if (filetype.find("P3", 0) == 0 || filetype.find("P6", 0) == 0) {
    // A comment can follow; or the size of the image
    std::string curline;
    in >> curline;
    while (!curline.empty() && curline[0] == '#') {
      std::getline(in, curline); // skip rest of line also
      in >> curline;
    }
    // The last token wasn't a comment, extract the image size
    std::istringstream iss(curline);
    iss >> m_width;
    in >> m_height;
    // read maxvalue
    int max;
    in >> max;
    std::getline(in, curline); // read line end

    std::cout << "PPM read: " << m_width << "x" << m_height << "(" << max << ", " << filetype << ")" << std::endl;
    if (m_width <= 0 || m_height <= 0) throw std::runtime_error("Invalid image size in file " + filename);
    if (max > 255) throw std::runtime_error("depth to large (> 255) in file " + filename);
    // set size of the bitmaps
    resize(m_width, m_height);
    if (filetype.find("P3", 0) == 0) {
      for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
          // read ASCII number from file per color
          int d;
          in >> d;
          red[y][x] = d;
          in >> d;
          green[y][x] = d;
          in >> d;
          blue[y][x] = d;
        }
      }
    }
    else {
      // data in binary format
      for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
          // read byte from file per color
          int d;
          d = in.get();
          red[y][x] = d;
          d = in.get();
          green[y][x] = d;
          d = in.get();
          blue[y][x] = d;
        }
      }
    }
  }
  else {
    throw std::runtime_error("Unsupported image type in file: " + filename);
  }
  in.close();
}

void SimpleRGBImage::writeToFile(const std::string &filename) const
{
  // store image in PGM format.
  if (filename == "") throw std::runtime_error("Unable to save image to file: Empty filename");
  std::ofstream out(filename.c_str(), std::ios::binary);
  if (!out.good()) throw std::runtime_error("Unable to open file " + filename + " for writing");
  // check for file type
  out << "P6\n" << m_width << " " << m_height << "\n255\n";
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      // write bytes to file per color
      out.put(red[y][x]);
      out.put(green[y][x]);
      out.put(blue[y][x]);
    }
  }
  out.close();
}

void SimpleRGBImage::clear(byte value)
{
  red.clear(value);
  green.clear(value);
  blue.clear(value);
}

void SimpleRGBImage::dump() const
{
  std::cout << "Red plane: " << std::endl;
  red.dump();
  std::cout << "Green plane: " << std::endl;
  green.dump();
  std::cout << "Blue plane: " << std::endl;
  blue.dump();
}

#if defined(S_NO_OPENGL)
void SimpleRGBImage::show(std::string title)
{
  static int MsgCnt = 0;
  if (MsgCnt++) return;
  std::cout << "Note: SimpleRGBImage has been compiled without OpenGL support and thus" << std::endl;
  std::cout << "      the show() function is deactivated. Comment out the definition of" << std::endl;
  std::cout << "      S_NO_OPENGL in SimpleImage.h to activate it again." << std::endl;
  std::cout << "      Otherwise use writeToFile() and an image viewer as workaround." << std::endl;
}
#else

void SimpleRGBImage::show(std::string title)
{
  GLuint texName;
  init_display(title);

  byte *texels = new byte [width() * height() * 3];

  // generating texelmap
  byte *tp = texels;
  // dumb and slow ...
  // but avoid range checks, access data directly:
  byte **rpred = red, **rpgreen = green, **rpblue = blue;
  for (int y = 0; y < height(); y++) {
    byte *cpred = rpred[y], *cpgreen = rpgreen[y], *cpblue = rpblue[y];
    for (int x = 0; x < width(); x++) {
      *tp++ =   *cpred++;
      *tp++ = *cpgreen++;
      *tp++ =  *cpblue++;
    }
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texels);

  //! Render loop
  while (!glfwWindowShouldClose(window)) {
    display_function();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);

  delete [] texels;
}

#endif // !defined(S_NO_OPENGL)
