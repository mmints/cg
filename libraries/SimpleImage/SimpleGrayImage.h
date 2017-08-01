/** @file SimpleGrayImage.h
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Simple image class to read and write PGM Images.
 *
 *  @author Detlev Droege
 *  @author Frank Schmitt
 *  @author Erik Knauer
 *  @author Christian Gaida
 *  @author Gerrit Lochmann
 *  @author Guido Schmidt
 *
 *  @created    November 2007
 *  @modified   March 2010
 *  @modified   May 2010
 *  @modified   November 2013
 *  @modified   October 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */
#ifndef SIMPLEGRAYIMAGE_H_
#define SIMPLEGRAYIMAGE_H_

#include <string>
#include <memory>
#include <sstream>
#include <ostream>

typedef unsigned char byte; //! usual type for (gray) pixels

//#define S_IMAGE_RANGE_CHECKS  // #define to do row and column range checks

#include "SimpleImage/SimpleImage.h"

//! \cond
#ifdef S_IMAGE_RANGE_CHECKS
// ImageRow class adapted from agasForge/coreDataStructs/trunk/lib/Image/Image.h
class SimpleGrayImage;
class SimpleFloatImage;

//! @class ImageRow
//! Class to easily add range checking
template<typename T> class ImageRow
{
public:
  T &operator[](const int i)
  {
    if ((i < 0) || (i >= columns)) {
      std::ostringstream err_msg;
      err_msg << "Simple___Image: column bounds violated: column = " << i << " not in [0 .. " << columns - 1 << "]    ";
      throw std::range_error(err_msg.str());
    }
    return row[i];
  }
  const T &operator[](const int i) const
  {
    if ((i < 0) || (i >= columns)) {
      std::ostringstream err_msg;
      err_msg << "Simple___Image: column bounds violated: column = " << i << " not in [0 .. " << columns - 1 << "]    ";
      throw std::range_error(err_msg.str());
    }
    return row[i];
  }
  operator T *()
  {
    return row;
  }
  operator const T *() const
  {
    return row;
  }

private:
  friend class SimpleGrayImage;
  friend class SimpleFloatImage;
  explicit ImageRow(T *_row, int _columns) : row(_row), columns(_columns) {}
  T *row;
  int columns;
};
#endif //! S_IMAGE_RANGE_CHECKS
//! \endcond

//! @class SimpleGrayImage
class SimpleGrayImage : public SimpleImage
{
public:
  typedef byte ElementType;
private:
  ElementType *pixels;    ///< Pointer to the pixel memory
  ElementType **rows;   ///< Pointer array to rows

public:
  /// \brief Default constructor
  /// Creates empty image, normally not used.
  SimpleGrayImage();

  /// \brief Constructor: create image of given size.
  /// The pixels are not initialized.
  /// @param wid  width of the desired image
  /// @param hid  heigth of the desired image
  SimpleGrayImage(int wid, int hig);

  /// \brief Constructor: copy constructor.
  /// Creates a deep copy of img.
  /// @param img  image to copy
  SimpleGrayImage(const SimpleGrayImage & img);

#if __cplusplus >= 201103L // C++11 and later
  /// \brief Constructor: move constructor.
  /// Creates a new Image by moving the assets of the old one there, giving it up.
  /// @param img  image to copy
  SimpleGrayImage(SimpleGrayImage && img);
#endif

  /// \brief Constructor: Read PGM image (depth 255) from file.
  /// Reads a PGM file into this object. The value range of the pixels must be 0..255.
  /// @param filename   name of image file
  SimpleGrayImage(const std::string &filename);

  /// \brief Destructor
  /// Frees all allocated memory.
  virtual ~SimpleGrayImage();

  /// \brief copy assignment
  SimpleGrayImage& operator=(const SimpleGrayImage & img);
  
#if __cplusplus >= 201103L // C++11 and later
  /// \brief move assignment
  SimpleGrayImage& operator=(SimpleGrayImage && img);
#endif

  /// \brief Returns a pointer to array of row pointers in ElementType**p = (ElementType**)img;
  operator ElementType **()
  {
    return rows;
  }

  /// \brief Returns a pointer to array of row pointers in const ElementType**p = (const ElementType**)img;
  operator const ElementType **() const
  {
    return const_cast<const ElementType **>(rows);
  }

  /// \brief Read only index operator
  /// image[i] will return a pointer to the image row i
  /// thus offering access to pixel[i][j]
#ifdef S_IMAGE_RANGE_CHECKS
  const ImageRow<ElementType> operator[](const int i) const;  // access row[i]
#else
  const ElementType *operator [](const int i) const;    // access row[i]
#endif

  /// \brief Index operator
  /// image[i] will return a pointer to the (writable) image row i
  /// thus offering access to pixel[i][j]
#ifdef S_IMAGE_RANGE_CHECKS
  ImageRow<ElementType> operator[](const int i);  // access row[i]
#else
  ElementType *operator [](const int i);      // access row[i]
#endif

  /// \brief Returns a (read only) sample of an image
  inline ElementType sample(int x, int y) const
  {
#ifdef S_IMAGE_RANGE_CHECKS
    if ((x < 0) || (y < 0) || (x >= m_width) || (y >= m_height)) {
      std::ostringstream err_msg;
      err_msg << "Simple___Image: bounds violated";
      throw std::range_error(err_msg.str());
    }
#endif
    return pixels[y * m_width + x];
  }

  /// \brief Returns a sample of an image as reference
  inline ElementType &sample(int x, int y)
  {
#ifdef S_IMAGE_RANGE_CHECKS
    if ((x < 0) || (y < 0) || (x >= m_width) || (y >= m_height)) {
      std::ostringstream err_msg;
      err_msg << "Simple___Image: bounds violated";
      throw std::range_error(err_msg.str());
    }
#endif
    return pixels[y * m_width + x];
  }

  /// \brief Write image to file in PGM format.
  /// @param filename   name of image file to be written
  void writeToFile(const std::string &filename) const;

  /// \brief Resize the image to the given size.
  /// The pixels are not initialized.
  /// @param wid  new desired width
  /// @param hid  new desired heigth
  void resize(int wid, int hig);

  /// \brief Clears the image with a given value, default 0.
  /// @param value  the value to set all pixels to.
  void clear(ElementType value = 0);

  /// \brief Dumps the image's pixel values row-wise in numbers onto the console.
  /// @attention Should only be used with small images, lots of output otherwise.
  void dump() const;

  /// \brief Display the image in a window
  /// Window creation is managed by WindowManager, utilizing GLFW
  void show(std::string title = "Simple Gray Image");

private:
  /// \brief Allocates pixel storage
  /// Allocates needed memory of the image by given width and height
  /// @param wid The width of the image
  /// @param hig The height of the image
  void alloc_mem(int wid, int hig);

  /// \brief Initlizes all needed attributes
  void init_attributes();

};

/** \brief Clamps a given value to range [0, 255]
 * @param value    the input value, which should be clamped
 * @return       the clamped value
 */
inline int clampToByte(int value)
{
  if (value <   0) return   0;
  if (value > 255) return 255;
  return value;
}

#endif /*SIMPLEGRAYIMAGE_H_*/
