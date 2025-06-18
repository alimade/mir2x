#pragma once
#include <type_traits>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

template<typename C> class NodeACWrapper
{
    private:
        template<typename T, typename = void> struct has_insert_return_type                                                : std::false_type {};
        template<typename T                 > struct has_insert_return_type<T, std::void_t<typename T::insert_return_type>>: std:: true_type {};

    public:
        std::remove_cvref_t<C> c;

    private:
        std::vector<typename C::node_type> m_nodes;

    public:
        bool has_node() const noexcept
        {
            return !m_nodes.empty();
        }

    public:
        template<typename Iter> requires (std::same_as<Iter, typename C::iterator> || std::same_as<Iter, typename C::const_iterator>) std::pair<Iter, bool> erase(Iter p)
        {
            auto nextp = std::next(p);
            m_nodes.push_back(c.extract(p));
            return {nextp, true};
        }

    public:
        template<typename Key> auto erase(this auto && self, const Key & key)
        {
            if(auto iter = self.c.find(key); iter != self.c.end()){
                return self.erase(iter);
            }
            return std::pair(self.c.end(), false);
        }

    public:
        void clear()
        {
            while(!c.empty()){
                m_nodes.push_back(c.extract(c.begin()));
            }
        }

        void shrink()
        {
            decltype(m_nodes)().swap(m_nodes);
        }

    public:
        template<typename Func> std::pair<typename C::iterator, bool> insert_node(Func && func)
        {
            func(m_nodes.back());
            if constexpr (has_insert_return_type<C>::value){
                if(auto r = c.insert(std::move(m_nodes.back())); r.inserted){
                    m_nodes.pop_back();
                    return {r.position, true};
                }
                else{
                    std::swap(m_nodes.back(), r.node);
                    return {r.position, false};
                }
            }
            else{
                auto r = c.insert(std::move(m_nodes.back()));
                m_nodes.pop_back();
                return {r, true};
            }
        }
};
