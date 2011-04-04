itk_module_test()
set(ITK-FEMTests
itkFEMHeaderTest.cxx
itkFEMExceptionTest.cxx
itkFEMElement2DMembraneTest.cxx
itkFEMElement3DMembraneTest.cxx
itkFEMElement2DStrainTest.cxx
itkFEMElement2DQuadraticTriangularTest.cxx
itkFEMLinearSystemWrapperItpackTest.cxx
itkFEMLinearSystemWrapperItpackTest2.cxx
itkFEMLinearSystemWrapperVNLTest.cxx
itkFEMLinearSystemWrapperDenseVNLTest.cxx
itkFEMPArrayTest.cxx
itkFEMElement2DC0LinearTriangleStressTest.cxx
itkFEMElement2DC0LinearQuadrilateralStrainItpackTest.cxx
itkFEMElement2DC0LinearTriangleStrainTest.cxx
itkFEMElement2DC0LinearTriangleMembraneTest.cxx
itkFEMElement2DC0LinearQuadrilateralStressTest.cxx
itkFEMElement2DC0LinearQuadrilateralStrainTest.cxx
itkFEMElement2DC0LinearQuadrilateralMembraneTest.cxx
itkFEMElement2DC0QuadraticTriangleStrainTest.cxx
itkFEMElement2DC0QuadraticTriangleStressTest.cxx
itkFEMElement2DC0LinearLineStressTest.cxx
itkFEMElement2DC1BeamTest.cxx
itkFEMElement3DC0LinearHexahedronStrainTest.cxx
itkFEMElement3DC0LinearHexahedronMembraneTest.cxx
itkFEMElement3DC0LinearTetrahedronStrainTest.cxx
itkFEMElement3DC0LinearTetrahedronMembraneTest.cxx
itkFEMLoadBCMFCTest.cxx
itkFEMLoadBCMFCTestUser.cxx
itkFEMLoadEdgeTest.cxx
itkFEMLoadGravConstTest.cxx
itkFEMLandmarkLoadImplementationTest.cxx
#itkFEMRegistrationFilterTest.cxx
# itkFEMSolverTest2D.cxx
itkFEMSolverTest3D.cxx
itkImageToRectilinearFEMObjectFilter2DTest.cxx
itkImageToRectilinearFEMObjectFilter3DTest.cxx
itkFEMElement2DTest.cxx
itkFEMElement3DTest.cxx
)

CreateTestDriver(ITK-FEM  "${ITK-FEM-Test_LIBRARIES}" "${ITK-FEMTests}")

add_test(NAME itkFEMHeaderTest
      COMMAND ITK-FEMTestDriver itkFEMHeaderTest)
add_test(NAME itkFEMElement2DMembraneTest
      COMMAND ITK-FEMTestDriver itkFEMElement2DMembraneTest)
add_test(NAME itkFEMElement2DQuadraticTriangularTest
      COMMAND ITK-FEMTestDriver itkFEMElement2DQuadraticTriangularTest)
add_test(NAME itkFEMElement2DStrainTest
      COMMAND ITK-FEMTestDriver itkFEMElement2DStrainTest)
add_test(NAME itkFEMElement3DMembraneTest
      COMMAND ITK-FEMTestDriver itkFEMElement3DMembraneTest)
add_test(NAME itkFEMExceptionTest
      COMMAND ITK-FEMTestDriver itkFEMExceptionTest)
add_test(NAME itkFEMLinearSystemWrapperDenseVNLTest
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperDenseVNLTest)
add_test(NAME itkFEMLinearSystemWrapperItpackTest
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest)
add_test(NAME itkFEMLinearSystemWrapperItpackTest1
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              0)
add_test(NAME itkFEMLinearSystemWrapperItpackTest2
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              1)
add_test(NAME itkFEMLinearSystemWrapperItpackTest3
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              2)
add_test(NAME itkFEMLinearSystemWrapperItpackTest4
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              3)
add_test(NAME itkFEMLinearSystemWrapperItpackTest5
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              4)
add_test(NAME itkFEMLinearSystemWrapperItpackTest6
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              5)
add_test(NAME itkFEMLinearSystemWrapperItpackTest7
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest
              6)
