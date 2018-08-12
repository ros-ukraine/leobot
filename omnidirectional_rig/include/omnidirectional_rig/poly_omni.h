/*
 *  poly_omni.h
 *  Copyright (c) 2014 PAL Robotics sl. All Rights Reserved
 *  Created on: 07/2014
 *      Author: Jéremie Deray
 */

#ifndef POLY_OMNI_H
#define POLY_OMNI_H

#include "omnidirectional_rig/omni_camera.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>

#include <sensor_msgs/PointCloud.h>
#include <boost/utility.hpp>

#include <stdio.h>

class OmniCameraRig : boost::noncopyable
{// Handle a omni-directional camera rig
 // So far limited to 2 cameras.

public :

        boost::shared_ptr<OmniCamera> camera_1;
        boost::shared_ptr<OmniCamera> camera_2;

        OmniCameraRig();
        OmniCameraRig(const std::vector<std::string> &paramPath);
        OmniCameraRig(const std::vector<std::string> &cameraParamPath, const std::string &extrinPath);

        ~OmniCameraRig() {}

        //Load Rig Extrinsic Parameters
        bool loadCalibration(const std::string&);

        void dispParam();

        void mergeLUTWrap(bool heal = false);

        void mergeLUTHeal();

        void mergeLUTSph();

        void rescaleWrapLUT(cv::Size size = cv::Size(1200,400));

        //Create Rig Panoramic Image from Cameras Image
        void stitchImage(bool INPAIN_FLAG = 0);

        void saveImage(const std::string &filename = "panoramicImage.jpg");

        //Apply Extrinsic Parameters to 2nd Camera Spherical Points
        void applyBaseline();

        //Fill Message with Colors from Spherical Rig Image
        void messRGBSph(sensor_msgs::PointCloud &);

        //Pre-compute 3D Points according to Spherical Rig Image
        void partiallyFillMess(sensor_msgs::PointCloud &);

        void setImages(const std::vector<cv::Mat>&);

        bool isInit() {return this->_init;}

        cv::Mat getExtrin();
        cv::Mat getPano();
        cv::Mat getLUT();

        void setExtrin(const cv::Mat &);
        void setPanoSize(cv::Size &);
        void setPanoSize(int,int);

        //Down Sample Cameras ~> K/samp_ratio
        //Images will be Down Sampled too
        void downSample(int sampling_ratio = 1);

        //
        void sph2Pano();

        void sph2HealPano();

private :

        //Since Camera Rig was Mounted on Robot with
        //a Rotation of -90roll this Compensate
        //to Retrieve Image in Correct Direction.
        //Todo - make function more generic and
        //retrieve Camera Rig Pose from a Proper tf.
        void rotate90roll();

        cv::Mat _extrin;
        cv::Size _panoSize;
        cv::Mat _pano;

        //Projection of Camera Rig Pixels
        //onto Unit Sphere
        cv::Mat _LUTsphere;

        //Projection of Camera Rig Spherical Pixels
        //onto Image Plan - Panoramic Image
        cv::Mat _LUT_wrap_im;

        bool _init;
        bool _isSampled;

        int _sampling_ratio;
        int _ind_LUTsph;
};


#endif // POLY_OMNI_H



