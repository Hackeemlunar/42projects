/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:02:34 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/20 22:02:37 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void replace(std::string& tempLine, size_t pos, size_t len, const std::string& toReplace)
{
    tempLine.erase(pos, len);
    tempLine.insert(pos, toReplace);
}

void findAndReplace(std::string& tempLine, const std::string& toFind,
    const std::string& toReplace)
{
    size_t pos = 0;
    while ((pos = tempLine.find(toFind)) != std::string::npos) {
        replace(tempLine, pos, toFind.length(), toReplace);
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Error: Usage: <filename> string1 string2 !\n";
        return 1;
    }

    std::string tempFilename = std::string(argv[1]) + ".replace";
    std::ofstream outf(tempFilename);

    if (!outf)
    {
        std::cerr << "Uh oh, <" << argv[1] << ".replace> could not be opened for writing!\n";
        return 1;
    }

    std::ifstream inf(argv[1]);
    if (!inf)
    {
        std::cerr << "Uh oh, " << argv[1] << " could not be opened for reading!\n";
        return 1;
    }

    std::string line;

    while (std::getline(inf, line))
    {
        findAndReplace(line, std::string(argv[2]), std::string(argv[3]));
        outf << line << '\n';
    }

    return 0;
}
