#! /usr/bin/env python

import roslib
roslib.load_manifest('leobot_vision')
import sys
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:
    def __init__(self):
        self.image_pub = rospy.Publisher("/camera", Image, queue_size=2)

        # self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/right_fisheye_camera/image_raw", Image, self.callback)

    def callback(self, data):
        try:
            # cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            print 'Callback!'
            self.image_pub.publish(data)
        except CvBridgeError as e:
            print(e)

        # (rows, cols, channels) = cv_image.shape
        # if cols > 60 and rows > 60:
        #     cv2.circle(cv_image, (50, 50), 10, 255)
        #
        # cv2.imshow("Image window", cv_image)
        # cv2.waitKey(3)
        #
        # try:
        #     self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
        # except CvBridgeError as e:
        #     print(e)


def main(args):
    rospy.init_node('image_converter')
    ic = image_converter()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    # cv2.destroyAllWindows()


if __name__ == '__main__':
    main(sys.argv)
