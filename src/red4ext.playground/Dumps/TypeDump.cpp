#include <stdafx.hpp>
#include <Dumps/TypeDump.hpp>

#include <App.hpp>

namespace
{
    struct IType
    {
        RED4ext::CName name;

        virtual void Dump(std::fstream& file) = 0;
    };

    std::unordered_map<uint64_t, std::unique_ptr<IType>> types;

    struct Type : IType
    {
        void Dump(std::fstream& file)
        {
            file << name.ToString();
        }
    };

    struct Property : IType
    {
        std::unique_ptr<Type> type;

        void Dump(std::fstream& file)
        {
            file << name.ToString();

            if (type)
            {
                file << ": ";
                type->Dump(file);
            }
        }
    };

    struct Function : IType
    {
        std::unique_ptr<Type> type;
        RED4ext::CName name2;
        std::vector<std::unique_ptr<Property>> params;

        virtual void Dump(std::fstream& file)
        {
            file << "function " << name2.ToString() << "(";

            for (size_t i = 0; i < params.size(); i++)
            {
                auto param = params[i].get();
                param->Dump(file);

                if (i != params.size() - 1)
                {
                    file << ", ";
                }
            }

            file << ")";

            if (type)
            {
                file << ": ";
                type->Dump(file);
            }

            file << ";";
        }
    };

    struct ClassFunction : Function
    {
        void Dump(std::fstream& file)
        {
            Function::Dump(file);
        }
    };

    struct GlobalFunction : Function
    {
        void Dump(std::fstream& file)
        {
            file << "static ";
            Function::Dump(file);
        }
    };

    struct ClassType : IType
    {
        ClassType* parent;

        std::vector<std::unique_ptr<Property>> props;
        std::vector<std::unique_ptr<Function>> funcs;

        void Dump(std::fstream& file)
        {
            if (parent)
            {
                parent->Dump(file);
                file << std::endl << std::endl;
            }

            file << "class ";
            if (name.hash == 0)
            {
                file << "Global";
            }
            else
            {
                file << name.ToString();
            }

            if (parent)
            {
                file << " extends " << parent->name.ToString();
            }
            file << std::endl;
            file << "{" << std::endl;

            for (auto& prop : props)
            {
                file << "\tvar ";
                prop->Dump(file);
                file << ";" << std::endl;
            }

            if (props.size())
            {
                file << std::endl;
            }

            for (auto& func : funcs)
            {
                file << "\t";
                func->Dump(file);
                file << std::endl;
            }

            file << "}";
        }
    };

    template<typename T>
    void ProcessClassFunction(ClassType* aClass, RED4ext::DynArray<RED4ext::CClassFunction*>& aFuncs)
    {
        for (uint32_t i = 0; i < aFuncs.size; i++)
        {
            auto func = new T();
            func->name = aFuncs[i]->name;
            func->name2 = aFuncs[i]->name2;

            if (aFuncs[i]->returnType)
            {
                func->type.reset(new Type());
                aFuncs[i]->returnType->type->GetName(func->type->name);
            }

            auto& params = aFuncs[i]->params;
            for (uint32_t i = 0; i < params.size; i++)
            {
                auto param = new Property();
                param->name = params[i]->name;

                param->type.reset(new Type());
                params[i]->type->GetName(param->type->name);

                func->params.emplace_back(param);
            }

            aClass->funcs.emplace_back(func);
        }
    }

    ClassType* ProcessClass(RED4ext::CClass* aClass)
    {
        ClassType* parent = nullptr;
        if (aClass->parent)
        {
            parent = ProcessClass(aClass->parent);
        }

        RED4ext::CName name;
        aClass->GetName(name);

        ClassType* classPtr = nullptr;

        auto find = types.find(name.hash);
        if (find != types.end())
        {
            return static_cast<ClassType*>(find->second.get());
        }

        auto ptr = std::make_unique<ClassType>();
        classPtr = ptr.get();

        types.insert({ name.hash, std::move(ptr) });

        classPtr->name = name;
        classPtr->parent = parent;

        auto& props = aClass->props;
        for (uint32_t i = 0; i < props.size; i++)
        {
            auto prop = new Property();
            prop->name = props[i]->name;

            prop->type.reset(new Type());
            props[i]->type->GetName(prop->type->name);

            classPtr->props.emplace_back(prop);
        }

        ProcessClassFunction<ClassFunction>(classPtr, aClass->funcs);
        ProcessClassFunction<GlobalFunction>(classPtr, aClass->staticFuncs);

        return classPtr;
    }
}

void RED4ext::Playground::DumpTypes()
{
    auto app = App::Get();
    auto [err, docsPath] = app->GetDocumentsPath();
    if (err)
    {
        spdlog::error("Could not get the path to 'Documents' folder.");
        return;
    }

    docsPath = docsPath / L"dumps";
    if (!std::filesystem::exists(docsPath) && !std::filesystem::create_directories(docsPath))
    {
        return;
    }

    auto rtti = RED4ext::CRTTISystem::Get();
    spdlog::info("Dumping RTTI types...", rtti->types.size);
    rtti->types.for_each([](uint64_t aHash, RED4ext::CRTTIType* aType) {
        CName name;
        aType->GetName(name);

        if (aType->GetType() == RED4ext::ERTTIType::Class)
        {
            auto castedType = static_cast<RED4ext::CClass*>(aType);
            ProcessClass(castedType);
        }
    });

    auto global = std::make_unique<ClassType>();
    rtti->funcs.for_each([rtti, global = global.get()](uint64_t aHash, RED4ext::CGlobalFunction* aFunc) {
        std::string name = aFunc->name.ToString();

        Function* func;

        auto pos = name.find_first_of("::");
        if (pos == std::string::npos)
        {
            func = new GlobalFunction();
            global->funcs.emplace_back(func);
        }
        else
        {
            CName className(name.substr(0, pos).c_str());
            ClassType* classPtr;

            auto find = types.find(className.hash);
            if (find != types.end())
            {
                classPtr = static_cast<ClassType*>(find->second.get());
            }
            else
            {
                classPtr = ProcessClass(rtti->GetClass(className));
            }

            func = new ClassFunction();
            classPtr->funcs.emplace_back(func);
        }

        if (aFunc->returnType)
        {
            func->type.reset(new Type());
            aFunc->returnType->type->GetName(func->type->name);
        }

        func->name = aFunc->name;
        func->name2 = aFunc->name2;

        auto& params = aFunc->params;
        for (uint32_t i = 0; i < params.size; i++)
        {
            auto param = new Property();
            param->name = params[i]->name;

            param->type.reset(new Type());
            params[i]->type->GetName(param->type->name);

            func->params.emplace_back(param);
        }
    });

    for (auto& i : types)
    {
        auto ptr = i.second.get();

        auto path = docsPath / L"classes";
        if (!std::filesystem::exists(path))
        {
            std::filesystem::create_directories(path);
        }

        std::fstream file(path / fmt::format("{}.txt", ptr->name.ToString()), std::ios::out);
        i.second->Dump(file);
    }

    auto path = docsPath;
    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directories(path);
    }

    std::fstream file(path / L"globals.txt", std::ios::out);
    global->Dump(file);

    spdlog::info("Dump done", rtti->types.size);
}
