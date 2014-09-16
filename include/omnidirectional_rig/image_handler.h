#ifndef IMAGE_HANDLER_H_
#define IMAGE_HANDLER_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <message_filters/subscriber.h>
#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


class SingleImageHandler
{

public:

    SingleImageHandler(const std::string &topicName);
    ~SingleImageHandler();

    bool isImageReceived();

    void getImage(sensor_msgs::ImageConstPtr&);
    void waitUntilImageReceived(sensor_msgs::ImageConstPtr&);

    void getImage(cv::Mat&);
    void waitUntilImageReceived(cv::Mat&);

    void saveImage(const std::string &name, const cv::Mat& image);
    void saveImage(const std::string &name, const IplImage* image);
    void readImage(const std::string &file, cv::Mat& img);

protected:

    ros::NodeHandle _nh;
    ros::CallbackQueue _cbqueue;
    image_transport::ImageTransport _it;
    image_transport::Subscriber _subscriber;
    sensor_msgs::ImageConstPtr _image;

    std::string folder;
    bool _imageReceived;

    void topicCallback(const sensor_msgs::ImageConstPtr& received_image);
};


class SyncImageHandler
{

    typedef message_filters::sync_policies::ApproximateTime<
            sensor_msgs::Image,
            sensor_msgs::Image> ApproxSync;

public:

    SyncImageHandler() :_imageReceived(false) {}
    SyncImageHandler(const std::string &topic1, const std::string &topic2);
    ~SyncImageHandler();

    void init(const std::string &topic1, const std::string &topic2);

    void getImages(std::vector<sensor_msgs::ImageConstPtr >&);
    void waitUntilImages(std::vector<sensor_msgs::ImageConstPtr >&);

    void getImages(std::vector<cv::Mat >&);
    void waitUntilImages(std::vector<cv::Mat >&);

    void saveImages(const std::string &common_name, const std::vector<cv::Mat > &images);

protected:

    ros::NodeHandle _nh;

    void stereoCallback(const sensor_msgs::ImageConstPtr& msgImg1,
                        const sensor_msgs::ImageConstPtr& msgImg2);

    std::vector<sensor_msgs::ImageConstPtr> _images;
    boost::shared_ptr<image_transport::ImageTransport> _imageTransport;

    boost::shared_ptr<image_transport::SubscriberFilter> _imgSub1, _imgSub2;

//    boost::ptr_vector<image_transport::SubscriberFilter> _imSubs;

    boost::shared_ptr<message_filters::Synchronizer<ApproxSync> > _approxSynchronizer;

    bool _imageReceived;
};

#endif  // IMAGE_HANDLER_H_
