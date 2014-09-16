#include "omnidirectional_rig/omni_camera.h"


OmniCamera::OmniCamera(const std::string &paramPath)
{
    this->_init = this->_loadParam(paramPath);
    _isSampled = false;
    _sampling_ratio = 1;
}

OmniCamera::~OmniCamera()
{
}

bool OmniCamera::_loadParam(const std::string &paramPath)
{
    cv::FileStorage fs(paramPath,cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        std::cout<<"Failed to open "<<paramPath<< std::endl;
        return false;
    }

    fs["type"] >> this->_cameraParam.cameraType;
    fs["xi"] >> this->_cameraParam.xi;
    fs["K"] >> this->_cameraParam.intrinParam;

    cv::FileNode fn = fs["image_size"];

    fn["rows"] >> this->_cameraParam.imSize.rows;
    fn["cols"] >> this->_cameraParam.imSize.cols;

    fs.release();

    this->_cameraParam.intrinParam.convertTo(this->_cameraParam.intrinParam,CV_32FC1);

    return true;
}

std::string OmniCamera::GetType(){
    return this->_cameraParam.cameraType;
}

double OmniCamera::GetXi(){
    return this->_cameraParam.xi;
}

cv::Mat OmniCamera::GetIntrinsic(){
    return this->_cameraParam.intrinParam;
}

imageSize OmniCamera::GetImageSize(){

    return this->_cameraParam.imSize;
}

bool OmniCamera::IsSampled(){
    return this->_isSampled;
}

cv::Mat OmniCamera::GetLUT(){
    return this->_LUTsphere;
}

cv::Mat OmniCamera::GetLUT(const std::string &LUT ){

    std::string LUTsphere =  "Sphere";
    std::string LUTheal = "Healpix";
    std::string LUTplatte = "PlCa";

    if (LUT.compare(LUTsphere) == 0 && !this->_LUTsphere.empty())
    {
        return this->_LUTsphere;

    }else if(LUT.compare(LUTheal) == 0 && !this->_LUT_wrap_im.empty()){

        return this->_LUT_wrap_im;

    }else if(LUT.compare(LUTplatte) == 0 && !this->_LUT_wrap_im.empty()){

        return this->_LUT_wrap_im;

    }else{

        std::cout<<"Wrong LUT choice, please choose a correct option :\n"<<
                   "1 : 'Sphere' for points lying on the S2 sphere\n"<<
                   "2 : 'Healpix' for the Healpix unwrapped points\n"<<
                   "3 : 'PlCa' for Platte Carree unwrapped points"<<std::endl;

        return cv::Mat();
    }
}

cv::Mat OmniCamera::GetMask(){
    return this->_Mask;
}


void OmniCamera::setImage(const cv::Mat &image)
{
    this->_Frame = image.clone();
    if(this->_isSampled) cv::resize(this->_Frame,this->_Frame,cv::Size(),
                                    1.0/this->_sampling_ratio,1.0/this->_sampling_ratio);
}


//void OmniCamera::ReadFrame(){

//    sensor_msgs::ImageConstPtr frame;// = ImageHandler::waitUntilImageReceived();

//    cv_bridge::CvImagePtr cvPtr;

//    cvPtr = cv_bridge::toCvCopy(frame,"8UC3");

//    this->_Frame = cvPtr->image;

//    if(this->_isSampled) cv::resize(this->_Frame,this->_Frame,cv::Size(),1.0/this->_sampling_ratio,1.0/this->_sampling_ratio);
//}

cv::Mat OmniCamera::getImage(){
    return this->_Frame;
}

bool OmniCamera::IsInit(){
    return this->_init;
}

void OmniCamera::SetType(const std::string& type){
    this->_cameraParam.cameraType = type;
}

void OmniCamera::SetXi(double xi){
    this->_cameraParam.xi = xi;
}

void OmniCamera::SetIntrinsic(const cv::Mat &intrin){
    this->_cameraParam.intrinParam = intrin;
}

void OmniCamera::SetImageSize(const imageSize &imSize){
    this->_cameraParam.imSize = imSize;
}

