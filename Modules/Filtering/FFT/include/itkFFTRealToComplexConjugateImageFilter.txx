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
#ifndef __itkFFTRealToComplexConjugateImageFilter_txx
#define __itkFFTRealToComplexConjugateImageFilter_txx
#include "itkMetaDataObject.h"

#include "itkVnlFFTRealToComplexConjugateImageFilter.h"

#if defined( USE_FFTWD ) || defined( USE_FFTWF )
#include "itkFFTWRealToComplexConjugateImageFilter.h"
#endif

namespace itk
{

template <typename TSelfPointer, unsigned int VDimension, typename TPixel>
struct DispatchFFTW_R2C_New
{
  static TSelfPointer apply()
    {
      return VnlFFTRealToComplexConjugateImageFilter< TPixel, VDimension >
        ::New().GetPointer();
    }
};

#ifdef USE_FFTWD
template <typename TSelfPointer, unsigned int VDimension>
struct DispatchFFTW_R2C_New<TSelfPointer, VDimension, double>
{
  static TSelfPointer apply()
    {
      return FFTWRealToComplexConjugateImageFilter< double, VDimension >
        ::New().GetPointer();
    }
};
#endif

#ifdef USE_FFTWF
template <typename TSelfPointer, unsigned int VDimension>
struct DispatchFFTW_R2C_New<TSelfPointer, VDimension, float>
{
  static TSelfPointer apply()
    {
      return FFTWRealToComplexConjugateImageFilter< float, VDimension >
        ::New().GetPointer();
    }
};
#endif

template< class TPixel, unsigned int VDimension >
typename FFTRealToComplexConjugateImageFilter< TPixel, VDimension >::Pointer
FFTRealToComplexConjugateImageFilter< TPixel, VDimension >
::New(void)
{
  Pointer smartPtr = ::itk::ObjectFactory< Self >::Create();

  if ( smartPtr.IsNull() )
    {
    smartPtr = DispatchFFTW_R2C_New<Pointer, VDimension, TPixel>::apply();
    }

  return smartPtr;
}

template< class TPixel, unsigned int VDimension >
void
FFTRealToComplexConjugateImageFilter< TPixel, VDimension >
::GenerateOutputInformation()
{
  // call the superclass' implementation of this method
  Superclass::GenerateOutputInformation();
  //
  // If this implementation returns a full result
  // instead of a 'half-complex' matrix, then none of this
  // is necessary
  if ( this->FullMatrix() )
    {
    return;
    }

  // get pointers to the input and output
  typename TInputImageType::ConstPointer inputPtr  = this->GetInput();
  typename TOutputImageType::Pointer outputPtr = this->GetOutput();

  if ( !inputPtr || !outputPtr )
    {
    return;
    }

  //
  // This is all based on the same function in itk::ShrinkImageFilter
  // ShrinkImageFilter also modifies the image spacing, but spacing
  // has no meaning in the result of an FFT.
  unsigned int i;
  const typename TInputImageType::SizeType &   inputSize =
    inputPtr->GetLargestPossibleRegion().GetSize();
  const typename TInputImageType::IndexType &  inputStartIndex =
    inputPtr->GetLargestPossibleRegion().GetIndex();

  typename TOutputImageType::SizeType outputSize;
  typename TOutputImageType::IndexType outputStartIndex;

  //
  // in 4.3.4 of the FFTW documentation, they indicate the size of
  // of a real-to-complex FFT is N * N ... + (N /2+1)
  //                              1   2        d
  // complex numbers.
  // static_cast prob. not necessary but want to make sure integer
  // division is used.
  outputSize[0] = static_cast< unsigned int >( inputSize[0] ) / 2 + 1;
  outputStartIndex[0] = inputStartIndex[0];

  for ( i = 1; i < TOutputImageType::ImageDimension; i++ )
    {
    outputSize[i] = inputSize[i];
    outputStartIndex[i] = inputStartIndex[i];
    }
  //
  // the halving of the input size hides the actual size of the input.
  // to get the same size image out of the IFFT, need to send it as
  // Metadata.
  typedef typename TOutputImageType::SizeType::SizeValueType SizeScalarType;
  itk::MetaDataDictionary & OutputDic = outputPtr->GetMetaDataDictionary();
  itk::EncapsulateMetaData< SizeScalarType >(OutputDic,
                                             std::string("FFT_Actual_RealImage_Size"),
                                             inputSize[0]);
  typename TOutputImageType::RegionType outputLargestPossibleRegion;
  outputLargestPossibleRegion.SetSize(outputSize);
  outputLargestPossibleRegion.SetIndex(outputStartIndex);

  outputPtr->SetLargestPossibleRegion(outputLargestPossibleRegion);
}

template< class TPixel, unsigned int VDimension >
void
FFTRealToComplexConjugateImageFilter< TPixel, VDimension >
::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // get pointers to the inputs
  typename TInputImageType::Pointer input  =
    const_cast< TInputImageType * >( this->GetInput() );

  if ( !input )
    {
    return;
    }

  input->SetRequestedRegionToLargestPossibleRegion();
}

template< class TPixel, unsigned int VDimension >
void
FFTRealToComplexConjugateImageFilter< TPixel, VDimension >
::EnlargeOutputRequestedRegion(DataObject *output)
{
  Superclass::EnlargeOutputRequestedRegion(output);
  output->SetRequestedRegionToLargestPossibleRegion();
}
}
#endif
