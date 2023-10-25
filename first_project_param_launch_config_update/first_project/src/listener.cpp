#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "interfacce/msg/call.hpp"     
#include "interfacce/msg/response.hpp"  

using std::placeholders::_1;
 

class Listener : public rclcpp::Node
{
public:
  Listener(/*int id_value*/)
  : Node("listener_node")
  {
    this->declare_parameter("id");
    id = this->get_parameter("id").as_int();
    stato="Stato del nodo ";
    stato += std::to_string(id);
    RCLCPP_INFO(this->get_logger(), "NODO '%d' ATTIVO", id);
    RCLCPP_INFO(this->get_logger(), "stato: '%s' ", stato.c_str());
    publisher_status_ = this->create_publisher<interfacce::msg::Response>("status", 10);
    subscription_call_ = this->create_subscription<interfacce::msg::Call>(         
      "call", 10, std::bind(&Listener::call_callback, this, _1));
    subscription_ping_ = this->create_subscription<interfacce::msg::Call>(         
      "ping", 10, std::bind(&Listener::ping_callback, this, _1));
  }

private:
  void ping_callback(const interfacce::msg::Call::SharedPtr msg) const      
  {
    if(id==msg->id){
        RCLCPP_INFO(this->get_logger(), "[PING] controller pinged me: '%d'", msg->id);

    }

                 
  }

  void call_callback(const interfacce::msg::Call::SharedPtr msg) const      
  {
    if(msg->id==0){
        RCLCPP_INFO(this->get_logger(), "[STATUS] publishing my status");
        auto message = interfacce::msg::Response(); 
        message.stato=stato;
        publisher_status_->publish(message);
    }

                 
  }
  rclcpp::Subscription<interfacce::msg::Call>::SharedPtr subscription_call_;
  rclcpp::Subscription<interfacce::msg::Call>::SharedPtr subscription_ping_;
  rclcpp::Publisher<interfacce::msg::Response>::SharedPtr publisher_status_;      
  int id;
  std::string stato;
};

int main(int argc, char * argv[])
{
  /*if (argc != 2) {
    std::cerr << "Usage: listener <node_id>" << std::endl;
    return 1;
  }

  int id_node=std::stoi(argv[1]);*/

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>(/*id_node*/));
  rclcpp::shutdown();
  return 0;
}