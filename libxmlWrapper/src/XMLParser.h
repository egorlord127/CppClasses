#include <string>
#include <list>
#include <map>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "XMLNode.h"


struct XMLFileParser
{
    xmlDocPtr parse(const std::string& file)
    {
        return xmlParseFile(file.c_str());
    }
};

struct XMLMemoryParser
{
    xmlDocPtr parse(const std::string& xml)
    {
        return xmlParseMemory(xml.c_str(), xml.size());
    }
};

template <class Parser>
class XMLParser 
{
public:
    XMLParser(const std::string& s);
    ~XMLParser();
    void parse(std::list<XMLNode>& nodes);

private:
    Parser parser;
    xmlDocPtr doc;
};

void getAttributes(xmlNode *node, std::map<std::string, std::string>& data);
void getChildren(xmlNode *node, XMLNode& result);
void populateNode(xmlNode *node, XMLNode& result);