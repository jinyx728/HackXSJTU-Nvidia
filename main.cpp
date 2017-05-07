#include "object_detection.h"
#include <ros/ros.h>
#include <ros/package.h>
#include "std_msgs/String.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "time_helper.h"
#include "geometry_msgs/Twist.h"
#include <signal.h>
#include <iostream>


geometry_msgs::Twist cmd = geometry_msgs::Twist();
geometry_msgs::Twist cmd2 = geometry_msgs::Twist();	
int flag = 0;


void turn_left()
{
	cmd.linear.x = 3.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void turn_right()
{
	cmd.linear.x = 4.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void move_forward()
{
	cmd.linear.x = 1.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void move_back()
{
	cmd.linear.x = 2.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void stop()
{
 	cmd.linear.x = 5.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void left_forward()
{
	cmd.linear.x = 7.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void right_forward()
{
	cmd.linear.x = 6.0;
	cmd.linear.y = 0.0;
	cmd.linear.z = 0.0;
	cmd.angular.x = 0.0;
	cmd.angular.y = 0.0;
	cmd.angular.z = 0.0;
}

void terminate()
{
	cmd2.linear.x = 8.0;
	cmd2.linear.y = 0.0;
	cmd2.linear.z = 0.0;
	cmd2.angular.x = 0.0;
	cmd2.angular.y = 0.0;
	cmd2.angular.z = 0.0;
}


void handler(int sig)
{
	flag = 1;
}


int main(int argc, char **argv)
{
	
	ros::init(argc,argv,"ros_caffe_test");
	ros::NodeHandle nh;
	ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("stop", 1);
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("keyboard",1);
        ros::Rate loop_rate(20);
        const std::string ROOT_SAMPLE = ros::package::getPath("ros_caffe");
        std::string configfile=ROOT_SAMPLE+"/src/object_detection-v2/config/config.xml";
	SSD ssd(configfile);
  	
        std::string result;
	std::string presult;
        cv::VideoCapture vcap(0);
        
	signal(SIGQUIT, handler);

    	if (false == vcap.isOpened())
    	{
        	ROS_ERROR_STREAM( "camera cannot open!");
        	ros::shutdown;
    	}
    
    	cv_bridge::CvImagePtr frame;
    	frame = boost::make_shared<cv_bridge::CvImage>();
    	frame->encoding=sensor_msgs::image_encodings::BGR8;

    	cv::Mat image;
    	while(true)
	{
	  std::cout << flag << "1st"<<std::endl;
	  if (flag == 1){
		flag = 0;
		ROS_ERROR_STREAM( "keyboard interrupt!");
		terminate();
		pub2.publish(cmd2);
		std::cout << flag << "2nd"<<std::endl;
	  }
	  vcap >> image;
    	  __TIC__();
	  std::string result = ssd.detect(image);
		
	  if(result == "cat")
	    turn_left();
	  else if (result == "person")
    	    turn_right();
	  else if (result == "car")
	    move_forward();
	  else if (result == "chair")
	    move_back();
	  else if (result == "aeroplane")
            left_forward();
	  else if (result == "horse")
	    right_forward();
	  else
	    stop();
		
	  pub.publish(cmd);
    	  std::cout << flag << "3rd"<<std::endl;   
          __TOC__();
	  loop_rate.sleep();
	  cv::waitKey(1);
	  
	}
    
    
    return 0;
}