void OmniCamera::SetImageSize(int rows, int cols){
    this->_cameraParam.imSize.rows = rows;
    this->_cameraParam.imSize.cols = cols;
}

void OmniCamera::SetLUTSph(const cv::Mat &LUTSph)
{
    this->_LUTsphere = LUTSph;
}

void OmniCamera::ReleaseLut(){
    if (!this->_LUT_wrap_im.empty()) this->_LUT_wrap_im.release();
    if (!this->_LUTsphere.empty()) this->_LUTsphere.release();
}

void OmniCamera::DispParam()
{
    std::cout << "camera type : " << this->_cameraParam.cameraType << std::endl;

    std::cout << "camera xi   : " << this->_cameraParam.xi << std::endl;

    std::cout << "camera intrinsic parameters : \n " << this->_cameraParam.intrinParam << std::endl;

    std::cout << "image size :\n   rows : " << this->_cameraParam.imSize.rows
              << "\n   cols : " << this->_cameraParam.imSize.cols << std::endl<< std::endl;
}


void OmniCamera::LoadMask(const std::string& maskFile){

    if (maskFile.empty()) return;

    cv::Mat tmp;
    tmp = cv::imread(maskFile,CV_LOAD_IMAGE_GRAYSCALE);
    cv::threshold(tmp,tmp,240,1,cv::THRESH_BINARY);
    tmp.convertTo(this->_Mask,CV_8UC1);
}

void OmniCamera::readImage(const std::string &file){

    ROS_DEBUG_STREAM("Reading image " << file);
    this->_Frame = cv::imread(file);
    if(this->_isSampled) cv::resize(this->_Frame,this->_Frame,cv::Size(),
                                    1.0/this->_sampling_ratio,1.0/this->_sampling_ratio);
}

void OmniCamera::Im2Sph(int rows,int cols){

    if (!this->IsInit()) return;

    if (this->_Mask.empty()) this->_Mask = cv::Mat::ones(this->_cameraParam.imSize.rows,this->_cameraParam.imSize.cols,CV_8UC1);

    this->_LUTsphere = cv::Mat::zeros(3,rows * cols,CV_32FC1);

    cv::Mat pts = cv::Mat::ones(3,1,CV_32FC1);

    float alpha;

    int i = 0;

    cv::Mat inv_K = this->_cameraParam.intrinParam.inv();

    std::complex<float> tmp;

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (!this->_Mask.at<uchar>(row,col) == 0)
            {
                pts.at<float>(0) = (float)col;
                pts.at<float>(1) = (float)row;

                pts = inv_K * pts;

                tmp = std::sqrt( std::complex<float>(pts.at<float>(2) * pts.at<float>(2) + (1 - this->_cameraParam.xi * this->_cameraParam.xi) *
                                                    (pts.at<float>(0) * pts.at<float>(0) + pts.at<float>(1) * pts.at<float>(1))) );

                alpha = (this->_cameraParam.xi * pts.at<float>(2) + (float)tmp.real())
                        / (pts.at<float>(0) * pts.at<float>(0) + pts.at<float>(1) * pts.at<float>(1) + pts.at<float>(2) * pts.at<float>(2));

                this->_LUTsphere.at<float>(0,i) = pts.at<float>(0) * alpha;
                this->_LUTsphere.at<float>(1,i) = pts.at<float>(1) * alpha;
                this->_LUTsphere.at<float>(2,i) = pts.at<float>(2) * alpha - this->_cameraParam.xi;
            }
            i++;
        }
    }
}

void OmniCamera::Im2Sph(const cv::Size &im){
    this->Im2Sph(im.height,im.width);
}

