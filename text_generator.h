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
#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>

class TextGenerator {
public:
	virtual void addWords(const std::string &str) = 0 ;
	virtual std::string generateWords(int count, int steps) = 0;
private:

};

class DefaultTextGenerator : public TextGenerator {
public:
	DefaultTextGenerator();
	void addWords(const std::string &str);
	std::string generateWords(int count, int steps);
private:
	std::string stripChars(std::string str);
	std::vector<std::string> m_words;

};

#endif //TEXT_GENERATOR_H