add_test(NAME itkFEMLinearSystemWrapperItpackTest8
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              0)
add_test(NAME itkFEMLinearSystemWrapperItpackTest9
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              1)
add_test(NAME itkFEMLinearSystemWrapperItpackTest10
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              2)
add_test(NAME itkFEMLinearSystemWrapperItpackTest11
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              3)
add_test(NAME itkFEMLinearSystemWrapperItpackTest12
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              4)
add_test(NAME itkFEMLinearSystemWrapperItpackTest13
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              5)
add_test(NAME itkFEMLinearSystemWrapperItpackTest14
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperItpackTest2
              6)
add_test(NAME itkFEMLinearSystemWrapperVNLTest
      COMMAND ITK-FEMTestDriver itkFEMLinearSystemWrapperVNLTest)
add_test(NAME itkFEMPArrayTest
      COMMAND ITK-FEMTestDriver itkFEMPArrayTest)


# 3D Element Tests
add_test(NAME itkFEMC0HexahedralElement-NodalLoads-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/hexa2.meta)
add_test(NAME itkFEMC0HexahedralElement-NoLoads
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/hexa3.meta)
add_test(NAME itkFEMC0HexahedralElement-GravityLoad-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/hexa4-grav.meta)
add_test(NAME itkFEMC0TetrahedralElement-NodalLoads-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/tetra2.meta)
add_test(NAME itkFEMC0TetrahedralElement-NoLoads
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/tetra3.meta)
add_test(NAME itkFEMC0TetrahedralElement-GravityLoad-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement3DTest
              ${ITK_DATA_ROOT}/Input/FEM/tetra4-grav.meta)


# 2D Element Tests
add_test(NAME itkFEMC0QuadElement-NodalLoads-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/quad2-small.meta)
add_test(NAME itkFEMC0QuadElement-Strain
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/quad2-strain.meta)
add_test(NAME itkFEMC0QuadElement-NoLoads
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/quad4.meta)
add_test(NAME itkFEMC0QuadElement-GravityLoad-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/quad6-grav.meta)
add_test(NAME itkFEMLoadLandmarkImplementation
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/quad-lm.meta)
add_test(NAME itkFEMC0QuadElementTrapezoidalGeometry-NoLoads
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/trapezoid.meta)
add_test(NAME itkFEMC0TriangularElement-NodalLoads-BCs
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/tri2.meta)
add_test(NAME itkFEMC0TriangularElement-NoLoads
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/tri3.meta)
add_test(NAME itkFEMC0TriangularElement-Strain
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/tri3-e.meta)
add_test(NAME itkFEMC0TriangularElement-Quadratic
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/tri3-q.meta)
add_test(NAME itkFEMTruss
      COMMAND ITK-FEMTestDriver itkFEMElement2DTest
              ${ITK_DATA_ROOT}/Input/FEM/truss.meta)




add_test(NAME itkFEMElement2DC0LinearQuadrilateralStrainTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearQuadrilateralStrainTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearQuadrilateralStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearQuadrilateralStrainTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearQuadrilateralStressTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearQuadrilateralStressTest
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearQuadrilateralStressTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearQuadrilateralMembraneTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearQuadrilateralMembraneTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearQuadrilateralMembraneTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearQuadrilateralMembraneTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearTriangleMembraneTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearTriangleMembraneTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearTriangleMembraneTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearTriangleMembraneTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearTriangleStressTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearTriangleStressTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearTriangleStressTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearTriangleStressTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearTriangleStrainTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearTriangleStrainTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearTriangleStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearTriangleStrainTestWrite.meta)

add_test(NAME itkFEMElement2DC0QuadraticTriangleStrainTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0QuadraticTriangleStrainTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0QuadraticTriangleStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0QuadraticTriangleStrainTestWrite.meta)

add_test(NAME itkFEMElement2DC0QuadraticTriangleStressTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0QuadraticTriangleStressTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0QuadraticTriangleStressTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0QuadraticTriangleStressTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearLineStressTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearLineStressTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearLineStressTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearLineStressTestWrite.meta)

add_test(NAME itkFEMElement2DC0LinearQuadrilateralStrainItpackTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC0LinearQuadrilateralStrainItpackTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearQuadrilateralStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC0LinearQuadrilateralStrainTestWrite.meta)

add_test(NAME itkFEMElement2DC1BeamTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement2DC1BeamTest
         ${ITK_DATA_ROOT}/Input/FEM/2DC1BeamTest.meta
         ${ITK_TEST_OUTPUT_DIR}/2DC1BeamTestWrite.meta)

