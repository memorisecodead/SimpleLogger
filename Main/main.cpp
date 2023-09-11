#include <Logger/Logger.hpp>

#define LOG_TRACE(message) Logs::getGlobalLogger().log(Logs::Logger::Level::TRACE_LEVEL, __FILE__, (message))
#define LOG_DEBUG(message) Logs::getGlobalLogger().log(Logs::Logger::Level::DEBUG_LEVEL, __FILE__, (message))
#define LOG_INFO(message) Logs::getGlobalLogger().log(Logs::Logger::Level::INFO_LEVEL, __FILE__, (message))
#define LOG_WARN(message) Logs::getGlobalLogger().log(Logs::Logger::Level::WARN_LEVEL, __FILE__, (message))
#define LOG_ERROR(message) Logs::getGlobalLogger().log(Logs::Logger::Level::ERROR_LEVEL, __FILE__, (message))
#define LOG_FATAL(message) Logs::getGlobalLogger().log(Logs::Logger::Level::FATAL_LEVEL, __FILE__, (message))

int main()
{
	std::thread wlogg([] {
		for (size_t i = 0; i < 100u; ++i)
		{
			LOG_DEBUG("Hello From Another Main Thread.");
		}
		});

	for (size_t i = 0; i < 100u; ++i)
	{
		LOG_DEBUG("Hello From Main Thread.");
	}

	wlogg.join();

	return EXIT_SUCCESS;
}
