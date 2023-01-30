#pragma once
#include <cstdint>
#include <robot2D/Core/Vector2.hpp>

namespace viewer {
    class PixelBuffer {
        using byte = unsigned char;

        struct Iterator {
            Iterator(byte* b): ptr{b}{}
            ~Iterator() = default;

            bool operator ==(const Iterator& other) {
                return ptr == other.ptr;
            }

            bool operator !=(const Iterator& other) {
                return  !(*this == other);
            }

            byte& operator*() {
                return *ptr;
            }

            void operator++() {
                ++ptr;
            }
        private:
            byte* ptr;
        };
    public:
        PixelBuffer();
        PixelBuffer(byte* buffer, std::size_t size, unsigned int channelNum = 4);
        ~PixelBuffer() = default;

        void setBuffer(byte* buffer, std::size_t size, unsigned int channelNum = 4) {
            m_ptr = buffer;
            m_size = size;
            m_channelNum = channelNum;
        }

        Iterator begin() const {
            return Iterator{m_ptr};
        }

        Iterator end() const {
            return Iterator{m_ptr + m_size};
        }

        byte& operator[](std::size_t index) {
            return m_ptr[index];
        }

        byte& operator()(std::size_t row, std::size_t column) {
            unsigned int index = row * m_size * m_channelNum + column * m_channelNum;
            return m_ptr[index];
        }

        explicit operator bool() {
            return m_ptr && m_size;
        }
    private:
        byte* m_ptr;
        std::size_t m_size;
        unsigned int m_channelNum = 4;
    };
} // namespace viewer