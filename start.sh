#!/bin/bash
Cur_Dir=$(pwd)
echo $Cur_Dir

source $Cur_Dir/devel/setup.bash

cd $Cur_Dir/params
roslaunch udcamera.launch &
sleep 0.5

cd $Cur_Dir/params
roslaunch elevatorBtn.launch &
sleep 0.5

wait
exit 0
