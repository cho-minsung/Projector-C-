#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "Algorithm.h"
#include "DataStructure.h"
#include "Geometry.h"

std::vector<float> linspace(float start_in, float end_in, int num_in) {
    std::vector<float> linspaced;

    float start = static_cast<float>(start_in);
    float end = static_cast<float>(end_in);
    float num = static_cast<float>(num_in);

    float delta = (end - start) / (num - 1);

    for (int i = 0; i < num - 1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end); // I want to ensure that start and end
                              // are exactly the same as the input
    return linspaced;
}


int main() {
    const int projectionAngleCount = 1000;
    int detectorCount = 1000;
    float detectorWidth = 1.0f;

    std::vector<float> ProjectionAngles = linspace(0, PI, projectionAngleCount);

    float* anglesArray = new float[projectionAngleCount];
    for (int i = 0; i < projectionAngleCount; i++) {
        anglesArray[i] = ProjectionAngles[i];
    }

    float sourceDistance = 500.f;
    float detectorDistance = 500.f;

    int FOVColumnCount = 512;
    int FOVRowCount = 512;

    Geometry geom(
        projectionAngleCount,
        detectorCount,
        detectorWidth,
        anglesArray,
        sourceDistance,
        detectorDistance,
        FOVColumnCount,
        FOVRowCount
    );

    std::cout << "Projection angle count: " << geom.getProjectionAngleCount() << std::endl;
    std::cout << "Detector count: " << geom.getDetectorCount() << std::endl;
    std::cout << "FOV column count: " << geom.getFOVColumnCount() << std::endl;
    std::cout << "FOV row count: " << geom.getFOVRowCount() << std::endl;
    std::cout << "Window x left border: " << geom.getWindowMinX() << std::endl;
    std::cout << "Window y top border: " << geom.getWindowMaxY() << std::endl;

    double phantom[262144];
    float phantomf[262144];

    std::ifstream fileIn("../../modified_shepp_logan_512.bin", std::ios::binary);

    if (fileIn) {
        fileIn.seekg(0, fileIn.end);
        int lengthOfPhantomFile = fileIn.tellg();
        fileIn.seekg(0, fileIn.beg);
        std::cout << "File exists with the length of :" << lengthOfPhantomFile << std::endl;
    }
    else {
        std::cout << "File does not exist." << std::endl;
        return 1;
    }

    fileIn.read(reinterpret_cast<char*>(&phantom), sizeof(double) * 262144);
    fileIn.close();

    std::copy(phantom, phantom + 262144, phantomf);

    DataStructure phantomData(FOVColumnCount, FOVRowCount, phantomf);
    std::cout << "Phantom data width:" << phantomData.getWidth() << std::endl;
    std::cout << "Phantom data height:" << phantomData.getHeight() << std::endl;

    DataStructure sinogramData(detectorCount, projectionAngleCount, 0.0f);

    std::cout << "Data written to sinogram." << std::endl;

    Algorithm forwardProject(&geom, &phantomData, &sinogramData);

    auto start = std::chrono::high_resolution_clock::now();
    forwardProject.runProjection();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of operation: " << duration.count() << std::endl;

    int sinogramSize = sinogramData.getSize();
    std::cout << "sinogram data size: " << sinogramSize << std::endl;

    std::vector<double> sinogramDataDouble;

    for (int i = 0; i < sinogramSize; i++) {
        sinogramDataDouble.push_back((double)sinogramData.getData(i));
    }

    std::ofstream fileOut("sinogram_cleanup.bin", std::ios::out | std::ios::binary);

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