#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <string>
#include "MathUtils.h"
#include <chrono>

Mesh* ModelLoader::LoadMeshAtPath(std::string path)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    Mesh* mesh = new Mesh();
    std::string fileContents;
    std::ifstream File;
    File.open(path);

    if (!File.is_open())
        return nullptr;

    int lineCount = 0;
    while (getline(File, fileContents))
    {
        switch (fileContents[0])
        {
        case '#':
            std::cout << "Skipping line " << lineCount << " was a comment!" << std::endl;
            break;
        case 'v':
            switch(fileContents[1])
            {
            case 'n':
                break;
            case 't':
                break;
            case ' ':
                mesh->AddVert(LoadLine(fileContents, 2));
                break;
            default:
                break;
            }
            break;
        case 'f':
            LoadLineInt(fileContents, 2, &mesh->indicies);
            break;
        case 's':
            std::cout << "Skipping line " << lineCount << " was a shading mode!" << std::endl;
            break;
        case 'o':
            break;
        case 'm':
            std::cout << "Skipping line " << lineCount << " was a material thingy!" << std::endl;
            break;
        case 'u':
            std::cout << "Skipping line " << lineCount << " was a comment!" << std::endl;
            break;
        default:
            break;
        }
        

        lineCount++;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    std::cout << "Execution time: " << elapsedTime << " milliseconds" << std::endl;
    return mesh;
}

Vector3* ModelLoader::LoadLine(std::string line, int startPoint)
{
    Vector3* toReturn = new Vector3();
    size_t firstSpaceIndex = line.find(' ');
    line = line.substr(firstSpaceIndex + 1);
    
    std::vector<std::string> stringVector;
    std::istringstream stream(line);
    std::string token;

    while (getline(stream, token, ' '))
    {
        stringVector.push_back(token);
    }

    if (stringVector[0] == "")
        stringVector.erase(stringVector.begin());

    toReturn->x = std::stof(stringVector[0]);
    toReturn->y = std::stof(stringVector[1]);
    toReturn->z = std::stof(stringVector[2]);

    return toReturn;
}

void ModelLoader::LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector)
{   
    std::string string = line;

    size_t firstSpaceIndex = string.find(' ');
    string = string.substr(firstSpaceIndex + 1);

    std::vector<std::string> stringVector;
    std::istringstream stream(string);
    std::string token;

    while (getline(stream, token, ' '))
    {
        stringVector.push_back(token);
    }

    std::vector<Vector3> VectorVector;
    for (int i = 0; i < stringVector.size(); i++)
    {
        std::istringstream stream2(stringVector[i]);
        std::string token2;

        int pointInArray = 0;
        //Vector3 v3 = Vector3();
        while (getline(stream2, token2, '/'))
        {
            switch (pointInArray) {
            case 0:
                vector->push_back(std::stoi(token2));
                break;
            case 1:
                //v3.y = std::stoi(token2);
                break;
            case 2:
                //v3.z = std::stoi(token2);
                break;
            }

            pointInArray++;
        }
        //VectorVector.push_back(v3);
    }

    

    //for (int j = 0; j < VectorVector.size(); j++)
    //{
    //    vector->push_back(VectorVector[j].x);
    //}
    std::cout << "";
}
