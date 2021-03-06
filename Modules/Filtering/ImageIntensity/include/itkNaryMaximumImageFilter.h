/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkNaryMaximumImageFilter_h
#define __itkNaryMaximumImageFilter_h

#include "itkNaryFunctorImageFilter.h"
#include "itkNumericTraits.h"

namespace itk
{
/** \class NaryMaximumImageFilter
 * \brief Implements an operator computing the pixel-wise maximum of several images.
 *
 * This class is parametrized over the types of the input images and the type
 * of the output image.  Numeric conversions (castings) are done by the C++
 * defaults.
 *
 * The pixel type of the output images must have a valid defintion of the
 * operator<. This condition is required because internally this filter will
 * perform an operation similar to:
 *
 *    const OutputPixelType query_value = static_cast<OutputPixelType>(pixel_from_input_n);
 *    if(current_maximum < query_value)
 *      {
 *      current_maximum = query_value;
 *      }
 * (where current_maximum is also of type OutputPixelType)
 *
 * for each of the n input images.
 *
 * For example, this filter could be used directly to find a "maximum projection"
 * of a series of images, often used in preliminary analysis of time-series data.
 *
 * \author Zachary Pincus
 *
 * This filter was contributed by Zachary Pincus from the Department of
 * Biochemistry and Program in Biomedical Informatics at Stanford University
 * School of Medicine
 *
 * \ingroup IntensityImageFilters  Multithreaded
 */

namespace Functor
{
template< class TInput, class TOutput >
class Maximum1
{
public:
  typedef typename NumericTraits< TOutput >::ValueType OutputValueType;
  // not sure if this typedef really makes things more clear... could just use
  // TOutput?

  Maximum1() {}
  ~Maximum1() {}
  inline TOutput operator()(const std::vector< TInput > & B) const
  {
    OutputValueType A = NumericTraits< TOutput >::NonpositiveMin();

    for ( unsigned int i = 0; i < B.size(); i++ )
      {
      if ( A < static_cast< OutputValueType >( B[i] ) )
        {
        A = static_cast< OutputValueType >( B[i] );
        }
      }
    return A;
  }

  bool operator==(const Maximum1 &) const
  {
    return true;
  }

  bool operator!=(const Maximum1 &) const
  {
    return false;
  }
};
}
template< class TInputImage, class TOutputImage >
class ITK_EXPORT NaryMaximumImageFilter:
  public
  NaryFunctorImageFilter< TInputImage, TOutputImage,
                          Functor::Maximum1<  typename TInputImage::PixelType,
                                              typename TInputImage::PixelType > >
{
public:
  /** Standard class typedefs. */
  typedef NaryMaximumImageFilter Self;
  typedef NaryFunctorImageFilter<
    TInputImage, TOutputImage,
    Functor::Maximum1< typename TInputImage::PixelType,
                       typename TInputImage::PixelType > > Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(NaryMaximumImageFilter,
               NaryFunctorImageFilter);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro( InputConvertibleToOutputCheck,
                   ( Concept::Convertible< typename TInputImage::PixelType,
                                           typename TOutputImage::PixelType > ) );
  itkConceptMacro( InputLessThanComparableCheck,
                   ( Concept::LessThanComparable< typename TInputImage::PixelType > ) );
  itkConceptMacro( InputHasNumericTraitsCheck,
                   ( Concept::HasNumericTraits< typename TInputImage::PixelType > ) );
  /** End concept checking */
#endif
protected:
  NaryMaximumImageFilter() {}
  virtual ~NaryMaximumImageFilter() {}
private:
  NaryMaximumImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);         //purposely not implemented
};
} // end namespace itk

#endif
