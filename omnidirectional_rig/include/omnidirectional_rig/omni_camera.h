/*
 *  omni_camera.h
 *  Copyright (c) 2014 PAL Robotics sl. All Rights Reserved
 *  Created on: 07/2014
 *      Author: Jéremie Deray
 */

#ifndef OMNI_CAMERA_H
#define OMNI_CAMERA_H

#include "omnidirectional_rig/image_handler.h"
#include "omnidirectional_rig/usefull.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <complex>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
//#include <yaml-cpp/yaml.h>

struct imageSize{

    int rows;
    int cols;

    imageSize() : rows(0), cols(0) {}
    imageSize(int rows_,int cols_) : rows(rows_), cols(cols_) {}
};

struct CameraParam{

    std::string cameraType;
    double xi;
    cv::Mat intrinParam;
    imageSize imSize;

    CameraParam() : cameraType(""), xi(0), intrinParam(cv::Mat::zeros(3,4,CV_32F)), imSize(0,0) {}
    CameraParam(const std::string& camT_, double xi_, const cv::Mat& param_, const imageSize& imSize_) :
        cameraType(camT_), xi(xi_), intrinParam(param_), imSize(imSize_) {}
};


class OmniCamera
{
public:

    OmniCamera();
    OmniCamera(const std::string &paramPath);

    ~OmniCamera();

    std::string GetType();
    double GetXi();
    cv::Mat GetIntrinsic();
    imageSize GetImageSize();
    cv::Mat GetLUT();
    cv::Mat GetLUT(const std::string &);
    cv::Mat GetMask();
    cv::Mat getImage();
    bool IsSampled();

    bool IsInit();

    void SetType(const std::string&);
    void SetXi(double);
    void SetIntrinsic(const cv::Mat&);
    void SetImageSize(const imageSize&);
    void SetImageSize(int rows, int cols);
    void SetLUTSph(const cv::Mat&);
    void setImage(const cv::Mat&);

    void readImage(const std::string&);

    void ReleaseLut();

    void DispParam();

    void LoadMask(const std::string&);

    void Im2Sph(const cv::Size &im = cv::Size(1280,1024));
    void Im2Sph(int rows = 1024,int cols = 1280);
    cv::Vec3f Pix2Sph(int ind_row, int ind_col);

    void Sph2Pano();

    void Sph2Im(const cv::Mat&);
    void Sph2Im(const cv::Mat&, cv::Mat&);
    cv::Vec2i Sph2Im(float, float, float);

    void DownSample(int sampling_ratio = 1);

//private :


    CameraParam _cameraParam;

    bool _init;

    cv::Mat _LUTsphere;
    cv::Mat _LUT_wrap_im;
    cv::Mat _LUT_sampSph_im;

    cv::Mat _Mask;
    cv::Mat _Frame;

    bool _loadParam(const std::string &paramPath);

    bool _isSampled;
    int _sampling_ratio;
};



#endif // OMNI_CAMERA_H
