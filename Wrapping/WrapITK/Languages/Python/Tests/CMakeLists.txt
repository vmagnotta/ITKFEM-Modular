
# configure the test driver
macro(add_python_test name)
  add_test(NAME ${name}
    COMMAND "${ITK_TEST_DRIVER}"
    --add-before-env PYTHONPATH "${WRAP_ITK_PYTHON_BINARY_DIR}/$<CONFIGURATION>"
    --add-before-env PYTHONPATH "${WRAP_ITK_PYTHON_BINARY_DIR}"
    --add-before-env PYTHONPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIGURATION>"
    --add-before-env PYTHONPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    --add-before-libpath "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIGURATION>"
    --add-before-libpath "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    --add-before-libpath "${ITK_DIR}"
    --process "${PYTHON_EXECUTABLE}"
    ${ARGN}
    )
endmacro()


add_python_test(PythonTestDirectory ${CMAKE_CURRENT_SOURCE_DIR}/TestDirectory.py)

add_python_test(PythonTestObject ${CMAKE_CURRENT_SOURCE_DIR}/TestObject.py)

# TODO: drop -E option once all filters/spatial objects/cost functions are actually wrapped
add_python_test(NonBlockingPythonFilterCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -E -b Filter -e ${CMAKE_CURRENT_SOURCE_DIR}/exclude-filters.txt ${ITK_INCLUDE_DIRS})
add_python_test(NonBlockingPythonSpatialObjectCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -E -b SpatialObject ${ITK_INCLUDE_DIRS})
add_python_test(NonBlockingPythonCostFunctionCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -E -b CostFunction ${ITK_INCLUDE_DIRS})

add_python_test(PythonImageIOCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -b ImageIO -e ${CMAKE_CURRENT_SOURCE_DIR}/exclude-imageio.txt ${ITK_INCLUDE_DIRS})
add_python_test(PythonOptimizerCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -b Optimizer ${ITK_INCLUDE_DIRS})
add_python_test(PythonTransformCoverage ${CMAKE_CURRENT_SOURCE_DIR}/wrappingCoverage.py -b Transform -e ${CMAKE_CURRENT_SOURCE_DIR}/exclude-transform.txt ${ITK_INCLUDE_DIRS})

add_python_test(PythonFindEmptyClasses ${CMAKE_CURRENT_SOURCE_DIR}/findEmptyClasses.py)

add_python_test(PythonGetNameOfClass ${CMAKE_CURRENT_SOURCE_DIR}/getNameOfClass.py)

add_python_test(PythonTiming ${CMAKE_CURRENT_SOURCE_DIR}/timing.py)


# some tests will fail if dim=2 and unsigned short are not wrapped
INTERSECTION(WRAP_2 2 "${WRAP_ITK_DIMS}")
if(WRAP_unsigned_short AND WRAP_2)
  add_python_test(PythonTypemaps ${CMAKE_CURRENT_SOURCE_DIR}/typemaps.py)

  add_python_test(PythonTemplate ${CMAKE_CURRENT_SOURCE_DIR}/template.py)

  add_python_test(PythonAutoPipeline
    ${CMAKE_CURRENT_SOURCE_DIR}/auto_pipeline.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    auto_pipeline.png
    3
    --compare auto_pipeline.png ${WrapITK_SOURCE_DIR}/images/MedianImageFilter.png
  )

  add_python_test(PythonTemplatedPipeline
    ${CMAKE_CURRENT_SOURCE_DIR}/templated_pipeline.py
    ${WrapITK_SOURCE_DIR}/images/2th_cthead1.png
    templated_pipeline.png
    10
    --compare templated_pipeline.png ${WrapITK_SOURCE_DIR}/images/templated_pipeline.png
  )

  add_python_test(PythonExtras
    ${CMAKE_CURRENT_SOURCE_DIR}/extras.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png out.png
  )

  add_python_test(PythonModuleToModule
    ${CMAKE_CURRENT_SOURCE_DIR}/module2module.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
  )

  add_python_test(PythonBinaryDilateImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryDilateImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/2th_cthead1.png
    BinaryDilateImageFilter.png
    --compare BinaryDilateImageFilter.png ${WrapITK_SOURCE_DIR}/images/BinaryDilateImageFilter.png
  )

  add_python_test(PythonBinaryErodeImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryErodeImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/2th_cthead1.png
    BinaryErodeImageFilter.png
    --compare BinaryErodeImageFilter.png ${WrapITK_SOURCE_DIR}/images/BinaryErodeImageFilter.png
  )

  add_python_test(PythonBinaryThresholdImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryThresholdImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    BinaryThresholdImageFilter.png
    50 150
    0 65535
    --compare BinaryThresholdImageFilter.png ${WrapITK_SOURCE_DIR}/images/BinaryThresholdImageFilter.png
  )

  add_python_test(PythonCastImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/CastImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    CastImageFilter.png
    --compare CastImageFilter.png ${WrapITK_SOURCE_DIR}/images/cthead1.png
  )

  add_python_test(PythonGrayscaleDilateImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/GrayscaleDilateImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    GrayscaleDilateImageFilter.png
    --compare GrayscaleDilateImageFilter.png ${WrapITK_SOURCE_DIR}/images/GrayscaleDilateImageFilter.png
  )

  add_python_test(PythonBoxGrayscaleDilateImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/BoxGrayscaleDilateImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    BoxGrayscaleDilateImageFilter.png
    --compare BoxGrayscaleDilateImageFilter.png ${WrapITK_SOURCE_DIR}/images/BoxGrayscaleDilateImageFilter.png
  )

