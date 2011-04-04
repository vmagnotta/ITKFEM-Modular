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

#ifndef __itkFEMElement2DC0QuadraticTriangular_h
#define __itkFEMElement2DC0QuadraticTriangular_h

#include "itkFEMElementStd.h"

namespace itk
{
namespace fem
{
/**
 * \class Element2DC0QuadraticTriangular
 * \brief 6-noded, quadratic, C0 continuous finite element in 2D space
 *        that defines a triangle.
 *
 * The ordering of the nodes is counter clockwise. That is the nodes
 * should be defined in the following order:
 *
 *          (0,1)
 *          2
 *          *
 *          |\
 *          |  \
 *          |    \
 *(0,0.5) 5 *      * 4 (0.5, 0.5)
 *          |        \
 *          |          \
 *          *-----*-----*
 *          0     3      1
 *       (0,0)  (0,0.5)  (0,1)
 *
 * This class defines the geometry of the FE problem.
 * It must be combined with the physics component of the problem.
 * This has already been done in the following classes:
 *
 * \sa Element2DC0QuadraticTriangularStrain
 * \sa Element2DC0QuadraticTriangularStress
 */
class Element2DC0QuadraticTriangular : public ElementStd<6, 2>
{
public:
  /** Standard class typedefs. */
  typedef Element2DC0QuadraticTriangular Self;
  typedef ElementStd<6, 2>               TemplatedParentClass;
  typedef TemplatedParentClass           Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(Element2DC0QuadraticTriangular, TemplatedParentClass);

  // ////////////////////////////////////////////////////////////////////////
  /**
   * Methods related to numeric integration
   */

  enum { DefaultIntegrationOrder = 2 };

  virtual void GetIntegrationPointAndWeight(unsigned int i, VectorType & pt, Float & w, unsigned int order) const;

  virtual unsigned int GetNumberOfIntegrationPoints(unsigned int order) const;

  // ////////////////////////////////////////////////////////////////////////
  /**
   * Methods related to the geometry of an element
   */

  virtual VectorType ShapeFunctions(const VectorType & pt) const;

  virtual void ShapeFunctionDerivatives(const VectorType & pt, MatrixType & shapeD) const;

  virtual bool GetLocalFromGlobalCoordinates(const VectorType & GlobalPt, VectorType & LocalPt) const;

  // Since the Jacobian is not quadratic, we need to provide our
  // own implementation of calculating the determinant and inverse.
  virtual Float JacobianDeterminant(const VectorType & pt, const MatrixType *pJ = 0) const;

  virtual void JacobianInverse(const VectorType & pt, MatrixType & invJ, const MatrixType *pJ = 0) const;

protected:
  virtual void PrintSelf(std::ostream& os, Indent indent) const;

  virtual void PopulateEdgeIds(void);

};
}
}  // end namespace itk::fem

#endif  // #ifndef __itkFEMElement2DC0QuadraticTriangular_h
