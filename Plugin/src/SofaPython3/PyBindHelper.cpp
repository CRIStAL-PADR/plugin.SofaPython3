/******************************************************************************
*                              SofaPython3 plugin                             *
*                  (c) 2021 CNRS, University of Lille, INRIA                  *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#include <SofaPython3/config.h>

#include <regex>
#include <iostream>

#include "PyBindHelper.h"

namespace sofapython3
{

//void PythonMethodDescription::add_entry(const std::string& signature)
//{
//    signatures.push_back(signature);
//    docstrings.push_back("");
//}

void PythonMethodDescription::parse_docstring(const std::string& name, std::string docstring)
{
    std::smatch m;
    std::string last;
    std::regex e;

    if(signatures.size()==0)
        return;

    // easy path. Take the signature, then consider the remaining as a docstring
    if(signatures.size()==1)
    {
        e = std::regex("("+name+".*)");
        if (std::regex_search (docstring, m,e))
        {
            for (auto x:m)
                last = x;
            if(signatures[0].size()==0)
                signatures[0] = last;
            docstrings[0] = m.suffix().str();
        }
        return;
    }

    int idx = 0;
    e = std::regex("(1\\. )("+name+".*)");
    while (std::regex_search (docstring, m,e))
    {
        for (auto x:m)
            last = x;

        if(signatures[idx].size()==0)
            signatures[idx] = last;

        if(idx>0)
            docstrings[idx-1] = m.prefix().str();
        idx++;
        docstring = m.suffix().str();

        auto pex = "("+std::to_string(idx+1)+"\\. )("+name+".*)";
        e = std::regex(pex);
    }
    if(!docstring.empty())
        docstrings[idx-1] = docstring;
}

const std::string PythonMethodDescription::build_docstring(const std::string& name) const
{
    std::stringstream tmp;
    if(signatures.size() == 1)
    {
        tmp << signatures[0];
        tmp << docstrings[0];
        return tmp.str();
    }
    else
    {
        tmp << name <<"(*args, **kwargs)\n";
        tmp << "Overloaded function.\n\n";
    }
    for(unsigned int i=0;i<docstrings.size();i++)
    {
        tmp << (i+1) << ". " << signatures[i] ;
        tmp << docstrings[i] ;
    }
    return tmp.str();
}


}
