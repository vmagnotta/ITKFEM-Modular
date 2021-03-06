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
#ifndef __itkFEMElement3DC0LinearTetrahedron_h
#define __itkFEMElement3DC0LinearTetrahedron_h

#include "itkFEMElementStd.h"
//to make some checks in GetLocalFromGlobalCoordinates
#include <vnl/vnl_matrix.h>
#include <vnl/algo/vnl_matrix_inverse.h>

namespace itk
{
namespace fem
{
/**
 * \class Element3DC0LinearTetrahedron
 * \brief 4-noded, linear, C0 continuous finite element in 3D space.
 *
 * The ordering of the nodes should be defined in the following order:
 *
 *            (1,0,1)
 *               3
 *               *
 *              /|\
 *             / | \
 *            /  |  \
 * (0,0,0) 0 *-- | --* 2 (2,0,0)
 *            \  |  /
 *             \ | /
 *              \|/
 *               *
 *               1
 *            (1,1,0)
 *
 *
 * This is an abstract class. Specific concrete implemenations of this 
 * It must be combined with the physics component of the problem. 
 * This has already been done in the following classes: 
 *
 * \sa Element3DC0LinearTetrahedronMembrane
 * \sa Element3DC0LinearTetrahedronStrain
 *
 *
 */
class Element3DC0LinearTetrahedron:public ElementStd< 4, 3 >
{
public:
  /** Standard class typedefs. */
  typedef Element3DC0LinearTetrahedron        Self;
  typedef ElementStd< 4, 3 >                  TemplatedParentClass;
  typedef TemplatedParentClass                Superclass;
  typedef SmartPointer< Self >                Pointer;
  typedef SmartPointer< const Self >          ConstPointer;
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(Element3DC0LinearTetrahedron, TemplatedParentClass);
  
  //////////////////////////////////////////////////////////////////////////
  /**
   * Methods related to numeric integration
   */
   
  enum { DefaultIntegrationOrder = 1 };
  
  virtual void GetIntegrationPointAndWeight(unsigned int i, VectorType & pt, Float & w, unsigned int order) const;

  virtual unsigned int GetNumberOfIntegrationPoints(unsigned int order) const;
  
  //////////////////////////////////////////////////////////////////////////
  /**
   * Methods related to the geometry of an element
   */

  virtual VectorType ShapeFunctions(const VectorType & pt) const;

  virtual void ShapeFunctionDerivatives(const VectorType & pt, MatrixType & shapeD) const;

  virtual bool GetLocalFromGlobalCoordinates(const VectorType & globalPt, VectorType & localPt) const;

  
protected:
  virtual void PrintSelf(std::ostream& os, Indent indent) const;  
  virtual void PopulateEdgeIds(void);
  
  
};
}
}  // end namespace itk::fem

#endif  // #ifndef __itkFEMElement3DC0LinearTetrahedron_h