#   add_python_test(PythonStrelFromImageGrayscaleDilateImageFilter
#     ${CMAKE_CURRENT_SOURCE_DIR}/StrelFromImageGrayscaleDilateImageFilter.py
#     ${WrapITK_SOURCE_DIR}/images/cthead1.png
#     StrelFromImageGrayscaleDilateImageFilter.png
#     ${WrapITK_SOURCE_DIR}/images/StrelFromImage.png
#     --compare StrelFromImageGrayscaleDilateImageFilter.png ${WrapITK_SOURCE_DIR}/images/StrelFromImageGrayscaleDilateImageFilter.png
#   )

  add_python_test(PythonGrayscaleErodeImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/GrayscaleErodeImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    GrayscaleErodeImageFilter.png
    --compare GrayscaleErodeImageFilter.png ${WrapITK_SOURCE_DIR}/images/GrayscaleErodeImageFilter.png
  )

#   add_python_test(PythonFlatStructuringElementBall
#     ${CMAKE_CURRENT_SOURCE_DIR}/FlatStructuringElement.py
#     Ball-5.png
#     Ball
#     5
#     --compare Ball-5.png ${WrapITK_SOURCE_DIR}/images/Ball-5.png
#   )

#   add_python_test(PythonFlatStructuringElementBox
#     ${CMAKE_CURRENT_SOURCE_DIR}/FlatStructuringElement.py
#     Box-5.png
#     Box
#     5
#     --compare Box-5.png ${WrapITK_SOURCE_DIR}/images/Box-5.png
#   )

#   add_python_test(PythonFlatStructuringElementFromImage
#     ${CMAKE_CURRENT_SOURCE_DIR}/FlatStructuringElement.py
#     StrelFromImage.png
#     FromImage
#     ${WrapITK_SOURCE_DIR}/images/StrelFromImage.png
#     --compare StrelFromImage.png ${WrapITK_SOURCE_DIR}/images/StrelFromImage.png
#   )

  add_python_test(PythonMeanImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/MeanImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    MeanImageFilter.png
    3
    --compare MeanImageFilter.png ${WrapITK_SOURCE_DIR}/images/MeanImageFilter.png
  )

  add_python_test(PythonMedianImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/MedianImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    MedianImageFilter.png
    3
    --compare MedianImageFilter.png ${WrapITK_SOURCE_DIR}/images/MedianImageFilter.png
  )

  add_python_test(PythonSigmoidImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/SigmoidImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    SigmoidImageFilter.png
    10 240 10 170
    --compare SigmoidImageFilter.png ${WrapITK_SOURCE_DIR}/images/SigmoidImageFilter.png
  )

  add_python_test(PythonThresholdImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/ThresholdImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    ThresholdImageFilter.png
    150 150
    --compare ThresholdImageFilter.png ${WrapITK_SOURCE_DIR}/images/ThresholdImageFilter.png
  )

  add_python_test(PythonResampleImageFilterTest1
    --compare ResampleImageFilterTest1.png
              ${WrapITK_SOURCE_DIR}/images/ResampleImageFilterTest1.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ResampleImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ResampleImageFilterTest1.png
          0
  )

  add_python_test(PythonResampleImageFilterTest2
    --compare ResampleImageFilterTest2.png
              ${WrapITK_SOURCE_DIR}/images/ResampleImageFilterTest2.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ResampleImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ResampleImageFilterTest2.png
          1
  )

  add_python_test(PythonResampleImageFilterTest3
    --compare ResampleImageFilterTest3.png
              ${WrapITK_SOURCE_DIR}/images/ResampleImageFilterTest3.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ResampleImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ResampleImageFilterTest3.png
          2
  )

  add_python_test(PythonResampleImageFilterTest4
    --compare ResampleImageFilterTest4.png
              ${WrapITK_SOURCE_DIR}/images/ResampleImageFilterTest4.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ResampleImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ResampleImageFilterTest4.png
          3
  )

