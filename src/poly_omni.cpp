/*
 *  poly_omni.cpp
 *  Copyright (c) 2014 PAL Robotics sl. All Rights Reserved
 *  Created on: 07/2014
 *      Author: Jéremie Deray
 */

#include "omnidirectional_rig/poly_omni.h"

OmniCameraRig::OmniCameraRig()
{
    // ! may need to be swap depending on cameras initialization order.
    // TODO : find way to force cameras init order
    this->camera_1.reset( new OmniCamera("etc/calib/Pal_intrinsicParam_cam1.yaml") );
    this->camera_2.reset( new OmniCamera("etc/calib/Pal_intrinsicParam_cam2.yaml") );

    this->loadCalibration("etc/calib/Pal_extrinsicParam.yaml");

    // ! same camera init prob
    this->camera_1->LoadMask("etc/images/cam2/Img_mask2.jpg");
    this->camera_2->LoadMask("etc/images/cam1/Img_mask1.jpg");

    this->_panoSize = cv::Size(1200,400);

    this->_isSampled = false;
    this->_sampling_ratio = 1;
    this->_ind_LUTsph = 0;

    this->_init = this->camera_1->IsInit() && this->camera_2->IsInit() && true;
}


OmniCameraRig::OmniCameraRig(const std::vector<std::string> &cameraParamPath)
{
    this->camera_1.reset( new OmniCamera(cameraParamPath.at(0)) );
    this->camera_2.reset( new OmniCamera(cameraParamPath.at(1)) );

    cv::Mat extrin = cv::Mat::zeros(3,4,CV_32F);
    extrin(cv::Rect(0,0,3,3)) = GetRotationMat(0,180,0);
    extrin.at<float>(0,3) = 0.;
    extrin.at<float>(1,3) = 0.;
    extrin.at<float>(2,3) = 0.;
    extrin.copyTo(this->_extrin,CV_32F);

    this->_panoSize = cv::Size(1200,400);
    this->_isSampled = false;
    this->_sampling_ratio = 1;
    this->_ind_LUTsph = 0;

    this->_init = this->camera_1->IsInit() && this->camera_2->IsInit() && true;
}

OmniCameraRig::OmniCameraRig(const std::vector<std::string> &cameraParamPath, const std::string &extrinPath)
{
    this->camera_1.reset( new OmniCamera(cameraParamPath.at(0)) );
    this->camera_2.reset( new OmniCamera(cameraParamPath.at(1)) );

    this->loadCalibration(extrinPath);

    this->_panoSize = cv::Size(1200,400);
    this->_isSampled = false;
    this->_sampling_ratio = 1;
    this->_ind_LUTsph = 0;

    this->_init = this->camera_1->IsInit() && this->camera_2->IsInit() && true;
}

bool OmniCameraRig::loadCalibration(const std::string& paramPath){

    cv::FileStorage fs(paramPath,cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        std::cout<<"Failed to open "<<paramPath<< std::endl;
        return false;
    }

    fs["extrinsicParam"] >> this->_extrin;

    fs.release();

    this->_extrin.convertTo(this->_extrin,CV_32FC1);

    return true;
}

void OmniCameraRig::dispParam(){

    if(this->camera_1->IsInit()) {
        this->camera_1->DispParam();
    }else{
        std::cout<<"Camera 1 not initialized !!!"<<std::endl;
    }

    if(this->camera_2->IsInit()) {
        this->camera_2->DispParam();
    }else{
        std::cout<<"Camera 2 not initialized !!!"<<std::endl;
    }

    if(this->isInit()) {
        std::cout<<"system extrinsic parameters : \n" << this->getExtrin() <<std::endl<<std::endl;
    }
}


cv::Mat OmniCameraRig::getExtrin(){
    return this->_extrin;
}

cv::Mat OmniCameraRig::getPano(){
    return this->_pano;
}

cv::Mat OmniCameraRig::getLUT(){
    return this->_LUT_wrap_im;
}

void OmniCameraRig::setExtrin(const cv::Mat &extrin){
    this->_extrin = extrin;

}

void OmniCameraRig::setPanoSize(cv::Size &panoSize)
{
    this->_panoSize = panoSize;
}

void OmniCameraRig::setPanoSize(int rows, int cols)
{
    this->_panoSize = cv::Size(cols,rows);
}

