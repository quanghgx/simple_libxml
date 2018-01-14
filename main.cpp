#include <boost/algorithm/string.hpp>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sstream>
#include <string>

using std::string;

static string get_tag_name(xmlNodePtr node) {
  std::stringstream ss;
  ss << node->name;
  return ss.str();
}
static string get_attribute(xmlNodePtr node, const string &attr) {
  xmlChar *value = xmlGetProp(node, (const xmlChar *)attr.c_str());
  if(value) {
    string result((const char *)value);
    xmlFree(value);
    return result;
  } else {
    return "";
  }
}

static void print_element_names(xmlNode *a_node) {
  xmlNode *cur_node = NULL;
  for(cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if(cur_node->type == XML_ELEMENT_NODE) {
      string tag = get_tag_name(cur_node);
      std::cout << "node type: Element, name: " << tag;
      if(cur_node->children && cur_node->children->type == XML_TEXT_NODE && cur_node->children->content) {
        string content((const char *)cur_node->children->content);
        boost::trim(content);
        if(!content.empty()) std::cout << ", value: " << content;
      }
      if(tag == "book") {
        string id = get_attribute(cur_node, "id");
        boost::trim(id);
        if(!id.empty()) {
          std::cout << ", it is a book: " << id;
        }
      }
      if(tag == "author") {
        string tags = get_attribute(cur_node, "tags");
        boost::trim(tags);
        if(!tags.empty()) {
          std::cout << ", tags: " << tags;
        }
      }
      std::cout << "\n";
    }
    print_element_names(cur_node->children);
  }
}

int main(int argc, char **argv) {
  std::cout << "Study XML parser\n";

  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;

  if(argc != 2) {
    std::cout << "Usage:\n"
              << "study_libxml xml_file_name\n";
    return (1);
  }

  /* Macro to check API for match with library we are using*/
  LIBXML_TEST_VERSION

  /* Parse the file and get the DOM*/
  if((doc = xmlReadFile(argv[1], NULL, 0)) == NULL) {
    std::cout << "error: could not parse file " << argv[1] << "\n";
    return (-1);
  }

  root_element = xmlDocGetRootElement(doc);
  print_element_names(root_element);

  /* Release XML resource*/
  xmlFreeDoc(doc);
  xmlCleanupParser();

  std::cout << "done (2)!\n";
}