cv::Vec3f OmniCamera::Pix2Sph(int ind_row, int ind_col)
{
    cv::Vec3f pts;

    cv::Mat _pts = cv::Mat::ones(3,1,CV_32FC1);

    _pts.at<float>(0) = ind_col;
    _pts.at<float>(1) = ind_row;

    float alpha;

    _pts = this->_cameraParam.intrinParam.inv() * _pts;

    alpha = (this->_cameraParam.xi * _pts.at<float>(2) + sqrt(_pts.at<float>(2)*_pts.at<float>(2) + (1-this->_cameraParam.xi*this->_cameraParam.xi)*
            (_pts.at<float>(0)*_pts.at<float>(0) + _pts.at<float>(1)*_pts.at<float>(1)))) / cv::norm(_pts);

    pts[0] = _pts.at<float>(0) * alpha;
    pts[1] = _pts.at<float>(1) * alpha;
    pts[2] = _pts.at<float>(2) * alpha - this->_cameraParam.xi;

    return pts;
}

void OmniCamera::DownSample(int sampling_ratio)
{
    if (!this->IsInit()) return;

    this->_cameraParam.imSize.cols /= sampling_ratio;
    this->_cameraParam.imSize.rows /= sampling_ratio;

    this->_cameraParam.intrinParam /= sampling_ratio;
    this->_cameraParam.intrinParam.at<float>(2,2) = 1;

    if (!this->_Frame.empty()) cv::resize(this->_Frame,this->_Frame,cv::Size(),1.0/sampling_ratio,1.0/sampling_ratio);
    if (!this->_Mask.empty()) cv::resize(this->_Mask,this->_Mask,cv::Size(),1.0/sampling_ratio,1.0/sampling_ratio);
    if (!this->_LUTsphere.empty()) this->Im2Sph(this->_cameraParam.imSize.rows,this->_cameraParam.imSize.cols);

    this->_isSampled = true;
    this->_sampling_ratio = sampling_ratio;
}


void OmniCamera::Sph2Im(const cv::Mat &sphPoints)
{
    if (!this->IsInit() || sphPoints.empty()) return;

    this->_LUT_sampSph_im = cv::Mat::zeros(2,sphPoints.cols,CV_8U);

    int row,col;

    for (int i = 0; i < sphPoints.cols; i++)
    {
        col = (int)((sphPoints.at<float>(0,i) * this->_cameraParam.intrinParam.at<float>(0,0)) /
              (sphPoints.at<float>(2,i) + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(0,2));

        row = (int)((sphPoints.at<float>(1,i) * this->_cameraParam.intrinParam.at<float>(1,1)) /
                (sphPoints.at<float>(2,i) + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(1,2));

        this->_LUT_sampSph_im.at<int>(0,i) = row;
        this->_LUT_sampSph_im.at<int>(1,i) = col;
    }
}

void OmniCamera::Sph2Im(const cv::Mat &sphPts,cv::Mat &imPts)
{
    if (!this->IsInit() || sphPts.empty()) return;

    imPts = cv::Mat::zeros(2,sphPts.cols,CV_32S);

    int row,col;

    for (int i = 0; i < sphPts.cols; i++)
    {
        col = (int)((sphPts.at<float>(0,i) * this->_cameraParam.intrinParam.at<float>(0,0)) /
              (sphPts.at<float>(2,i) + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(0,2));

        row = (int)((sphPts.at<float>(1,i) * this->_cameraParam.intrinParam.at<float>(1,1)) /
                (sphPts.at<float>(2,i) + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(1,2));

        imPts.at<int>(0,i) = row;
        imPts.at<int>(1,i) = col;
    }
}

cv::Vec2i OmniCamera::Sph2Im(float x, float y, float z)
{
    cv::Vec2i pix;
    int row,col;

    col = (int)((x * this->_cameraParam.intrinParam.at<float>(0,0)) /
          (z + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(0,2));

    row = (int)((y * this->_cameraParam.intrinParam.at<float>(1,1)) /
            (z + this->_cameraParam.xi) + this->_cameraParam.intrinParam.at<float>(1,2));

    pix[0] = row;
    pix[1] = col;

    return pix;
}


void OmniCamera::Sph2Pano()
{
    if (!this->IsInit()) return;
    if (this->_LUTsphere.empty()) return;

    Cart2Sph(this->_LUTsphere,this->_LUT_wrap_im);
}




