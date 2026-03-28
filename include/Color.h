#pragma once

#include <string>
namespace Colors
{
/**
 * @brief This class represents a color.
 */
class Color
{
  private:
    std::string asii_code;

  public:
    Color(const std::string &code);

    /**
     * @returns the ASII color code of this color.
     */
    const std::string &get_code() const;
};
}; // namespace Colors