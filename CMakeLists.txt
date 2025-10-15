cmake_minimum_required(VERSION 3.15)
project(ChronoForge2D)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Функция для рекурсивного поиска всех исходных файлов
function(get_all_source_files return_list)
    set(source_files)
    
    # Рекурсивно ищем все .cpp и .h файлы в src и поддиректориях
    file(GLOB_RECURSE found_sources
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
    )
    
    # Добавляем найденные файлы в список
    set(${return_list} ${found_sources} PARENT_SCOPE)
endfunction()

# Получаем все исходные файлы
get_all_source_files(ALL_SOURCES)

# Выводим информацию о найденных файлах (для отладки)
message(STATUS "Found source files:")
foreach(source_file ${ALL_SOURCES})
    message(STATUS "  ${source_file}")
endforeach()

# Создание исполняемого файла
add_executable(ChronoForge2D ${ALL_SOURCES})

# Подключение библиотек Windows
target_link_libraries(ChronoForge2D
    opengl32
    gdi32
    user32
)

# Настройки для Windows
if(WIN32)
    target_compile_definitions(ChronoForge2D PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# Включаем директории с заголовками
target_include_directories(ChronoForge2D PRIVATE src)