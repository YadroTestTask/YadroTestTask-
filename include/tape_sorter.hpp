/// \file sort_tape.hpp
/// \author Ашмаров Ефим
/// \date 06.2023
/// \brief Описание класса для сортировки данных на ленте

#ifndef TAPE_SORTER_HPP_
#define TAPE_SORTER_HPP_

#include <tape_config.hpp>

namespace tape {

/// \brief Класс для сортировки данных на ленте.
class tape_sorter {
public:
    /// \brief Конструтор.
    ///
    /// \param[in] path_to_tape_config 
    explicit tape_sorter(const std::string& path_to_tape_config="");

    /// \brief Деструтор.
    ~tape_sorter( );

    /// \brief Сортировать элементы ленты, расположенной по пути input_fnamе. Результат сохранить по пути output_fname
    ///
    /// \param[in] input_fname - Имя файла, соотвествующего ленте, элементы которой подлежат сортировке
    /// \param[in] output_fname - Имя файла, соответсвующего отсортированной ленте
    ///
    /// \return Код ошибки или 0 в случае успеха.
    int sort(const std::string& input_fname, const std::string& output_fname);

private:
    tape_config cfg_;           ///< Настройки ленты.
    std::string tmp_tape_path_; ///< Путь к временной ленте.
};

} // tape_sorter 

#endif // TAPE_SORTER_HPP_