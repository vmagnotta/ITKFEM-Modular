/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    ImageReadImageSeriesWrite.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

//  Software Guide : BeginLatex
//  
//  This example illustrates how to save an image using the
//  \doxygen{ImageSeriesWriter}. This class allows to save a 3D volume as a set
//  of files containting one 2D slice per file.
//
//  \index{itk::ImageFileReader!header}
//  \index{itk::ImageSeriesWriter!header}
//
//  Software Guide : EndLatex 


#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageSeriesWriter.h"

int main( int argc, char *argv[] )
{
  if (argc < 3 )
    {
    std::cout << "Usage: ImageReadImageSeriesWrite inputFile outputPrefix" << std::endl;
    return EXIT_FAILURE;
    }


  //  Software Guide : BeginLatex
  //
  //  The type of the input image is declared here and it is used for declaring
  //  the type of the reader. This will be a conventional 3D image reader. 
  //
  //  Software Guide : EndLatex 

  // Software Guide : BeginCodeSnippet
  typedef itk::Image< unsigned char, 3 >      ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;
  // Software Guide : EndCodeSnippet



  //  Software Guide : BeginLatex
  //
  //  The reader object is constructed using the \code{New()} operator and
  //  assigning the result to a \code{SmartPointer}. The filename of the 3D
  //  volume to be read is taken from the command line arguments and passed to
  //  the reader using the \code{SetFileName()} method.
  //
  //  Software Guide : EndLatex 

  // Software Guide : BeginCodeSnippet
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  // Software Guide : EndCodeSnippet
  


  //  Software Guide : BeginLatex
  //
  //  The type of the writer must be instantiated taking into account that the
  //  input file is a 3D volume and the output files are 2D images.
  //  Additionally, the output of the reader is connected as input to the
  //  writer.
  //
  //  Software Guide : EndLatex 


  // Software Guide : BeginCodeSnippet
  typedef itk::Image< unsigned char, 2 >     Image2DType;

  typedef itk::ImageSeriesWriter< ImageType, Image2DType > WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetInput( reader->GetOutput() );
  // Software Guide : EndCodeSnippet


  //  Software Guide : BeginLatex
  //
  //  The writer requires a string in the form of a \code{printf()} format in
  //  order to have a template for generating the filenames of all the output
  //  slices. Here we compose this string using a prefix taken from the command
  //  line arguments and adding the extension for PNG files.
  //
  //  Software Guide : EndLatex 


  // Software Guide : BeginCodeSnippet
  std::string format = argv[2];
  format += "%03d.png";
  // Software Guide : EndCodeSnippet


  //  Software Guide : BeginLatex
  //
  //  Finally we trigger the execution of the pipeline with the Update()
  //  method on the writer. At this point the slices of the image will be
  //  saved in individual files containing a single slice per file.
  //
  //  Software Guide : EndLatex 


  // Software Guide : BeginCodeSnippet
  writer->SetSeriesFormat( format.c_str() );
  writer->SetStartIndex( 0 );
  writer->SetIncrementIndex( 1 );
  // Software Guide : EndCodeSnippet



  //  Software Guide : BeginLatex
  //
  //  Finally we trigger the execution of the pipeline with the Update()
  //  method on the writer. At this point the slices of the image will be
  //  saved in individual files containing a single slice per file.
  //
  //  Software Guide : EndLatex 

  // Software Guide : BeginCodeSnippet
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception thrown while reading the image" << std::endl;
    std::cerr << excp << std::endl;
    }
  // Software Guide : EndCodeSnippet


  return EXIT_SUCCESS;
}


