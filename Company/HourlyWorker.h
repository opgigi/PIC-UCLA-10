#ifndef HOURLYWORKER_HPP_
#define HOURLYWORKER_HPP_

#include<iostream>
#include <string>
#include <fstream>
#include "Company.h"
#include "Employee.h"

class HourlyWorker : public Employee
{
private:
	int hours_worked = 0;
	double hourly_pay_rate = 0;

public:
	/**
	This is the default constructor enables to create the variable without specific initialization of the variable.
	*/
	HourlyWorker();

	/**
	constructor accepting a name, email, and hourly rate, setting the hours worked to 0 initially;

	@param employee_name: this will initialize the name of the employee
	@param employee_email: this will initialize the email address of employee.
	*/
	HourlyWorker(std::string employee_name_ , std::string employee_email_);

	/**
	constructor accepting an input file stream to read in the name, email, id, hours worked, and hourly rate;

	@param In_file: enables to open the txt file and read all the information of employee.
	*/
	HourlyWorker(std::ifstream& In_File);

	/**
	set hours function that sets the hours worked; this will asks the user prompt that how many hours
	did the employee work this week.

	*/
	virtual void set_hours();

	/**
	This is the funtion to print the salary of the employee.
	*/
	void print_pay();

	/**
	This is the function saves all the informations of Salaried Employee. this function will open the txt file and overwrite
	all the informations of employee again.
	*/
	void save();

};


#endif