endif(WRAP_unsigned_short AND WRAP_2)


if(WRAP_float AND WRAP_2)
  add_python_test(PythonCurvatureAnisotropicDiffusionImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/CurvatureAnisotropicDiffusionImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    CurvatureAnisotropicDiffusionImageFilter.png
    5 0.125 3
  )

  add_python_test(PythonCurvatureFlowImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/CurvatureFlowImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    CurvatureFlowImageFilter.png
    5 0.125 1.0
  )

  add_python_test(PythonSmoothingRecursiveGaussianImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/SmoothingRecursiveGaussianImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    SmoothingRecursiveGaussianImageFilter.png
    3
  )

  add_python_test(PythonLaplacianImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/LaplacianImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    LaplacianImageFilter.png
  )

  add_python_test(PythonFFTImageFilter
    ${CMAKE_CURRENT_SOURCE_DIR}/FFTImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/cthead1.png
    FFTImageFilterReal.png
    FFTImageFilterImaginary.png
    --compare FFTImageFilterReal.png ${WrapITK_SOURCE_DIR}/images/FFTImageFilterReal.png
    --compare FFTImageFilterImaginary.png ${WrapITK_SOURCE_DIR}/images/FFTImageFilterImaginary.png
#     --compare complexImage.mhd ${WrapITK_SOURCE_DIR}/images/complexImage.mhd
  )

  add_python_test( PythonGradientMagnitudeRecursiveGaussianImageFilterTest
    ${CMAKE_CURRENT_SOURCE_DIR}/GradientMagnitudeRecursiveGaussianImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
    GradientMagnitudeRecursiveGaussianImageFilter.png
    5
    --compare GradientMagnitudeRecursiveGaussianImageFilter.png
            ${WrapITK_SOURCE_DIR}/images/GradientMagnitudeRecursiveGaussianImageFilter.png
  )

  add_python_test( PythonGradientAnisotropicDiffusionImageFilterTest
    ${CMAKE_CURRENT_SOURCE_DIR}/GradientAnisotropicDiffusionImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
    GradientAnisotropicDiffusionImageFilter.png
    5 0.125 1.0
    --compare GradientAnisotropicDiffusionImageFilter.png
              ${WrapITK_SOURCE_DIR}/images/GradientAnisotropicDiffusionImageFilter.png
  )


# TODO: reenable the geodesic test once we get why the result is not the
# same than with c++
# keep just one to be sure it run, but don't compare the images

  add_python_test( PythonGeodesicActiveContourLeftVentricleTest
#     --compare GeodesicActiveContourLeftVentricleTest.png
#             ${WrapITK_SOURCE_DIR}/images/GeodesicActiveContourLeftVentricleTest.png
    --
    ${CMAKE_CURRENT_SOURCE_DIR}/GeodesicActiveContourImageFilter.py
    ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
    GeodesicActiveContourLeftVentricleTest.png
    81 114 5.0 1.0 -0.5 3.0 2.0
  )

#   add_python_test( PythonGeodesicActiveContourWhiteMatterTest
#     --compare GeodesicActiveContourWhiteMatterTest.png
#             ${WrapITK_SOURCE_DIR}/images/GeodesicActiveContourWhiteMatterTest.png
#     --
#     ${CMAKE_CURRENT_SOURCE_DIR}/GeodesicActiveContourImageFilter.py
#     ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
#     GeodesicActiveContourWhiteMatterTest.png
#     56 92 5.0 1.0 -0.3 2.0 10.0
#   )

