#include "XMLParser.h"


template <class Parser>
XMLParser<Parser>::XMLParser(const std::string& s)
: parser()
, doc(NULL)
{
    doc = parser.parse(s);
}

template <class Parser>
XMLParser<Parser>::~XMLParser()
{
    if (doc != NULL)
        xmlFree(doc);
}

template <class Parser>
void XMLParser<Parser>::parse(std::list<XMLNode>& nodes)
{
    xmlNode *current = xmlDocGetRootElement(doc);
    while (current != NULL)
    {
        XMLNode result;
        populateNode(current, result);
        nodes.push_back(result);
        current = current->next;
    }
}

void populateNode(xmlNode *node, XMLNode& result)
{
    result.name = std::string((const char*) node->name);
    if (node->xmlChildrenNode != NULL && node->xmlChildrenNode->type == XML_TEXT_NODE)
    {
        result.text = std::string((char *)xmlNodeGetContent(node->xmlChildrenNode));
    }

    getAttributes(node, result.attributes);
    getChildren(node, result);
}

void getAttributes(xmlNode *node, std::map<std::string, std::string>& data)
{
    for (xmlAttrPtr attr = node->properties; attr != NULL; attr = attr->next)
    {
        data.insert(std::make_pair(std::string((const char*)attr->name), std::string((const char*)attr->children)));
    }
}

void getChildren(xmlNode *node, XMLNode& result)
{
    if ( node->type != XML_ELEMENT_NODE )   
        return;
    node = node->children;
    while ( node != NULL ) {
        XMLNode child;
        populateNode(node, child);
        result.children[child.name].push_back(child);
        node = node->next;
    }
}
    
