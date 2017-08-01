/*! @file SimpleGrayImage.cpp
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Simple image class to read and write PGM Images.
 *
 *  @author   Detlev Droege
 *  @author   Frank Schmitt
 *  @author   Erik Knauer
 *  @author   Christian Gaida
 *  @author   Gerrit Lochmann
 *  @author   Guido Schmidt
 *
 *  @created    November 2007
 *  @modified   March 2010
 *  @modified   May 2010
 *  @modified   November 2013
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

#include "SimpleImage/SimpleGrayImage.h"

//! --------------- Image row checks ---------------
#ifdef S_IMAGE_RANGE_CHECKS
const ImageRow<SimpleGrayImage::ElementType> SimpleGrayImage::operator [](const int i) const
{
  if ((i < 0) || (i >= m_height)) {
    std::ostringstream err_msg;
    err_msg << "SimpleGrayImage: row bounds violated: row = " << i << " not in [0 .. " << m_height - 1 << "]    ";
    throw std::range_error(err_msg.str());
  }
  return ImageRow<SimpleGrayImage::ElementType>(rows[i], m_width);
}
#else
const SimpleGrayImage::ElementType *SimpleGrayImage::operator [](const int i) const
{
  return rows[i];
}
#endif

#ifdef S_IMAGE_RANGE_CHECKS
ImageRow<SimpleGrayImage::ElementType> SimpleGrayImage::operator [](const int i)
{
  if ((i < 0) || (i >= m_height)) {
    std::ostringstream err_msg;
    err_msg << "SimpleGrayImage: row bounds violated: row = " << i << " not in [0 .. " << m_height - 1 << "]    ";
    throw std::range_error(err_msg.str());
  }
  return ImageRow<SimpleGrayImage::ElementType>(rows[i], m_width);
}
#else
SimpleGrayImage::ElementType *SimpleGrayImage::operator [](const int i)
{
  return rows[i];
}
#endif

//! --------------- SimpleGreyImage implementation ---------------
SimpleGrayImage::SimpleGrayImage()
{
  init_attributes();
}

SimpleGrayImage::SimpleGrayImage(int wid, int hig)
{
  init_attributes();
  resize(wid, hig);
}

SimpleGrayImage::SimpleGrayImage(const SimpleGrayImage &img)
{
  init_attributes();
  resize(img.width(), img.height());
  std::memcpy(this->pixels, img.pixels, width()*height());
}

#if __cplusplus >= 201103L // C++11 and later
SimpleGrayImage::SimpleGrayImage(SimpleGrayImage && img)
{
  m_height = img.m_height;
  m_width = img.m_width;
  pixels = img.pixels;
  rows = img.rows;
  img.m_width = img.m_height = 0;
  img.pixels = nullptr;
  img.rows = nullptr;
}
#endif

SimpleGrayImage::SimpleGrayImage(const std::string &filename)
{
  init_attributes();

  if (filename == "") {
    throw std::runtime_error("Unable to load image from file: Empty filename");
  }

  std::ifstream in(filename.c_str(), std::ios::binary);

  if (!in.good()) {
    throw std::runtime_error("Unable to open file " + filename);
  }

  // check for file type
  std::string filetype;
  in >> filetype;
  if (filetype.find("P2", 0) == 0 || filetype.find("P5", 0) == 0) {
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

    // read maximum value (although unused)
    int max;
    in >> max;
    if (m_width <= 0 || m_height <= 0) throw std::runtime_error("Invalid image size in file " + filename);
    // allocate data for the bitmap
    alloc_mem(m_width, m_height);
    // read maxvalue
    std::getline(in, curline);
    if (filetype.find("P2", 0) == 0) {
      for (int p = 0; p < m_width * m_height; p++) {
        //We can't read directly into image.data[p] as we
        //would only get one char and not the whole number,
        //e.g. 2 instead of 255
        int d;
        in >> d;
        pixels[p] = d;
      }
    }
    else {
      // data in binary format
      in.read((char *)pixels, m_width * m_height);
    }
  }
  else {
    throw std::runtime_error("Unsupported image type in file: " + filename);
  }
  in.close();
}

SimpleGrayImage::~SimpleGrayImage()
{
  delete[] pixels;
  delete[] rows;
}

SimpleGrayImage& SimpleGrayImage::operator=(const SimpleGrayImage & img)
{
  init_attributes();
  resize(img.width(), img.height());
  std::memcpy(this->pixels, img.pixels, width()*height());
  return *this;
}

#if __cplusplus >= 201103L // C++11 and later
SimpleGrayImage& SimpleGrayImage::operator=(SimpleGrayImage && img)
{
  if (this == &img) // copying me to myself ...
    return *this;
  delete [] pixels;
  delete [] rows;
  m_height = img.m_height;
  m_width = img.m_width;
  pixels = img.pixels;
  rows = img.rows;
  img.m_width = img.m_height = 0;
  img.pixels = nullptr;
  img.rows = nullptr;
  return *this;
}
#endif

void SimpleGrayImage::init_attributes()
{
  m_width    = 0;
  m_height   = 0;
  pixels     = NULL;
  rows     = NULL;
#if !defined(S_NO_OPENGL)
  WindowManager::instance().addImageWindow(this);
  m_id = WindowManager::instance().getImageCount();
#endif
}

void SimpleGrayImage::alloc_mem(int wid, int hig)
{
  if (pixels) delete[] pixels;  // delete old pixel data
  if (rows) delete[] rows;    // delete old row pointers
  pixels = new SimpleGrayImage::ElementType[wid * hig]; // get memory for pixels
  rows = new SimpleGrayImage::ElementType*[m_height];     // get memory for row pointers
  SimpleGrayImage::ElementType *pp = pixels;        // let pp point to 1. pixel row
  for (int i = 0; i < m_height; i++) { // for every row i
    rows[i] = pp;       // make rows[i] point to it
    pp += m_width;          // advance pp to next row
  }
}

void SimpleGrayImage::resize(int wid, int hig)
{
  if (!((wid > 0) && (hig > 0)))
    throw std::range_error(std::string("SimpleGrayImage::resize(): width and height must be > 0"));
  if ((wid == m_width) && (hig == m_height))
    return; // no size change - nothing to do
  m_width = wid;
  m_height = hig;
  alloc_mem(wid, hig);
}

void SimpleGrayImage::writeToFile(const std::string &filename) const
{
  // store image in PGM format.
  if (filename == "") throw std::runtime_error("Unable to save image to file: Empty filename");
  std::ofstream out(filename.c_str(), std::ios::binary);
  if (!out.good()) throw std::runtime_error("Unable to open file " + filename + " for writing");
  // check for file type
  out << "P5\n" << m_width << " " << m_height << "\n255\n";
  out.write((char *)pixels, m_width * m_height);
  out.close();
}

void SimpleGrayImage::clear(SimpleGrayImage::ElementType value)
{
  std::memset(pixels, value, m_width * m_height);
}

void SimpleGrayImage::dump() const
{
  for (int y = 0; y < m_height; y++) {
    std::copy(pixels + y * m_width, pixels + y * m_width + m_width, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
}

#if defined(S_NO_OPENGL)
void SimpleGrayImage::show(std::string title)
{
  static int MsgCnt = 0;
  if (MsgCnt++) return;
  std::cout << "Note: SimpleGrayImage has been compiled without OpenGL support and thus" << std::endl;
  std::cout << "      the show() function is deactivated. Comment out the definition of" << std::endl;
  std::cout << "      S_NO_OPENGL in SimpleImage.h to activate it again." << std::endl;
  std::cout << "      Otherwise use writeToFile() and an image viewer as workaround." << std::endl;
}
#else
void SimpleGrayImage::show(std::string title)
{
  GLuint texName;
  init_display(title);
  reset();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width(), height(), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);

  //! Render loop
  while (!glfwWindowShouldClose(window)) {

    display_function();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
}
#endif /* S_NO_OPENGL */
