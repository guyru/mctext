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
TextGenerator::TextGenerator()
{
	//TODO initialize the random number generator here;
}

/**
 * This function takes a string of words, and adds them into the sample text
 * base
 */
void TextGenerator::addWords(const std::string &str)
{
	string buf;
	stringstream ss(str);

	while (ss >> buf)
		m_words.push_back(buf);
	
}


string TextGenerator::generateText()
{
	const int count = 40;
	const int vec_length = m_words.size();

	//DEBUG
	cerr<<"Num of words: "<<vec_length<<endl;

	string output;
	vector<string> temp;
	
	//TODO move the random number generator from here to a class member
	boost::uniform_int<size_t> uni_dist(0, vec_length-2);
	boost::variate_generator<boost::rand48, boost::uniform_int<size_t> >
		rand(boost::rand48((int) time(NULL)), uni_dist);

	//this is for randomizing the search order
	boost::uniform_int<size_t> uni_int(0, -1);
	boost::variate_generator<boost::rand48, boost::uniform_int<size_t> >
		randint(boost::rand48((int) time(NULL)), uni_int);
	//TODO check if we can give up on one of the random number generators
	
	int initial_rand = rand();
	temp.push_back(m_words[initial_rand]);	
	temp.push_back(m_words[initial_rand+1]);

	vector< vector<string>::iterator > itr_vec; //this will hold iterator to results
	for (int i = count; i>0 ; --i) {
		itr_vec.clear();
		vector<string>::iterator last_it = m_words.begin();

		last_it = search(last_it, m_words.end()-1, temp.end()-2, temp.end());
		while (last_it != m_words.end()) {
			itr_vec.push_back(last_it+2);
			last_it = search(last_it+1, m_words.end(), temp.end()-2, temp.end());
		}
		if (itr_vec.size()==0) { 
			cerr<<"debug: don't know how to continue - "<<temp.size()<<endl;
			initial_rand = rand();
			temp.push_back(m_words[initial_rand]);	
			temp.push_back(m_words[initial_rand+1]);
		}
		temp.push_back( *(itr_vec[ randint()%itr_vec.size() ] ) ); //there is probably better way to code this
	}
	
	for (int i = 0; i < temp.size(); ++i) {
		output += temp[i]+" ";
	}
	return output;
}
