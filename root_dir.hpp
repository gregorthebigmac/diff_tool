#ifndef ROOT_DIR_HPP
#define ROOT_DIR_HPP

#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "command.hpp"

class dir;

class root_dir {
public:
	root_dir();		// ctor
	~root_dir();	// dtor

	void set_target_dir(std::string path) { m_target_path = path; }
	void get_root_dir(std::string path);
	void build_dir_list(std::string path, std::vector<std::string> &file_list);
	void create_child_dir();
	std::vector <std::string> get_target_file_list() { return &m_target_file_list; }

	// DEBUG Functions
	void print_dir_list(const std::string path, const std::vector<std::string> file_list);

private:

	command m_cmd;
	std::string m_org_path;
	std::string m_target_path;
	std::vector<char> m_org_dir_id;
	std::vector<char> m_target_dir_id;
	std::vector<dir> *m_org_child_dir;
	std::vector<dir> *m_target_child_dir;
	std::vector<std::string> m_org_file_list;
	std::vector<std::string> m_target_file_list;
	std::vector<long> m_org_file_size;
	std::vector<long> m_target__file_size;

};

root_dir::root_dir() {
	get_root_dir(m_org_path);
	build_dir_list(m_org_path, m_org_file_list);
}

void root_dir::create_child_dir() {}

void root_dir::build_dir_list(std::string path, std::vector<std::string> &file_list) {
	if (path.size() > 0) {
		DIR *dp;
		struct dirent *dirp;
		if ((dp = opendir(path.c_str())) == NULL)
			std::cout << "Error[" << errno << "] opening " << path << std::endl;
		while ((dirp = readdir(dp)) != NULL) {
			file_list.push_back(std::string(dirp->d_name));
		}
		closedir(dp);
	}
}

void root_dir::get_root_dir(std::string path) {
	if (path.size() > 0) {
		std::vector<std::string> _terminal_feedback, _error_list;
		m_cmd.exec("pwd", _terminal_feedback, _error_list);
		if (_terminal_feedback.size() > 0)
			path = _terminal_feedback[0];
		else
			std::cout << "Couldn't get path!" << std::endl;
	}
}

// DEBUG Functions
void root_dir::print_dir_list(const std::string path, const std::vector<std::string> file_list) {
	std::cout << "Printing contents of " << path << ":" << std::endl;
	for (int i = 0; i < file_list.size(); i++) {
		std::cout << "[";
		if (i < 10)
			std::cout << "0";
		else if (i < 10)
			std::cout << "00";
		std::cout << i << "] " << file_list[i] << std::endl;
	}
}

#endif