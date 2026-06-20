#include "CsvLogger.hpp"

#include <iomanip>

bool openCsvFile(
    std::ofstream& csvFile,
    const std::string& fileName
)
{
    // Check if the CSV file is new or empty
    std::ifstream existingFile(
        fileName,
        std::ios::binary | std::ios::ate
    );

    bool writeHeader =
        !existingFile.is_open() || existingFile.tellg() == 0;

    existingFile.close();

    // Open the file in append mode so old readings are kept
    csvFile.open(fileName, std::ios::app);

    if (!csvFile.is_open()) {
        return false;
    }

    if (writeHeader) {
        csvFile << "timestamp,temperature" << std::endl;
    }

    return csvFile.good();
}

bool writeCsvReading(
    std::ofstream& csvFile,
    const std::string& timestamp,
    double temperature
)
{
    // Write one temperature reading to the CSV file
    csvFile
        << timestamp
        << ","
        << std::fixed
        << std::setprecision(2)
        << temperature
        << std::endl;

    return csvFile.good();
}
