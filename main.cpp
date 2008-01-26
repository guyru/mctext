/***************************************************************************
 *   Copyright (C) 2008 by Guy Rutenberg                                   *
 *   guyrutenberg@gmail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include "text_generator.h"
#include "config.h"

namespace po = boost::program_options;
using namespace std;

int main (int argc, char **argv)
{
	po::options_description desc("Allowed desc");
        desc.add_options()
            ("help,h", "produce this help message")
            ("version", "prints version string")
	    ("input-file", po::value<string>(), "sample text input file")
        ;
	po::positional_options_description p;
	p.add("input-file", 1);
	po::variables_map vm;
	try {
		po::store(po::command_line_parser(argc, argv).
			options(desc).positional(p).run(), vm);
	}
	catch(po::too_many_positional_options_error &e)
	{
		///TODO print usage information
		cerr<<e.what()<<endl;
		return 1;
	}
	catch(po::unknown_option &e)
	{
		///TODO print usage information
		cerr<<e.what()<<endl;
		return 1;
	}
	po::notify(vm);
	if (vm.count("help")) {
		cout << desc << "\n";
		return 0;
	}
	if (vm.count("version")) {
		cout << PACKAGE_STRING << "\n";
		return 0;
	}
	if (vm.count("input-file")) {
		cout<<"Input file: "<< vm["input-file"].as<string>()<<endl;
		ifstream file (vm["input-file"].as<string>().c_str());
		if (!file.is_open()) {
			cerr<<"Error openning specified file"<<endl;
		}

		TextGenerator gen;

		string line;
		while (!file.eof()) {
			getline(file, line);
			gen.addWords(line);
		}
		file.close();

		cout<<gen.generateText()<<endl;
	}

	return 0;
}
