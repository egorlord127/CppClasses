#include "XMLBuilder.h"


/*************************************************************
* XMLMemoryWriter implementation                           * 
************************************************************/
XMLMemoryWriter::XMLMemoryWriter()
{
    buffer = xmlBufferCreate();
    writer = xmlNewTextWriterMemory(buffer, 0);
}

XMLMemoryWriter::~XMLMemoryWriter()
{
    xmlFreeTextWriter(writer);
}

xmlTextWriterPtr XMLMemoryWriter::getWriter()
{
    return writer;
}

std::string XMLMemoryWriter::getContent()
{
    return std::string((const char*)buffer->content);
}

/*************************************************************
* XMLMemoryWriter implementation                           * 
************************************************************/
XMLDocument::XMLDocument(xmlTextWriterPtr w)
: writer(w)
, isInit(false)
{

}

XMLDocument::XMLDocument(xmlTextWriterPtr w, const DTDInfo& info)
: writer(w)
, dtdinfo(info)
, isInit(false)
{

}

XMLDocument::~XMLDocument()
{
    if (isInit)
        end();
}

void XMLDocument::init()
{
    isInit = true;
    if (xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL) < 0)
    {
        // TODO: Error Handle
    }

    if (xmlTextWriterSetIndent(writer, 2) < 0)
    {
        // TODO: Error Handle
    }

    if (!dtdinfo.name.empty())
    {
        if (xmlTextWriterStartDTD(writer, BAD_CAST dtdinfo.name.c_str(),
                                          BAD_CAST dtdinfo.id.c_str(),
                                          BAD_CAST dtdinfo.url.c_str()))
        {
            // TODO: Error Handle
        }

        if (xmlTextWriterEndDTD(writer) < 0)
        {
            // TODO: Error Handle
        }
    }
}

void XMLDocument::end()
{
    if (xmlTextWriterEndDocument(writer) < 0)
    {
        // TODO: Error Handle
    }
}

void XMLDocument::writeNode(XMLNode& node)
{
    if (xmlTextWriterStartElement(writer, BAD_CAST node.name.c_str()) < 0)
    {
        // TODO: Error Handle
    }

    if (node.attributes.size() > 0)
    {
        writeAttributes(node.attributes);
    }

    if (node.children.size() > 0)
    {
        writeChildren(node.children);
    } 
    else if (node.text.length() > 0)
    {
        if (xmlTextWriterWriteString(writer, BAD_CAST node.text.c_str()) < 0)
        {
            // TODO: Error Handle
        }
    }

    if (xmlTextWriterEndElement(writer) < 0)
    {
        // TODO: Error Handle
    }
}

void XMLDocument::writeChildren(XMLNode::MapType& children)
{
    for (XMLNode::MapType::iterator it = children.begin();
        it != children.end(); ++it)
    {
        XMLNode::ListType &list = it->second;
        for (XMLNode::ListType::iterator it1 = list.begin();
            it1 != list.end(); ++it1)
        {
            writeNode(*it1);
        }
    }
}

void XMLDocument::writeAttributes(std::map<std::string, std::string>& attr)
{
    for (std::map<std::string, std::string>::iterator it = attr.begin(); 
        it != attr.end(); ++it)
    {
        if (xmlTextWriterWriteAttribute(writer, BAD_CAST it->first.c_str(),
                                                BAD_CAST it->second.c_str()) < 0)
        {
            // TODO: Error Handle
        }
    }
}

// template <class Writer>
// XMLBuilder<Writer>::XMLBuilder(Writer& w)
// : writer(w)
// {

// }

// template <class Writer>
// XMLBuilder<Writer>::XMLBuilder(Writer& w, DTDInfo& info)
// : writer(w)
// , dtdinfo(info)
// {

// }

// template <class Writer>
// XMLBuilder<Writer>::~XMLBuilder()
// {

// }

// template <class Writer>
// void XMLBuilder<Writer>::addNode(const XMLNode &n)
// {
//     nodeList.push_back(n);
// }

// template <class Writer>
// XMLNode& XMLBuilder<Writer>::addNode(const std::string& name)
// {
//     nodeList.push_back(XMLNode());
//     XMLNode& back =  nodeList.back();
//     back.name = name;
//     return back;
// }

// template <class Writer>
// void XMLBuilder<Writer>::write()
// {
//     XMLDocument doc(writer.getWriter(), dtdinfo);
//     doc.init();
//     for (XMLNode::ListType::iterator it = nodeList.begin();
//         it != nodeList.end(); ++it)
//     {
//         doc.writeNode(*it);
//     }
//     doc.end();
// }
