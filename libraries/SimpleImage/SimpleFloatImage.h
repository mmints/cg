/** @file SimpleFloatImage.h
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Simple image class for float images.
 *
 *  @author     Detlev Droege
 *  @author     Frank Schmitt
 *
 *  @created    November 2007
 *  @modified   December 2013
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */

#ifndef SIMPLEFLOATIMAGE_H_
#define SIMPLEFLOATIMAGE_H_
#include "SimpleGrayImage.h"

//! @class SimpleFloatImage
class SimpleFloatImage
{
  int   m_width;  ///< width of the image
  int   m_height; ///< height of the image
public:
  typedef float ElementType;  /// to allow easy global change to e.g. double
private:
  ElementType *pixels;  ///< pointer to the pixel memory
  ElementType **rows;   ///< pointer array to rows


public:
  //! --------------- Image row checks -----------------------
  //! \brief Read only index operator
  /*!
  image[i] will return a pointer to the image row i
  thuss offering access to pixel[y][x]
  */
#ifdef S_IMAGE_RANGE_CHECKS
  const ImageRow<ElementType> operator[](const int i) const;
#else
  const ElementType *operator [](const int i) const;
#endif

  //! \brief Index operator
  /*!
  image[i] will return a pointer to the image row i
  thuss offering access to pixel[y][x]
  */
#ifdef S_IMAGE_RANGE_CHECKS
  ImageRow<ElementType> operator[](const int i);
#else
  ElementType *operator [](const int i);
#endif

  //! --------------- SimpleFloatImage definition ---------------
  //! \brief Constructor: default
  //! Creates empty image. Normally not used
  SimpleFloatImage();

  //! \brief Constructor: creates an image of a given size
  /*!
    The pixels are not initialized.
    @param wid  width of the desired image
    @param hid  height of the desired image
  */
  SimpleFloatImage(int wid, int hig);

  /// \brief Constructor: copy constructor
  /// Creates a deep copy of an image
  //   @param img  image to copy
  SimpleFloatImage(const SimpleFloatImage &img);

#if __cplusplus >= 201103L // C++11 and later
  /// \brief Constructor: move constructor.
  /// Creates a new Image by moving the assets of the old one there, giving it up.
  /// @param img  image to copy
  SimpleFloatImage(SimpleFloatImage && img);
#endif

  //! \brief Constructor: create an image as copy of a SimpleGrayImage
  //! @param gimg  image to copy from
  SimpleFloatImage(const SimpleGrayImage &gimg);

  //! \brief Destructor: releases all data.
  //! Frees all allocated memory
  virtual ~SimpleFloatImage();

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

  /// \brief copy assignment
  SimpleFloatImage& operator=(const SimpleFloatImage & img);
  
#if __cplusplus >= 201103L // C++11 and later
  /// \brief move assignment
  SimpleFloatImage& operator=(SimpleFloatImage && img);
#endif

  //! \brief Returns a pointer to an array of row pointers
  /*!
    @return Pointer to an array of row pointers in ElementType**p = (ElementType**)img;
  */
  operator ElementType **()
  {
    return rows;
  }
  //! \brief Returns a pointer to array of row pointers to raw const image data
  /*!
    @return Pointer to an array of row pointers in const ElementType**p = (const ElementType**)img;
  */

  operator const ElementType **() const
  {
    return const_cast<const ElementType **>(rows);
  }

  //! \brief Resize the image to the given size.
  /*!
  The pixels are not initialized.
  @param wid  New desired width
  @param hid  New desired height
  */
  void resize(int wid, int hig);

  //! \brief Generates a SimpleGrayImage from this image
  /*!
    Generates a SimpleGreyImage from this imahe, mapping values in range
    \p_low .. \p_high to 0 .. 255
    @param gimg  image to copy to
    @param low   lower bound of mapping range
    @param high  upper bound of mapping range
  */
  void copyToGray(SimpleGrayImage &gimg, ElementType low, ElementType high);

  //! \brief Clears the image with a given value, default 0
  //! @param value  The value to set all pixels
  void clear(ElementType value = 0);

private:
  //! \brief Allocates the needed memory for the image
  /*!
    Allocates needed memory of the image by given width and height
    @param wid The width of the image
    @param hig The height of the image
  */
  void alloc_mem(int wid, int hig);

  //! \brief Initializes all needed attributes
  void init_attributes();
};

#endif /*SIMPLEFLOATIMAGE_H_*/
