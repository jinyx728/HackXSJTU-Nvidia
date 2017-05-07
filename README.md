# NVIDIA SMART CAR
 We made this project when we participated Hack x SJTU compotition.\
 Thanks NVIDIA for their technical support
## Group member:
[Jin Yongxu](https://github.com/JosephKim6)\
[Luo Anqi](https://github.com/AnastasiaAN)\
[Gou Minghao]()\
[Wang Tao](https://github.com/IrvingW)\
[Qian Xinxin]()

## Function Detail
We implemented a smart car using Arduino and TX1.
The smart car do some movement as following:
* Move forward when the camera detects a car
* Move Back when it detects a chair
* Turn left when it detects a cat
* Turn right when it detects a person
* Turn left then move forward when it detects a bird
* Turn right then move forward when it detects a bicycle
* Stop immediatily when the car meets an obstacle(using ultrasonic sensor)

## Techniques
* Caffe Deeplearning framework
* Arduino
* ROS
* OpenCV

## Picture
![Picture](https://github.com/JosephKim6/HackXSJTU-Nvidia/blob/master/4775AC0C5F0EC7A554805684CA0FF74F.jpg)

## Files
* car4.c is (controlling arduino)
* main.cpp is (controlling TX1)


## Deployment
You should use ROS to create a function package named ros_caffe\
Then create a node named ros_caffe_test

## Run
``` bash
  catkin_make
  roscore
  rosrun rosserial_python serial_node.py /dev/ttyACM0
  rosrun ros_caffe ros_caffe_test

```

#### Here is the [official website of Hackson.](https://www.hackx.org/)

