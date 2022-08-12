// ProjectorCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <stdlib.h>

#include "FanFlatProjectionGeometry2D.h"
#include "FanFlatBeamLineKernelProjector2D.h"
#include "VolumeGeometry2D.h"
#include "Float32VolumeData2D.h"
#include "Float32ProjectionData2D.h"
#include "Float32Data2D.h"
#include "ForwardProjectionAlgorithm.h"

std::vector<float> linspace(float start_in, float end_in, int num_in)
{

    std::vector<float> linspaced;

    float start = static_cast<float>(start_in);
    float end = static_cast<float>(end_in);
    float num = static_cast<float>(num_in);

    //if (num == 0) { return linspaced; }
    //if (num == 1)
    //{
    //    linspaced.push_back(start);
    //    return linspaced;
    //}

    float delta = (end - start) / (num - 1);

    for (int i = 0; i < num - 1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end); // I want to ensure that start and end
                              // are exactly the same as the input
    return linspaced;
}

int main(int argc, char* argv[])
{
    /*
    workflow:
    1. create projector(
        'line_fanflat',
        'fanflat', 'DetectorWidth', 'DetectorCount', 'ProjectionAngles', 'DistanceOriginSource', 'DistanceOriginDetector'
        'GridRowCount', 'GridColCount')
        return projector.create(config)
    4. load data
    5. create sino
    */
    const int projectionAngleCount = 1000;
    int detectorCount = 1000;
    std::vector<float> ProjectionAngles = linspace(0, PI, projectionAngleCount);
    
    float anglesArray[projectionAngleCount];

    for (int i = 0; i < projectionAngleCount; i++) {
        anglesArray[i] = ProjectionAngles[i];
    }

    // create_proj_geom
    CFanFlatProjectionGeometry2D testGeom(
        projectionAngleCount,
        detectorCount,
        1.0f,
        anglesArray,
        500.0f,
        500.0f
        );

    std::cout << "Initialized: " << testGeom.isInitialized() << std::endl;
    std::cout << "Detector count: " << testGeom.getDetectorCount() << std::endl;
    std::cout << "Detector width: " << testGeom.getDetectorWidth() << std::endl;
    std::cout << "Projection angles: ";
    std::cout << "Source distance: " << testGeom.getOriginSourceDistance() << std::endl;
    std::cout << "Detector distance: " << testGeom.getOriginDetectorDistance() << std::endl;

    std::cout << std::setw(50) << std::setfill('-') << "Projeciton test passed." << std::endl;

    int gridColumnCount = 512;
    int gridRowCount = 512;

    // create_vol_geom
    CVolumeGeometry2D testVolume(
        gridColumnCount,
        gridRowCount
        );

    std::cout << "Initialized: " << testVolume.isInitialized() << std::endl;
    std::cout << "Grid column count: " << testVolume.getGridColCount() << std::endl;
    std::cout << "Grid row count: " << testVolume.getGridRowCount() << std::endl;
    std::cout << "grid total count: " << testVolume.getGridTotCount() << std::endl;
    std::cout << "window length x: " << testVolume.getWindowLengthX() << std::endl;
    std::cout << "window length y: " << testVolume.getWindowLengthY() << std::endl;
    std::cout << "window area: " << testVolume.getWindowArea() << std::endl;
    std::cout << "pixel length x: " << testVolume.getPixelLengthX() << std::endl;
    std::cout << "pixel length y: " << testVolume.getPixelLengthY() << std::endl;
    std::cout << "pixel area: " << testVolume.getPixelArea() << std::endl;
    std::cout << "window minimum x: " << testVolume.getWindowMinX() << std::endl;
    std::cout << "window maximum x: " << testVolume.getWindowMaxX() << std::endl;
    std::cout << "window minimum y: " << testVolume.getWindowMinY() << std::endl;
    std::cout << "window maximum y: " << testVolume.getWindowMaxY() << std::endl;

    std::cout << std::setw(50) << std::setfill('-') << "Volume test passed." << std::endl;

    // create_projector
    CFanFlatBeamLineKernelProjector2D testProjector(
        &testGeom,
        &testVolume
        );

    std::cout << "Initialized: " << testProjector.isInitialized() << std::endl;
    std::cout << std::setw(50) << std::setfill('-') << "Projector test passed." << std::endl;

    double phantom[262144];
    float phantomf[262144];

    std::ifstream fileIn("modified_shepp_logan_512.bin", std::ios::binary);

    if (fileIn) {
        fileIn.seekg(0, fileIn.end);
        int lengthOfPhantomFile = fileIn.tellg();
        fileIn.seekg(0, fileIn.beg);
        std::cout << "File exists with the length of :" << lengthOfPhantomFile << std::endl;
    }
    else {
        std::cout << "File does not exist." << std::endl;
    }

    fileIn.read(reinterpret_cast<char*>(&phantom), sizeof(double) * 262144);
    fileIn.close();

    std::copy(phantom, phantom + 262144, phantomf);

    CFloat32VolumeData2D volumeData (&testVolume, phantomf);
    volumeData.updateStatistics();

    std::cout << "Initialized: " << volumeData.isInitialized() << std::endl;
    std::cout << "Dimension: " << volumeData.getDimensionCount() << std::endl;
    std::cout << "Type: " << volumeData.getType() << std::endl;
    std::cout << "Width: " << volumeData.getWidth() << std::endl;
    std::cout << "Height: " << volumeData.getHeight() << std::endl;
    std::cout << "Size: " << volumeData.getSize() << std::endl;
    std::cout << "Global minumum: " << volumeData.getGlobalMin() << std::endl;
    std::cout << "Global maximum: " << volumeData.getGlobalMax() << std::endl;
    std::cout << "Global mean: " << volumeData.getGlobalMean() << std::endl;

    std::cout << std::setw(50) << std::setfill('-') << "Volume data test passed." << std::endl;

    CFloat32ProjectionData2D projectionData(&testGeom, 0.f);
    projectionData.updateStatistics();

    std::cout << "Initialized: " << projectionData.isInitialized() << std::endl;
    std::cout << "Detector count: " << projectionData.getDetectorCount() << std::endl;
    std::cout << "Angle count: " << projectionData.getAngleCount() << std::endl;
    std::cout << "Type: " << projectionData.getType() << std::endl;
    std::cout << "Width: " << projectionData.getWidth() << std::endl;
    std::cout << "Height: " << projectionData.getHeight() << std::endl;
    std::cout << "Size: " << projectionData.getSize() << std::endl;
    std::cout << "Global minumum: " << projectionData.getGlobalMin() << std::endl;
    std::cout << "Global maximum: " << projectionData.getGlobalMax() << std::endl;
    std::cout << "Global mean: " << projectionData.getGlobalMean() << std::endl;

    std::cout << std::setw(50) << std::setfill('-') << "Projection data test passed." << std::endl;


    CForwardProjectionAlgorithm forwardProjectionAlgorithm(
        &testProjector,
        &volumeData,
        &projectionData
    );

    std::cout << std::setw(50) << std::setfill('-') << "Starting forward project algorithm." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    forwardProjectionAlgorithm.run();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of operation: " << duration.count() << std::endl;

    int projectionSize = projectionData.getSize();

    std::vector<double> sinogramDataDouble;

    for (int i = 0; i < projectionSize; i++) {
        sinogramDataDouble.push_back((double)projectionData.getData(i));
    }

    std::ofstream fileOut("sinogram.bin", std::ios::out | std::ios::binary);

    if (fileOut) {
        fileOut.write(reinterpret_cast<const char*>(&sinogramDataDouble[0]), sinogramDataDouble.size() * sizeof(double));
        std::cout << "File write complete." << std::endl;
    }
    else {
        std::cout << "File does not exist." << std::endl;
    }
    fileOut.close();

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
