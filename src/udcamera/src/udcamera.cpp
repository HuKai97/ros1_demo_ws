#include "udcamera.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "udcamera");
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh("~");

    int width = 3840;
    int height = 1080;

    image_transport::ImageTransport it(nh_);
    image_transport::Publisher camera_pub = it.advertise("/udcamera/image", 1);

    cv::VideoCapture cap;
    cap.open("/dev/video0");
    cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    cap.set(CV_CAP_PROP_FPS, 30);

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(30);
    while (nh_.ok())
    {
        if (cap.isOpened())
        {
            cap >> frame;
            if (!frame.empty())
            {
                msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
                camera_pub.publish(msg);
                // cv::imshow("left", frame);
                // cv::waitKey(2);
            }
        }
        else
        {
            ROS_INFO("can not opencv video device\n");
        }
    }

    ros::spinOnce();
    loop_rate.sleep();

    return 0;
}
