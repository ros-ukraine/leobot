#ifndef USEFULL_H
#define USEFULL_H

#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>


const double mypi = 3.141592653589793238462643383279;


template <class NumType>
cv::Mat Vector2Mat(std::vector< NumType > vect){

    cv::Mat matrix = cv::Mat::zeros(1,vect.size(), cv::DataType<NumType>::type);

    for (int r=0; r<vect.size(); r++)
    {
         matrix.at<NumType>(0,r) = vect[r];
    }

    return matrix;
}


void Cart2Sph(const cv::Mat&, cv::Mat&, int rad_flag = 0);

void Sph2Cart(const cv::Mat&, cv::Mat &);

void Sph2Heal(const cv::Mat&, cv::Mat &);

void MeshGrid(const cv::Mat&, const cv::Mat&, cv::Mat&, cv::Mat&);

void RotateCloudPoint(cv::Mat&,double,double,double, bool rad = false);

cv::Mat GetRotationMat(double,double,double, bool rad = false);

cv::Mat GetZYZRotationMat(double yaw1, double pitch, double yaw2, bool rad = false);

double Deg2Rad(double);

std::string AddPath(const std::string& obj, const std::string& root);

void MatInfo(const cv::Mat&,const std::string &matname = "", bool val = false);

void getListOfFilesInFolder(const std::string& path, const std::string& extension, std::vector<std::string>& baseFileNames);

std::set<std::string> loadFilesName(const std::string &dir);

#endif // USEFULL_H
