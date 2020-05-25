// Unification_Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
bool check_type(const char symbol)
{
	return symbol == 'x';
}

bool contains(const std::string& variable, const std::string& term)
{
	return term.find(variable) != std::string::npos;
}
void unify(std::ostringstream& c_u, std::string& first_term, std::string& second_term, std::string& sub)
{
	if (check_type(*first_term.begin()) && !contains(first_term, second_term))
	{
		c_u << " { " << second_term << " / " << first_term << "}";
		sub = "first";
	}
	else  if (check_type(*second_term.begin()) && !contains(second_term, first_term))
	{
		c_u << " { " << first_term << " / " << second_term << "}";
		sub = "second";
	}
	else
	{
		c_u << "Disjunctions can't be unified";
		sub = " ";
	}
}
void unify_func(std::ostream& out, std::ostringstream& cur_unifier)
{
	cur_unifier.seekp(0, std::ios_base::end);
	if (cur_unifier.tellp() == 0)
	{
		return;
	}
	else
	{
		out.seekp(0, std::ios_base::end);
		if (out.tellp() == 0)
		{
			out << cur_unifier.str();
			return;
		}
		else
		{
			out.seekp(-1, std::ios_base::end);
			out << ',';
			cur_unifier.seekp(1);
			cur_unifier << ' ';
			out << cur_unifier.str();
			return;
		}
	}
}
void substitution(std::string& disjunction, std::string& s1, std::string& s2)
{
	size_t i = disjunction.find(s2);
	while (i != std::string::npos)
	{
		disjunction.replace(i, s2.size(), s1);
		i = disjunction.find(s2);
	}
}
void Unification(std::string& first_disjunction, std::string& second_disjunction, std::ostream& out)
{
	int pos1 = 0;
	int pos2 = 0;
	char first_char;
	char second_char;
	int b1 = std::count(first_disjunction.begin(), first_disjunction.end(), ')');
	int b2 = std::count(second_disjunction.begin(), second_disjunction.end(), ')');
	int bracket_count_open1 = 0;
	int bracket_count_open2 = 0;
	int bracket_count_close1 = 0;
	int bracket_count_close2 = 0;
	char a;
	int x = 0;
	while (1)
	{
		std::istringstream first(first_disjunction);
		std::istringstream second(second_disjunction);
		first.seekg(pos1);
		second.seekg(pos2);
		while (first >> first_char && second >> second_char)
		{
			if (first_char == second_char && first_char != 'x')
			{
				if (first_char == 'f' || first_char == 'g' || first_char == 'h')
				{
					++x;
				}

				if (first_char == '(')
				{
					++bracket_count_open1;
					++bracket_count_open2;
				}
				if (first_char == ')')
				{
					++bracket_count_close1;
					++bracket_count_close2;
				}
				continue;
			}
			else if (first_char != second_char || first_char == 'x')
			{
				if (x > 0 && (isdigit(first_char) || isdigit(second_char)))
				{
					out.seekp(0);
					out << "Disjunctions can't be unified";
					return;
				}


				std::string term1;
				std::string term2;

				while (first_char != ',')
				{
					if (first_char == '(')
						++bracket_count_open1;
					if (first_char == ')')
						++bracket_count_close1;
					if (bracket_count_open1 == bracket_count_close1)
						break;
					term1.push_back(first_char);
					first >> first_char;
				}
				while (second_char != ',')
				{
					if (second_char == '(')
						++bracket_count_open2;
					if (second_char == ')')
						++bracket_count_close2;
					if (bracket_count_open2 == bracket_count_close2)
						break;
					term2.push_back(second_char);
					second >> second_char;
				}
				while (x > 0)
				{
					term1.pop_back();
					term2.pop_back();
					--x;
				}
				if (term1 == term2)
					continue;

				std::ostringstream cur_unify;
				std::string sub;
				unify(cur_unify, term1, term2, sub);
				if (sub == " ")
				{
					out.seekp(0);
					out << cur_unify.str();
					return;
				}
				unify_func(out, cur_unify);
				std::string s1;
				std::string s2;

				s1 = sub == "first" ? term2 : term1;
				s2 = sub == "first" ? term1 : term2;

				substitution(first_disjunction, s1, s2);
				substitution(second_disjunction, s1, s2);
				pos1 = first.tellg();
				pos2 = second.tellg();
				pos1 = std::max(pos1, pos2);
				pos2 = pos1;
				bracket_count_open1 = std::max(bracket_count_open1, bracket_count_open2);
				bracket_count_open2 = bracket_count_open1;
				bracket_count_close1 = std::max(bracket_count_close1, bracket_count_close2);
				bracket_count_close2 = bracket_count_close1;
			}
			break;
		}
		if (first_disjunction == second_disjunction)
			break;
	}
}

int main()
{
	std::ofstream out("out1.txt");
	std::ifstream test_file("test.txt");
	std::string d1;
	std::string d2;
	if (test_file.is_open())
	{
		while (test_file >> d1 >> d2)
		{
			if (*d1.begin() != *d2.begin())
			{
				out << "Disjunctions can't be unified\n";
			}
			else
			{
				std::ostringstream out1;
				Unification(d1, d2, out1);
				out << out1.str() << "\n";
			}
		}
	}
	else
	{
		std::cout << "file is not open";
	}

}