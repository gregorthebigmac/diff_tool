#ifndef DIR_HPP
#define DIR_HPP

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <deque>

class dir {
public:
	dir();	// ctor
	~dir();	// dtor

	void set_parent_dir(dir *parent_dir) { m_parent_dir = parent_dir; }
	void create_child_dir();


private:
	std::deque <std::string> m_dir_list;
	dir *m_parent_dir;

	int get_dir_list (std::string dir, std::vector<std::string> &files) {
		DIR *dp;
		struct dirent *dirp;
		if((dp  = opendir(dir.c_str())) == NULL) {
			std::cout << "Error(" << errno << ") opening " << dir << std::endl;
			return errno;
		}

		while ((dirp = readdir(dp)) != NULL) {
			files.push_back(std::string(dirp->d_name));
		}
		closedir(dp);
		return 0;
	}

	int example() {
		std::string dir = std::string(".");
		std::vector<std::string> files = std::vector<std::string>();

		get_dir_list(dir,files);

		for (unsigned int i = 0;i < files.size();i++) {
			std::cout << files[i] << std::endl;
		}
		return 0;
	}
};

void dir::create_child_dir() {}

#endif