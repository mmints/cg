/** @file SimpleFloatImage.cpp
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Simple image class for float images.
 *
 *  @author     Detlev Droege
 *  @author     Frank Schmitt
 *  @created    November 2007
 *  @modified   December 2013
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "SimpleFloatImage.h"

using namespace std;

//! --------------- Image row checks ---------------
#ifdef S_IMAGE_RANGE_CHECKS
const ImageRow<SimpleFloatImage::ElementType> SimpleFloatImage::operator [](const int i) const
{
  if ((i < 0) || (i >= m_height)) {
    std::ostringstream err_msg;
    err_msg << "SimpleFloatImage: row bounds violated: row = " << i << " not in [0 .. " << m_height - 1 << "]    ";
    throw std::range_error(err_msg.str());
  }
  return ImageRow<SimpleFloatImage::ElementType>(rows[i], m_width);
}
#else
const SimpleFloatImage::ElementType *SimpleFloatImage::operator [](const int i) const
{
  return rows[i];
}
#endif

#ifdef S_IMAGE_RANGE_CHECKS
ImageRow<SimpleFloatImage::ElementType> SimpleFloatImage::operator [](const int i)
{
  if ((i < 0) || (i >= m_height)) {
    std::ostringstream err_msg;
    err_msg << "SimpleFloatImage: row bounds violated: row = " << i << " not in [0 .. " << m_height - 1 << "]    ";
    throw std::range_error(err_msg.str());
  }
  return ImageRow<SimpleFloatImage::ElementType>(rows[i], m_width);
}
#else
SimpleFloatImage::ElementType *SimpleFloatImage::operator [](const int i)
{
  return rows[i];
}
#endif

//! --------------- SimpleFloatImage implementation ---------------
void SimpleFloatImage::alloc_mem(int wid, int hig)
{
  if (pixels) delete[] pixels; //delete old pixel data
  if (rows) delete[] rows; //delete old row pointers
  pixels = new SimpleFloatImage::ElementType[wid * hig]; // get memory for pixels
  rows = new SimpleFloatImage::ElementType*[hig];        // get memory for row pointers
  SimpleFloatImage::ElementType *pp = pixels;            // let pp point to 1. pixel row
  for (int i = 0; i < hig; i++) { // for every row i
    rows[i] = pp;       // make rows[i] point to it
    pp += m_width;      // advance pp to next row
  }
}

void SimpleFloatImage::init_attributes()
{
  m_width = 0;
  m_height = 0;
  pixels = NULL;
  rows = NULL;
}

SimpleFloatImage::SimpleFloatImage()
{
  init_attributes();
}

#if __cplusplus >= 201103L // C++11 and later
SimpleFloatImage::SimpleFloatImage(SimpleFloatImage && img)
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

SimpleFloatImage::~SimpleFloatImage()
{
  delete [] pixels;
  delete [] rows;
}

SimpleFloatImage& SimpleFloatImage::operator=(const SimpleFloatImage & img)
{
  init_attributes();
  resize(img.width(), img.height());
  std::memcpy(this->pixels, img.pixels, width()*height()*sizeof(SimpleFloatImage::ElementType));
  return *this;
}

#if __cplusplus >= 201103L // C++11 and later
SimpleFloatImage& SimpleFloatImage::operator=(SimpleFloatImage && img)
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

SimpleFloatImage::SimpleFloatImage(int wid, int hig)
{
  init_attributes();
  resize(wid, hig);
}

SimpleFloatImage::SimpleFloatImage(const SimpleFloatImage &img)
{
  init_attributes();
  resize(img.width(), img.height());
  std::memcpy(this->pixels, img.pixels, width()*height()*sizeof(SimpleFloatImage::ElementType));
}

SimpleFloatImage::SimpleFloatImage(const SimpleGrayImage &gimg)
{
  init_attributes();
  resize(gimg.width(), gimg.height());
  const int wid = gimg.width();
  for (int y = 0; y < gimg.height(); y++) {
    for (int x = 0; x < wid; x++) {
      rows[y][x] = SimpleFloatImage::ElementType(gimg[y][x]);
    }
  }
}

void SimpleFloatImage::clear(SimpleFloatImage::ElementType value)
{
  const int wid = m_width;
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < wid; x++) {
      rows[y][x] = value;
    }
  }
}

void SimpleFloatImage::copyToGray(SimpleGrayImage &gimg, SimpleFloatImage::ElementType low, SimpleFloatImage::ElementType high)
{
  gimg.resize(m_width, m_height);
  const int wid = m_width;
  const double scale = 255.0 / (high - low);
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < wid; x++) {
      gimg[y][x] = clampToByte((rows[y][x] - low) * scale);
    }
  }
}

void SimpleFloatImage::resize(int wid, int hig)
{
  if (!((wid > 0) && (hig > 0)))
    throw std::runtime_error("SimpleFloatImage::resize(): width and height must be > 0");
  m_width = wid;
  m_height = hig;
  alloc_mem(wid, hig);
}
