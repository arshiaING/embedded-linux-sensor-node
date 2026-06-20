#pragma once

#include <fstream>
#include <string>

bool openCsvFile(
    std::ofstream& csvFile,
    const std::string& fileName
);

bool writeCsvReading(
    std::ofstream& csvFile,
    const std::string& timestamp,
    double temperature
);