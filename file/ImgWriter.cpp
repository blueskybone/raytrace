    // int w = scene->renderer->width;
    // int h = scene->renderer->height;
    // FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
    // fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    // for (int i=0; i<w*h; i++)
    // fprintf(f,"%d %d %d ", toInt(pix[i].x), toInt(pix[i].y), toInt(pix[i].z));
    // std::cout<<"file printed."<<std::endl;
#include "ImgWriter.h"
#include "RayTrace.h"
#include <iostream>
bool WriteToFile(Scene * scene, vec3 * pix)
{
    int w = scene->renderer->width;
    int h = scene->renderer->height;
    FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i=0; i<w*h; i++)
    fprintf(f,"%d %d %d ", toInt(pix[i].x), toInt(pix[i].y), toInt(pix[i].z));
    std::cout<<"file printed."<<std::endl;
    return true;
}