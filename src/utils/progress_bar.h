#include <cmath>
#include <iomanip>
#include <ostream>
#include <string>
#include <chrono>

#include "utils/utils.h"

class ProgressBar
{
    public:
        ProgressBar(std::ostream& stream, std::size_t width)
            : _stream{stream}, _width(width), _start(std::chrono::system_clock::now()) {}

        // Not copyable
        ProgressBar(const ProgressBar&) = delete;
        ProgressBar& operator=(const ProgressBar&) = delete;

        ~ProgressBar() { _stream << '\n'; }

        void write(double fraction);

    private:
        std::ostream& _stream;
        std::size_t _width;
        std::chrono::system_clock::time_point _start;
};

void ProgressBar::write(double fraction) {
    fraction = clamp(fraction, 0, 1);

    auto offset = _width - static_cast<unsigned>(_width * fraction);

    _stream << "\r[";

    for(int i = 0; i < _width - offset; ++i)
        _stream << "▒";

    for(int i = 0; i < offset; ++i)
        _stream << " ";

    _stream << "] " << std::setprecision(1) << std::fixed << 100 * fraction << "% | ";

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - _start;

    _stream << elapsed.count() << "s\r";

    _stream << std::flush;
}
