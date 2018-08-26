#! /usr/bin/env python

import roslib
roslib.load_manifest('leobot_vision')
import sys
import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:
    def __init__(self):
        self.image_pub = rospy.Publisher("/camera", Image, queue_size=2)

        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/right_fisheye_camera/image_raw", Image, self.callback)

    def callback(self, data):
        try:
            original_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        (rows, cols, channels) = original_image.shape
        if cols > 60 and rows > 60:
            cv2.circle(original_image, (cols/2, rows/2), min(cols, rows)/2-1, (255, 255, 255))

        resulting_image = original_image

        cv2.imshow("Image window", resulting_image)
        cv2.waitKey(3)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(resulting_image, "bgr8"))
        except CvBridgeError as e:
            print(e)


def main(args):
    rospy.init_node('image_converter')
    ic = image_converter()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main(sys.argv)
