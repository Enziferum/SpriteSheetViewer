#include <viewer/PixelBuffer.hpp>

namespace viewer {
    PixelBuffer::PixelBuffer():m_ptr{nullptr}, m_size{0} {}
    PixelBuffer::PixelBuffer(byte* buffer, std::size_t size, unsigned int channelNum):
        m_ptr{nullptr}, m_size{0}, m_channelNum{channelNum}
        {}
} // namespace viewer