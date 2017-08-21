#pragma once

#include <string>
#include <map>
#include <list>

namespace openiam
{
    class XMLNode
    {
    public:
        XMLNode(const std::string& n);
        XMLNode();
        
        static XMLNode NULL_NODE;
        static const XMLNode END_NODE;

        typedef std::list<XMLNode> ListType;
        typedef std::map<std::string, ListType> MapType;

        std::string name;
        std::string text;
        std::map<std::string, std::string> attributes;
        MapType children;

        XMLNode& addChild(const std::string& name);
        XMLNode& operator[](const std::string& name);
        ListType::iterator firstChild(const std::string& name);
        ListType::iterator lastChild(const std::string& name);
        bool hasChild(const std::string& name);
    };
}