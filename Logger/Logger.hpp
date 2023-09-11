#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

namespace Logs
{
	class FileSink
	{
		mutable std::mutex _mutex;
		std::vector<char> _buffer;
		std::ofstream _output;
		std::size_t _offset;

	public:
		FileSink(const std::string& file_name, std::size_t buffer_size = 4096u)
			: _buffer(buffer_size), _output(file_name), _offset(0u)
		{
			if (!_output.is_open())
			{
				throw std::runtime_error("File wasn't created");
			}
		}

		void write(const std::string& data)
		{
			const std::size_t data_size = data.size();

			std::lock_guard<std::mutex> lock(_mutex);
			if (data_size + _offset >= _buffer.size())
			{
				flush();
			}

			std::copy(begin(data), end(data), begin(_buffer) + _offset);
			_offset += data_size;
		}

		~FileSink()
		{
			flush();
		}
	private:
		void flush()
		{
			if (_offset != 0u)
			{
				_output.write(_buffer.data(), _offset);
				_offset = 0u;
			}
		}

	};

	class Logger
	{
	public:
		enum Level
		{
			TRACE_LEVEL,
			DEBUG_LEVEL,
			INFO_LEVEL,
			WARN_LEVEL,
			ERROR_LEVEL,
			FATAL_LEVEL
		};

		static inline std::array<std::string, Level::FATAL_LEVEL + 1u> LevelStr = 
		{ "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };

	public:
		Logger(const std::string& file_name)
			:_sink(file_name) {}

		void log(Level level, const char* source, const std::string& message)
		{
			const std::string formated_message = "[" + LevelStr[level] + "] - " + source + " - " + message + "\n";
			_sink.write(formated_message);
		}

	private:
		FileSink _sink;
	};

	inline Logger& getGlobalLogger()
	{
		static Logs::Logger logger("./data.log");
		return logger;
	}
}
