#include <algorithm>
#include <viewer/MessageDispather.hpp>

namespace viewer {
    IFunction::~IFunction() {}

    MessageDispatcher::MessageDispatcher(): m_functions{} {}

    void MessageDispatcher::process(const robot2D::Message& message) {
        auto findRange = m_functions.equal_range(message.id);
        std::for_each(findRange.first, findRange.second,
                      [&message](const std::pair<const int, std::unique_ptr<IFunction>>& ptr) {
                          ptr.second -> execute(message);
                      });
    }

} // namespace viewer