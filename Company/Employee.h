#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include<iostream>
#include<string>
#include<fstream>
#include <memory>



class Employee
{
private:
	std::string employee_name = { 0 };
	std::string employee_email = { 0 };
	int employee_id = 0;
	static int next_id;
	std::ifstream In_File;

public:

	

	std::string employee_text_file;

	/**
	This is default constructor of Employee, this enables the variable to be declared and we need this because of upcast/downcast the constructor.
	*/
	Employee();

	/**
	constructor that accepts a name and email address, and creates an Employee from that; this constructor will specify what type of txt file they
	have to set up for the new employee information and store the name and email and pass it onto the Hourly or Salaried class to fill out
	more information.

	@param employee_name: this will initialize the name of the employee
	@param employee_email: this will initialize the email address of employee.
	*/
	Employee(std::string employee_name, std::string employee_email);

	/**
	constructor accepting an input file stream to read in the name, email, id. once they read this information, then pass it onto the downcast class 
	at Hourly or Salaried class.
	*/
	Employee(std::ifstream&);

	/**
	This function print function that prints directory information of the form
	and this will print out name and space and email and tab and id number.

	*/
	virtual void print_directory();

	/**
	write data function that writes the name, email, and id of the Employee to a file, each entry separated by a tab;
	This function will prompt the user input to fill out the name of the employee and email address of the employee.

	*/
	void write_data();

	/**
	this is the virtual print_pay funtion to print out the salary of the employee. since it is virtual, then 
	the function has the same name in the downcast, will do the same job.
	*/
	virtual void print_pay();

	/**
	This is the function saves all the informations of Salaried Employee. this function will open the txt file and overwrite
	all the informations of employee again.
	*/
	virtual void save();



};

#endif
