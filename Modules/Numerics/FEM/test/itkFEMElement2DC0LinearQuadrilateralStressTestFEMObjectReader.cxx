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

#include "itkFEM.h"
#include "itkFEMObject.h"
#include "itkFEMObjectSpatialObject.h"
#include "itkGroupSpatialObject.h"
#include "itkSpatialObject.h"
#include "itkSpatialObjectReader.h"
#include "itkSpatialObjectWriter.h"

#include <iostream>

//  Example taken from 'Fundamentals of the Finite ELement Method' - Grandin
int itkFEMElement2DC0LinearQuadrilateralStressTestFEMObjectReader(int argc, char *argv[])
{
  //Need to register default FEM object types,
  //and setup SpatialReader to recognize FEM types
  //which is all currently done as a HACK in
  //the initializaiton of the itk::FEMFactoryBase::GetFactory()
  itk::FEMFactoryBase::GetFactory()->RegisterDefaultTypes();

  typedef itk::SpatialObject<2>      SpatialObjectType;
  typedef SpatialObjectType::Pointer SpatialObjectPointer;
  SpatialObjectPointer Spatial = SpatialObjectType::New();

  typedef itk::SpatialObjectReader<2>      SpatialObjectReaderType;
  typedef SpatialObjectReaderType::Pointer SpatialObjectReaderPointer;
  SpatialObjectReaderPointer SpatialReader = SpatialObjectReaderType::New();
  // SpatialReader->SetFileName("C:/Research/ITKGit/ITK/Testing/Data/Input/FEM/SpatialObjects.meta");
  SpatialReader->SetFileName("C:/Research/ITKGit/ITK/Testing/Data/Input/FEM/Trial.meta");
  SpatialReader->Update();

  typedef itk::SpatialObjectWriter<2>      SpatialObjectWriterType;
  typedef SpatialObjectWriterType::Pointer SpatialObjectWriterPointer;
  SpatialObjectWriterPointer SpatialWriter = SpatialObjectWriterType::New();
  SpatialWriter->SetInput(SpatialReader->GetScene() );
  SpatialWriter->SetFileName("C:/Research/ITKGit/ITK/Testing/Data/Input/FEM/TrialWrite.meta");
  SpatialWriter->Update();

  SpatialObjectReaderType::ScenePointer myScene = SpatialReader->GetScene();
  if( !myScene )
    {
    std::cout << "No Scene : [FAILED]" << std::endl;
    return EXIT_FAILURE;
    }
  std::cout << " [PASSED]" << std::endl;

  // Testing the fe mesh validity
  typedef itk::FEMObjectSpatialObject<2>      FEMObjectSpatialObjectType;
  typedef FEMObjectSpatialObjectType::Pointer FEMObjectSpatialObjectPointer;

  FEMObjectSpatialObjectType::ChildrenListType* children = SpatialReader->GetGroup()->GetChildren();
  if( strcmp( (*(children->begin() ) )->GetTypeName(), "FEMObjectSpatialObject") )
    {
    std::cout << " [FAILED]" << std::endl;
    return EXIT_FAILURE;
    }

  FEMObjectSpatialObjectType::Pointer femSO =
    dynamic_cast<FEMObjectSpatialObjectType *>( (*(children->begin() ) ).GetPointer() );

  femSO->GetFEMObject()->Solve();

  float soln[8];
  for( int i = 0; i < 8; i++ )
    {
    soln[i] = femSO->GetFEMObject()->GetSolution(i);
    std::cout << "Solution[" << i << "]:" << soln[i] << std::endl;
    }

  std::cout << "Test PASSED!" << std::endl;
  return EXIT_SUCCESS;
}
