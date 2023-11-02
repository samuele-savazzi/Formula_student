
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "interfacce/msg/call.hpp"     
#include "interfacce/msg/response.hpp"  


using std::placeholders::_1;
 

class Listener : public rclcpp::Node
{
public:
  Listener();

private:
  void ping_callback(const interfacce::msg::Call::SharedPtr msg) const;

  void call_callback(const interfacce::msg::Call::SharedPtr msg) const;

  rclcpp::Subscription<interfacce::msg::Call>::SharedPtr subscription_call_;
  rclcpp::Subscription<interfacce::msg::Call>::SharedPtr subscription_ping_;
  rclcpp::Publisher<interfacce::msg::Response>::SharedPtr publisher_status_;      
  int id;
  std::string stato;
};