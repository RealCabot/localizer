#include "ros/ros.h"
#include "Fusion.h"

#define LOOP_RATE 10

int main(int argc, char **argv) {

    ros::init(argc, argv, "localizer");
    ros::NodeHandle n;

    Fusion pose(n);
    ros::Subscriber encoder_sub = n.subscribe("/encoder", 1000, &Fusion::encoderCallback, &pose);
    ros::Subscriber imu_sub = n.subscribe("/imu", 1000, &Fusion::IMUCallback, &pose);

    ros::Rate loop_rate(LOOP_RATE);
    while (ros::ok())
    {
        if ( pose.isAllUpdated() ){
            pose.publish();
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    ros::spin();

    return 0;
}