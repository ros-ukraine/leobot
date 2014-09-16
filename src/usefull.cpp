#include "omnidirectional_rig/usefull.h"

#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>


void Cart2Sph(const cv::Mat& cart_coor, cv::Mat& sph_coor, int rad_flag )
{
    // Uses Physics convention (r,theta,phi)
    // with r radial distance
    // theta polar angle from Z axis (range 0 - PI)
    // phi azimuthal angle in X-Y plan and from X axis (range 0 - 2PI)

    if (!cart_coor.rows==3)
    {
        return;
    }

    float x,y,z;

    float el,az,rad;

    if(rad_flag == 1){

        sph_coor = cv::Mat::ones(3,cart_coor.cols,CV_32F);

        for (int i=0;i<cart_coor.cols;i++)
        {
            x = cart_coor.at<float>(0,i);
            y = cart_coor.at<float>(1,i);
            z = cart_coor.at<float>(2,i);

            rad = sqrt( x*x + y*y + z*z ); //r
            el = acos(z / rad); //elevation
            az = atan2(y,x); //azimmuth

            if (az < 0) az += (2*mypi);

            sph_coor.at<float>(0,i) = el;
            sph_coor.at<float>(1,i) = az;
            sph_coor.at<float>(2,i) = rad;
        }
    }else{

        sph_coor = cv::Mat::ones(2,cart_coor.cols,cart_coor.type());

        for (int i=0;i<cart_coor.cols;i++)
        {
            x = cart_coor.at<float>(0,i);
            y = cart_coor.at<float>(1,i);
            z = cart_coor.at<float>(2,i);

            el = acos(z / sqrt( x*x + y*y + z*z)); //elevation
            az = atan2(y,x); //azimmuth

            if (az < 0) az += (2*mypi);

            sph_coor.at<float>(0,i) = el;
            sph_coor.at<float>(1,i) = az;
        }
    }
}


void MeshGrid(const cv::Mat &X_val, const cv::Mat &Y_val, cv::Mat &X_grid, cv::Mat &Y_grid)
{
    cv::repeat(X_val,Y_val.total(),1,X_grid);
    cv::repeat(Y_val.reshape(1,1).t(),1,X_val.total(),Y_grid);
}


void Sph2Cart(const cv::Mat &sph_pts, cv::Mat &cart_pts)
{
    cv::Mat cart_pts_tmp = cv::Mat::zeros(3,sph_pts.cols,sph_pts.type());

    // Uses Physics convention (r,theta,phi)
    // with r radial distance
    // theta polar angle from Z axis (range 0 - PI)
    // phi azimuthal angle in X-Y plan and from X axis (range 0 - 2PI)

    if (sph_pts.rows == 2)
    {
        for (int i=0; i<sph_pts.cols; i++)
        {
            cart_pts_tmp.at<float>(0,i) = sin(sph_pts.at<float>(0,i)) * cos(sph_pts.at<float>(1,i));
            cart_pts_tmp.at<float>(1,i) = sin(sph_pts.at<float>(0,i)) * sin(sph_pts.at<float>(1,i));
            cart_pts_tmp.at<float>(2,i) = cos(sph_pts.at<float>(0,i));
        }

    }else if (sph_pts.rows == 3){

        for (int i=0; i<sph_pts.cols; i++)
        {
            cart_pts_tmp.at<float>(0,i) = sph_pts.at<float>(2,i) * sin(sph_pts.at<float>(0,i)) * cos(sph_pts.at<float>(1,i));
            cart_pts_tmp.at<float>(1,i) = sph_pts.at<float>(2,i) * sin(sph_pts.at<float>(0,i)) * sin(sph_pts.at<float>(1,i));
            cart_pts_tmp.at<float>(2,i) = sph_pts.at<float>(2,i) * cos(sph_pts.at<float>(0,i));
        }
    }else{
        return;
    }

    cart_pts_tmp.convertTo(cart_pts,sph_pts.type());
}

void Sph2Heal(const cv::Mat &sph_pts, cv::Mat &healPts)
{
    float H = 4.;

    float K = 3.;

    float thresh = mypi / 2.;

    float theta_c = std::asin(2./K);

    float xi_c, phi_c, el, azi;

    cv::Mat healPts_tmp = cv::Mat::zeros(2,sph_pts.cols,CV_32F);

    for (int i=0; i<sph_pts.cols; i++)
    {

        if (sph_pts.at<float>(0,i) < thresh)
        {
            el = - (sph_pts.at<float>(0,i) - thresh);
        }else{
            el = thresh - sph_pts.at<float>(0,i);
        }

        if (sph_pts.at<float>(1,i) < mypi)
        {
            azi = sph_pts.at<float>(1,i);
        }else{
            azi = sph_pts.at<float>(1,i) - (2*mypi);
        }

        if( std::abs(el) < theta_c )
        {
            healPts_tmp.at<float>(1,i) = azi;

            healPts_tmp.at<float>(0,i) = ((K*mypi)/(2.*H)) * std::sin(el);

        }else if( el < 0. ){

            xi_c = std::sqrt( K * ( 1. - std::abs( std::sin(el) ) ) );

            phi_c = -mypi + ( 2. * std::floor( ((azi+mypi)*H)/(2.*mypi) ) + 1. ) * (mypi / H);

            healPts_tmp.at<float>(1,i) = phi_c + (azi-phi_c) * xi_c;

            healPts_tmp.at<float>(0,i) = - (mypi/H) * (2.-xi_c);

        }else{

            xi_c = std::sqrt( K * ( 1. - std::abs( std::sin(el) ) ) );

            phi_c = -mypi + ( 2. * std::floor( ((azi+mypi)*H)/(2*mypi) ) + 1. ) * (mypi / H);

            healPts_tmp.at<float>(1,i) = phi_c + (azi-phi_c) * xi_c;

            healPts_tmp.at<float>(0,i) = (mypi/H) * (2.-xi_c);

        }
    }

    healPts_tmp.convertTo(healPts,sph_pts.type());
}

