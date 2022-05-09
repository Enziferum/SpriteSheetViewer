#include <robot2D/robot2D.hpp>
#include "viewer/Viewer.hpp"


int main() {
    logger::Log::Init();
    try{
        viewer::Viewer app{};
        app.run();
    }
    catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}

class Entity {
public:
    Entity(): m_id(0) {}
    Entity(const int& id): m_id(id) {}
    ~Entity() = default;

    void setParameter(const int& parameter) {
        m_parameter = parameter;
    }

    const int& getParameter() const {
        return m_parameter;
    }

    const int& getID() const {
        return m_id;
    }
private:
    int m_parameter;
    int m_id;
};

class Scene {
public:
    Scene(): m_entites(0) {}
    ~Scene() = default;

    void addEntity(Entity entity) {
        m_entites.emplace_back(entity);
    }

    void removeEntity(Entity entity) {
        auto it = std::find_if(m_entites.begin(), m_entites.end(),
                               [&entity](const Entity& ent){
            return entity.getID() == ent.getID();
        });

        if(it == m_entites.end())
            return;
        m_entites.erase(it);
    }

    void printScene() {
        std::cout << "Print Scene" << std::endl;
        for(auto& it: m_entites) {
            std::cout << "Entity ID:=" << it.getID() << " Parameter:=" << it.getParameter() << std::endl;
        }
    }
private:
    std::vector<Entity> m_entites;
};

#include <memory>
#include <unordered_map>

enum class CommandID {
    None = 0,
    AddScene
};

class Command {
public:
    using Ptr = std::shared_ptr<Command>;
public:
    Command(): m_id(CommandID::None) {}
    virtual ~Command() = 0;

    virtual void execute();
    virtual void unexecute();

    const CommandID& getCommandID() const {
        return m_id;
    }
protected:
    friend class CommandInvoker;
    void setCommandID(const CommandID& commandId) {
        m_id = commandId;
    }
    CommandID m_id;
};

Command::~Command() {}

void Command::execute() {}

void Command::unexecute() {}


class AddSceneCommand: public Command {
public:
    AddSceneCommand(Scene& scene, Entity& entity): m_scene(scene),
    m_entity(&entity) {}
    ~AddSceneCommand() override = default;

    void execute() override {
        if(m_entity == nullptr)
            return;
        m_scene.addEntity(*m_entity);
    }

    void unexecute() override {
        if(m_entity == nullptr)
            return;
        m_scene.removeEntity(*m_entity);
    }
private:
    Scene& m_scene;
    Entity* m_entity;
};


class CommandInvoker {
public:
    CommandInvoker();
    ~CommandInvoker() = default;

    CommandInvoker(const CommandInvoker&)=delete;
    CommandInvoker& operator=(const CommandInvoker&)=delete;

    template<typename T, typename ...Args>
    T* addCommand(const CommandID& commandId, Args&& ... args);

    bool undo();
private:
    std::vector<Command::Ptr> m_commands;
};

CommandInvoker::CommandInvoker(): m_commands() {
    // allocate memory for 1000 commands at start
    m_commands.reserve(1000);
}

template<typename T, typename... Args>
T* CommandInvoker::addCommand(const CommandID& commandId, Args &&... args) {
    auto command = std::make_shared<T>(std::forward<Args>(args)...);
    if(!command)
        return nullptr;
    command -> setCommandID(commandId);
    m_commands.template emplace_back(command);

    return dynamic_cast<T*>(m_commands.back().get());
}

bool CommandInvoker::undo() {
    if(m_commands.empty())
        return false;

    auto command = m_commands.back();
    m_commands.pop_back();
    command -> unexecute();

    return true;
}



//int main() {
//    CommandInvoker commandInvoker;
//    // for example imgui sends create new object
//    Scene scene;
//    // Entity will creates of course in scene class but for demo propose we pack class
//    for(int it = 0; it < 2; ++it) {
//        Entity randEntity(it);
//        randEntity.setParameter((it + 1));
//        auto addCommand = commandInvoker.addCommand<AddSceneCommand>(CommandID::AddScene,
//                                                                     scene, randEntity);
//        addCommand -> execute();
//    }
//    scene.printScene();
//    if(!commandInvoker.undo()) {
//        std::cerr << "Can't undo last command" << std::endl;
//    }
//    scene.printScene();
//}