add_test(NAME itkFEMElement3DC0LinearHexahedronStrainTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement3DC0LinearHexahedronStrainTest
         ${ITK_DATA_ROOT}/Input/FEM/3DC0LinearHexahedronStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/3DC0LinearHexahedronStrainTestWrite.meta)

add_test(NAME itkFEMElement3DC0LinearHexahedronMembraneTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement3DC0LinearHexahedronMembraneTest
         ${ITK_DATA_ROOT}/Input/FEM/3DC0LinearHexahedronMembraneTest.meta
         ${ITK_TEST_OUTPUT_DIR}/3DC0LinearHexahedronMembraneTestWrite.meta)

add_test(NAME itkFEMElement3DC0LinearTetrahedronStrainTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement3DC0LinearTetrahedronStrainTest
         ${ITK_DATA_ROOT}/Input/FEM/3DC0LinearTetrahedronStrainTest.meta
         ${ITK_TEST_OUTPUT_DIR}/3DC0LinearTetrahedronStrainTestWrite.meta)

add_test(NAME itkFEMElement3DC0LinearTetrahedronMembraneTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMElement3DC0LinearTetrahedronMembraneTest
         ${ITK_DATA_ROOT}/Input/FEM/3DC0LinearTetrahedronMembraneTest.meta
         ${ITK_TEST_OUTPUT_DIR}/3DC0LinearTetrahedronMembraneTestWrite.meta)

add_test(NAME itkFEMLoadBCMFCTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMLoadBCMFCTest
         ${ITK_DATA_ROOT}/Input/FEM/LoadBCMFCTest.meta
         ${ITK_TEST_OUTPUT_DIR}/LoadBCMFCTestWrite.meta)

add_test(NAME itkFEMLoadBCMFCTestUser ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMLoadBCMFCTestUser)

add_test(NAME itkFEMLoadEdgeTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMLoadEdgeTest
         ${ITK_DATA_ROOT}/Input/FEM/LoadEdgeTest.meta
         ${ITK_TEST_OUTPUT_DIR}/LoadEdgeTestWrite.meta)

add_test(NAME itkFEMLoadGravConstTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMLoadGravConstTest
         ${ITK_DATA_ROOT}/Input/FEM/LoadGravConstTest.meta
         ${ITK_TEST_OUTPUT_DIR}/LoadGravConstWrite.meta)

add_test(NAME itkFEMLandmarkLoadImplementationTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMLandmarkLoadImplementationTest
         ${ITK_DATA_ROOT}/Input/FEM/quad-lm.meta
         ${ITK_TEST_OUTPUT_DIR}/QuadLandmardkWrite.meta)

#add_test(NAME itkFEMRegistrationFilterTest ${FEM_TESTS3}
#         COMMAND ITK-FEMTestDriver itkFEMRegistrationFilterTest)

#add_test(NAME itkFEMSolverTest2D ${FEM_TESTS3}
#        COMMAND ITK-FEMTestDriver itkFEMSolverTest2D
#        ${ITK_DATA_ROOT}/Input/FEM/2DC0LinearTriangleStressTest.meta
#        ${ITK_TEST_OUTPUT_DIR}/2DC0LinearTriangleStressTestWrite_NewSolver.meta)

add_test(NAME itkFEMSolverTest3D ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkFEMSolverTest3D
         ${ITK_DATA_ROOT}/Input/FEM/3DC0LinearHexahedronMembraneTest.meta
         ${ITK_TEST_OUTPUT_DIR}/3DC0LinearHexahedronMembraneTestWrite_NewSolver.meta)

add_test(NAME itkImageToRectilinearFEMObjectFilter2DTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkImageToRectilinearFEMObjectFilter2DTest
         ${ITK_DATA_ROOT}/Input/circle.png
         20 20 7 7 64 49 3 0 0 0 10 14 7 33 7 28 3 0 0 1 9 8 10 11 12 20 19 33 37 38 46 45)

add_test(NAME itkImageToRectilinearFEMObjectFilter3DTest ${FEM_TESTS3}
         COMMAND ITK-FEMTestDriver itkImageToRectilinearFEMObjectFilter3DTest
         ${ITK_DATA_ROOT}/Input/HeadMRVolumeWithDirection.mhd
         10 10 10 4 6 4 175 96 3 0 0 0 0 10 24 41.5692 0 33 122.497 100.172 0 3 0 0 1 6 5 35 36 41 40 10 12 13 18 17 47 48 53 52 33 46 47 52 51 81 82 87 86)





