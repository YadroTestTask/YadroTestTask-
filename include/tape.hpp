/// \file tape.сpp
/// \author Ашмаров Ефим
/// \date 6.2023
/// \brief Описание взимодействия с лентой

#ifndef TAPE_HPP_
#define TAPE_HPP_

#include <cstdint>
#include <string>
#include <fstream>
#include <chrono>

#include <tape_config.hpp>


namespace tape {

/// \brief Класс для взимодействия с лентой.
class tape {
public:    
    /// \brief Конструктор.
    ///
    /// \param[in] src_path - Путь к файлу я данными ленты.
    /// \param[in] cfg - Парметры ленты (задержки чтения/записи/перемещения).
    /// \param[in] init_size - Размер ленты. Указывать только если создаётся новый файл.
    tape(const std::string& src_path, const tape_config& cfg, std::size_t init_size = 0);

    /// \brief Деструктор.
    ~tape( );

    /// \brief Подвинуть ленту влево.
    void move_left( );

    /// \brief Подвинуть ленту вправо.
    void move_right( );

    /// \brief Прочитать число под головкой.
    uint32_t read( );

    /// \brief Записать в ячейку под головкой.
    void write(uint32_t elem);

    /// \brief Получить размер ленты (кол-во шагов вправо - кол-во шагов влево).
    ///
    /// \return Рзмер ленты (кол-во шагов вправо - кол-во шагов влево)
    std::size_t get_current_pos( ) const;

private:
    std::fstream tape_file_;                ///< Файл с записями ленты.
    std::chrono::milliseconds read_delay_;  ///< Задержка по чтению ячейки.
    std::chrono::milliseconds write_delay_; ///< Задержка по записи ячейки.
    std::chrono::milliseconds move_delay_;  ///< Задержка по переммещению ленты.
    std::size_t current_pos_;               ///< Размер ленты.
};

} // tape

#endif // TAPE_HPP_