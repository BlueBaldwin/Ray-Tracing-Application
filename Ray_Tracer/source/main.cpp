///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Main.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <cstdlib>
#include <iostream>
#include <ColourRGB.h>
#include <string>
#include <fstream>
#include <time.h>
#include <Random.h>

#include "Ellipsoid.h"
#include "Camera.h"
#include "Ray.h"
#include "ColourRGB.h"
#include "DirectionalLight.h"
#include "Scene.h"
#include "Light.h"
#include "Material.h"
//\------------------------

//\====================================================================================================
//\ MAIN - RAY_TRACER
//\====================================================================================================

typedef enum input_args
{
    OUTPUT_FILE = 1,
    OUTPUT_WIDTH,
    OUTPUT_HEIGHT,
}input_args;

void displayUsage(char* a_path)
{
    std::string fullpath = a_path; // get the full path as a string
    // strup off the path part of the string to only keep the executable name
    std:: string exeName = fullpath.substr(fullpath.find_first_of('\\') + 1, fullpath.length());
    // Display a message to the user indicating usage of the executable
    std::cout << "usage: " << exeName << " [output image name] [image width] [imageheight]" << std::endl;
}

int main(int argv, char* argc[])
{
    // set up the diamensions of the image
    int imageWidth = 512;
    int imageHeight = 256;
    int channelColours = 255;
    // Output the file name
    std::string outputFilename;

    if (argv < 2) // Less than 2 as the path and executable name are always present
        {
        displayUsage(argc[0]);
        return EXIT_SUCCESS;
        }
    else // Some variadic arguments have been passed]
    {
        for (int i = 1; i < argv; ++i)
        {
            std::string arg = argc[i];
            if (arg == "-h" || arg == "--help")
            {
                displayUsage(argc[0]);
                return EXIT_SUCCESS;
            }
            switch (i)
            {
            case OUTPUT_FILE:
                {
                    outputFilename = argc[OUTPUT_FILE];
                    // Check to see if the extension was included
                    if (outputFilename.find_last_of(".") == std::string::npos)
                    {
                        // No extension better add one
                        outputFilename.append(".ppm");
                    }
                    break;
                }
            case OUTPUT_WIDTH:
                {
                    imageWidth = atoi(argc[OUTPUT_WIDTH]);
                    break;
                }
            case OUTPUT_HEIGHT:
                {
                    imageHeight = atoi(argc[OUTPUT_HEIGHT]);
                    break;
                }
            default:
                {
                    continue;
                }
            }
        }
    }
   
    // Need to change std::cout to outputFilename
    std::streambuf* backup = std::cout.rdbuf();         // Backup std::cout's stream buffer
    std::ofstream outbuff(outputFilename.c_str());      // Create an out file stream and set it to our output file name
    std::cout.rdbuf(outbuff.rdbuf());                   // Set the stream buffer for the cout to the file out stream buffer

    //\----------------------------------------------------------------------------------
    //\ SCENE AND CAMERA - Position, Direction and Dimensions
    //\----------------------------------------------------------------------------------
    Scene mainScene;

    Camera mainCamera;
    mainCamera.SetPerspective(60.f, (float)imageWidth/(float)imageHeight, 0.1f, 1000.0f);
    mainCamera.Setposition(Vector3(0.f,0.f, 1.f));
    mainCamera.LookAt(Vector3(0.f,0.f,-2.5f), Vector3(0.f,1.f,0.f));
   
    Random::SetSeed(time(nullptr));
    int raysPerPixel = 100;

    Random::SetSeed((int)time(nullptr));

    // Output the Image Header Data
    std::cout << "P3" << std::endl;
    std::cout << imageWidth << ' ' << imageHeight << std::endl;
    std::cout << channelColours << std::endl;

    //\----------------------------------------------------------------------------------
    //\ LIGHTING 
    //\----------------------------------------------------------------------------------
    // Put the light in the scene
    DirectionalLight dl = DirectionalLight(Matrix4::IDENTITY, Vector3(1.f, 1.f, 1.f), Vector3(-0.5773f, -0.5733f, -0.5773f));

    //\----------------------------------------------------------------------------------
    // MATERIALS 
    //\----------------------------------------------------------------------------------
                                                // | R     | G   | B        Ambient|Difuse|Specular|Rough |Reflect |Trans  |RefIndx
    Material lightBlueSmooth =   Material(Vector3(0.2,   0.6,    1.f),    0.2f,   0.9f,   0.9f,   0.f,    0.9f,   0.9f,   1.52f);
    Material lightBlueRough =    Material(Vector3(0.3f,  0.6f,   1.f),    0.2f,   0.9f,   0.6f,   1.f,    0.0f,   0.0f,   1.52f);
    Material greenSmooth =       Material(Vector3(0.f,   0.6f,   0.0f),   0.2f,   0.9f,   0.9f,   0.f,    0.9f,   1.0f,   1.52f);
    Material greenRough =        Material(Vector3(0.f,   0.6f,   0.f),    0.2f,   0.9f,   0.5f,   1.f,    0.0f,   0.f,    2.61f);
    Material yellowSmooth =      Material(Vector3(0.5f,  0.5f,   0.f),    0.2f,   0.9f,   0.9f,   0.f,    1.0f,   0.f,    2.61f);
    Material yellowRough =       Material(Vector3(0.5f,  0.5f,   0.f),    0.2f,   0.9f,   0.1f,   1.f,    0.0f,   0.f,    2.61f);
    Material redSmooth =         Material(Vector3(1.f,   0.0f,   0.f),    0.2f,   0.9f,   0.9f,   0.f,    1.0f,   0.f,    2.61f);
    Material redRough =          Material(Vector3(1.f,   0.0f,   0.f),    0.2f,   0.9f,   0.1f,   1.f,    0.0f,   0.f,    1.52f);
    Material Clear = Material(Vector3(1.f, 1.0f, 1.0f), 0.1f, 0.1f, 0.9f, 0.f, 0.5f, 1.f, 1.52f);
    Material ClearInner = Material(Vector3(1.f, 1.0f, 1.0f), 0.1f, 0.1f, 0.9f, 0.f, 0.5f, 1.f, 1.0f);

    Material Metal =             Material(Vector3(0.8f,  0.8f,   0.8f),   0.1f,   0.1f,   0.9f,   0.f,    1.0f,   0.f,    2.61f);

    //\----------------------------------------------------------------------------------
    //\ OBJECTS IN SCENE - Spheres size, position and material
    //\----------------------------------------------------------------------------------

    // GROUND
    Ellipsoid s1(Vector3(0.f, -100.5f, -2.5f), 100.f);
    s1.SetScale(Vector3(1.f, 1.f, 1.f));
    s1.SetMaterial(&greenRough);

    // Sphere on the - LEFT [BLUE]
    Ellipsoid s2(Vector3(-1.f, 0.f, -1.5f), 0.5f);
    s2.SetScale(Vector3(1.f, 1.f, 1.f));
    s2.SetMaterial(&lightBlueRough);

    // THIRD ELLIPSOIN - CENTRE

    Ellipsoid s3(Vector3(0.f, 0.f, -3.5f), 0.5f);
    s3.SetScale(Vector3(1.f, 1.f, 1.f)); 
    s3.SetMaterial(&redSmooth);

    // THIRD ELLIPSOIN - CENTRE Right

    Ellipsoid s6(Vector3(2.5f, 0.25f, -1.5f), 0.8f);
    s6.SetScale(Vector3(1.f, 1.f, 1.f));
    s6.SetMaterial(&greenSmooth);


    // Sphere on the - RIGHT
    Ellipsoid s4(Vector3(1.5f, 0.f, -4.5f), 0.5f);
    s4.SetScale(Vector3(1.f, 1.f, 1.f));
    s4.SetMaterial(&Clear);

    // Clear Sphere
    Ellipsoid s5(Vector3(1.5f, 0.f, -4.5f), 0.4f);
    s5.SetScale(Vector3(1.f, 1.f, 1.f));
    s5.SetMaterial(&ClearInner);

    // ADDING SPHERES INTO THE SCENE
    mainScene.AddObject(&s1);
    mainScene.AddObject(&s2);
    mainScene.AddObject(&s3);
    mainScene.AddObject(&s4);
    mainScene.AddObject(&s5);
    mainScene.AddObject(&s6);
    mainScene.AddLight(&dl);
    mainScene.SetCamera(&mainCamera);


    // Get reciprical of image dimensions
    float invWidth = 1.f / (float)imageWidth;
    float invHeight = 1.f / (float)imageHeight;
    

    //\----------------------------------------------------------------------------------
    //\ Main Render Loop 
    //\----------------------------------------------------------------------------------

    // For each vertical interval of near plane
    for (int i = 0; i < imageHeight; i++)
    {
        std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
        // For each interval of the near plane horizontally
        for (int j = 0; j < imageWidth; j++)
        {
            ColourRGB rayColour(0.f, 0.f, 0.f);
            for (int p = 0; p < raysPerPixel; p++)
            {
                // Calcuate Screen space Y Location
                float screenSpaceY = 1.f - 2.f * ((float)i + Random::RandomFloat()) * invHeight;
                // Get current pixel in screen sace coordinates
                float screenSpaceX = 2.f * ((float)j + 0.5f) * invWidth - 1.f;
                Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);
                Ray screenRay = mainScene.GetScreenRay(screenSpacePos);
                rayColour += mainScene.CastRay(screenRay, 15);
            }
            rayColour = rayColour * (1.f / (float)raysPerPixel);
            //Write to output stream
            WriteColourRGB(std::cout, rayColour);
        }
        std::cout << std::endl;
    }

    // Set the output stream buffer back to what it was previously
    std::cout.rdbuf(backup);
    return EXIT_SUCCESS;
}
