
/*
    Copyright 2012 Andrew Perrault and Saurav Kumar.

    This file is part of DetectText.

    DetectText is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DetectText is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DetectText.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <cassert>
#include <fstream>
#include "TextDetection.h"
#include <opencv2/opencv.hpp>
#include <exception>

void convertToFloatImage ( cv::Mat byteImage, cv::Mat floatImage )
{
  byteImage.convertTo(floatImage, CV_32F);
}

class FeatureError : public std::exception
{
std::string message;
public:
FeatureError ( const std::string & msg, const std::string & file )
{
  std::stringstream ss;

  ss << msg << " " << file;
  message = msg.c_str ();
}
~FeatureError () throw ( )
{
}
};

cv::Mat loadByteImage ( const char * name )
{
  cv::Mat image = cv::imread( name );
  
  cv::cvtColor( image, image, cv::COLOR_BGR2RGB );
  return image;
}

cv::Mat loadFloatImage ( const char * name )
{
  cv::Mat image = cv::imread ( name );

  cv::cvtColor ( image, image, cv::COLOR_BGR2RGB );
  cv::Mat floatingImage;
  
  convertToFloatImage(image, floatingImage);
  
  return floatingImage;
}

int mainTextDetection ( int argc, char * * argv )
{
  cv::Mat byteQueryImage = loadByteImage ( argv[1] );
  
  std::cout << byteQueryImage.size << std::endl;

  // Detect text in the image
  int x = atoi(argv[3]);
  cv::Mat output = textDetection ( byteQueryImage,  x);
  cv::imwrite(argv[2], output);
  return 0;
}

int main ( int argc, char * * argv )
{
  if ( ( argc != 4 ) )
  {
    printf ( "usage: %s imagefile resultImage darkText\n",
             argv[0] );

    return -1;
  }
  return mainTextDetection ( argc, argv );
}