std::string AddPath(const std::string &obj, const std::string &root)
{
    std::stringstream ss;
            ss << root << "/" << obj;
            return ss.str();
}


void RotateCloudPoint(cv::Mat &ClPts, double roll, double pitch, double yaw, bool rad)
{
    cv::Mat rotationMat;
    cv::Mat tmp;

    rotationMat = GetRotationMat(roll,pitch,yaw,rad);

    rotationMat.convertTo(rotationMat,CV_32F);

    tmp = rotationMat * ClPts;

    tmp.convertTo(ClPts,ClPts.type());
}

cv::Mat GetRotationMat(double roll, double pitch, double yaw, bool rad)
{
    cv::Mat rotYaw = cv::Mat::eye(3,3,CV_64F);
    cv::Mat rotPitch = cv::Mat::eye(3,3,CV_64F);
    cv::Mat rotRoll = cv::Mat::eye(3,3,CV_64F);

    if (!rad)
    {
        yaw = Deg2Rad(yaw);
        pitch = Deg2Rad(pitch);
        roll = Deg2Rad(roll);
    }

    rotPitch.at<double>(0,0) =  cos( pitch ); //pitch
    rotPitch.at<double>(0,2) =  sin( pitch );
    rotPitch.at<double>(2,0) = -sin( pitch );
    rotPitch.at<double>(2,2) =  cos( pitch );


    rotYaw.at<double>(0,0) =  cos( yaw ); //yaw
    rotYaw.at<double>(0,1) = -sin( yaw );
    rotYaw.at<double>(1,0) =  sin( yaw );
    rotYaw.at<double>(1,1) =  cos( yaw );


    rotRoll.at<double>(1,1) =  cos( roll ); //roll
    rotRoll.at<double>(1,2) = -sin( roll );
    rotRoll.at<double>(2,1) =  sin( roll );
    rotRoll.at<double>(2,2) =  cos( roll );

    return rotYaw * rotPitch * rotRoll;
}

cv::Mat GetZYZRotationMat(double yaw1, double pitch, double yaw2, bool rad)
{
    cv::Mat rotYaw1 = cv::Mat::eye(3,3,CV_64F);
    cv::Mat rotPitch = cv::Mat::eye(3,3,CV_64F);
    cv::Mat rotYaw2 = cv::Mat::eye(3,3,CV_64F);

    if (!rad)
    {
        yaw1 = Deg2Rad(yaw1);
        pitch = Deg2Rad(pitch);
        yaw2 = Deg2Rad(yaw2);
    }

    rotPitch.at<double>(0,0) =  cos( pitch ); //pitch y
    rotPitch.at<double>(0,2) =  sin( pitch );
    rotPitch.at<double>(2,0) = -sin( pitch );
    rotPitch.at<double>(2,2) =  cos( pitch );

    rotYaw1.at<double>(0,0) =  cos( yaw1 ); //yaw1 z
    rotYaw1.at<double>(0,1) = -sin( yaw1 );
    rotYaw1.at<double>(1,0) =  sin( yaw1 );
    rotYaw1.at<double>(1,1) =  cos( yaw1 );

    rotYaw2.at<double>(0,0) =  cos( yaw2 ); //yaw2 z
    rotYaw2.at<double>(0,1) = -sin( yaw2 );
    rotYaw2.at<double>(1,0) =  sin( yaw2 );
    rotYaw2.at<double>(1,1) =  cos( yaw2 );


    return rotYaw1 * rotPitch * rotYaw2;
}

double Deg2Rad(double angle)
{
    return angle * (mypi/180.0);
}




void MatInfo(const cv::Mat &mat, const std::string &matname, bool val)
{
    std::cout<<"\nMat Info : \nName : "<<matname<<"\nisEmpty : "<<mat.empty()<<"\nrows : "<<mat.rows<<" cols : "<<mat.cols<<std::endl;
    std::cout<<"type : "<<mat.type()<<std::endl;

    if(val)
    {
        std::cout<<"\nvalues : "<<mat<<std::endl<<std::endl;
    }else{
        std::cout<<std::endl<<std::endl;
    }
}

void getListOfFilesInFolder(const std::string& path, const std::string& extension, std::vector<std::string>& baseFileNames)
{

    baseFileNames.clear();
    const int extensionLength = extension.length();

    boost::filesystem::directory_iterator end_iter;
    for (boost::filesystem::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter)
    {
        if (boost::filesystem::is_regular_file(dir_iter->status()))
        {
            std::string filename = dir_iter->path().filename().string();
            if (boost::algorithm::ends_with(filename, extension))
            {
                std::string basename = filename.substr(0, filename.length() - extensionLength);
                baseFileNames.push_back(basename);
            }
        }
    }
    std::sort(baseFileNames.begin(), baseFileNames.end());
}

std::set<std::string> loadFilesName(const std::string &dir)
{
    std::set<std::string> result;

    boost::filesystem::path directory(dir);
    if (!boost::filesystem::is_directory(dir))
    {
        std::cout << "DERE" << std::endl;
        return std::set<std::string>();

    }

    boost::filesystem::directory_iterator end_iter;
    for (boost::filesystem::directory_iterator it(dir); it != end_iter; ++it)
    {
        boost::filesystem::path file = it->path();

        if (boost::filesystem::is_regular_file(it->status()) && file.filename().string()[0] != '.')
        {
            result.insert(file.string());
        }
    }

    return result;
}

