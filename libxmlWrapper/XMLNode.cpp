#include "XMLNode.h"

namespace openiam
{
    XMLNode XMLNode::NULL_NODE;
    XMLNode const XMLNode::END_NODE;

    XMLNode::XMLNode()
    {

    }

    XMLNode::XMLNode(const std::string& n)
    : name(n)
    {

    }

    XMLNode& XMLNode::operator[](const std::string& name)
    {
        XMLNode::ListType &list = children[name];
        if (list.size() == 0)
        {
            list.push_front(XMLNode());
            list.front().name = name;
        }
        return list.front();
    }

    bool XMLNode::hasChild(const std::string& name)
    {
        XMLNode::MapType::iterator it = children.find(name);
        return it != children.end();
    }

    XMLNode& XMLNode::addChild(const std::string& name)
    {
        XMLNode::ListType &list = children[name];
        list.push_back(XMLNode(name));
        XMLNode &node = list.back();
        return node;
    }

    XMLNode::ListType::iterator XMLNode::firstChild(const std::string& name)
    {
        return children[name].begin();
    }

    XMLNode::ListType::iterator XMLNode::lastChild(const std::string& name)
    {
        return children[name].end();
    }
}