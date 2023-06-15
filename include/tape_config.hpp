/// \file tape_config.hpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Описание класса для чтения конфигурационного файла ленты

#ifndef TAPE_CONFIG_HPP_
#define TAPE_CONFIG_HPP_

#include <string>
#include <chrono>
#include <filesystem>

namespace tape {

/// \brief Класс для чтния конфигурационного файла ленты
class tape_config {
public:
    /// \brief Конструктор настроек по умолчанию
    tape_config( );

    /// \brief Конструтор
    ///
    /// \param[in] config_path - Путь к файлу с настройками.
    explicit tape_config(const std::string& config_path);

    /// \brief Деструтор.
    ~tape_config( );

    /// \brief Получить задержку по чтению элемента.
    ///
    /// \return Задержка по чтнию элемента.
    std::chrono::milliseconds get_read_delay( ) const;

    /// \brief Получить задержку по записи элемента.
    ///
    /// \return Задержка по записи элемента.
    std::chrono::milliseconds get_write_delay( ) const;

    /// \brief Получить задержку по перемещению лента на 1 ячейку.
    ///
    /// \return Задержка по перемещении ленты на 1 ячейку.
    std::chrono::milliseconds get_move_delay( ) const;

    /// \brief Получить путь к директории для размещения временных лент.
    /// 
    /// \return Путь к директории для размещения временных лент.
    std::filesystem::path get_tmp_path( ) const;

private:
    std::chrono::milliseconds read_delay_;  ///< Задержка по чтению ячейки.
    std::chrono::milliseconds write_delay_; ///< Здержка по записи в ячейку.
    std::chrono::milliseconds move_delay_;  ///< Задержка по перемещении ленты на 1 ячейку.
    std::filesystem::path     tmp_path_;    ///< Путь к директории для размещения временных лент.
};

} // tape 

#endif // TAPE_CONFIG_HPP_