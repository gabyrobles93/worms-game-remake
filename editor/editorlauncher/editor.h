#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <string>
#include <map>

class Editor {
    private:

    public:
        Editor(std::string &, std::string &, int, int, int, std::map<int,size_t>);
        void launchEditor(void);
};

#endif