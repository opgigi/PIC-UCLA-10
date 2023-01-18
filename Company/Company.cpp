#include "Company.h"
#include "SalariedWorker.h"
#include "HourlyWorker.h"

Employee::Employee()
{

}

//this constructor will accepts the input from the user and overwrite the name and email in the existing file  
Employee::Employee(std::string employee_name, std::string employee_email)
{
	
	std::string employee_txt_file = { 0 };
	employee_txt_file = "employee";
	employee_txt_file += std::to_string(employee_id);
	employee_txt_file += ".txt";

	std::ofstream create_employee(employee_txt_file);

	write_data();

	create_employee << employee_name << '\t' << employee_email << '\t';

}


Employee::Employee(std::ifstream& In_File)
{
	char reading_file = 0;
	std::string wage_info = { 0 };

	employee_text_file = "employee";
	employee_text_file += std::to_string(employee_id);
	employee_text_file += ".txt";

		In_File.open(employee_text_file);
	
		// if the In_file is opened and be able to read the content then proceed and read the input of the file
		if (In_File.is_open())
		{
			In_File >> wage_info;
			//if the stream input read that the very first information is "Hourly", then proceed.
			if (wage_info == "Hourly")
			{
				do {
					size_t i = 0;
					reading_file = In_File.get();
					employee_name[i] = reading_file;
					++i;
					// let the reading_file keep reads the character from the stream and store into name of employee and one it detect the tab then escape.
				} while (reading_file != '\t'); 

				do {
					size_t i = 0;
					reading_file = In_File.get();
					employee_email[i] = reading_file;
					++i;
					// let the reading_file keep reads the character from the stream and store the email info until it detects the tab and emaploy email has .com
				} while (reading_file != '\t' && employee_email.find(".com"));

				In_File >> employee_id;
				++next_id;
			}

		}
		else //if the file is not opened then print out this message
		{
			std::cout << "The file is not vaild to open";
		}
	

		


}

// this function will print out the name id and email.
void Employee::Employee::print_directory()
{
	std::cout << employee_name << '\t' << employee_id << '\t' << employee_email << '\t' << '\n';

}

//this function will asks the input from user for the name and email
void Employee::Employee::write_data()
{
	std::cout << "Enter name: ";
	std::cin >> employee_name;
	std::cout << "\n";

	std::cout << "Enter email: ";
	std::cin >> employee_email;
	std::cout << "\n";

}

//since this is the virtual function then pass it onto the print_pay function in other classes
void Employee::Employee::print_pay() {}

//since this is the virtual function then pass it onto the print_pay function in other classes
void Employee::Employee::save(){}

//default constructor
HourlyWorker::HourlyWorker() {};

//this contructor will set the hours zero and and will ask the user the pay grade of the employee.
HourlyWorker::HourlyWorker(std::string employee_name_, std::string employee_email_) : Employee(employee_name_, employee_email_), hours_worked(0)
{
	std::cout << "Enter hourly rate: ";
	std::cin >> hourly_pay_rate;
	std::cout << "\n \n";

}

//this will open the file and reads the txt file from Hourlywage worker
HourlyWorker::HourlyWorker(std::ifstream& In_File) : Employee(In_File)
{
	
	int reading_numbers = 0;
	employee_text_file = "employee" + std::to_string(employee_id) + ".txt";

	In_File.open(employee_text_file);

	In_File >> reading_numbers;
	hours_worked = reading_numbers;

	In_File >> reading_numbers;
	hourly_pay_rate = reading_numbers;

	In_File.close();

}


//this function will ask use to input the hours worked 
void HourlyWorker::HourlyWorker::set_hours()
{
	std::cout << "How many hours did" << employee_name << " work? ";
	std::cin >> hours_worked;


}

//this is the inherited functions from the Employee class and this is the total salary of the employee for hourlywage worker 
void HourlyWorker::HourlyWorker::print_pay()
{
	std::cout << employee_name << " receives $" << hours_worked * hourly_pay_rate;
}