void OmniCameraRig::mergeLUTWrap(bool heal)
{
    if(this->camera_1->_LUTsphere.empty() || this->camera_2->_LUTsphere.empty())
    {
        this->camera_1->Im2Sph(this->camera_1->_cameraParam.imSize.rows,this->camera_1->_cameraParam.imSize.cols);
        this->camera_2->Im2Sph(this->camera_2->_cameraParam.imSize.rows,this->camera_2->_cameraParam.imSize.cols);

        this->applyBaseline();

        this->mergeLUTSph();
    }
    if (this->_LUT_wrap_im.empty())
    {
        if(heal)
        {
            this->sph2HealPano();
        }else{
            this->sph2Pano();
        }
    }
}

void OmniCameraRig::mergeLUTHeal()
{
    if(this->camera_1->_LUTsphere.empty() || this->camera_2->_LUTsphere.empty())
    {
        this->camera_1->Im2Sph(this->camera_1->_cameraParam.imSize.rows,this->camera_1->_cameraParam.imSize.cols);
        this->camera_2->Im2Sph(this->camera_2->_cameraParam.imSize.rows,this->camera_2->_cameraParam.imSize.cols);

        this->applyBaseline();

        this->mergeLUTSph();
    }
    if (this->_LUT_wrap_im.empty())
    {
        this->sph2Pano();
    }
}

void OmniCameraRig::mergeLUTSph()
{
    if(this->camera_1->_LUTsphere.empty() || this->camera_2->_LUTsphere.empty()) return;

    cv::Mat tmp;

    cv::hconcat(this->camera_1->_LUTsphere,this->camera_2->_LUTsphere,tmp);

    this->camera_1->ReleaseLut();
    this->camera_2->ReleaseLut();

    tmp.convertTo(this->_LUTsphere,CV_32FC1);
}

void OmniCameraRig::rescaleWrapLUT(cv::Size size)
{
    double min,max;

    cv::minMaxLoc(this->_LUT_wrap_im.row(0),&min,&max);

    this->_LUT_wrap_im.row(0).convertTo(this->_LUT_wrap_im.row(0), CV_16UC1
                         ,(double)(size.width/(max-min)),(double)(- (min * (size.width/(max-min)))));

    cv::minMaxLoc(this->_LUT_wrap_im.row(1),&min,&max);

    this->_LUT_wrap_im.row(1).convertTo(this->_LUT_wrap_im.row(1),CV_16UC1,
                         size.height/(max-min),- (min * (size.height/(max-min))));

    this->_pano = cv::Mat::zeros(size.height,size.width,this->_pano.type());
}

void OmniCameraRig::stitchImage(bool INPAIN_FLAG)
{
    if (!this->isInit() || this->camera_1->_Frame.empty() || this->camera_2->_Frame.empty() || this->_LUT_wrap_im.empty())
    {
        return;
    }

    if (this->camera_1->_Mask.empty()) this->camera_1->_Mask = cv::Mat::ones(this->camera_1->_cameraParam.imSize.rows,this->camera_1->_cameraParam.imSize.cols,CV_8UC1);
    if (this->camera_2->_Mask.empty()) this->camera_2->_Mask = cv::Mat::ones(this->camera_2->_cameraParam.imSize.rows,this->camera_2->_cameraParam.imSize.cols,CV_8UC1);

    this->_pano = cv::Mat::zeros(this->_panoSize, 16);

    cv::Mat mask_inpaint = cv::Mat::zeros(this->_panoSize, 0);
    mask_inpaint += 255;

    int pix_im1 = this->camera_1->_cameraParam.imSize.cols * this->camera_1->_cameraParam.imSize.rows;

    cv::Mat im_val = this->camera_1->_Frame;

    cv::Mat im_mask = this->camera_1->_Mask;

    int _cross_ind_row = 0;
    int _cross_ind_col = 0;

    for (int i = 0; i < this->_LUT_wrap_im.cols; i++)
    {
        if(im_mask.at<uchar>(_cross_ind_row,_cross_ind_col) > 0)
        {

            this->_pano.at<cv::Vec3b>(this->_LUT_wrap_im.at<unsigned short>(0,i),this->_LUT_wrap_im.at<unsigned short>(1,i)) =
                    im_val.at<cv::Vec3b>(_cross_ind_row,_cross_ind_col);


            if (INPAIN_FLAG) mask_inpaint.at<uchar>(this->_LUT_wrap_im.at<unsigned short>(0,i),this->_LUT_wrap_im.at<unsigned short>(1,i)) = 0;
        }
        _cross_ind_row++;

        if (_cross_ind_row == im_val.rows)
        {
            _cross_ind_row = 0;
            _cross_ind_col++;
        }

        if (i == pix_im1-1)
        {
            im_val = this->camera_2->_Frame;
            im_mask = this->camera_2->_Mask;
            _cross_ind_row = 0;
            _cross_ind_col = 0;
        }
    }

    cv::inpaint(this->_pano,mask_inpaint,this->_pano,5,cv::INPAINT_TELEA);
}


