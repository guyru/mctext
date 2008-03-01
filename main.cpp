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

string usage();

int main (int argc, char **argv)
{
	po::options_description desc("Options");
        desc.add_options()
		("help,h", "produce this help message")
		("version", "prints version string")
		("num-of-words,w", po::value<int>()->default_value(40), "how many words should be generated")
		("steps,s", po::value<int>()->default_value(2), "the number of steps used in the Markov chain.")
        ;

	po::options_description hidden("Hidden options");
	hidden.add_options()
		("input-file", po::value<string>()->default_value("-"), "sample text input file")
	;

	po::options_description cmdline_options;
	cmdline_options.add(desc).add(hidden);

	po::positional_options_description p;
	p.add("input-file", 1);

	po::variables_map vm;
	try {
		po::store(po::command_line_parser(argc, argv).
			options(cmdline_options).positional(p).run(), vm);
	}
	catch(po::too_many_positional_options_error &e)
	{
		cerr<<e.what()<<endl;
		cerr<<usage();
		return 1;
	}
	catch(po::unknown_option &e)
	{
		cerr<<PACKAGE<<": "<<e.what()<<endl;
		cerr<<usage();
		cerr<<"Try `"<<PACKAGE<<" --help' for more information."<<endl;
		return 1;
	}
	po::notify(vm);
	if (vm.count("help")) {
		cout<<usage();
		cout<<"Reads a sample text from file and generate new text based on it using Markov chains.\n\n";
		cout << desc << "\n";
		cout <<"With no FILE, or when FILE is -, read standard input.\n"<<endl;
		cout <<"Report bugs to <"<< PACKAGE_BUGREPORT <<">"<<endl;

		return 0;
	}
	if (vm.count("version")) {
		cout << PACKAGE_STRING << "\n";
		cout << "Copyright (C) 2008 Guy Rutenberg.\n";
		cout << "This is free software; see the source for copying "
			"conditions.  There is NO\nwarranty; not even for "
			"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
		return 0;
	}

	if (vm["steps"].as<int>()<1) {
		cerr<<"The number of steps must be positive value"<<endl;
		cerr<<usage();
		return 1;
	}

	TextGenerator *gen = new DefaultTextGenerator();
	// read file (or stdin) and generate text
	if (vm["input-file"].as<string>() == "-") {
		string line;
		while (!cin.eof()) {
			getline(cin, line);
			gen->addWords(line);
		}
	} else {
		ifstream file (vm["input-file"].as<string>().c_str());
		if (!file.is_open()) {
			cerr<<"Error openning file: "<<vm["input-file"].as<string>()<<endl;
			return 1;
		}
		string line;
		while (!file.eof()) {
			getline(file, line);
			gen->addWords(line);
		}
		file.close();
	}

	int num_words = vm["num-of-words"].as<int>();
	int num_steps = vm["steps"].as<int>();
	cout<<gen->generateWords(num_words, num_steps)<<endl;

	return 0;
}

/**
 * Prints usage information.
 */
string usage()
{
	string out = "Usage: ";
	out += PACKAGE;
	out += " [options] FILE\n";
	return out;
}
