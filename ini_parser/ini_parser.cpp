#include "ini_parser.h"
#include <vector>
using namespace std;


namespace qh
{
    INIParser::INIParser(){
        
    }
    
    INIParser::~INIParser(){
        
    }
    
    bool INIParser::Parse(const std::string& ini_file_path)
    {
        string path = ini_file_path;
        return 1;
    }
    
    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
    {
        vector<string > str_line;
        string str_data = ini_data;
        int i = 0;
        string str = "";
        while (str_data.size() != 0)
        {
            size_t pos = str_data.find(line_seperator);
            if (pos != string::npos)
            {
                string str = str_data.substr(0, pos);
                str_data = str_data.substr(pos + line_seperator.size(), str_data.size() - 1);
                str_line.push_back(str);
            }
            else
            {
                str_line.push_back(str_data);
                str_data = "";
            }
        }
        
        for (int i = 0; i < str_line.size(); i++)
        {
            string a_str = str_line[i];
            int pos = a_str.find(key_value_seperator);
            string lmap = a_str.substr(0, pos);
            string rmap = a_str.substr(pos + 1, a_str.size() - 1);
            key_value[lmap] = rmap;
        }
        
        return 1;
    }
    
    const std::string& INIParser::Get(const std::string& key, bool* found)
    {
        string value = key_value[key];
        if (value != "")
            found = new bool(1);
        else
            found = new bool(0);
        
        return key_value[key];
    }
    
    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
        string str_data = section;
        bool key_find = false;
        while (str_data.size() != 0)
        {
            size_t pos = str_data.find(',');
            if (pos != string::npos)
            {
                string str = str_data.substr(0, pos);
                str_data = str_data.substr(pos + 1, str_data.size() - 1);
                if (key == str)
                {
                    key_find = true;
                    break;
                }
            }
            else
            {
                if (str_data == key)
                {
                    key_find = true;
                }
                str_data = "";
            }
        }
        if (key_find)
            return Get(key, found);
        else
            return NULL;
    }
}
