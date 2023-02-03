#include <cassert>
#include <viewer/NamesContainer.hpp>

namespace viewer {

    IAddGetName::~IAddGetName() noexcept {}

    NamesContainer::NamesContainer(): m_currentIndex{0}, m_names{} {}

    void NamesContainer::updateIndex(std::size_t newIndex) {
        assert(newIndex < m_names.size() && "Invalid index, out of range");
        m_currentIndex = newIndex;
    }

    void NamesContainer::addName(const std::string& name) {
        m_names[m_currentIndex].emplace_back(name);
    }

    void NamesContainer::clearNames(std::size_t index) {
        assert(index < m_names.size() && "Invalid index, out of range");
        m_names[index].clear();
    }

    void NamesContainer::removeNames(std::size_t index) {
        assert(index < m_names.size() && "Invalid index, out of range");
        m_names.erase(m_names.begin() + index);
        if(index > 0)
            --m_currentIndex;
    }

    const std::vector<std::string>& NamesContainer::getNames() const {
        return m_names[m_currentIndex];
    }

    std::string& NamesContainer::operator[](std::size_t index) {
        assert(index < m_names[m_currentIndex].size() && "Invalid index, out of range");
        return m_names[m_currentIndex][index];
    }

    const std::string& NamesContainer::operator[](std::size_t index) const {
        assert(index < m_names[m_currentIndex].size() && "Invalid index, out of range");
        return m_names[m_currentIndex][index];
    }

    std::vector<std::string>& NamesContainer::getNames() {
        return m_names[m_currentIndex];
    }

    void NamesContainer::addNames() {
        m_names.push_back(stringArray{});
        m_currentIndex = m_names.size() - 1;
    }

    void NamesContainer::removeName(std::size_t index) {
        assert(index < m_names[m_currentIndex].size() && "Invalid index, out of range");
        m_names[m_currentIndex].erase(m_names[m_currentIndex].begin() + index);
    }



} // namespace viewer