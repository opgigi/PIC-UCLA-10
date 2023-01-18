#ifndef COMPANY_HPP_
#define COMPANY_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


class Company: HourlyWorker, SalariedWorker
{
private:
	std::vector<std::shared_ptr<Employee>> employee_ = { 0 };
	
public:
	/**
	reads through all the files and creates Employees of suitable type for
	each file, storing them as pointers
	*/
	Company();


	/**
	This member function will print out the information of all employees are currently register in the system.
	this function will print out name of the employee and their email address and their employee id number.
	
	@param vector<shared_ptr<Employee>>: This is the vector of pointers and make it possible to store all the employee's info in single vector.
	*/
	void print_directory(std::vector <std::shared_ptr<Employee>>&);


	/**
	do hours function that runs through the vector and through using a
	dynamic pointer cast, for the HourlyWorkers, prompts the user input The function will call 
	set_hour function in HourlyWorker class and record the amount of hour they worked.

	@param vector<shared_ptr<Employee>>: This is the vector of pointers and make it possible to store all the employee's info in single vector.
	*/
	void do_hours(std::vector <std::shared_ptr<Employee>>&);


	/**
	this funtion will print out all the employee's salarly on the display.

	@param vector<shared_ptr<Employee>>: This is the vector of pointers and make it possible to store all the employee's info in single vector.
	*/
	void print_payroll(std::vector <std::shared_ptr<Employee>>&);


	/**
	create salaried function that prompts a user for a name, email address,
	and salary for a SalariedWorker and instantiates that class, saves it, and adds it
	to employees.

	*/
	void create_salaried();

	/**
	create hourly function that prompts a user for a name, email address, and
	hourly pay rate for an HourlyWorker and instantiates that class, saves it, and
	adds it to employees.

	*/
	void create_hourly();

	/**
	create employee function that asks a user what type of employee they
	want to create with “S” for salaried, “H” for hourly worker; with other commands
	aborting the creation.

	*/
	void create_employee();




};



#endif
