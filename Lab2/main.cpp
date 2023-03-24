#include "functions.h"

int main() {
	cout << sizeof(size_t);
	string start_file = get_filename();
	append_file(start_file);
	read_data(start_file);
	split_workers_to_files(start_file);
	choose_file_to_read();
	
}

