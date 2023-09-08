#include "ini.h"

using namespace std;

namespace ini {
    namespace additive {
        void CutSpaces(string &str) {
            str = str.substr(str.find_first_not_of(' '),
                             str.find_last_not_of(' ') - str.find_first_not_of(' ') + 1);
        }
    }

    Section &Document::AddSection(string name) {
        return sections_[name];
    }

    const Section &Document::GetSection(const std::string &name) const {
        if (sections_.find(name) != end(sections_))
            return sections_.at(name);
        static const Section emptysection;
        return emptysection;
    }

    size_t Document::GetSectionCount() const {
        return sections_.size();
    }

    Document Load(std::istream &input) {
        Document doc;
        string str, last_section;
        while (getline(input, str)) {
            if (str != "")
                additive::CutSpaces(str);
            if (str != "" && str[0] == '[') {
                last_section = str = str.substr(1, str.size() - 2);
                doc.AddSection(last_section);
            } else if (str != "") {
                string key = str.substr(0, str.find('='));
                string value = str.substr(str.find('=') + 1);
                additive::CutSpaces(key);
                additive::CutSpaces(value);
                doc.AddSection(last_section)[key] = value;
            }
        }
        return doc;
    }
}