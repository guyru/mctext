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
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <boost/random/uniform_int.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>

#include "text_generator.h"

using namespace std;

/**
 *\param sample_file an open stream to a file holding sample text.
 */
TextGenerator::TextGenerator(ifstream &sample_file)
{
	sampleFile(sample_file);
}

/**
 *\param sample_file an open stream to a file holding sample text.
 */
void TextGenerator::sampleFile(ifstream &sample_file)
{
	string line;
	while(! sample_file.eof()) {
		getline(sample_file, line);
		addLine(line);
	}
	
        /*
	 *for (vector<string>::iterator itr = m_words.begin(); itr != m_words.end(); ++itr) {
	 *        cout<<*itr<<endl;	
	 *}
         */
}

/**
 * This function takes a line, parses it into words (by whitespaces) and adds
 * them to m_words
 */
void TextGenerator::addLine(const std::string &str)
{
	string buf;
	stringstream ss(str);

	while (ss >> buf)
		m_words.push_back(buf);
}


string TextGenerator::generateText()
{
	const int count = 20;
	const int vec_length = m_words.size();

	boost::uniform_int<size_t> uni_dist(0, vec_length-1);
	boost::variate_generator<boost::rand48, boost::uniform_int<size_t> >
		rand(boost::rand48((int) time(NULL)), uni_dist);
}
