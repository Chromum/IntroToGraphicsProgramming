#include "ModelLoader.h"
#include <fstream>
#include <string>
#include "MathUtils.h"

Mesh* ModelLoader::LoadMeshAtPath(std::string path)
{
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



    return mesh;
}

Vector3* ModelLoader::LoadLine(std::string line, int startPoint)
{
    Vector3* toReturn = new Vector3();
    int position = 0;
    std::string stringOfFloat ="";

    for (int i = startPoint; i < line.size(); i++)
    {
        if (line[i] == ' ' || i == line.size() -1)
        {
            //if (stringOfFloat.size() == 0)
            //    return toReturn;

            if (stringOfFloat.size() == 0)
                continue;


            switch (position)
            {
            case 0:
                toReturn->x = std::stof(stringOfFloat);
                break;  
            case 1:     
                toReturn->y = std::stof(stringOfFloat);
                break;  
            case 2:     
                toReturn->z = std::stof(stringOfFloat);
                break;
            default:
                break;
            }

            position++;
            stringOfFloat.clear();
        }
        //if (line[i] == '\0')
        //{
        //    //if (stringOfFloat.size() == 0)
        //    //    return toReturn;

        //    switch (position)
        //    {
        //    case 0:
        //        toReturn->x = std::stof(stringOfFloat);
        //        break;
        //    case 1:
        //        toReturn->y = std::stof(stringOfFloat);
        //        break;
        //    case 2:
        //        toReturn->z = std::stof(stringOfFloat);
        //        break;
        //    default:
        //        break;
        //    }

        //    position++;
        //    stringOfFloat.clear();
        //}
        stringOfFloat.push_back(line[i]);
    }


    return toReturn;
}

void ModelLoader::LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector)
{   
    std::string string;
    for (int i = startPoint; i < line.size(); i++)
    {
        

        if (line[i] == '/')
        {
            vector->push_back(std::stoi(string));
            string.clear();
            i += 4;
        }
        else if (line[i] == ' ')
        {
        }
        else
        {
            string.push_back(line[i]);
        }
    }
}
