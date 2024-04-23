#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype> // For isspace

// Function to remove whitespace characters from a string
std::string removeWhitespace(const std::string &str)
{
    std::string result;
    for (char c : str)
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            result += c;
        }
    }
    return result;
}

void compareFiles(const std::string &file1, const std::string &file2)
{
    std::ifstream fileStream1(file1);
    std::ifstream fileStream2(file2);

    if (!fileStream1.is_open() || !fileStream2.is_open())
    {
        std::cerr << "Unable to open one or both files." << std::endl;
        return;
    }

    std::string line1, line2;
    int lineNum = 1;
    bool filesAreEqual = true;

    while (std::getline(fileStream1, line1) && std::getline(fileStream2, line2))
    {
        // Remove whitespace from lines before comparing
        std::string trimmedLine1 = removeWhitespace(line1);
        std::string trimmedLine2 = removeWhitespace(line2);

        if (trimmedLine1 != trimmedLine2)
        {
            std::cout << "Files differ at line " << lineNum << std::endl;
            filesAreEqual = false;
        }
        lineNum++;
    }

    // If one file has more lines than the other
    while (std::getline(fileStream1, line1))
    {
        std::string trimmedLine1 = removeWhitespace(line1);
        if (!trimmedLine1.empty())
        {
            std::cout << "File 2 is shorter, difference at line " << lineNum << std::endl;
            filesAreEqual = false;
        }
        lineNum++;
    }
    while (std::getline(fileStream2, line2))
    {
        std::string trimmedLine2 = removeWhitespace(line2);
        if (!trimmedLine2.empty())
        {
            std::cout << "File 1 is shorter, difference at line " << lineNum << std::endl;
            filesAreEqual = false;
        }
        lineNum++;
    }

    if (filesAreEqual)
    {
        std::cout << "Files are identical." << std::endl;
    }
}

int main()
{
    std::string filename1, filename2;
    std::cout << "Enter path to the first file: ";
    std::getline(std::cin, filename1);
    std::cout << "Enter path to the second file: ";
    std::getline(std::cin, filename2);
    compareFiles(filename1, filename2);
    system("pause");
    return 0;
}
