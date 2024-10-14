#pragma once

namespace huan_renderer_cpu
{
namespace functional
{
    class Logger
    {
        public:
        static void create_instance()
        {
            if(instance == nullptr)
            {
                instance = new Logger();
            }
        }
        static Logger* get_instance()
        {
            if(!instance)
                return nullptr;
            return instance;
        }
        ~Logger();
        void error(const char* message);
        void warning(const char* message);
        void info(const char* message);
        void debug(const char* message);
        private:
        inline static Logger* instance = nullptr;
    };
}
} // namespace huan_renderer_cpu

