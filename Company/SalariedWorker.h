#ifndef SALARIEDWORKER_HPP_
#define SALARIEDWORKER_HPP_

#include "Company.h"
#include <iostream>
#include <string>
#include <fstream>

class SalariedWorker : Employee
{
private:
	double salary_employee = 0;

public:

	/**
	This is the default constructor of Salaried Worker. This enables to declare the varible in SalariedWorker data type
	without initialization of variables.
	*/
	SalariedWorker();

	/**
	constructor accepting an input file stream to read in the name, email, id, and salary once the string variable passed in the function then
	this will ask the input for the name and email,id, and salary information for employee.

	@param employee_name: this will initialize the name of the employee
	@param employee_email: this will initialize the email address of employee.
	*/
	SalariedWorker(std::string employee_name, std::string employee_email);

	/**
	constructor accepting an input file stream to read in the name, email, id, and their salary;

	@param In_file: enables to open the txt file and read all the information of employee.
	*/
	SalariedWorker(std::ifstream& In_file);

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
