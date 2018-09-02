#! /usr/bin/env python

import roslib
roslib.load_manifest('leobot_vision')
import sys
import rospy
import numpy as np
import cv2 as cv
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:
    def __init__(self):
        self.image_pub = rospy.Publisher("/camera", Image, queue_size=2)

        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/right_fisheye_camera/image_raw", Image, self.callback)

    def create_blank_image(self, size, channels, data_type):
        """Create new image(numpy array) filled with certain color in RGB"""
        # Create black blank image
        image_matrix_dimensions = size + (channels,)

        # image = np.zeros((width, height, channels), data_type)
        image = np.zeros(image_matrix_dimensions, data_type)

        # Since OpenCV uses BGR, convert the color first
        # color = tuple(reversed(rgb_color))
        # Fill image with color
        image[:] = np.zeros(channels)

        return image

    def callback(self, data):
        try:
            original_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        (rows, cols, channels) = original_image.shape
        if cols > 60 and rows > 60:
            cv.circle(original_image, (cols/2, rows/2), min(cols, rows)/2-1, (255, 255, 255))

        # resulting_image = original_image

        original_image_size = original_image.shape[:2][::-1]

        # fx, fy, cx, cy, k1, k2, p1, p2, output = argv[2:]
        # 1367.451167 1367.451167 0 0 -0.246065 0.193617 -0.002004 -0.002056

        fx = 1367.451167
        fy = 1367.451167
        cx = original_image_size[0]
        cy = original_image_size[1]
        k1 = -0.246065
        k2 = 0.193617
        p1 = -0.002004
        p2 = -0.002056

        # intrinsics = cv.CreateMat(3, 3, cv.CV_64FC1)
        intrinsics = np.zeros((3, 3), np.float64)
        # cv.Zero(intrinsics)
        intrinsics[0, 0] = float(fx)
        intrinsics[1, 1] = float(fy)
        intrinsics[2, 2] = 1.0
        intrinsics[0, 2] = float(cx)
        intrinsics[1, 2] = float(cy)

        # dist_coeffs = cv.CreateMat(1, 4, cv.CV_64FC1)
        dist_coeffs = np.zeros((1, 4), np.float64)
        # cv.Zero(dist_coeffs)
        dist_coeffs[0, 0] = float(k1)
        dist_coeffs[0, 1] = float(k2)
        dist_coeffs[0, 2] = float(p1)
        dist_coeffs[0, 3] = float(p2)

        # print "original_image_size ", original_image_size

        mapx, mapy = cv.initUndistortRectifyMap(cameraMatrix=intrinsics, distCoeffs=dist_coeffs, R=np.eye(3), newCameraMatrix=intrinsics, size=original_image_size, m1type=cv.CV_32FC1)

        # print "intrinsics ", intrinsics
        # print "dist_coeffs ", dist_coeffs

        # print "mapx ", mapx
        # print "mapy ", mapy

        resulting_image = cv.remap(src=original_image, map1=mapx, map2=mapy, interpolation=cv.INTER_LINEAR, borderMode=cv.BORDER_CONSTANT)

        # cv.SaveImage(output, resulting_image)

        cv.imshow("Source", original_image)
        cv.imshow("Converted", resulting_image)
        cv.waitKey(3)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(resulting_image, "bgr8"))
        except CvBridgeError as e:
            print(e)


def main(args):
    print "Version: " + cv.__version__
    rospy.init_node('image_converter')
    ic = image_converter()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv.destroyAllWindows()


if __name__ == '__main__':
    main(sys.argv)
