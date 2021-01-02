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

    std::unordered_map<uint64_t, std::shared_ptr<IType>> types;

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
        std::shared_ptr<ClassType> parent;

        std::vector<std::unique_ptr<Property>> props;

        std::vector<std::unique_ptr<ClassFunction>> funcs;
        std::vector<std::unique_ptr<GlobalFunction>> staticFuncs;

        void Dump(std::fstream& file)
        {
            if (parent)
            {
                parent->Dump(file);
                file << std::endl << std::endl;
            }

            std::sort(props.begin(), props.end(), [](auto& lhs, auto& rhs) {
                return std::strcmp(lhs->name.ToString(), rhs->name.ToString()) < 0;
            });

            std::sort(funcs.begin(), funcs.end(), [](auto& lhs, auto& rhs) {
                return std::strcmp(lhs->name2.ToString(), rhs->name2.ToString()) < 0;
            });

            std::sort(staticFuncs.begin(), staticFuncs.end(), [](auto& lhs, auto& rhs) {
                return std::strcmp(lhs->name2.ToString(), rhs->name2.ToString()) < 0;
            });

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

            if (props.size() && (funcs.size() || staticFuncs.size()))
            {
                file << std::endl;
            }

            for (auto& func : staticFuncs)
            {
                file << "\t";
                func->Dump(file);
                file << std::endl;
            }

            if (funcs.size() && staticFuncs.size())
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
    void ProcessClassFunction(std::shared_ptr<ClassType> aClass, RED4ext::DynArray<RED4ext::CClassFunction*>& aFuncs)
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

            if constexpr (std::is_same_v<T, ClassFunction>)
            {
                aClass->funcs.emplace_back(func);
            }
            else
            {
                aClass->staticFuncs.emplace_back(func);
            }
        }
    }

    struct ProcessResult
    {
        bool isNew;
        std::shared_ptr<IType> type;
    };

    ProcessResult ProcessClass(RED4ext::CClass* aClass)
    {
        std::shared_ptr<ClassType> parent = nullptr;
        if (aClass->parent)
        {
            auto processed = ProcessClass(aClass->parent);
            if (processed.isNew)
            {
                types.insert({ processed.type->name.hash, processed.type });
            }

            parent = std::dynamic_pointer_cast<ClassType>(processed.type);
        }

        RED4ext::CName name;
        aClass->GetName(name);

        auto find = types.find(name.hash);
        if (find != types.end())
        {
            return { false, find->second };
        }

        auto ptr = std::make_shared<ClassType>();
        ptr->name = name;
        ptr->parent = parent;

        auto& props = aClass->props;
        for (uint32_t i = 0; i < props.size; i++)
        {
            auto prop = new Property();
            prop->name = props[i]->name;

            prop->type.reset(new Type());
            props[i]->type->GetName(prop->type->name);

            ptr->props.emplace_back(prop);
        }

        ProcessClassFunction<ClassFunction>(ptr, aClass->funcs);
        ProcessClassFunction<GlobalFunction>(ptr, aClass->staticFuncs);

        return { true, ptr };

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
            auto processed = ProcessClass(castedType);

            types.insert({ name.hash, processed.type });
        }
    });

    auto global = std::make_shared<ClassType>();
    rtti->funcs.for_each([rtti, global = global.get()](uint64_t aHash, RED4ext::CGlobalFunction* aFunc) {
        std::string name = aFunc->name.ToString();

        GlobalFunction* func;

        auto pos = name.find_first_of("::");
        if (pos == std::string::npos)
        {
            func = new GlobalFunction();
            global->staticFuncs.emplace_back(func);
        }
        else
        {
            CName className(name.substr(0, pos).c_str());
            std::shared_ptr<ClassType> classPtr;

            auto find = types.find(className.hash);
            if (find != types.end())
            {
                classPtr = std::dynamic_pointer_cast<ClassType>(find->second);
            }
            else
            {
                auto processed = ProcessClass(rtti->GetClass(className));
                classPtr = std::dynamic_pointer_cast<ClassType>(processed.type);
            }

            func = new GlobalFunction();
            classPtr->staticFuncs.emplace_back(func);
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
