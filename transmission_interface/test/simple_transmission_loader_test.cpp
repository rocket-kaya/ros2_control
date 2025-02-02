// Copyright 2022 PAL Robotics S.L.
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

#include <gmock/gmock.h>
#include <exception>
#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/component_parser.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "pluginlib/class_loader.hpp"
#include "transmission_interface/simple_transmission.hpp"
#include "transmission_interface/simple_transmission_loader.hpp"
#include "transmission_interface/transmission_loader.hpp"

class TransmissionPluginLoader
{
public:
  std::shared_ptr<transmission_interface::TransmissionLoader> create(const std::string & type)
  {
    try
    {
      return class_loader_.createUniqueInstance(type);
    }
    catch (std::exception & ex)
    {
      std::cerr << ex.what() << std::endl;

      return std::shared_ptr<transmission_interface::TransmissionLoader>();
    }
  }

private:
  // must keep it alive because instance destroyers need it
  pluginlib::ClassLoader<transmission_interface::TransmissionLoader> class_loader_ = {
    "transmission_interface", "transmission_interface::TransmissionLoader"};
};

TEST(SimpleTransmissionLoaderTest, FullSpec)
{
  // Parse transmission info

  std::string urdf_to_test =
    R"(
  <?xml version="1.0" encoding="utf-8"?>
  <!-- =================================================================================== -->
  <!-- |    This document was autogenerated by xacro from minimal_robot.urdf.xacro       | -->
  <!-- |    EDITING THIS FILE BY HAND IS NOT RECOMMENDED                                 | -->
  <!-- =================================================================================== -->
  <robot name="MinimalRobot">
    <!-- Used for fixing robot -->
    <link name="world"/>
    <joint name="base_joint" type="fixed">
      <origin rpy="0 0 0" xyz="0 0 0"/>
      <parent link="world"/>
      <child link="base_link"/>
    </joint>
    <link name="base_link">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="0.2" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="joint1" type="revolute">
      <origin rpy="-1.57079632679 0 0" xyz="0 0 0.2"/>
      <parent link="base_link"/>
      <child link="link1"/>
      <limit effort="0.1" lower="-3.14159265359" upper="3.14159265359" velocity="0.2"/>
    </joint>
    <link name="link1">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="joint2" type="revolute">
      <origin rpy="1.57079632679 0 0" xyz="0 0 0.9"/>
      <parent link="link1"/>
      <child link="link2"/>
      <limit effort="0.1" lower="-3.14159265359" upper="3.14159265359" velocity="0.2"/>
    </joint>
    <link name="link2">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="tool_joint" type="fixed">
      <origin rpy="0 0 0" xyz="0 0 1"/>
      <parent link="link2"/>
      <child link="tool_link"/>
    </joint>
    <link name="tool_link">
    </link>
    <ros2_control name="RRBotModularJoint1" type="actuator">
      <hardware>
        <plugin>ros2_control_demo_hardware/VelocityActuatorHardware</plugin>
        <param name="example_param_write_for_sec">1.23</param>
        <param name="example_param_read_for_sec">3</param>
      </hardware>
      <joint name="joint1">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission1">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint1" role="joint1">
          <mechanical_reduction>325.949</mechanical_reduction>
        </joint>
      </transmission>
    </ros2_control>
    <ros2_control name="RRBotModularJoint2" type="actuator">
      <hardware>
        <plugin>ros2_control_demo_hardware/VelocityActuatorHardware</plugin>
        <param name="example_param_write_for_sec">1.23</param>
        <param name="example_param_read_for_sec">3</param>
      </hardware>
      <joint name="joint2">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
    </ros2_control>
    <ros2_control name="RRBotModularPositionSensorJoint1" type="sensor">
      <hardware>
        <plugin>ros2_control_demo_hardware/PositionSensorHardware</plugin>
        <param name="example_param_read_for_sec">2</param>
      </hardware>
      <joint name="joint1">
        <state_interface name="position"/>
      </joint>
    </ros2_control>
    <ros2_control name="RRBotModularPositionSensorJoint2" type="sensor">
      <hardware>
        <plugin>ros2_control_demo_hardware/PositionSensorHardware</plugin>
        <param name="example_param_read_for_sec">2</param>
      </hardware>
      <joint name="joint2">
        <state_interface name="position"/>
      </joint>
    </ros2_control>
  </robot>
  )";

  std::vector<hardware_interface::HardwareInfo> infos =
    hardware_interface::parse_control_resources_from_urdf(urdf_to_test);
  ASSERT_EQ(1lu, infos[0].transmissions.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  std::shared_ptr<transmission_interface::TransmissionLoader> transmission_loader =
    loader.create(infos[0].transmissions[0].type);
  ASSERT_TRUE(nullptr != transmission_loader);

  std::shared_ptr<transmission_interface::Transmission> transmission;
  const hardware_interface::TransmissionInfo & info = infos[0].transmissions[0];
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(nullptr != transmission);
  ASSERT_STREQ(infos[0].transmissions[0].joints[0].role.c_str(), "joint1");

  // Validate transmission
  transmission_interface::SimpleTransmission * simple_transmission =
    dynamic_cast<transmission_interface::SimpleTransmission *>(transmission.get());
  ASSERT_TRUE(nullptr != simple_transmission);
  EXPECT_EQ(325.949, simple_transmission->get_actuator_reduction());
  EXPECT_EQ(0.0, simple_transmission->get_joint_offset());
}

