/** @file SimpleRGBImage.h
 *  Image Processing Lecture, BV1, Uni Koblenz.
 *  Simple image class to read and write PGM Images.
 *
 *  @author     Detlev Droege
 *  @author     Christian Gaida
 *  @created    November 2007
 *  @modified   March 2010
 *  @modified   May 2010
 *  @modified   November 2013
 *  @modified   October 2014
 *  @modified   November 2014
 *  @modified   January 2016
 *  @modified   January 2017
 *  @version  2017-01-24
 */
#ifndef SIMPLERGBIMAGE_H_
#define SIMPLERGBIMAGE_H_

#include <string>
#include <stdexcept>
#include <ostream>

#include "SimpleImage.h"
#include "SimpleGrayImage.h"
/**
 * Die Klasse SimpleRGBImage vereinigt einfach 3 SimpleGrayImage-Objekte
 * zu einem RGB Bild. Das wird dadurch in untypischer (und ineffizienter)
 * Form gespeichert. Für ein paar einfache Versuchsprogramme reicht
 * das so aus, für eine produktive Bildverarbeitung ist das in vielen
 * Fällen ungünstig (es gibt aber auch Situationen, in denen das
 * gar nicht so schlecht ist -- wie so oft hängt es vom konkreten Problem ab).
 *
 * Ein Objekt dieser Klasse hat 3 Member, 'red', 'green' und 'blue', die
 * jedes für sich eine Farbebene des RGB Bildes speichern.
 * Der Zugriff auf Pixel erfolgt also mit 'colimg.blue[12][5]' oder bei
 * Zeigern mit z.B. 'pcolimg->green[3][7]'.
 *
 * Wie bei SimpleGrayImage gibt es eine Funktion 'writeToFile' mit der das
 * Bild als PPM-Datei unter dem als Parameter angegebenen Namen gespeichert wird.
 * Außerdem eine Funktion 'show()' die das Bild anzeigt. Wie auch bei
 * SimpleGrayImage wird nach der ersten Anzeige eines Bildes das Programm beendet.
 * (show() ist deaktiviert wenn in SimpleGrayImage.h #define S_NO_OPENGL aktiv ist.)
 */

class SimpleRGBImage : public SimpleImage
{
  void alloc_mem(int wid, int hig); // allocate and init memory (internal)
  void init_attributes();   // initialize (internal)

public:
  // Softwaretechnisch SEHR unsauber, diese Member
  // frei zugreifbar zu machen. Sollte man besser kapseln.
  SimpleGrayImage red;  ///< red image plane
  SimpleGrayImage green;  ///< green image plane
  SimpleGrayImage blue; ///< blue image plane

  /// Default constructor: creates empty image.
  /// not normally used.
  SimpleRGBImage();

  /// Constructor: create image of given size.
  /// The pixels are not initialized.
  /// @param wid  width of the desired image
  /// @param hid  heigth of the desired image
  SimpleRGBImage(int wid, int hig);

  /// Constructor: copy constructor.
  /// The pixels are initialized from the given image img.
  /// @param img  source image
  SimpleRGBImage(const SimpleRGBImage &img);

#if __cplusplus >= 201103L // C++11 and later
  /// Constructor: move constructor.
  /// The pixels are transferred from the given image img.
  /// @param img  source image
  SimpleRGBImage(SimpleRGBImage &&img);
#endif

  /// Destructor: releases all data.
  /// Free all allocated memory.
  virtual ~SimpleRGBImage();    // destructor

  /// \brief copy assignment
  SimpleRGBImage& operator=(const SimpleRGBImage & img);
  
#if __cplusplus >= 201103L // C++11 and later
  /// \brief move assignment
  SimpleRGBImage& operator=(SimpleRGBImage && img);
#endif
  
  /// constructor: Read PPM image (depth 255) from file.
  /// Reads a PPM file into this object.
  /// The value range for the pixels must be 0..255.
  /// @param filename   name of image file
  SimpleRGBImage(const std::string &filename);

  /// Write image to file in PPM format.
  /// @param filename   name of image file to be written
  void writeToFile(const std::string &filename) const;

  /// Resize the image to the given size.
  /// The pixels are not initialized.
  /// @param wid  new desired width
  /// @param hid  new desired heigth
  void resize(int wid, int hig);

  /// Clears the image with a given value, default 0.
  /// @param value  the value to set all pixels to.
  void clear(byte value = 0);

  /// Dumps the image's pixel values row-wise in numbers onto the console.
  /// @attention Should only be used with small images.
  void dump() const;

  // ======================================================
  /// display image in a GLFW window
  void show(std::string title = "Simple RGB Image");
};


#endif /*SIMPLERGBIMAGE_H_*/
