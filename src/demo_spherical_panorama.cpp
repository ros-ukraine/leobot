#include "omnidirectional_rig/image_handler.h"
#include "omnidirectional_rig/poly_omni.h"

#include <opencv2/core/core.hpp>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cvwimage.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <string>


int main(int argc, char** argv){

    ros::init(argc,argv, "omnicamera_live");
    ros::NodeHandle nh;

    std::vector<std::string> topics_name;
    nh.getParam("/spherical_vision/topic_left",topics_name);

    OmniCameraRig omniSys;

    if (!omniSys.isInit())
    {
        ROS_ERROR( "Omni System Not Init !" );
        return 2;
    }

    image_transport::ImageTransport imTrans(nh);
    sensor_msgs::Image img_msg;
    image_transport::Publisher pub = imTrans.advertise("/omni_camera/panorama", 1);
    cv_bridge::CvImage cv_img;

    cv_img.encoding = "bgr8";

    omniSys.dispParam();

    omniSys.setPanoSize(400,1000);

    omniSys.mergeLUTWrap();

    SyncImageHandler syncImageHandler(topics_name[0],topics_name[1]);

//     //Test with images from disk
//    std::string imCam1 = "/home/student/JeremieDeray/rosbag/run3/images/omni/left/025Img_10.8304_-2.4232_0_0_-0.112161_0.99369.jpg";
//    std::string imCam2 = "/home/student/JeremieDeray/rosbag/run3/images/omni/right/025Img_10.8304_-2.4232_0_0_-0.112161_0.99369.jpg";
//    omniSys.camera_1->readImage(imCam1);
//    omniSys.camera_2->readImage(imCam2);

//    time = (double)cv::getTickCount();
//    omniSys.StitchImage();
//    std::cout << "time to stitch : "<<((double)cv::getTickCount() - time) / cv::getTickFrequency()<<std::endl<<std::endl;

//    cv::namedWindow("pano");
//    cv::imshow("pano",omniSys.GetPano());
//    cv::waitKey(0);
//    cv::destroyWindow("pano");
//    return 0;

    std::vector<cv::Mat> images;

    do
    {
        syncImageHandler.waitUntilImages(images);

        omniSys.camera_1->setImage(images[0]);
        omniSys.camera_2->setImage(images[1]);

        omniSys.stitchImage();

        cv_img.image = omniSys.getPano();

        cv_img.toImageMsg(img_msg);

        img_msg.header.stamp = ros::Time::now();

        pub.publish(img_msg);

        //TODO : exit on key pressing

    }while(ros::ok());

    return 0;
}
