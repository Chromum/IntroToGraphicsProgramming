#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <string>
#include "MathUtils.h"
#include <chrono>

std::vector<Mesh*> ModelLoader::LoadMeshAtPath(std::string path)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<Mesh*> meshes;
    std::string fileContents;
    std::ifstream File;
    File.open(path);

    if (!File.is_open())
        return meshes;

    int lineCount = 0;
    Mesh* currentMesh = nullptr;
    while (getline(File, fileContents))
    {
        switch (fileContents[0])
        {
        case '#':
            std::cout << "Skipping line " << lineCount << " was a comment!" << std::endl;
            break;
        case 'v':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
            }
            switch(fileContents[1])
            {
            case 'n':
                break;
            case 't':
                currentMesh->AddTextureUV(LoadLineV2(fileContents, 2));
                break;
            case ' ':
                currentMesh->AddVert(LoadLine(fileContents, 2));
                break;
            default:
                break;
            }
            break;
        case 'f':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
            }
            currentMesh->isQuadMesh = LoadLineInt(fileContents, 2, &currentMesh->indicies, &currentMesh->UVindicies);
            break;
        case 's':
            std::cout << "Skipping line " << lineCount << " was a shading mode!" << std::endl;
            break;
        case 'o':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
                break;
            }
            meshes.push_back(currentMesh);
            currentMesh = new Mesh();
            break;
        case 'g':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
                break;
            }
            meshes.push_back(currentMesh);
            currentMesh = new Mesh();
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

    meshes.push_back(currentMesh);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    std::cout << "Execution time: " << elapsedTime << " milliseconds" << std::endl;
    return meshes;
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

Vector2* ModelLoader::LoadLineV2(std::string line, int startPoint)
{
    Vector2* toReturn = new Vector2();
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

    return toReturn;
}


bool ModelLoader::LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector, std::vector<unsigned int>* vector2)
{   
    bool isQuadMode = false;
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
        if (stringVector.size() == 4)
        {
            isQuadMode = true;
        }

        std::istringstream stream2(stringVector[i]);
        std::string token2;

        int pointInArray = 0;
        //Vector3 v3 = Vector3();
        while (getline(stream2, token2, '/'))
        {
            if (token2.size() <= 0)
                continue;


            switch (pointInArray) {
            case 0:
                vector->push_back(std::stoi(token2));
                break;
            case 1:
                
                vector2->push_back(std::stoi(token2));
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
    return isQuadMode;
}
