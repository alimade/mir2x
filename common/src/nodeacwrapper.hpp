#pragma once
#include <type_traits>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

template<typename C> class NodeAcWrapper
{
    private:
        template<typename U, typename = void> struct has_insert_return_type                                                : std::false_type {};
        template<typename U                 > struct has_insert_return_type<U, std::void_t<typename C::insert_return_type>>: std:: true_type {};

    public:
        std::remove_cvref_t<C> c;

    private:
        std::vector<C::node_type> m_nodes;

    public:
        bool      empty() const noexcept { return       c.empty(); }
        bool node_empty() const noexcept { return m_nodes.empty(); }

    public:
        auto erase(C::iterator       p) { auto nextp = std::next(p); m_nodes.push_back(c.extract(p)); return nextp; }
        auto erase(C::const_iterator p) { auto nextp = std::next(p); m_nodes.push_back(c.extract(p)); return nextp; }

    public:
        template<typename Key> auto erase(auto this &&self, const Key &key)
        {
            if(auto iter = self.c.find(key); iter != self.c.end()){
                return self.erase(iter);
            }
            return self.c.end();
        }

    public:
        void clear()
        {
            for(auto iter = c.begin(); iter != c.end();){
                iter = erase(iter);
            }
        }

        void shrink()
        {
            decltype(m_nodes)().swap(m_nodes);
        }

    public:
        template<typename Func> std::pair<C::iterator, bool> insert_node(Func && func)
        {
            func(m_nodes.back());
            if constexpr (has_insert_return_type<C>::value){
                if(auto res = c.insert(std::move(m_nodes.back())); res.inserted){
                    m_nodes.pop_back();
                    return {res.position, true};
                }
                else{
                    std::swap(m_nodes.back(), res.node);
                    return {res.position, false};
                }
            }
            else{
                auto res = c.insert(std::move(m_nodes.back()));
                m_nodes.pop_back();
                return {res, true};
            }
        }
};
