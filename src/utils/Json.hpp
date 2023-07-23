#pragma once

#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>
namespace JSON{
class Node;
class Array;
using Value = std::variant<int, bool, float, double, std::string, Node, Array>;
class Array : public std::vector<Node>{
public:
    Array() = delete;
    Array(std::initializer_list<Value> _list);
};


class Node{
    std::map<std::string, Value> m_data;
    std::shared_ptr<Value> m_value;

    std::string stringify_value(const Value& val) const{
        std::stringstream ss;
        if(std::holds_alternative<int>(val)){
            int v = std::get<int>(val);
            ss << v;
        }else if(std::holds_alternative<bool>(val)){
            bool v = std::get<bool>(val);
            ss << (v ? "true" : "false");
        }else if(std::holds_alternative<float>(val)){
            float v = std::get<float>(val);
            ss << v;
        }else if(std::holds_alternative<double>(val)){
            double v = std::get<double>(val);
            ss << v;
        }else if(std::holds_alternative<std::string>(val)){
            std::string v = std::get<std::string>(val);
            ss << "\"" << v << "\"";
        }else if(std::holds_alternative<Node>(val)){
            Node v = std::get<Node>(val);
            ss << v.stringify();
        }else if(std::holds_alternative<Array>(val)){
            Array v = std::get<Array>(val);
            ss << "[";
            int i = 0;
            for(const auto& n : v){
                ss << n.stringify();
                if(i < (int)v.size() - 1){
                    ss << ",";
                }
                i++;
        }
        ss << "]";
        }
        return ss.str();
    }

public:
    Node() = default;
    Node(std::initializer_list<std::pair<std::string, Value>> _list){
        for(const auto& p : _list){
            m_data.insert(p);
        }
    }

    Node(Value val){
        m_value = std::make_shared<Value>(val);
    }

    template<typename T>
    Node& set_value(const std::string& key, const T& val){
        m_data.insert({key, val});

        return *this;
    }

    template<typename T>
    const T& get_value(const std::string& key) const{
        auto it = m_data.find(key);
        if(it == m_data.end()){
            throw std::runtime_error("No value with specified key!");
        }
        try{
            T result = std::get<T>(m_data);
            return result;
        }catch(...){
            throw std::runtime_error("Incorrect type accessed!");
        }
    }

    std::string stringify() const{
        std::stringstream ss;
        if(m_value){
            ss << stringify_value(*m_value);
        }else{
            ss << "{";
            int it = 0;

            for(const auto& p : m_data){
                ss << "\"" << p.first << "\":" << stringify_value(p.second);
                if(it < (int)m_data.size() - 1){
                    ss << ",";
                }
                it++;
            }

            ss << "}";
        }

        return ss.str();
    };
};

inline Array::Array(std::initializer_list<Value> _list){
    for(const auto& n : _list){
        push_back(n);
    }
}

}