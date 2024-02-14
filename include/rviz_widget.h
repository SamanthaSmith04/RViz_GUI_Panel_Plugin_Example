#ifndef TEST_WIDGET_H
#define TEST_WIDGET_H

#include <QWidget>
#include <rclcpp/node.hpp>
#include <rclcpp/client.hpp>
#include <QKeyEvent>
#include <QRadioButton>
#include <QPushButton>
#include <sensor_msgs/msg/joint_state.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { //Namespace for User Interface
    class TestWidget;
}
QT_END_NAMESPACE

class TestWidget : public QWidget //The TestWidget class inherits from QWidget
{
    Q_OBJECT 

    public:
        explicit TestWidget(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr); //Constructor Definition - called when object is created
        ~TestWidget(); //Deconstructor - called when object is destroyed
    private:
        rclcpp::Node::SharedPtr node_;
        Ui::TestWidget *ui_;
        //other functions and variables
        //populate as items are needed
        void lButtonClicked();
        void radioClicked();
        void jointCallback();
        void rButtonClicked();
        void mainClicked();

        rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_pub;
        //rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub;
};

#endif // TEST_WIDGET_H
