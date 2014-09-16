#include "omnidirectional_rig/image_handler.h"
#include "omnidirectional_rig/poly_omni.h"

#include <opencv2/core/core.hpp>

#include <iostream>
#include <string>

// //needed by demo from image files
//#include <boost/range/combine.hpp>
//#include <boost/tuple/tuple.hpp>
//#include <boost/foreach.hpp>

int main(int argc, char** argv){

    //if (argc != 3) ROS_ERROR("Usage: demo_omni_oculus <rootpath_to_conf_files>");

    int sampling_ratio = atof(argv[1]);
    std::string conf_path = argv[2];

    ros::init(argc,argv, "demo_spherical_oculus");

    ros::NodeHandle nh;

    std::vector< cv::Mat > images;

    std::vector<std::string> path_yamls_cam;
    std::vector<std::string> topics_name;
    std::string maskCamera_1;
    std::string maskCamera_2;
    std::string extrinParam;

    ros::Publisher pub_CloudSph = nh.advertise<sensor_msgs::PointCloud>("/cloud_sphere",1);

    nh.getParam("/spherical_vision/topics",topics_name);

    path_yamls_cam.push_back(AddPath("etc/calib/proto2/Pal_intrinsicParam_cam1.yaml",conf_path));
    path_yamls_cam.push_back(AddPath("etc/calib/proto2/Pal_intrinsicParam_cam2.yaml",conf_path));

    extrinParam = AddPath("etc/calib/proto2/Pal_extrinsicParam.yaml",conf_path);

    maskCamera_1  = AddPath("etc/images/cam1/Img_mask1.jpg",conf_path);
    maskCamera_2  = AddPath("etc/images/cam2/Img_mask2.jpg",conf_path);

    SyncImageHandler syncImageHandler(topics_name[0],topics_name[1]);
    OmniCameraRig omniSys(path_yamls_cam,extrinParam);

    omniSys.dispParam();

    omniSys.camera_1->LoadMask(maskCamera_1);
    omniSys.camera_2->LoadMask(maskCamera_2);

    omniSys.downSample(sampling_ratio);

    omniSys.dispParam();

    sensor_msgs::PointCloud ptsCld;

//    double time;

    omniSys.partiallyFillMess(ptsCld);

    ros::AsyncSpinner aspin(1);
    aspin.start();

    do
    {
        syncImageHandler.waitUntilImages(images);

        omniSys.camera_1->setImage(images[0]);
        omniSys.camera_2->setImage(images[1]);

        //time = (double)cv::getTickCount();

        omniSys.messRGBSph(ptsCld);

        //std::cout << "time to comp sphere : "<<((double)cv::getTickCount() - time) / cv::getTickFrequency()<<std::endl<<std::endl;

        //time = (double)cv::getTickCount();

        pub_CloudSph.publish(ptsCld);

        //std::cout << "time to publish sphere : "<<((double)cv::getTickCount() - time) / cv::getTickFrequency()<<std::endl<<std::endl;

        //TODO : exit on key pressing

        cv::waitKey(500);

    } while (ros::ok());


      ////// Demo example : image from folder

//    std::set<std::string> imagesR = loadFilesName("/home/student/JeremieDeray/rosbag/runvideo/images/1/left/");
//    std::set<std::string> imagesL = loadFilesName("/home/student/JeremieDeray/rosbag/runvideo/images/1/right/");

//    std::string file1,file2;

//    BOOST_FOREACH(boost::tie(file1,file2), boost::combine(imagesR,imagesL))
//    {
//        omniSys.camera_1->readImage(file1);
//        omniSys.camera_2->readImage(file2);

//        omniSys.messRGBSph(ptsCld);

//        pub_CloudSph.publish(ptsCld);

//        ros::spinOnce();

//        cv::waitKey(500);

//        //TODO : exit on key pressing
//    }
//    return 0;

}
