#pragma once

#include <string>
#include <vector>

namespace viewer {
    class IAddGetName {
    public:
        virtual ~IAddGetName() = 0;
        virtual void addName(const std::string& name) = 0;
        virtual std::string& operator[](std::size_t index) = 0;
        virtual std::vector<std::string>& getNames() = 0;
        virtual const std::vector<std::string>& getNames() const = 0;
    };

    class NamesContainer: public IAddGetName {
    public:
        using stringArray = std::vector<std::string>;
        NamesContainer();
        ~NamesContainer() override = default;


        void updateIndex(std::size_t newIndex);
        void addName(const std::string& name) override;
        void addNames();

        void clearNames(std::size_t index);
        void removeName(std::size_t index);
        void removeNames(std::size_t index);

        std::vector<std::string>& getNames() override;
        const std::vector<std::string>& getNames() const override;

        std::string& operator[](std::size_t index) override;
        const std::string& operator[](std::size_t index) const;
    private:
        std::size_t m_currentIndex;
        std::vector<stringArray> m_names;
    };
}