TEST(SimpleTransmissionLoaderTest, MinimalSpec)
{
  std::string urdf_to_test = R"(
<?xml version="1.0"?>

<robot name="robot" xmlns="http://www.ros.org">
  <ros2_control name="MinimalSpec" type="actuator">
    <joint name="joint1">
      <command_interface name="velocity">
        <param name="min">-1</param>
        <param name="max">1</param>
      </command_interface>
      <state_interface name="velocity"/>
    </joint>
    <transmission name="transmission1">
      <plugin>transmission_interface/SimpleTransmission</plugin>
      <joint name="joint1" role="joint1">
        <mechanical_reduction>50</mechanical_reduction>
      </joint>
    </transmission>
  </ros2_control>
</robot>
)";
  // Parse transmission info
  std::vector<hardware_interface::HardwareInfo> infos =
    hardware_interface::parse_control_resources_from_urdf(urdf_to_test);
  ASSERT_EQ(1lu, infos[0].transmissions.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  std::shared_ptr<transmission_interface::TransmissionLoader> transmission_loader =
    loader.create(infos[0].transmissions[0].type);
  ASSERT_TRUE(nullptr != transmission_loader);

  std::shared_ptr<transmission_interface::Transmission> transmission;
  const hardware_interface::TransmissionInfo & info = infos[0].transmissions[0];
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(nullptr != transmission);

  // Validate transmission
  transmission_interface::SimpleTransmission * simple_transmission =
    dynamic_cast<transmission_interface::SimpleTransmission *>(transmission.get());
  ASSERT_TRUE(nullptr != simple_transmission);
  EXPECT_EQ(50.0, simple_transmission->get_actuator_reduction());
  EXPECT_EQ(0.0, simple_transmission->get_joint_offset());
}

// TODO(someone): Waiting for a fix to parsing
/*
TEST(SimpleTransmissionLoaderTest, InvalidSpec)
{
  std::string urdf_to_test = R"(

  <?xml version="1.0"?>

  <robot name="robot" xmlns="http://www.ros.org">
  <ros2_control name="InvalidSpec" type="actuator">
      <joint name="joint1">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission1">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint1" role="joint1">
          <!-- Unspecified element -->

        </joint>
      </transmission>

      <joint name="joint2">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission2">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint2" role="joint2">
          <mechanical_reduction>50</mechanical_reduction> <!-- Not a number -->
        </joint>
      </transmission>

      <joint name="joint3">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission3">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint3" role="joint3">
          <offset> 0</offset> <!-- Not a number -->
          <mechanical_reduction>50</mechanical_reduction>
        </joint>
      </transmission>

      <joint name="joint4">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission4">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint4" role="joint4">
          <mechanical_reduction>60</mechanical_reduction>           <!-- Invalid value -->
        </joint>
      </transmission>
  </ros2_control>
  </robot>
)";
  // Parse transmission info
  std::vector<HardwareInfo> infos = parse_control_resources_from_urdf(urdf_to_test);
  ASSERT_EQ(4lu, infos[0].transmissions.size());

  // Transmission loader

  std::vector<TransmissionPluginLoader> loader(4);
  std::vector<std::shared_ptr<TransmissionLoader>> transmission_loader(4);

  for (int i = 0; i < 4; ++i)
  {
    transmission_loader[i] = loader[i].create(infos[0].transmissions[i].type);
    ASSERT_TRUE(nullptr != transmission_loader[i]);
  }

  for (int i = 0; i < 4; ++i)
  {
    std::shared_ptr<Transmission> transmission = nullptr;
    transmission = transmission_loader[i]->load(infos[0].transmissions[i]);
    ASSERT_TRUE(nullptr == transmission);
  }
}

*/

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
