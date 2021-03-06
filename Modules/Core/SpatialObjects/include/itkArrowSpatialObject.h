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
#ifndef __itkArrowSpatialObject_h
#define __itkArrowSpatialObject_h

#if defined( _MSC_VER )
#pragma warning ( disable : 4786 )
#endif

#include "itkSpatialObject.h"

namespace itk
{
/**
 * \class ArrowSpatialObject
 * \brief Representation of a Arrow based on the spatial object classes.
 *
 * A ArrowSpatialObject represents a Arrow by serving as the parent of
 * the elements of the Arrow.  Since any itk::SpatialObject can have
 * children (see SpatialObject::GetChildren()), this class needs no
 * additional methods.
 */

template< unsigned int TDimension = 3 >
class ITK_EXPORT ArrowSpatialObject:
  public SpatialObject< TDimension >
{
public:

  typedef ArrowSpatialObject                 Self;
  typedef SpatialObject< TDimension >        Superclass;
  typedef SmartPointer< Self >               Pointer;
  typedef SmartPointer< const Self >         ConstPointer;
  typedef double                             ScalarType;
  typedef Vector< double, TDimension >       VectorType;
  typedef Point< double, TDimension >        PointType;
  typedef typename Superclass::TransformType TransformType;
  typedef typename TransformType::MatrixType MatrixType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Method for creation through the object factory. */
  itkTypeMacro(ArrowSpatialObject, SpatialObject);

  /** Set the position of the arrow */
  void SetPosition(const PointType & p)
  {
    m_Position = p;
    this->UpdateTransform();
  }

  itkGetConstMacro(Position, PointType);

  void SetPosition(float x, float y)
  {
    m_Position[0] = x;
    m_Position[1] = y;
    this->UpdateTransform();
  }

  void SetPosition(float x, float y, float z)
  {
    m_Position[0] = x;
    m_Position[1] = y;
    m_Position[2] = z;
    this->UpdateTransform();
  }

  /** Set the direction of the arrow */
  void SetDirection(const VectorType & d)
  {
    m_Direction = d;
    this->UpdateTransform();
  }

  itkGetConstMacro(Direction, VectorType);

  void SetDirection(float x, float y)
  {
    m_Direction[0] = x;
    m_Direction[1] = y;
    this->UpdateTransform();
  }

  void SetDirection(float x, float y, float z)
  {
    m_Direction[0] = x;
    m_Direction[1] = y;
    m_Direction[2] = z;
    this->UpdateTransform();
  }

  /** Set the length of the arrow */
  void SetLength(double length);

  void SetLenght(double length)
  {
    itkWarningMacro(
      "Please change your code to use SetLength rather than SetLenght. "
      << "The latter method name was mispelled and the ITK developers failed to correct it before it was released. "
      << "The mispelled method name is retained in order to maintain backward compatibility.");
    this->SetLength(length);
    return;
  }

  /** Get the length of the arrow */
  itkGetConstReferenceMacro(Length, double);

  /** Get the length of the arrow. NOTE the misspelling of
    * length. This method is included for backward compatibility. */
  double GetLenght() const { return this->GetLength(); }

  /** Compute the local bounding box */
  bool ComputeLocalBoundingBox() const;

  /** Returns true if the point is inside the line, false otherwise. */
  bool IsInside(const PointType & point,
                unsigned int depth, char *name) const;

  /** Test whether a point is inside or outside the object
   *  For computational speed purposes, it is faster if the method does not
   *  check the name of the class and the current depth */
  virtual bool IsInside(const PointType & point) const;

protected:

  ArrowSpatialObject();
  virtual ~ArrowSpatialObject();

  /** Update the transformation given the position and the direction */
  void UpdateTransform();

  /** Method to print the object.*/
  virtual void PrintSelf(std::ostream & os, Indent indent) const;

private:
  ArrowSpatialObject(const Self &); //purposely not implemented
  void operator=(const Self &);     //purposely not implemented

  VectorType m_Direction;
  PointType  m_Position;
  double     m_Length;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkArrowSpatialObject.txx"
#endif

#endif // __itkArrowSpatialObject_h
