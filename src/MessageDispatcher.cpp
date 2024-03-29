#include <viewer/MessageDispather.hpp>

namespace viewer {

    IFunction::~IFunction() {}

    MessageDispatcher::MessageDispatcher(): m_functions{} {}

    void MessageDispatcher::process(const robot2D::Message& message) {
        auto found = m_functions.find(message.id);
        if(found != m_functions.end())
            found -> second -> execute(message);
    }

} // namespace viewer