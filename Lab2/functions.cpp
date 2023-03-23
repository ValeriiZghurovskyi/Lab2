#include "functions.h"
struct worker
{
	string name;
	string number;
	string sex;
	int day;
	int month;
	int year;
};

string get_filename() {
	string filename;
	cout << "Please enter name of the file (for example file.bin): ";
	cin >> filename;
	return filename;
}


bool check_date(int day, int month, int year, int min_age, int max_age) {
	auto now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	tm tm = *localtime(&t);

	if ((tm.tm_year + 1900) - year > min_age && (tm.tm_year + 1900) - year < max_age) {
		return true;
	}
	else if ((tm.tm_year + 1900) - year == min_age) {
		if (month == tm.tm_mon + 1) {
			if (day <= tm.tm_mday) {
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (month < tm.tm_mon + 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if ((tm.tm_year + 1900) - year == max_age) {
		if (month == tm.tm_mon + 1) {
			if (day > tm.tm_mday) {
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (month > tm.tm_mon + 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	//cout << tm.tm_mday << "." << tm.tm_mon + 1 << "." << tm.tm_year + 1900 << std::endl;


}

void append_file(string filename) {
	ofstream fout(filename, ios::binary | ios::app);
	if (!fout.is_open()) {
		cout << "Something went wrong!!!" << endl;
		exit;
	}

	char ch = 'y';
	worker worker;

	while (ch == 'y' || ch == 'Y') {
		cout << "\n\n";
		cout << "Enter worker name (in format: \"Yaroshenko D.I.\" ): ";
		cin.ignore();
		getline(cin, worker.name);

		cout << "Enter worker birthday (in format: 01.01.2023): ";
		scanf_s("%d.%d.%d", &worker.day, &worker.month, &worker.year);

		cout << "Enter worker table number (in format: 8938452): ";
		cin >> worker.number;

		cout << "Enter worker sex (in format: m/w): ";
		cin >> worker.sex;

		if (!check_date(worker.day, worker.month, worker.year, 20, 60)) {
			cout << "Sorry, but this age is incorrect\nWe can`t add this(" << endl;
		}
		else {
			fout.write((char*)&worker, sizeof(worker));
		}

		cout << "If you want to add more workers print \"Y\" else print \"N\": ";
		cin >> ch;
	}

	cout << "\nInformation was successfully added to file!\n" << endl;
	fout.close();
}


void read_data(string filename) {

	ifstream fin(filename, ios::binary);
	if (!fin.is_open()) {
		cout << "Something went wrong!!!" << endl;
		exit;
	}


	fin.seekg(0, ios::end);
	int count_workers = fin.tellg() / sizeof(worker);


	fin.seekg(0, ios::beg);


	worker* workers = new worker[count_workers];

	cout << "Data in \"" << filename << "\":" << endl;
	cout << "\n";


	for (int i = 0; i < count_workers; i++) {
		fin.read((char*)(&workers[i]), sizeof(worker));
		cout << "----------------------------------------------\n";
		cout << "Name: " << workers[i].name << endl;
		cout << "Birthday date: " << workers[i].day << '.' << workers[i].month << '.' << workers[i].year << endl;
		cout << "Table number: " << workers[i].number << endl;
		cout << "Sex: " << workers[i].sex << endl;
		cout << "----------------------------------------------";
		cout << "\n\n";
	}

	fin.close();
}


void split_workers_to_files(string filename) {


	ifstream fin(filename, ios::binary);
	if (!fin.is_open()) {
		cout << "Something went wrong!!!" << endl;
		exit;
	}

	fin.seekg(0, ios::end);
	int count_workers = fin.tellg() / sizeof(worker);


	fin.seekg(0, ios::beg);


	worker* workers = new worker[count_workers];

	for (int i = 0; i < count_workers; i++) {
		fin.read((char*)(&workers[i]), sizeof(worker));
	}

	fin.close();

	ofstream fout_less40("workers_less40", ios::binary | ios::out);
	if (!fout_less40.is_open()) {
		cout << "Something went wrong!!!" << endl;
		exit;
	}

	ofstream fout_more40("workers_more40", ios::binary | ios::out);
	if (!fout_more40.is_open()) {
		cout << "Something went wrong!!!" << endl;
		exit;
	}

	for (int i = 0; i < count_workers; i++) {
		if (check_date(workers[i].day, workers[i].month, workers[i].year, 20, 40)) {
			fout_less40.write((char*)&workers[i], sizeof(worker));
		}
		else {
			fout_more40.write((char*)&workers[i], sizeof(worker));
		}
	}

	cout << "Files \"workers_less40\" and \"workers_more40\" was successfully created!" << endl;

	fin.close();
	fout_less40.close();
	fout_more40.close();
}


void choose_file_to_read() {
	int choise = -1;
	while (choise != 0) {
		cout << "\nIf you want to check file \"workers_less40\" - print \'1\'" << endl;
		cout << "If you want to check file \"workers_more40\" - print \'2\'" << endl;
		cout << "If you don`t want to check any file - print \'0\'" << endl;
		cout << "Enter your number: ";
		cin >> choise;
		cout << "\n";
		switch (choise)
		{
		case 1:
			read_data("workers_less40");
			break;

		case 2:
			read_data("workers_more40");
			break;
		case 0:
			break;
		default:
			cout << "Incorrect choise!" << endl;
		}
	}
}