#   add_python_test( PythonGeodesicActiveContourGrayMatterTest
#     --compare GeodesicActiveContourGrayMatterTest.png
#             ${WrapITK_SOURCE_DIR}/images/GeodesicActiveContourGrayMatterTest.png
#     --
#     ${CMAKE_CURRENT_SOURCE_DIR}/GeodesicActiveContourImageFilter.py
#     ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
#     GeodesicActiveContourGrayMatterTest.png
#     40 90 5.0 .5 -0.3 2.0 10.0
#   )


  add_python_test(PythonFastMarchingLeftVentricleTest
    --compare FastMarchingLeftVentricleTest.png
              ${WrapITK_SOURCE_DIR}/images/FastMarchingLeftVentricleTest.png
    --
    ${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          FastMarchingLeftVentricleTest.png
          81 114 1.0 -0.5 3.0 100 100
  )

  add_python_test(PythonFastMarchingRightVentricleTest
    --compare FastMarchingRightVentricleTest.png
              ${WrapITK_SOURCE_DIR}/images/FastMarchingRightVentricleTest.png
    --
    ${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          FastMarchingRightVentricleTest.png
          99 114 1.0 -0.5 3.0 100 100
  )

  add_python_test(PythonFastMarchingWhiteMatterTest
    --compare FastMarchingWhiteMatterTest.png
              ${WrapITK_SOURCE_DIR}/images/FastMarchingWhiteMatterTest.png
    --
    ${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          FastMarchingWhiteMatterTest.png
          56 92 1.0 -0.3 2.0 200 100
  )

  add_python_test(PythonFastMarchingGrayMatterTest
    --compare FastMarchingGrayMatterTest.png
              ${WrapITK_SOURCE_DIR}/images/FastMarchingGrayMatterTest.png
    --
    ${CMAKE_CURRENT_SOURCE_DIR}/FastMarchingImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          FastMarchingGrayMatterTest.png
          40 90 .5 -0.3 2.0 200 100
  )

  add_python_test(PythonThresholdSegmentationLevelSetVentricleTest
    --compare ThresholdSegmentationLevelSetVentricleTest.png
              ${WrapITK_SOURCE_DIR}/images/ThresholdSegmentationLevelSetVentricleTest.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ThresholdSegmentationLevelSetImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ThresholdSegmentationLevelSetVentricleTest.png
          81 112 5 210 250
  )

  add_python_test(PythonThresholdSegmentationLevelSetWhiteMatterTest
    --compare ThresholdSegmentationLevelSetWhiteMatterTest.png
              ${WrapITK_SOURCE_DIR}/images/ThresholdSegmentationLevelSetWhiteMatterTest.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ThresholdSegmentationLevelSetImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ThresholdSegmentationLevelSetWhiteMatterTest.png
          60 116 5 150 180
  )

  add_python_test(PythonThresholdSegmentationLevelSetGrayMatterTest
    --compare ThresholdSegmentationLevelSetGrayMatterTest.png
              ${WrapITK_SOURCE_DIR}/images/ThresholdSegmentationLevelSetGrayMatterTest.png
    ${CMAKE_CURRENT_SOURCE_DIR}/ThresholdSegmentationLevelSetImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/BrainProtonDensitySlice.png
          ThresholdSegmentationLevelSetGrayMatterTest.png
          107 69 5 180 210
  )

  add_python_test(PythonCannyEdgeDetectionImageFilterTest
    --compareNumberOfPixelsTolerance 1
    --compare CannyEdgeDetectionImageFilter.png
              ${WrapITK_SOURCE_DIR}/images/CannyEdgeDetectionImageFilter.png
    ${CMAKE_CURRENT_SOURCE_DIR}/CannyEdgeDetectionImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/cthead1.png
          CannyEdgeDetectionImageFilter.png
          9
  )

  add_python_test(PythonWatershedSegmentation1
    --compare WatershedSegmentation1.png
              ${WrapITK_SOURCE_DIR}/images/WatershedSegmentation1.png
    ${CMAKE_CURRENT_SOURCE_DIR}/WatershedSegmentation1.py
          ${WrapITK_SOURCE_DIR}/images/VisibleWomanEyeSlice.png
          WatershedSegmentation1.png
  )

  add_python_test(PythonSpatialObject
    --compare SpatialObject.png
              ${WrapITK_SOURCE_DIR}/images/SpatialObject.png
    ${CMAKE_CURRENT_SOURCE_DIR}/SpatialObjectTest.py
          SpatialObject.png
  )

endif(WRAP_float AND WRAP_2)


INTERSECTION(WRAP_3 3 "${WRAP_ITK_DIMS}")
if(WRAP_float AND WRAP_3)
  add_python_test(PythonAntiAliasBinaryImageFilterTest
    --compare AntiAliasBinaryImageFilter.png
              ${WrapITK_SOURCE_DIR}/images/AntiAliasBinaryImageFilter.png
     ${CMAKE_CURRENT_SOURCE_DIR}/AntiAliasBinaryImageFilter.py
          ${WrapITK_SOURCE_DIR}/images/VentricleModel.png
          AntiAliasBinaryImageFilter.png
          .001 50
  )
endif(WRAP_float AND WRAP_3)


UNIQUE(types "${WRAP_ITK_SCALAR};UC")
# signed char can't be used to store an image with values up to 255
list(REMOVE_ITEM types SC)
foreach(d ${WRAP_ITK_DIMS})
  foreach(t ${types})
    add_python_test(PythonSimplePipeline${t}${d}
      ${CMAKE_CURRENT_SOURCE_DIR}/simple_pipeline.py
      ${t}
      ${d}
      ${WrapITK_SOURCE_DIR}/images/cthead1.png
      simple_pipeline${t}${d}.nrrd
      --compare simple_pipeline${t}${d}.nrrd ${WrapITK_SOURCE_DIR}/images/cthead1.png
    )
  endforeach(t)
endforeach(d)
