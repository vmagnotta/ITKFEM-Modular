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
#ifndef __itkAnchorUtilities_h
#define __itkAnchorUtilities_h

#include <list>

#include "itkSharedMorphologyUtilities.h"

namespace itk
{
/** \class AnchorUtilities
* \brief functionality in common for anchor openings/closings and
* erosions/dilation
*
**/
template< class TImage, class TBres, class TLine >
int ComputeStartEnd(const typename TImage::IndexType StartIndex,
                    const TLine line,
                    const float tol,
                    const typename TBres::OffsetArray LineOffsets,
                    const typename TImage::RegionType AllImage,
                    unsigned & start,
                    unsigned & end);

template< class TImage, class TBres, class TAnchor, class TLine >
void DoAnchorFace(const TImage * input,
                  TImage * output,
                  typename TImage::PixelType border,
                  TLine line,
                  TAnchor & AnchorLine,
                  typename TBres::OffsetArray LineOffsets,
                  std::vector<typename TImage::PixelType> & inbuffer,
                  std::vector<typename TImage::PixelType> & outbuffer,
                  const typename TImage::RegionType AllImage,
                  const typename TImage::RegionType face);

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkAnchorUtilities.txx"
#endif

#endif
