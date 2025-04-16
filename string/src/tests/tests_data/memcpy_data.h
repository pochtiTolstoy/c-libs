#ifndef MEMCPY_DATA_H
#define MEMCPY_DATA_H
#include "../../s21_string.h"
const char *sources[] = {
    "simplecopy",                   // Normal string
    "1234567890",                   // Numeric string
    "",                             // Empty source
    "short",                        // Shorter than destination
    "longerstringthandestination",  // Longer than destination
    "string\0withnull",             // Embedded null character
    "\0leadingnull",                // Leading null
    "exactfit",                     // Exactly fits n
    "padwithnulls",                 // Shorter than n
    "\0\0\0",                       // Source of nulls
    "special_case_test",            // Special case string
    "finalstring",                  // Arbitrary string
    "source",                       // General test case
    "0123456789abcdef",             // Hex-like pattern
    "padded\0string",               // Embedded null with content after
    "overflowtest",                 // Longer source
    "sameuntilnull\0different",     // Null terminator cuts source
    "lasttest",                     // Arbitrary string
    "\0onlynull",                   // Single null
    "onechar",                      // Single-character string
    "normalstring",                 // Обычная строка
    "string_with_null\0inside",  // Нулевой байт в середине
    "",                          // Пустая строка
    "short",                     // Короткая строка
    "this_is_a_really_long_string_that_exceeds_the_buffer",  // Очень длинная
                                                             // строка
    "\0\0\0\0\0",            // Только нули
    "edgecase_test",         // Смешанный случай
    "ends_with_space     ",  // Заканчивается пробелами
    "overwritten_data",  // Строка, которая заменит существующее
    "data_with_special_@#%&*()",  // Специальные символы
    "multiline\nstring\ttest",  // Строка с управляющими символами
    "embedded\0null_in_between",  // Встроенный нулевой байт
    "0123456789abcdef",  // Шестнадцатеричная строка
    "trailing_nulls\0\0\0",  // Строка с несколькими нулями в конце
    "unicode_пример",              // Юникод-символы
    "abcdefghijklmnopqrstuvwxyz",  // Полный алфавит
    "overlap_example",  // Возможный случай перекрытия
    "tiny",             // Короткая строка
    "data_for_partial_copy",  // Для частичного копирования
    "anotherlongstring",      // Еще одна длинная строка
};

char *destinations[] = {
    "initial_destination_buffer",  // Длинный буфер
    "1234567890",                  // Цифры
    "short",                       // Короткое содержимое
    "filled_with_spaces_________",  // Буфер, заполненный пробелами
    "case_sensitive_BUFFER",  // Смешанный регистр
    "\0\0\0\0\0\0",           // Только нули
    "edgecase",               // Просто строка
    "aaaaaaaaaaaaaaaa",       // Повторяющиеся символы
    "",                       // Пустой буфер
    "pre_filled_data_to_erase",  // Буфер с предварительными данными
    "ending_with_null\0trailing",  // С нулевым байтом в середине
    "0123456789abcdef",  // Шестнадцатеричная строка
    "buffer_with_special#@*&",     // Смешанный контент
    "simpletext",                  // Простая строка
    "tiny",                        // Очень короткий буфер
    "abcdefghijklmnopqrstuvwxyz",  // Полный алфавит
    "data_to_preserve_partially",  // Часть данных может остаться
    "buffer_almost_empty_____",     // Почти пустой
    "single_null\0",                // Один нулевой символ
    "longer_initial_data",          // Более длинные данные
    "filled_with_zeros__________",  // Заполнено нулями
    "preexisting_data",  // Предварительно заполненный буфер
    "shortbuf",                      // Короткий буфер
    "empty_______________________",  // Пустой буфер, но с длиной
    "data_to_preserve_______",  // Буфер с существующими данными
    "all_spaces_________________",  // Заполненный пробелами
    "same_length______________",  // Буфер той же длины, что и source
    "ends_with_trailing_null\0",  // Заканчивается на нуль
    "overlapping_source________",  // Потенциальный случай перекрытия
    "repeated_pattern_123123123",  // Повторяющийся шаблон
    "buffer_with_random_data",     // Произвольные данные
    "0123456789abcdef",  // Шестнадцатеричная строка
    "longdata_overwrite_________",  // Длинные данные
    "space_filled_data_________",  // Заполненные пробелами данные
    "unchanged_after_zero_fill",  // Неизменяемые данные
    "randomly_filled",  // Произвольное содержимое
    "empty_initial_data________",  // Изначально пустое содержимое
    "shortstring",                 // Короткая строка
    "destination_overwritten_____",  // Буфер для перезаписи
    "remaining_characters_______",   // Частичное заполнение
};

// Number of characters to copy (n values for strncpy)
s21_size_t n_sizes[] = {
    10,  // Matches source length
    5,   // Shorter than source
    0,   // Edge case: zero bytes copied
    5,   // Larger than source
    15,  // Larger than destination
    12,  // Includes embedded null
    4,   // Includes leading null
    8,   // Exact fit
    14,  // Padding with nulls
    3,   // Only nulls copied
    5,   // Partial copy
    5,   // Longer than source
    6,   // Partial copy
    16,  // Full copy
    12,  // Null-terminated within n
    20,  // Overflow test
    5,   // Includes null and beyond
    6,   // Partial copy
    1,   // Single null
    3,   // Single-character copy
    5,   // Частичное копирование
    16,  // Полное копирование строки
    0,   // Копирование 0 байт
    64,  // Попытка копирования больше длины строки
    20,  // Полное копирование строки
    3,  // Частичное копирование первых трех символов
    12,  // Полная длина строки
    8,   // Копирование до пробелов
    18,  // Перезаписывает данные
    25,  // Полное копирование строки
    10,  // Копирование строки с управляющими символами
    15,  // Копирование строки с нулевыми байтами
    32,  // Попытка копирования длинной строки
    8,   // Копирование с нулями в конце
    20,  // Частичное копирование Юникода
    26,  // Полное копирование алфавита
    7,   // Проверка перекрытия
    4,   // Короткое копирование
    15,  // Частичное копирование данных
    30   // Попытка копирования длинной строки
};

s21_size_t lenArray[] = {6, 11, 10, 24, 9,  1,  1, 6,  3,  32,
                         4, 7,  0,  26, 16, 13, 5, 12, 20, 10};
const s21_size_t size_ar_src = sizeof(sources) / sizeof(sources[0]);
const s21_size_t size_destinations = sizeof(sources) / sizeof(destinations[0]);
const s21_size_t size_n_sizes = sizeof(sources) / sizeof(n_sizes[0]);
s21_size_t tests_num = 0;
#endif
