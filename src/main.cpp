#include "main.h"

const int LEFT_FRONT_MOTOR = 1;
const int LEFT_BACK_MOTOR = 2;
const int RIGHT_FRONT_MOTOR = 3;
const int RIGHT_BACK_MOTOR = 4;

const auto WHEEL_DIAMETER = 4.125_in;
const auto CHASSIS_WIDTH = 12_in;

auto chassis = ChassisControllerFactory::create(
	{LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR},
	{RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR},
	AbstractMotor::gearset::green,
	{WHEEL_DIAMETER, CHASSIS_WIDTH}
);

Motor punch = 5_mtr;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	chassis.moveDistance(12_in);
	chassis.turnAngle(90_deg);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller master;

	while (true) {
		chassis.tank(
			master.getAnalog(ControllerAnalog::leftY),
			master.getAnalog(ControllerAnalog::rightY)
		);

		if (master.getDigital(ControllerDigital::L2)) {
			punch.moveVoltage(12000);
		}
		else {
			punch.moveVoltage(0);
		}

		pros::Task::delay(20);
	}
}
