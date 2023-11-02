import os

from ament_index_python.packages import get_package_share_directory


from launch.actions import GroupAction
from launch_ros.actions import PushRosNamespace
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
   controller = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('first_project'), 'launch'),
         '/controller.launch.py'])
      )
   
   listener = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('first_project'), 'launch'),
         '/listener_launch.py'])
      )
   listener_with_namespace = GroupAction(
     actions=[
         PushRosNamespace('listener'),
         listener,
      ]
   )

   listener2 = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('first_project'), 'launch'),
         '/listener_2_launch.py'])
      )
   
   
   return LaunchDescription([
      controller,
      listener,
      listener2,
   ])