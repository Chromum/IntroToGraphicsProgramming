#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <string>
#include "MathUtils.h"
#include <chrono>
#include "ImageReader.h"

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
    MaterialData* currentMatData = nullptr;
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
                currentMesh->matData = currentMatData;
                
            }
            switch(fileContents[1])
            {
            case 'n':
                currentMesh->AddNormal(LoadLine(fileContents, 2));
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
                currentMesh->matData = currentMatData;
            }
            currentMesh->isQuadMesh = LoadLineInt(fileContents, 2, &currentMesh->indicies, &currentMesh->UVindicies, &currentMesh->Normalindicies);
            break;
        case 's':
            std::cout << "Skipping line " << lineCount << " was a shading mode!" << std::endl;
            break;
        case 'o':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
                currentMesh->matData = currentMatData;
                break;
            }
            meshes.push_back(currentMesh);
            currentMesh = new Mesh();
            currentMesh->matData = currentMatData;
            break;
        case 'g':
            if (currentMesh == nullptr)
            {
                currentMesh = new Mesh();
                currentMesh->matData = currentMatData;
                break;
            }
            meshes.push_back(currentMesh);
            currentMesh = new Mesh();
            currentMesh->matData = currentMatData;
            break;
        case 'm':
            currentMatData = new MaterialData();
            currentMatData->LoadMaterialFile(fileContents);

            std::cout << "Skipping line " << lineCount << " was a material thingy!" << std::endl;
            break;
        case 'u':
            std::string matName = fileContents.substr(fileContents.find(" ") + 1);

            auto it = currentMatData->textureList.find(matName);

            if (it != currentMatData->textureList.end())
                currentMesh->texture = currentMatData->textureList[matName];
            else
                currentMesh->texture = 1;

            std::cout << "Skipping line " << lineCount << " was a comment!" << std::endl;
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


bool ModelLoader::LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector, std::vector<unsigned int>* vector2, std::vector<unsigned int>* vector3)
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
                vector3->push_back(std::stoi(token2));
                break;
            }

            pointInArray++;
        }
        //VectorVector.push_back(v3);
    }
    std::cout << "";
    return isQuadMode;
}

void MaterialData::LoadMaterialFile(std::string entered)
{
    ImageReader* image = new ImageReader();
    //Getting filename 
    std::string fileName = entered.substr(entered.find(" ") + 1);

    std::string fileContents;
    std::ifstream File;
    File.open("Models/" + fileName);

    std::string currentMaterial;

    while (getline(File, fileContents)) {
        switch (fileContents[0])
        {
        case '#':
            break;
        case 'n':
            currentMaterial = fileContents.substr(fileContents.find(" ") + 1);
            this->textureList.insert(std::pair<std::string, int>(currentMaterial, 0));
            break;
        case 'm':
        {
            size_t lastSlashPos = fileContents.find_last_of("/\\");

            std::string e = fileContents.substr(lastSlashPos + 1);
            this->textureList[currentMaterial] = image->ReadImage("Models/" + e);
        }
            break;
        case 'K':
            switch (fileContents[1])
            {
                case 'a':
                {
                    std::vector<std::string> stringVector;
                    std::istringstream stream(fileContents);
                    std::string token;

                    while (getline(stream, token, ' '))
                    {
                        stringVector.push_back(token);
                    }

                    stringVector.erase(stringVector.begin());


                    this->ambient.x = std::stof(stringVector[0]);
                    this->ambient.y = std::stof(stringVector[1]);
                    this->ambient.z = std::stof(stringVector[2]);
                    std::cout << "";
                }

                    break;
                case 'd':
                {
                    std::vector<std::string> stringVector;
                    std::istringstream stream(fileContents);
                    std::string token;

                    while (getline(stream, token, ' '))
                    {
                        stringVector.push_back(token);
                    }

                    stringVector.erase(stringVector.begin());


                    this->diffuse.x = std::stof(stringVector[0]);
                    this->diffuse.y = std::stof(stringVector[1]);
                    this->diffuse.z = std::stof(stringVector[2]);
                    std::cout << "";
                }

                break;
                case 's':
                {
                    std::vector<std::string> stringVector;
                    std::istringstream stream(fileContents);
                    std::string token;

                    while (getline(stream, token, ' '))
                    {
                        stringVector.push_back(token);
                    }

                    stringVector.erase(stringVector.begin());


                    this->specular.x = std::stof(stringVector[0]);
                    this->specular.y = std::stof(stringVector[1]);
                    this->specular.z = std::stof(stringVector[2]);
                    std::cout << "";
                }

                    break;
            }
            break;
        case 'N':
        {
            std::string e = fileContents.substr(fileContents.find(" ") + 1);
            this->opticalDensity = std::stof(e);
            std::cout << "";
        }
            break;
        }
    }


    std::cout << "";
}
