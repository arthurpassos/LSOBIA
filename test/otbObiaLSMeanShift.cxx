/*
 * Copyright (C) 2005-2018 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>

#include "otbObiaLSMeanShiftScheduler.txx"
#include "otbVectorImage.h"

int otbObiaLSMeanShift(int argc, char * argv[])
{
  if(argc < 13)
    {
      std::cerr << "Usage " << argv[0] << ":\n"
      << "Argument 1: " << "[input image path]\n"
      << "Argument 2: " << "[tile size with respect to x-axis]\n"
      << "Argument 3: " << "[tile size with respect to y-axis]\n"
      << "Argument 4: " << "[available memory in megabytes]\n"
      << "Argument 5: " << "[temporary directory to store intermediate results]\n"
      << "Argument 6: " << "[maximum number of iterations]\n"
      << "Argument 7: " << "[spatial range bandwidth]\n"
      << "Argument 8: " << "[spectral range bandwidth]\n"
      << "Argument 9: " << "[threshold]\n"
      << "Argument 10: " << "[spectral range ramp]\n"
      << "Argument 11: " << "[enable mode search yes(1) no (0)]"
      << "Argument 12: " << "[output directory path (must me already created)]\n"
      << "Argument 13: " << "[output label image name]\n"
      << std::endl; 
      return 1;
    }

  auto mpiConfig = otb::MPIConfig::Instance();
  mpiConfig->Init(argc, argv);

  /** Input parameters */
  const std::string filename = argv[1];
  const unsigned int MaxTileSizeX = atoi(argv[2]);
  const unsigned int MaxTileSizeY = atoi(argv[3]);
  const unsigned long int mem = atoi(argv[4]);
  const std::string tempDir = argv[5];
  const unsigned int maxIter = atoi(argv[6]);
  const unsigned int spatialr = atoi(argv[7]);
  const float spectralr = atof(argv[8]);
  const float threshold = atof(argv[9]);
  const float ranger = atof(argv[10]);
  const bool modeSearch = (atoi(argv[11]) > 0) ? true : false;
  const std::string outDir = argv[12];
  const std::string labelImage = argv[13];

  using InputImageType              = otb::VectorImage<float, 2>;
  using LabelPixelType              = unsigned int;
  using LSMeanShiftSchedulerType       = otb::obia::LSMeanShiftScheduler<InputImageType, LabelPixelType>;

  auto lsMSFilter = LSMeanShiftSchedulerType::New();
  lsMSFilter->SetFileName(filename);
  lsMSFilter->SetMaxTileSizeX(MaxTileSizeX);
  lsMSFilter->SetMaxTileSizeY(MaxTileSizeY);
  lsMSFilter->SetAvailableMemory(mem);
  lsMSFilter->SetTemporaryDirectory(tempDir);
  lsMSFilter->SetMaxNumberOfIterations(maxIter);
  lsMSFilter->SetSpatialBandWidth(spatialr);
  lsMSFilter->SetSpectralRangeBandWidth(spectralr);
  lsMSFilter->SetThreshold(threshold);
  lsMSFilter->SetSpectralRangeRamp(ranger);
  lsMSFilter->SetModeSearch(modeSearch);
  lsMSFilter->SetOutputDir(outDir);
  lsMSFilter->SetWriteLabelImage(true);
  lsMSFilter->SetWriteGraph(true);
  lsMSFilter->SetLabelImageName(labelImage);
  lsMSFilter->Update();
  
  return EXIT_SUCCESS;
}
