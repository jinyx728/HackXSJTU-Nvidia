#include <TimerOne.h>
#include <ros.h>
#include "SR04.h"
#include <geometry_msgs/Twist.h>
#include "DualMC33926MotorShield.h"

#define TRIG_PINL 22
#define ECHO_PINL 23
#define TRIG_PINR 24
#define ECHO_PINR 25
SR04 sr04l = SR04(ECHO_PINL, TRIG_PINL);
SR04 sr04r = SR04(ECHO_PINR, TRIG_PINR);
long xl;
long xr;
int v1;
int v2;
int stopflag = 0;
int disflag;
DualMC33926MotorShield md;
int cmd_ctrl = 0;
ros::NodeHandle nh;

void motor_cb(const geometry_msgs::Twist& vel)
{
	cmd_ctrl = vel.linear.x + 2 * vel.linear.y + 3 * vel.linear.z + 4 * vel.angular.x + 5 * vel.angular.y + 6 * vel.angular.z;
	Serial.println("0");
}
void terminate(const geometry_msgs::Twist& vel)
{
	stopflag = vel.linear.x;
}

ros::Subscriber<geometry_msgs::Twist> sub("keyboard", motor_cb);
ros::Subscriber<geometry_msgs::Twist> sub2("stop", terminate);


void Timer()
{
	Serial.println("trig");
	cmd_ctrl = 0;
	nh.spinOnce();
	if (stopflag == 8)
	{
		stopp();
		stopflag = 0;
		Serial.print("v1");
		Serial.print(v1);
		Serial.print(" v2");
		Serial.println(v2);
	}
	disflag = 1;
	xr = sr04r.Distance();
	Serial.print("xr");
	Serial.println(xr);
	if ((xr>0 && xr <20))
	{
		disflag = 0;
	}
	xr = sr04r.Distance();
	Serial.print(" xr");
	Serial.println(xr);
	if ((xr>0 && xr <20))
	{
		disflag = 0;

	}
	xr = sr04r.Distance();
	Serial.print(" xr");
	Serial.println(xr);
	if ((xr>0 && xr <20))
	{
		disflag = 0;
	}
	if (disflag == 0)
	{
		md.setM1Speed(0);
		md.setM2Speed(0);
		Serial.print("v1");
		Serial.print(v1);
		Serial.print(" v2");
		Serial.println(v2);
	}

}

void setup()
{
	Serial.begin(57600);
	nh.initNode();
	nh.subscribe(sub);
	md.init();
	Timer1.initialize(200000);
	Timer1.attachInterrupt(Timer); // blinkLED to run every 0.15 seconds
}

void loop()
{
	nh.spinOnce();
	switch (cmd_ctrl)
	{
	case 1:
	{
		Serial.print("C1\n");
		go();
		break;
	}
	case 2:
	{
		Serial.print("C2\n");
		back();
		break;
	}
	case 3:
	{
		Serial.print("C3\n");
		left();
		break;
	}
	case 4:
	{
		Serial.print("C4\n");
		right();
		break;
	}
	case 5:
	{
		Serial.print("C5\n");
		stopp();
		break;
	}
	case 6:
	{
		Serial.print("C6\n");
		rf();
		break;
	}
	case 7:
	{
		Serial.print("C7\n");
		lf();
		break;
	}
	case 8:
	{
		Serial.println("C8");
		stopp();
		break;
	}
	default:
	{
		break;
	}
	}
	cmd_ctrl = 0;
}


void go()
{
	Serial.println("1G");
	v1 = -100;
	v2 = 100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
void left()
{
	Serial.println("3L");
	v1 = 100;
	v2 = 100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
void right()
{
	Serial.println("4R");
	v1 = -100;
	v2 = -100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
void back()
{
	Serial.println("2B");
	v1 = 100;
	v2 = -100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
void stopp()
{
	Serial.println("5S");
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
void lf()
{
	Serial.println("7LF");
	v1 = 100;
	v2 = 100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(1000);
	v1 = -100;
	v2 = 100;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(v1);
	md.setM2Speed(v2);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}

void rf()
{
	Serial.println("6RF");
	v1 = -100;
	v2 = -100;
	md.setM1Speed(-100);
	md.setM2Speed(-100);
	delay(1000);
	v1 = -100;
	v2 = 100;
	md.setM1Speed(-100);
	md.setM2Speed(100);
	delay(2000);
	v1 = 0;
	v2 = 0;
	md.setM1Speed(0);
	md.setM2Speed(0);
	Serial.print("v1");
	Serial.print(v1);
	Serial.print(" v2");
	Serial.println(v2);
}
