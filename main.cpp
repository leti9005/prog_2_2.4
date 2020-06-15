#include <iostream>
#include <fstream>

struct Node
{
    char* data;
    Node *next;

    Node() {
        data = nullptr;
        next = nullptr;
    }

    ~Node() {
        delete data;
    }
};

struct List {
    Node *head;
    Node *tail;
};

size_t strlen(const char *str) {
    size_t result = 0;
    while(str[result] != 0) {
        result++;
    }
    return result;
}

char *strdup(const char *old_str) {
    size_t old_str_len = strlen(old_str);
    char *result = new char[old_str_len+1];
    size_t i = 0;
    for(i=0;i<old_str_len;i++) {
        result[i] = old_str[i];
    }
    result[i] = 0;
    return result;
}

bool strcmp(const char *s0, const char *s1) {
    size_t node_data_len = strlen(s0);
    if(node_data_len != strlen(s1)) {
        return false;
    }

    for(size_t i = 0;i<node_data_len;i++) {
        if(s0[i] != s1[i]) {
            return false;
        }
    }

    return true;
}

List *create_list() {
    List *result = new List;
    result->head = nullptr;
    return result;
}

void add_node(List *list, const char *str) {
    Node *newNode = new Node;
    newNode->data = strdup(str);
    newNode->next = nullptr;

    if(list->head == nullptr) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
}

void destroy_list(List *list) {
    Node *e = list->head;
    do {
        Node *node_to_del = e;
        e = e->next;
        delete node_to_del;
    } while(e != nullptr);
    delete list;
}

void replace(List *list, const char *what, const char *newstr) {
    Node *e = list->head;
    do {
        if( strcmp(e->data, what) ) {
            e->data = strdup(newstr);
        }
        e = e->next;
    } while (e!= nullptr);
}

int main() {

    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Author: Dmitrii Tochanskii, 9005"  << std::endl;
    std::cout << "Start date: 02.06.2020. End date: 02.06.2020 Version 1.0.0" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    List *list = create_list(); // Создадим структуру для списка

    std::ifstream input_file("input.txt");
    if(!input_file.good()) {
        std::cerr << "Input file error" << std::endl;
        return -1;
    }
    std::string line;

    while(!input_file.eof()) {
        std::getline(input_file, line);
        add_node(list, line.c_str());
    }
    input_file.close();

    input_file.open("replace.txt");
    if(!input_file.good()) {
        std::cerr << "Replace file error" << std::endl;
        return -1;
    }

    std::string replace_line;
    std::getline(input_file, line);

    std::getline(input_file, replace_line);
    input_file.close();

    replace(list, line.c_str(), replace_line.c_str());

    std::ofstream out_file("output.txt");
    if(out_file.good()) {
        Node *n = list->head;
        while(n != nullptr) {
            out_file << n->data << std::endl;
            n = n->next;
        }
        out_file.close();
    }

    destroy_list(list);
    return 0;
}