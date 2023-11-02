#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "interfacce/msg/call.hpp"     
#include "interfacce/msg/response.hpp"  

using std::placeholders::_1;
 

class Controller : public rclcpp::Node
{
public:
  Controller();

private:
  void timer_ping_callback();

  void timer_call_callback();

  void status_callback(const interfacce::msg::Response::SharedPtr msg) const;


  rclcpp::TimerBase::SharedPtr timer_ping;
  rclcpp::TimerBase::SharedPtr timer_call;
  rclcpp::Publisher<interfacce::msg::Call>::SharedPtr publisher_ping_;
  rclcpp::Publisher<interfacce::msg::Call>::SharedPtr publisher_call_;
  rclcpp::Subscription<interfacce::msg::Response>::SharedPtr subscription_status_;          
  std::mt19937 random_id_gen_;
  std::uniform_int_distribution<int> random_id_dist_;
  int count;
  int min_id;
  int max_id;
};
