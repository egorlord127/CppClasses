#pragma once

#include "XMLNode.h"

#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace openiam
{
    class XMLMemoryWriter
    {
    public:
        XMLMemoryWriter();
        ~XMLMemoryWriter();

        xmlTextWriterPtr getWriter();
        std::string getContent();

    private:
        xmlBufferPtr buffer;
        xmlTextWriterPtr writer;
    };

    struct DTDInfo
    {
        std::string name;
        std::string id;
        std::string url;

        DTDInfo(const std::string& n, const std::string& i, const std::string& u)
        : name(n)
        , id(i)
        , url(u)
        {
        }

        DTDInfo()
        {

        }
    };

    class XMLDocument
    {
    public:
        XMLDocument(xmlTextWriterPtr writer);
        XMLDocument(xmlTextWriterPtr writer, const DTDInfo& info);
        ~XMLDocument();

        void init();
        void end();
        void writeNode(XMLNode& node);
        void writeChildren(XMLNode::MapType& children);
        void writeAttributes(std::map<std::string, std::string>& attr);
    
    private:
        xmlTextWriterPtr writer;
        DTDInfo dtdinfo;
        bool isInit;
    };

    template <class Writer>
    class XMLBuilder
    {
    public:
        XMLBuilder(Writer& w);
        XMLBuilder(Writer& w, DTDInfo& dtdInfo);
        ~XMLBuilder();

        void addNode(const XMLNode &n);
        XMLNode& addNode(const std::string& name);
        void write();

    private:
        Writer& writer;
        DTDInfo dtdinfo;
        XMLNode::ListType nodeList;
    };
}

