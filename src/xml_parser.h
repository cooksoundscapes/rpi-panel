#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace rapidxml;

struct Schema {
    std::vector<char> string;
    xml_document<> document;
};

class XmlParser {
public:
    void readFile(std::string path) {
        std::ifstream stream(path);
        if (!stream.is_open()) {
            std::cout << "failed to open " << path << '\n';
            return;
        }
        Schema schema;
        std::copy(
            std::istreambuf_iterator<char>(stream), 
            std::istreambuf_iterator<char>(),
            std::back_inserter(schema.string)
        );
        schema.string.push_back('\0');
        schema.document.parse<0>(&schema.string[0]);

        auto root = schema.document.first_node();
        std::string type = root->name();
        auto titleAttr = root->first_attribute("title");
        std::string name = titleAttr->value();

        if (type == "Layout") {
            schemas.emplace(name, schema);
        }
    }

private:
    std::map<std::string, Schema> schemas;
};