void HourlyWorker::HourlyWorker::save()
{
	std::fstream overwrite_info;
	overwrite_info.open(employee_text_file);
	
	//if the file is open then rewrite the information of the hourly wage worker
	if (overwrite_info.is_open())
	{
		overwrite_info << "Hourly" << '\t' << employee_name << '\t' << employee_email << '\t' << employee_id << '\t' << hours_worked << '\t' << hourly_pay_rate;
	}
	else //if not then print out this message
	{
		std::cout << "\n the employee_text_file has not opened. \n";
	}
}

SalariedWorker::SalariedWorker()
{

}

//this constructor will initialized the name and email in Employee class and ask the user to input the salary information here
SalariedWorker::SalariedWorker(std::string employee_name, std::string employee_email) : Employee::Employee(employee_name, employee_email)
{
	std::cout << "Enter salary: $";
	std::cin >> salary_employee;
	std::cout << "\n" << "\n";

}

//and this consturctor will read the extra information to know how much is the salary 
SalariedWorker::SalariedWorker(std::ifstream& In_file): Employee(In_file)
{
	double reading_salary = 0;
	In_file.open(employee_text_file);

	In_file >> reading_salary;
	salary_employee = reading_salary;
}

//this function will display the total amount of salary what employee recived 
void SalariedWorker::SalariedWorker::print_pay()
{
	std::cout << employee_name << " receives $" << salary_employee;
}

//opens the new file and overwrite the information of salary worker and record the name, email, id, and salary
void SalariedWorker::SalariedWorker::save()
{
	std::fstream overwrite_info;
	
	overwrite_info.open(Employee::employee_text_file);
	// if the file is vaild and opened then overwrite the info
	if (overwrite_info.is_open())
	{
		overwrite_info << "salaried" << '\t' << employee_name << '\t' << employee_email << '\t' << employee_id << '\t' << salary_employee << '\t';
	}
	else //if not then print out this message
	{
		std::cout << "the employee_text_file is not opened. \n";
	}

}

// this is the defualt construtor and let it know that the calss is inherited from the Salary and hourly worker class to read all the information
// and records all the information in the pointer vector.
Company::Company() : SalariedWorker::SalariedWorker(Employee::In_File), HourlyWorker::HourlyWorker(Employee::In_File)
{
	std::ifstream read_info;
	Employee temp_copy_employee(read_info);
	//doing this loop as much as employee file exist in the folder 
	for (size_t i = 0; i < next_id; i++)
	{
		employee_[i]->employee_name = temp_copy_employee.employee_name;
		employee_[i]->employee_email = temp_copy_employee.employee_email;
		employee_[i]->employee_id = temp_copy_employee.employee_id;
	}

}


void Company::Company::print_directory(std::vector <std::shared_ptr<Employee>>& My_Employees)
{
	// doing this loop as much as employee file exist in the folder 
	for (size_t i = 0; i < Employee::next_id; i++)
	{
		My_Employees[i]->print_directory();
	}
	

}

// we need to downcast the function to do this
void do_hour(std::vector <std::shared_ptr<Employee>>& My_Employees)
{
	HourlyWorker hourly_worker;

	Employee* employee_pointer = dynamic_cast<Employee*>(&hourly_worker);


	

}

//once we have all the content in the vector, then we access the print_pay function with the pointer variable. and print out all the pay information
void print_payroll(std::vector <std::shared_ptr<Employee>>& My_Employees)
{
	//doing this for loop as much as the total employee file exist
	for (size_t i = 0; i < Employee::next_id; ++i)
	{
		My_Employees[i]->print_pay();
	}

}


void create_salaried()
{
	std::string salaried_employee_name;
	std::string salaried_employee_email;

	SalariedWorker salaried_worker(salaried_employee_name, salaried_employee_email);

	salaried_worker.save();

	Employee* salaried_emp = &salaried_worker;

	
}
