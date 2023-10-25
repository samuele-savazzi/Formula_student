import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
   config = os.path.join(
      get_package_share_directory('first_project'),
      'config',
      'listener2.yaml'
      )

   return LaunchDescription([
      Node(
         package='first_project',
         executable='listener',
         name='listener2',
         parameters=[config]
      )
   ])