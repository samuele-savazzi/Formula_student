from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

from launch_ros.actions import Node


def generate_launch_description():
   id_arg = DeclareLaunchArgument(
      'id', default_value=TextSubstitution(text='1')
   )



   return LaunchDescription([
      id_arg,
      Node(
         package='first_project',
         executable='listener',
         name='listener',
         parameters=[{
            'id': LaunchConfiguration('id'),
         }]
      ),
   ])