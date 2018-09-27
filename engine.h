#ifndef _ENGINE_HH_
#define _ENGINE_HH_

#include <random>
#include <functional>
#include <memory>
#include <set>
#include <map>
#include "common.h"

template<class F> class RandomFloatEngine;
template<class F> class CommandEngine;

/**!
 * class RandomFloatEngine
 * To generate random FloatBase object
 * Template argument must be an instance of template class FloatBase
 */
template<class F>
class RandomFloatEngine
{
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<u64> dis;

    public:
        RandomFloatEngine() : gen(rd()), dis(0, (1<<(F::LENGTH)) - 1) {}
        F Next()
        {
            u64 data = dis(gen);
            return F(&data);
        }
};

template<class F>
class CommandEngine
{
    private:
        using _rtype = std::string;
        using _func_t = std::function<_rtype(void)>;
        class CommandBase
        {
            private:
            private:
                const std::string cmd;
                const _func_t func;
                const std::string helpMsg;
                //std::shared_ptr<CommandEngine> engine;
                //
            public:
                CommandBase() : cmd("DEFUALT_CMD"), func(), helpMsg("No help found") {}
                CommandBase(const std::string &c, 
                        const _func_t &f,
                        const std::string &help) 
                    : cmd(c), func(f), helpMsg(help) {} 

                virtual _rtype Run(){return func();}
                virtual const std::string Name() {return cmd;}
                virtual void ShowHelp(std::ostream & o)
                {
                    o<< KCYN << "=== Help Info about command : "
                        << cmd << " ===" << KNRM <<std::endl;
                    o<< helpMsg <<std::endl;
                    o<< KCYN << "==== Help Info End ====" << KNRM <<std::endl;;
                }
                virtual void ShowHelp() { ShowHelp(std::cout); }
                bool operator<(const CommandBase &c) const { return cmd < c.cmd;}

                //void setEngine(std::shared_ptr<CommandEngine> e){engine = e;}
                virtual ~CommandBase() = default;
        };

        void printWelcome()
        {
            std::cout<<"Welcome to Floating Test"<<std::endl;
            std::cout<<"Type "<< KYEL << " list " << KNRM << " to list available commands, "
                << " and " << KCYN << " help <command> " << KNRM << " to show help message " 
                <<std::endl;
        }

        void printInput()
        {   
            std::cout<< KGRN << "In ["
                << KCYN << turn << KGRN << "] : " <<KNRM;
        }
        void printOutput(const std::string & s)
        {
            std::cout<< KYEL << "Out ["
               <<KCYN << turn << KYEL << "]: " << KNRM
               << s <<std::endl << std::endl; 
        }
        void printErr(const std::string &err)
        {
            std::cerr<< KRED << "ERROR: "<< KNRM
                << err << std::endl;
        }

        std::shared_ptr<CommandBase> GetCommand(const std::string &name)
        {
            if(commands.count(name))
                return std::make_shared<CommandBase>(commands[name]);
            else return std::shared_ptr<CommandBase>(nullptr);
        }


    public:
        CommandEngine() : isRunning(false), turn(1){ initCommands(); }
        void AddCommand(const std::string cmd, const _func_t &f,
                const std::string &help)
        {
            CommandBase base(cmd, f, help);
            commands.emplace(cmd, base);
        }

        void Start() 
        {
            printWelcome();
            GetCommand("format")->Run();
            isRunning = true;
            std::string code;
            while(isRunning)
            {
                printInput();
                std::cin>>code;
                auto cmd = GetCommand(code);
                if(!cmd)
                    printErr("Command Not Found : " + code);
                else 
                    printOutput(cmd->Run());

                ++turn;
            }
        }

        void Stop() const
        {
            isRunning = false;
        }

    private:
        bool isRunning;
        int turn;
        std::map<std::string, CommandBase> commands;

    private:
        void initCommands()
        {
            AddCommand("list", 
                    [this]()
                    {
                        std::cout<< KCYN << "Avaliable commands are: "<< KNRM
                                <<std::endl << "\t";
                        for(auto &cmd : commands) std::cout<< cmd.second.Name() <<" ";
                        std::cout<<std::endl;
                        return "";
                    },
                    "List all commands");
            AddCommand("nop", [this](){return "";}, "This command takes no effect");
            AddCommand("help", 
                    [this](){ 
                        std::string code; std::cin>>code; 
                        this->GetCommand(code)->ShowHelp(); return "";
                    },
                    "Usage: help <command>\nPrint help message of a command.");
            AddCommand("format",[](){
                        std::cout<<"Current float format is:\n\t"<<
                                KYEL << " EXP: " << F::EXP_LEN <<
                                KNRM << " ||" <<
                                KCYN << " FRAC: " << F::FRAC_LEN << KNRM
                                <<std::endl;
                                return "";
                        },
                        "Show current float format information");
            AddCommand("stop", [this](){this->isRunning = false;return "";},
                    "Stop the command engine");
            AddCommand("random-test",[](){
                        std::random_device rd;
                        std::mt19937_64 gen(rd());
                        std::uniform_int_distribution<> dis(0,1);
                        int a = dis(gen);
                        RandomFloatEngine<F> rfe;
                        gen:F data = rfe.Next();
                        if(data.isInf() || data.isNaN()) goto gen;
                        if(a == 0)  // give binary
                        {
                            std::cout<<" Binary value of the float is : "
                                << KYEL << data.to_binary() << KNRM <<std::endl;
                            LREAD1:
                            std::cout<< KGRN << "Input the PRECISE value please: " <<KNRM;
                            Fraction fra;
                            std::cin>>fra;
                            if(fra == data.to_fraction())
                                return KGRN "Answer Correct!";
                            else 
                            {
                                std::cout<< KRED << "Wrong Answer! Please Retry!" <<KNRM 
                                        << std::endl;
                                goto LREAD1;
                            }                            
                        }
                        else        // give precise
                        {
                            std::cout<<" Precise value of the float is : "
                                << KYEL << data.to_precise() << KNRM <<std::endl;
                            LREAD2:
                            std::cout<< KGRN << "Input the BINARY value please: " <<KNRM;
                            std::string bin;
                            std::cin>>bin;
                            if(bin == data.to_binary())
                                return KGRN "Answer Correct!";
                            else
                            {
                                std::cout<< KRED << "Wrong Answer! Please Retry!" <<KNRM 
                                        << std::endl;
                                goto LREAD2;
                            }
                        }
                        return "";
                    },"Generate a random test");

        }
};



#endif
