itk_module_test()
set(ITK-RegionGrowingTests
itkNeighborhoodConnectedImageFilterTest.cxx
itkIsolatedConnectedImageFilterTest.cxx
itkRegionGrowingHeaderTest.cxx
itkConfidenceConnectedImageFilterTest.cxx
itkVectorConfidenceConnectedImageFilterTest.cxx
itkConnectedThresholdImageFilterTest.cxx
)

CreateTestDriver(ITK-RegionGrowing  "${ITK-RegionGrowing-Test_LIBRARIES}" "${ITK-RegionGrowingTests}")

add_test(NAME itkRegionGrowingHeaderTest
      COMMAND ITK-RegionGrowingTestDriver itkRegionGrowingHeaderTest)
add_test(NAME itkNeighborhoodConnectedImageFilterTest
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/NeighborhoodConnectedImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/NeighborhoodConnectedImageFilterTest.png
    itkNeighborhoodConnectedImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/NeighborhoodConnectedImageFilterTest.png 146 167)
add_test(NAME itkIsolatedConnectedImageFilterTest
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/IsolatedConnectedImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/IsolatedConnectedImageFilterTest.png
    itkIsolatedConnectedImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/IsolatedConnectedImageFilterTest.png true 115 85 107 110)
add_test(NAME itkIsolatedConnectedImageFilterTest2
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/IsolatedConnectedImageFilterTest2.png
              ${ITK_TEST_OUTPUT_DIR}/IsolatedConnectedImageFilterTest2.png
    itkIsolatedConnectedImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/IsolatedConnectedImageFilterTest2.png false 175 125 100 170 176 125 101 170)
add_test(NAME itkConfidenceConnectedImageFilterTest
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/ConfidenceConnectedImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/ConfidenceConnectedImageFilterTest.png
    itkConfidenceConnectedImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/ConfidenceConnectedImageFilterTest.png 165 165)
add_test(NAME itkVectorConfidenceConnectedImageFilterTest
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/VectorConfidenceConnectedImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/VectorConfidenceConnectedImageFilterTest.png
    itkVectorConfidenceConnectedImageFilterTest ${ITK_DATA_ROOT}/Input/VisibleWomanEyeSlice.png ${ITK_TEST_OUTPUT_DIR}/VectorConfidenceConnectedImageFilterTest.png 72 44 23 67 5.0 6)
add_test(NAME itkConnectedThresholdImageFilterTest
      COMMAND ITK-RegionGrowingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/ConnectedThresholdImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/ConnectedThresholdImageFilterTest.png
    itkConnectedThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/ConnectedThresholdImageFilterTest.png 165 165 0 150)
add_test(NAME itkConnectedThresholdImageFilterTest2
      COMMAND ITK-RegionGrowingTestDriver
  --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/ConnectedThresholdImageFilterTest2.png
            ${ITK_TEST_OUTPUT_DIR}/ConnectedThresholdImageFilterTest2.png
   itkConnectedThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/8ConnectedImage.bmp
            ${ITK_TEST_OUTPUT_DIR}/ConnectedThresholdImageFilterTest2.png
            29 47 200 255 1)