void OmniCameraRig::saveImage(const std::string &filename)
{
    cv::imwrite(filename,this->_pano);
}

void OmniCameraRig::setImages(const std::vector<cv::Mat> &images)
{
    if(!this->isInit()) return;
    this->camera_1->setImage(images[0]);
    this->camera_1->setImage(images[1]);
}


void OmniCameraRig::applyBaseline()
{
    if(!this->isInit() || this->camera_2->_LUTsphere.empty()) return;

    cv::Mat tmp = this->_extrin(cv::Rect(0,0,3,3)) * this->camera_2->_LUTsphere;
    tmp.convertTo(this->camera_2->_LUTsphere,CV_32F);
}

void OmniCameraRig::rotate90roll()
{
    cv::Mat Rot90roll = GetRotationMat(-90,0,90);
    Rot90roll.convertTo(Rot90roll,this->_LUTsphere.type());

    cv::Mat tmp = Rot90roll * this->_LUTsphere;
    tmp.convertTo(this->_LUTsphere,CV_32F); // in theorz could be removed
}

void OmniCameraRig::partiallyFillMess(sensor_msgs::PointCloud &PointCloud){

    if (!this->isInit()) return;

    if (this->_LUTsphere.empty())
    {
        if (this->camera_1->_LUTsphere.empty())
        {
            this->camera_1->Im2Sph(this->camera_1->_cameraParam.imSize.rows ,this->camera_1->_cameraParam.imSize.cols);
        }

        if (this->camera_2->_LUTsphere.empty())
        {
            this->camera_2->Im2Sph(this->camera_2->_cameraParam.imSize.rows,this->camera_2->_cameraParam.imSize.cols);
        }

        this->applyBaseline();

        this->mergeLUTSph();

        //TODO retrieve rig pose through tf
        this->rotate90roll();
    }

    PointCloud.header.frame_id = "base_link";

    PointCloud.points.resize(this->_LUTsphere.cols);

    PointCloud.channels.resize(3);

    PointCloud.channels[0].name = "r";
    PointCloud.channels[1].name = "g";
    PointCloud.channels[2].name = "b";

    PointCloud.channels[0].values.resize(this->_LUTsphere.cols);
    PointCloud.channels[1].values.resize(this->_LUTsphere.cols);
    PointCloud.channels[2].values.resize(this->_LUTsphere.cols);

    int row_ind = 0;
    int col_ind = 0;

    int pix_im1 = this->camera_1->_cameraParam.imSize.cols * this->camera_1->_cameraParam.imSize.rows;

    cv::Mat mask = this->camera_1->_Mask;

    const uchar *ptr_mask;
    ptr_mask = mask.ptr<uchar>(row_ind) + col_ind;

    for (int i = 0; i<this->_LUTsphere.cols; i++)
    {
        if (*ptr_mask > 0)
        {
            PointCloud.points[i].x = this->_LUTsphere.at<float>(0,i) ;
            PointCloud.points[i].y = this->_LUTsphere.at<float>(1,i) ;
            PointCloud.points[i].z = this->_LUTsphere.at<float>(2,i) ;
        }

        row_ind++;

        if (row_ind == this->camera_1->_cameraParam.imSize.rows)
        {
            row_ind = 0;
            col_ind++;
        }

        if (i == pix_im1-1)
        {
            mask = this->camera_2->_Mask;
            row_ind = 0;
            col_ind = 0;
        }

        ptr_mask = mask.ptr<uchar>(row_ind) + col_ind;
    }
}

