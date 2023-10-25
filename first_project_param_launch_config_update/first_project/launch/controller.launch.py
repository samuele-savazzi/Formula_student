from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

from launch_ros.actions import Node


def generate_launch_description():
   min_id_arg = DeclareLaunchArgument(
      'min_id', default_value=TextSubstitution(text='1')
   )
   max_id_arg = DeclareLaunchArgument(
      'max_id', default_value=TextSubstitution(text='3')
   )


   return LaunchDescription([
      min_id_arg,
      max_id_arg,
      Node(
         package='first_project',
         executable='controller',
         name='controller',
         parameters=[{
            'min_id': LaunchConfiguration('min_id'),
            'max_id': LaunchConfiguration('max_id'),
         }]
      ),
   ])