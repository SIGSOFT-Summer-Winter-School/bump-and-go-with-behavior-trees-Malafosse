// Copyright 2024 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <iostream>

#include "bt_bumpgo/Turn.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace bt_bumpgo
{

using namespace std::chrono_literals;

Turn::Turn(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
:BT::ActionNodeBase(xml_tag_name, conf)
{
  config().blackboard->get("node",node_);

  // Complete here: Initialize vel_pub_ to  /output_vel
  vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>(
            "/output_vel",
            10 //queue size
    );
}

void
Turn::halt()
{
}

BT::NodeStatus
Turn::tick()
{
  if (status()==BT::NodeStatus::IDLE) {
    start_time_=node_->now();
  }
  auto elapsed_time_ = node_->now();
  // geometry_msgs::msg::Twist vel_msgs;
  // Complete here: Fill and publish velocities
  geometry_msgs::msg::Twist msg_;
  msg_.angular.z = 0.3;
  vel_pub_->publish(msg_);
  // Complete here: Return SUCCESS after moving back three seconds.
  if ((elapsed_time_.seconds() - start_time_.seconds()) >= 3){
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::RUNNING;
}

}  // namespace bt_bumpgo

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<bt_bumpgo::Turn>("Turn");
}