void OmniCameraRig::messRGBSph(sensor_msgs::PointCloud &PointCloud)
{
    if (!this->isInit()) return;

    if (this->_LUTsphere.empty()) return;

    PointCloud.header.stamp = ros::Time::now();

    int row_ind = 0;
    int col_ind = 0;

    int pix_im1 = this->camera_1->_cameraParam.imSize.cols * this->camera_1->_cameraParam.imSize.rows;

    cv::Mat im_val;

    this->camera_1->_Frame.convertTo(im_val,CV_32FC3);
    cv::Mat mask = this->camera_1->_Mask;

    const cv::Vec3f *ptr_pix;
    ptr_pix = im_val.ptr<cv::Vec3f>(row_ind) + col_ind;

    const uchar *ptr_mask;
    ptr_mask = mask.ptr<uchar>(row_ind) + col_ind;

    for (int i = 0; i<(this->_LUTsphere.cols); i++)
    {
        if (*ptr_mask > 0)
        {
            PointCloud.channels[0].values[i] = ((*ptr_pix)[2])/255.0; //r
            PointCloud.channels[1].values[i] = ((*ptr_pix)[1])/255.0; //g
            PointCloud.channels[2].values[i] = ((*ptr_pix)[0])/255.0; //b
        }

        row_ind++;

        if (row_ind == this->camera_1->_cameraParam.imSize.rows)
        {
            row_ind = 0;
            col_ind++;
        }

        if (i == (pix_im1-1))
        {
            this->camera_2->_Frame.convertTo(im_val,CV_32FC3);
            mask = this->camera_2->_Mask;
            row_ind = 0;
            col_ind = 0;
        }

        ptr_pix = im_val.ptr<cv::Vec3f>(row_ind) + col_ind;
        ptr_mask = mask.ptr<uchar>(row_ind) + col_ind;
    }
}


void OmniCameraRig::downSample(int sampling_ratio)
{
    this->camera_1->DownSample(sampling_ratio);
    this->camera_2->DownSample(sampling_ratio);

    this->applyBaseline();

    this->mergeLUTSph();

    this->_isSampled = true;
    this->_sampling_ratio = sampling_ratio;
}

void OmniCameraRig::sph2Pano()
{
    if (!this->isInit()) return;
    if (this->_LUTsphere.empty()) return;

    double min,max;

    cv::Mat tmp;

    this->rotate90roll();

    Cart2Sph(this->_LUTsphere, tmp);

    this->_LUT_wrap_im = cv::Mat::zeros(tmp.size(),CV_16UC1);

    cv::minMaxLoc(tmp.row(0),&min,&max);

    tmp.row(0).convertTo(this->_LUT_wrap_im.row(0), CV_16UC1
                         ,(double)((this->_panoSize.height-1)/(max-min)),(double)(- (min * ((this->_panoSize.height-1)/(max-min)))));

    cv::minMaxLoc(tmp.row(1),&min,&max);

    tmp.row(1).convertTo(this->_LUT_wrap_im.row(1), CV_16UC1
                         ,(double)((this->_panoSize.width-1)/(max-min)),(double)(- (min * ((this->_panoSize.width-1)/(max-min)))));
}

void OmniCameraRig::sph2HealPano()
{
    if (!this->isInit()) return;
    if (this->_LUTsphere.empty()) return;

    double min,max;

    cv::Mat tmp, tmp2;

    this->rotate90roll();

    Cart2Sph(this->_LUTsphere, tmp);

    Sph2Heal(tmp,tmp2);

    tmp.release();

    this->_LUT_wrap_im = cv::Mat::zeros(tmp2.size(),CV_16UC1);

    cv::minMaxLoc(tmp2.row(0),&min,&max);

    tmp2.row(0).convertTo(this->_LUT_wrap_im.row(0), CV_16UC1
                          ,(double)((this->_panoSize.height-1)/(max-min)),(double)(- (min * ((this->_panoSize.height-1)/(max-min)))));

    cv::minMaxLoc(tmp2.row(1),&min,&max);

    tmp2.row(1).convertTo(this->_LUT_wrap_im.row(1), CV_16UC1
                          ,(double)((this->_panoSize.width-1)/(max-min)),(double)(- (min * ((this->_panoSize.width-1)/(max-min)))));

}
