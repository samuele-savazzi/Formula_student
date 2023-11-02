#include <chrono>
#include <memory>
#include <random>
#include "rclcpp/rclcpp.hpp"
#include "interfacce/msg/call.hpp"    
#include "interfacce/msg/response.hpp"
#include "first_project/controller.hpp"    

using std::placeholders::_1;

using namespace std::chrono_literals;

/*
Banalmente questo nodo ros:
  - pinga in modo casuale altri nodi pubblicando su un topic chiamato ping 1 volta al secondo -> pub su ping
  - ogni 10 secondi manda un messagio sul topic call per leggere lo stato dei vari nodi -> pub su call
  - ricevi gli stati degli altri nodi su un topic chiamato status -> sub su status

Per ora il funzionamento è fin troppo basilare, perchè non si aspetta un segnale di risposta al ping e non fa niente
con i vari stati:

[FUTURE IMPLEMENTAZIONI]
::procedura per verificare se un nodo è in ascolto o meno -> meccanismo di ping
::procedura per controllare i vari stati ( per ora ho solo usato un interfaccia Response con una stringa che indica lo stato)

*/


Controller::Controller(/*int min_id,int max_id*/)
  : Node("controller")
  {
    this->declare_parameter("min_id");
    this->declare_parameter("max_id");
    min_id = this->get_parameter("min_id").as_int();
    max_id = this->get_parameter("max_id").as_int();
    publisher_ping_ = this->create_publisher<interfacce::msg::Call>("ping", 10);
    publisher_call_ = this->create_publisher<interfacce::msg::Call>("call", 10);
    subscription_status_ = this->create_subscription<interfacce::msg::Response>(         
      "status", 10, std::bind(&Controller::status_callback, this, _1));   
    timer_ping = this->create_wall_timer(1000ms, std::bind(&Controller::timer_ping_callback, this));
    timer_call = this->create_wall_timer(10000ms, std::bind(&Controller::timer_call_callback, this));
    random_id_gen_ = std::mt19937(std::random_device()());
    random_id_dist_ = std::uniform_int_distribution<int>(min_id, max_id);
  }


void Controller::timer_ping_callback()
  {
    auto message = interfacce::msg::Call();                              
    message.id = random_id_dist_(random_id_gen_);                                       
    RCLCPP_INFO(this->get_logger(), "[PING] Calling node: '%d'", message.id);    
    publisher_ping_->publish(message);

  }

void Controller::timer_call_callback()
  {
    auto message = interfacce::msg::Call();                              
    message.id = 0 ;                                  
    RCLCPP_INFO(this->get_logger(), "[CALL] Send status: '%d'", message.id);    
    publisher_call_->publish(message);
    
  }

void Controller::status_callback(const interfacce::msg::Response::SharedPtr msg) const       // CHANGE
  {
    RCLCPP_INFO(this->get_logger(), "[STATUS]: '%s'", msg->stato.c_str());              // CHANGE
  }


int main(int argc, char * argv[])
{
  /*if (argc != 3) {
    std::cerr << "Usage: controller <min_node_id> <max_node_id>" << std::endl;
    return 1;
  }

  int min_id_node=std::stoi(argv[1]);
  int max_id_node=std::stoi(argv[2]);

  */

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Controller>(/*min_id_node,max_id_node*/));
  rclcpp::shutdown();
  return 0;
}