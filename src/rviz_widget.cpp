#include "rviz_widget.h"
#include "ui_test_widget.h"  // Include the generated UI header file


TestWidget::TestWidget(rclcpp::Node::SharedPtr node, QWidget *parent) 
    : QWidget(parent)
    , node_(node) 
    , ui_(new Ui::TestWidget) // Initialize the ui_ variable
{
    ui_->setupUi(this); // Setup the ui_ variable

    //connect actions to functions
    connect(ui_->top_button_l, &QPushButton::clicked, this, &TestWidget::lButtonClicked);
    connect(ui_->top_button_r, &QPushButton::clicked, this, &TestWidget::rButtonClicked);
    /*connect(ui_->top_bottom_m, &QPushButton::clicked, this, &TestWidget::mButtonClicked);*/
    connect(ui_->main_button , &QPushButton::clicked, this, &TestWidget::mainClicked);
    connect(ui_->radioButton, &QRadioButton::clicked, this, &TestWidget::radioClicked);

    //publishers
    joint_pub = node->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
    //joint_sub = node_->create_subscription<sensor_msgs::msg::JointState>("joint_states", 10, std::bind(&TestWidget::jointCallback, this, std::placeholders::_1));
}

double i = 0.0;
void TestWidget::lButtonClicked(){
    sensor_msgs::msg::JointState joint_msg;
    joint_msg.name = {"joint_1_s", "joint_2_l", "joint_3_u", "joint_4_r", "joint_5_b", "joint_6_t"};
    joint_msg.position = {i, i, i, i, i, i};
    i += 0.05;
    joint_msg.velocity = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    joint_msg.effort = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    rclcpp::Time time_now = node_->now();
    joint_msg.header.stamp = time_now;
    
    joint_pub->publish(joint_msg);
}
void TestWidget::rButtonClicked(){
    sensor_msgs::msg::JointState joint_msg;
    joint_msg.name = {"joint_1_s", "joint_2_l", "joint_3_u", "joint_4_r", "joint_5_b", "joint_6_t"};
    joint_msg.position = {i, i, i, i, i, i};
    i -= 0.05;
    joint_msg.velocity = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    joint_msg.effort = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    rclcpp::Time time_now = node_->now();
    joint_msg.header.stamp = time_now;
    
    joint_pub->publish(joint_msg);
}

void TestWidget::mainClicked(){
    i=0;
    sensor_msgs::msg::JointState joint_msg;
    joint_msg.name = {"joint_1_s", "joint_2_l", "joint_3_u", "joint_4_r", "joint_5_b", "joint_6_t"};
    joint_msg.position = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    i -= 0.05;
    joint_msg.velocity = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    joint_msg.effort = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    rclcpp::Time time_now = node_->now();
    joint_msg.header.stamp = time_now;
    
    joint_pub->publish(joint_msg);
}

void TestWidget::radioClicked(){
    std::cout << "Radio Button Clicked" << std::endl;
}

void TestWidget::jointCallback(){
    std::cout << "Joint Callback" << std::endl;
}

TestWidget::~TestWidget() {
    delete ui_;
}