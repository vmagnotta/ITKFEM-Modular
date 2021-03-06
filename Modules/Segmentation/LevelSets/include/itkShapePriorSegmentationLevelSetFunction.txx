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
#ifndef __itkShapePriorSegmentationLevelSetFunction_txx
#define __itkShapePriorSegmentationLevelSetFunction_txx

#include "itkShapePriorSegmentationLevelSetFunction.h"

namespace itk
{
/**
 * Constructor
 */
template< class TImageType, class TFeatureImageType >
ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::ShapePriorSegmentationLevelSetFunction()
{
  m_ShapeFunction = NULL;
  m_ShapePriorWeight = NumericTraits< ScalarValueType >::Zero;
}

/**
 * PrintSelf
 */
template< class TImageType, class TFeatureImageType >
void
ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "ShapeFunction: " << m_ShapeFunction.GetPointer() << std::endl;
  os << indent << "ShapePriorWeight: " << m_ShapePriorWeight << std::endl;
}

/**
 * Compute the equation value.
 */
template< class TImageType, class TFeatureImageType >
typename ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::PixelType
ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::ComputeUpdate(
  const NeighborhoodType & neighborhood,
  void *gd,
  const FloatOffsetType & offset)
{
  // Compute the generic level set update using superclass
  PixelType value = this->Superclass::ComputeUpdate(neighborhood, gd, offset);

  // Add the shape prior term
  if ( m_ShapeFunction && m_ShapePriorWeight != NumericTraits< ScalarValueType >::Zero )
    {
    IndexType                                 idx = neighborhood.GetIndex();
    ContinuousIndex< double, ImageDimension > cdx;
    for ( unsigned int i = 0; i < ImageDimension; ++i )
      {
      cdx[i] = static_cast< double >( idx[i] ) - offset[i];
      }
    typename ShapeFunctionType::PointType point;
    this->GetFeatureImage()->TransformContinuousIndexToPhysicalPoint(cdx, point);

    ScalarValueType shape_term = m_ShapePriorWeight
                                 * ( m_ShapeFunction->Evaluate(point) - neighborhood.GetCenterPixel() );

    value += shape_term;

    // collect max change to be used for calculating the time step
    ShapePriorGlobalDataStruct *globalData = (ShapePriorGlobalDataStruct *)gd;
    globalData->m_MaxShapePriorChange =
      vnl_math_max( globalData->m_MaxShapePriorChange, vnl_math_abs(shape_term) );
    }

  return value;
}

/**
 * Compute the global time step.
 */
template< class TImageType, class TFeatureImageType >
typename ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::TimeStepType
ShapePriorSegmentationLevelSetFunction< TImageType, TFeatureImageType >
::ComputeGlobalTimeStep(void *gd) const
{
  TimeStepType dt;

  ShapePriorGlobalDataStruct *d = (ShapePriorGlobalDataStruct *)gd;

  d->m_MaxAdvectionChange += d->m_MaxPropagationChange + d->m_MaxShapePriorChange;

  if ( vnl_math_abs(d->m_MaxCurvatureChange) > 0.0 )
    {
    if ( d->m_MaxAdvectionChange > 0.0 )
      {
      dt = vnl_math_min( ( this->m_WaveDT / d->m_MaxAdvectionChange ),
                         (    this->m_DT / d->m_MaxCurvatureChange ) );
      }
    else
      {
      dt = this->m_DT / d->m_MaxCurvatureChange;
      }
    }
  else
    {
    if ( d->m_MaxAdvectionChange > 0.0 )
      {
      dt = this->m_WaveDT / d->m_MaxAdvectionChange;
      }
    else
      {
      dt = 0.0;
      }
    }

  double maxScaleCoefficient = 0.0;
  for ( unsigned int i = 0; i < ImageDimension; i++ )
    {
    maxScaleCoefficient = vnl_math_max(this->m_ScaleCoefficients[i], maxScaleCoefficient);
    }
  dt /= maxScaleCoefficient;

  // reset the values
  d->m_MaxAdvectionChange  = 0;
  d->m_MaxPropagationChange = 0;
  d->m_MaxCurvatureChange = 0;
  d->m_MaxShapePriorChange = 0;

  return dt;
}
} // end namespace itk

#endif
